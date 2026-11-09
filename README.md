# MQ5 AAF Firmware — Application 구조

LX61101 (Cortex-M3) 기반 MQ5 AAF 펌웨어의 소프트웨어 계층 구조와 작성 규칙.
AUTOSAR 계층 구조를 **참고**하되, 이미 제공되는 기능(LXS Composer 생성 코드 등)은 그대로 사용한다.

## 1. 계층 구조

```
+---------------------------------------------------------------+
| App      : 기능 로직 ("언제 무엇을 할지" 판단)                  |
+---------------------------------------------------------------+
| RTE      : App <-> 하위 계층 연결, 주기 실행                    |
+---------------------------------------------------------------+
| BSW                                                           |
|   +---------------+-----------------------+-----------------+ |
|   | Service       | EAL                   | CDD             | |
|   | 공통 서비스    | ECU Abstraction       | Complex Device  | |
|   | (저장, 진단,   | (보드 기준 추상화)     | Driver          | |
|   |  슬립 등)     |                       | (외부 칩, 고속   | |
|   |               |                       |  타이밍 제어)    | |
|   +---------------+-----------------------+-----------------+ |
|   | MCAL : MCU 레지스터 직접 접근 (LXS Composer 생성 코드 위) | |
|   +---------------------------------------------------------+ |
|   | Common : 모든 계층 공통 정의                             | |
|   +---------------------------------------------------------+ |
+---------------------------------------------------------------+
| CMSIS (LXS Composer 생성 코드) — 직접 수정 금지                 |
+---------------------------------------------------------------+
```

## 2. 호출 규칙

| 계층 | 호출 가능 대상 |
|---|---|
| App | RTE |
| RTE | Service, EAL, CDD |
| Service | EAL, MCAL |
| EAL | MCAL |
| CDD | MCAL (RTE / Service 에서 직접 호출 가능) |
| MCAL | CMSIS (LXS Composer 생성 코드) |

- 위에서 아래로만 호출한다. 아래에서 위로는 콜백(알림 함수)으로만 알린다.
- `LX61101.h` 는 **MCAL 에서만** include 한다.

## 3. 폴더 구조

```
MQ5\
 ├─ CMSIS\                  LXS Composer 생성 코드 (Generate 시 덮어씀, 수정 금지)
 ├─ FlashLoader\            Keil 플래시 알고리즘 (.FLM)
 ├─ MQ5.uvprojx             Keil 프로젝트
 └─ Application\
     ├─ main.c
     ├─ App\
     ├─ Rte\
     └─ Bsw\
         ├─ Service\
         ├─ Eal\
         ├─ Cdd\
         │   └─ Drv8889\
         ├─ Mcal\
         │   ├─ Adc\
         │   ├─ Dio\
         │   ├─ Lin\
         │   ├─ Spi\
         │   ├─ Tms\
         │   └─ Wdg\
         └─ Common\
```

- 모듈마다 폴더 하나 (`모듈.c`, `모듈.h`, `모듈_Tune.h`).
- 새 모듈을 추가하면 Keil Include Path 와 프로젝트 그룹(`Mcal/모듈`)에도 추가한다.

## 4. 모듈 목록

