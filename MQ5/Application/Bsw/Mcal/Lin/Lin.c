/***********************************************************************************************************************
 * File        : Lin.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : LIN 프레임 수신 저장 / 응답 처리 (Composer 콜백 사용)
 ***********************************************************************************************************************/
#include "Lin.h"
#include "Tms.h"
#include "device_LX61101.h"
#include "interrupt_LX61101.h"

/*
 * [Lin.c 내부 전용] IFCR : ID[5:0] | CCS[8] | DIR[9] | DFL[12:10] (DFL = 바이트 - 1). Composer 생성값 0x1425 = 0x25 / RX / 6B 와 동일 형식
 */
#define LIN_IFCR(ID, Ccs, Dir, Byte) \
    ((uint32)(ID) | ((uint32)(Ccs) << 8) | ((uint32)(Dir) << 9) | (((uint32)(Byte) - 1U) << 10))

static uint8            Lin_RxCtrl[LIN_DATA_MAX_BYTE];      /* LIN_CTRL 수신 데이터       */
static uint8            Lin_RxMasterReq[LIN_DATA_MAX_BYTE]; /* LIN_MASTER_REQ 수신 데이터 */
static uint8            Lin_TxResp[LIN_DATA_MAX_BYTE];      /* LIN_RESP 응답 데이터       */
static uint8            Lin_TxSlaveResp[LIN_DATA_MAX_BYTE]; /* LIN_SLAVE_RESP 응답 데이터 */

static volatile boolean Lin_RxCtrlNew       = FALSE;        /* 새 수신 여부 */
static volatile boolean Lin_RxMasterReqNew  = FALSE;
static volatile boolean Lin_TxRespOn        = FALSE;        /* 응답 허용 여부 */
static volatile boolean Lin_TxSlaveRespOn   = FALSE;
static volatile uint32  Lin_LastRxMs        = 0U;

/* 4바이트 레지스터 값 <-> 바이트 배열 (LX61101.h : BDRL DATA0 = [7:0] ... DATA3 = [31:24]) */
static void Lin_WordToByte(uint32 Word, uint8 *Data)
{
    Data[0] = (uint8)(Word >> LIN_BDRL_DATA0_Pos);
    Data[1] = (uint8)(Word >> LIN_BDRL_DATA1_Pos);
    Data[2] = (uint8)(Word >> LIN_BDRL_DATA2_Pos);
    Data[3] = (uint8)(Word >> LIN_BDRL_DATA3_Pos);
}

static uint32 Lin_ByteToWord(const uint8 *Data)
{
    return ((uint32)Data[0] << LIN_BDRL_DATA0_Pos) |
           ((uint32)Data[1] << LIN_BDRL_DATA1_Pos) |
           ((uint32)Data[2] << LIN_BDRL_DATA2_Pos) |
           ((uint32)Data[3] << LIN_BDRL_DATA3_Pos);
}

/*
 * Composer 필터(ICE 기준 고정)를 Lin_Tune.h 차종 값으로 다시 씀. 진단 프레임(IFCR4/6)은 공통이라 그대로.
 * SetupLIN() 과 같은 순서 : INIT 모드 진입 대기 → 필터 쓰기 → INIT 해제
 */
void Lin_Init(void)
{
    do {
        LIN->LINCR1 &= ~LIN_LINCR1_SLEEP_Msk;
        LIN->LINCR1 |= LIN_LINCR1_INIT_Msk;
    } while (0x1000U != (LIN->LINSR & 0xF000U));

    LIN->IFCR0 = LIN_IFCR(LIN_CTRL, LIN_ID_CS_ENHANCED, LIN_ID_DIR_RX, LIN_CTRL_BYTE);
    LIN->IFCR2 = LIN_IFCR(LIN_RESP, LIN_ID_CS_ENHANCED, LIN_ID_DIR_TX, LIN_RESP_BYTE);

    LIN->LINCR1 &= ~LIN_LINCR1_INIT_Msk;
}

/* 새 수신 데이터가 있으면 Data 에 복사하고 TRUE. 복사 중 인터럽트 갱신 방지 */
boolean Lin_GetRxData(Lin_IdType ID, uint8 *Data)
{
    boolean IsNew = FALSE;
    uint32  Primask = __get_PRIMASK();
    uint8   i;

    __disable_irq();

    if ((ID == LIN_CTRL) && (Lin_RxCtrlNew == TRUE))
    {
        for (i = 0U; i < LIN_CTRL_BYTE; i++) { Data[i] = Lin_RxCtrl[i]; }
        Lin_RxCtrlNew = FALSE;
        IsNew = TRUE;
    }
    else if ((ID == LIN_MASTER_REQ) && (Lin_RxMasterReqNew == TRUE))
    {
        for (i = 0U; i < LIN_DATA_MAX_BYTE; i++) { Data[i] = Lin_RxMasterReq[i]; }
        Lin_RxMasterReqNew = FALSE;
        IsNew = TRUE;
    }
    else
    {
        /* 새 데이터 없음 또는 수신 프레임 아님 */
    }

    __set_PRIMASK(Primask);

    return IsNew;
}

/* 응답 데이터 설정 후 응답 허용. 다음 헤더부터 이 데이터로 응답 */
void Lin_SetTxData(Lin_IdType ID, const uint8 *Data)
{
    uint32 Primask = __get_PRIMASK();
    uint8  i;

    __disable_irq();

    if (ID == LIN_RESP)
    {
        for (i = 0U; i < LIN_RESP_BYTE; i++) { Lin_TxResp[i] = Data[i]; }
        Lin_TxRespOn = TRUE;
    }
    else if (ID == LIN_SLAVE_RESP)
    {
        for (i = 0U; i < LIN_DATA_MAX_BYTE; i++) { Lin_TxSlaveResp[i] = Data[i]; }
        Lin_TxSlaveRespOn = TRUE;
    }
    else
    {
        /* 송신 프레임 아님 */
    }

    __set_PRIMASK(Primask);
}

/* 응답 안 함 (ICE : ReqRespAAFID 가 자기 AAF_INDEX 가 아닐 때 등) */
void Lin_SetNoResponse(Lin_IdType ID)
{
    if      (ID == LIN_RESP)       { Lin_TxRespOn      = FALSE; }
    else if (ID == LIN_SLAVE_RESP) { Lin_TxSlaveRespOn = FALSE; }
    else                           { /* 송신 프레임 아님 */ }
}

/* Bus Inactive(4초) 판정용. 등록된 ID 의 헤더 또는 데이터를 받을 때마다 갱신 */
uint32 Lin_GetLastRxMs(void)
{
    return Lin_LastRxMs;
}

/* Composer __weak 대체 : 수신 완료 인터럽트에서 호출 (id = 프레임 ID, dataL = Byte0~3, dataM = Byte4~7) */
void USER_LIN0RX_Function(uint8_t id, uint32_t dataL, uint32_t dataM)
{
    uint8 *Buffer = NULL_PTR;

    if (id == LIN_CTRL)
    {
        Buffer        = Lin_RxCtrl;
        Lin_RxCtrlNew = TRUE;
    }
    else if (id == LIN_MASTER_REQ)
    {
        Buffer             = Lin_RxMasterReq;
        Lin_RxMasterReqNew = TRUE;
    }
    else
    {
        /* 필터에 등록되지 않은 ID 는 하드웨어에서 걸러짐 */
    }

    if (Buffer != NULL_PTR)
    {
        Lin_WordToByte(dataL, &Buffer[0]);
        Lin_WordToByte(dataM, &Buffer[4]);
    }

    Lin_LastRxMs = Tms_GetTickMs();
}

/* Composer __weak 대체 : 응답 헤더 수신 인터럽트에서 호출. 0 이상 = 응답, 음수 = 무응답 */
int USER_LIN0TX_Function(uint8_t id, volatile uint32_t *dataL, volatile uint32_t *dataM)
{
    const uint8 *Buffer = NULL_PTR;
    int          Result = -1;

    if ((id == LIN_RESP) && (Lin_TxRespOn == TRUE))
    {
        Buffer = Lin_TxResp;
    }
    else if ((id == LIN_SLAVE_RESP) && (Lin_TxSlaveRespOn == TRUE))
    {
        Buffer = Lin_TxSlaveResp;
    }
    else
    {
        /* 응답 허용 안 됨 → 무응답 */
    }

    if (Buffer != NULL_PTR)
    {
        *dataL = Lin_ByteToWord(&Buffer[0]);
        *dataM = Lin_ByteToWord(&Buffer[4]);
        Result = 0;
    }

    Lin_LastRxMs = Tms_GetTickMs();

    return Result;
}