| 계층 | 모듈 | 파일 | 내용 | 상태 |
|---|---|---|---|---|
| Common | Config | `Bsw\Common\Config.h` | 공통 타입 (`common.h` 포함), 코드명 / 차종 / AAF 번호 값 | 작성 |
| Common | Config | `Bsw\Common\Config_Tune.h` | 코드명 선택 (빌드 시 변경) | 작성 |
| MCAL | Dio | `Bsw\Mcal\Dio\` | 디지털 입출력 핀 읽기/쓰기 (Composer `PB_GPxxx` 사용) | 작성 |
| MCAL | Tms | `Bsw\Mcal\Tms\` | 1ms 틱 (TMS01), 1us 틱 (TMS00) | 작성 |
| MCAL | Spi | `Bsw\Mcal\Spi\` | SPI1 16bit 송수신 (Composer 함수 사용) | 작성 |
| MCAL | Adc | `Bsw\Mcal\Adc\` | 채널별 변환값 (Composer 함수 사용) | 작성 |
| MCAL | Lin | `Bsw\Mcal\Lin\` | 차종별 필터, 프레임 수신 / 응답 | 작성 |
| MCAL | Wdg | `Bsw\Mcal\Wdg\` | 워치독 리프레시, 리셋 원인 | 작성 |
| MCAL | Mftr | - | STEP 펄스 시작 / 정지, 펄스 콜백 | 예정 |
| MCAL | DFlash | - | EEPROM (Data Flash) 읽기 / 쓰기 | 예정 (LX 자료 대기) |
| CDD | Drv8889 | `Bsw\Cdd\Drv8889\` | DRV8889-Q1 핀 / SPI 레지스터 제어 | 작성 |

### Dio 채널

| 채널 | 핀 | 회로도 넷 | 방향 |
|---|---|---|---|
| `DIO_CH_DRVOFF` | GPA0 | MCU_DRVOFF | 출력 (High = 모터 출력 OFF) |
| `DIO_CH_DRV_SLEEP` | GPA3 | MCU_DRV_SLEEP_MODE | 출력 (Low = DRV8889 슬립) |
| `DIO_CH_DIR` | GPA5 | MCU_DIR | 출력 |
| `DIO_CH_NSCS` | GPB3 | MCU_nSCS | 출력 (Low = 선택) |
| `DIO_CH_NFAULT` | GPC0 | MCU_DRV_nFAULT | 입력 (Low = Fault) |

## 5. 작성 규칙

### 파일 헤더 주석

```c
/***********************************************************************************************************************
 * File        : Dio.c
 * Layer       : App
 *               RTE
 *               BSW
 *                 - Service
 *                 - EAL
 *                 - CDD
 *                 - MCAL          <== HERE
 *                 - Common
 * Description : 디지털 입출력 핀 읽기/쓰기
 ***********************************************************************************************************************/
```

- `Description` 은 그 파일이 무엇을 다루는지만 한 줄로 적는다. 세부 설명은 해당 선언 옆에 적는다.

### 이름

- AUTOSAR 명명 규칙을 참고한다 (함수 `Module_FunctionName`, 매크로 `MODULE_NAME`).
- 데이터시트·회로도에서 실제로 쓰는 약어는 그대로 사용한다 (예: `DIO_CH_NSCS`).

### 설정 파일

| 구분 | 이름 | 예 |
|---|---|---|
| 거의 고정 | 접미어 없음 | `Config.h` |
| 바꿀 것 (차종 선택, 핀, ID, 튜닝 값) | `_Tune` | `Config_Tune.h`, `Dio_Tune.h`, `Drv8889_Tune.h` |

- 한 파일 안에서만 쓰는 define 은 `.c` 에 두고 `[파일명 내부 전용]` 주석을 단다.

## 6. 빌드 환경

| 항목 | 값 |
|---|---|
| IDE | Keil µVision (MDK 5.43a) |
| 컴파일러 | Arm Compiler 6 |
| Define | `USE_DEPRECATED_DEFINITION` (`common.h` 의 `STD_HIGH`, `TRUE`, `NULL_PTR` 등 활성화) |
| Include Path | `.\CMSIS;.\Application;.\Application\Bsw\Common;` + 모듈 폴더 (`.\Application\Bsw\Mcal\Dio` … `.\Application\Bsw\Cdd\Drv8889`) |

- `common.h` 에 `ERROR`, `SUCCESS`, `ENABLE`, `DISABLE` enum 이 정의되어 있으므로 이 이름은 다른 용도로 사용하지 않는다.
- LXS Composer 에서 Generate 할 때 **Create Build Template 은 끈다** (켜면 `MQ5.uvprojx` 설정이 초기화됨).
