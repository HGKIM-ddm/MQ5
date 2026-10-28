;/**
; *******************************************************************************
; * @file     startup_lx61101.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for Device lx61101
; * @version  V1.0.0
; * @date     2024/10/30
; *
; * DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LICENSE AGREEMENT.
; *
; * (C)Copyright LX Semicon CORPORATION 2024 All rights reserved
; *******************************************************************************
; */

;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------


;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>
; Stack 2KB
Stack_Size		EQU     0x800

				AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem		SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
; Heap 2KB
Heap_Size		EQU     0x00000000

				AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem		SPACE   Heap_Size
__heap_limit


				PRESERVE8
				THUMB

; Vector Table Mapped to Address 0 at Reset
				AREA    RESET, DATA, READONLY
				EXPORT  __Vectors
				EXPORT  __Vectors_End
				EXPORT  __Vectors_Size

__Vectors
                DCD     __initial_sp              ;  TopofStack
                DCD     Reset_Handler             ;  ResetHandler
                DCD     NMI_Handler               ;  NMIHandler
                DCD     HardFault_Handler         ;  HardFaultHandler
                DCD     MemManage_Handler         ;  MPUFaultHandler
                DCD     BusFault_Handler          ;  BusFaultHandler
                DCD     UsageFault_Handler        ;  UsageFaultHandler
                DCD     0                         ;  Reserved
                DCD     0                         ;  Reserved
                DCD     0                         ;  Reserved
                DCD     0                         ;  Reserved
                DCD     SVC_Handler               ;  SVCallHandler
                DCD     DebugMon_Handler          ;  DebugMonitorHandler
                DCD     0                         ;  Reserved
                DCD     PendSV_Handler            ;  PendSVHandler
                DCD     SysTick_Handler           ;  SysTickHandler

                ; External Interrupts
                DCD     EXTA_Handler              ;   0 External GPA Input Interrupt
                DCD     EXTB_Handler              ;   1 External GPB Input Interrupt
                DCD     EXTC_Handler              ;   2 External GPC Input Interrupt
                DCD     IOCPTC_Handler            ;   3 IOC Protection Event
                DCD     ADC0A_Handler             ;   4 ADC 0 A Interrupt
                DCD     ADC0B_Handler             ;   5 ADC 0 B Interrupt
                DCD     ADC0C_Handler             ;   6 ADC 0 C Interrupt
                DCD     ADC0E_Handler             ;   7 ADC 0 E Interrupt
                DCD     ADC0CMP_Handler           ;   8 ADC 0 Compare Interrupt
                DCD     ADC1A_Handler             ;   9 ADC 1 A Interrupt
                DCD     ADC1B_Handler             ;  10 ADC 1 B Interrupt
                DCD     ADC1C_Handler             ;  11 ADC 1 C Interrupt
                DCD     ADC1E_Handler             ;  12 ADC 1 E Interrupt
                DCD     ADC1CMP_Handler           ;  13 ADC 1 Compare Interrupt
                DCD     TMS0C_Handler             ;  14 TMS 00~01 combined Interrupt
                DCD     MFTR0A_Handler            ;  15 MFTR0 Compare Match A
                DCD     MFTR0B_Handler            ;  16 MFTR0 Compare Match B
                DCD     MFTR0V_Handler            ;  17 MFTR0 Overflow
                DCD     MFTR0U_Handler            ;  18 MFTR0 Underflow
                DCD     MFTR1A_Handler            ;  19 MFTR1 Compare Match A
                DCD     MFTR1B_Handler            ;  20 MFTR1 Compare Match B
                DCD     MFTR1V_Handler            ;  21 MFTR1 Overflow
                DCD     MFTR1U_Handler            ;  22 MFTR1 Underflow
                DCD     MFTR2A_Handler            ;  23 MFTR2 Compare Match A
                DCD     MFTR2B_Handler            ;  24 MFTR2 Compare Match B
                DCD     MFTR2V_Handler            ;  25 MFTR2 Overflow
                DCD     MFTR2U_Handler            ;  26 MFTR2 Underflow
                DCD     MFTR3A_Handler            ;  27 MFTR3 Compare Match A
                DCD     MFTR3B_Handler            ;  28 MFTR3 Compare Match B
                DCD     MFTR3V_Handler            ;  29 MFTR3 Overflow
                DCD     MFTR3U_Handler            ;  30 MFTR3 Underflow
                DCD     MFTP0A_Handler            ;  31 MFTP0 Compare Match A
                DCD     MFTP0B_Handler            ;  32 MFTP0 Compare Match B
                DCD     MFTP0V_Handler            ;  33 MFTP0 Overflow
                DCD     MFTP0U_Handler            ;  34 MFTP0 Underflow
                DCD     MFTP0O_Handler            ;  35 MFTP0 Compare Match O
                DCD     MFTP1A_Handler            ;  36 MFTP1 Compare Match A
                DCD     MFTP1B_Handler            ;  37 MFTP1 Compare Match B
                DCD     MFTP1V_Handler            ;  38 MFTP1 Overflow
                DCD     MFTP1U_Handler            ;  39 MFTP1 Underflow
                DCD     MFTP1O_Handler            ;  40 MFTP1 Compare Match O
                DCD     SPI0_Handler              ;  41 SPI 0 combined Interrupt
                DCD     SPI1_Handler              ;  42 SPI 1 combined Interrupt
                DCD     UART0_Handler             ;  43 UART 0 combined Interrupt
                DCD     LIN0ERR_Handler           ;  44 LIN 0 Error combined Interrupt
                DCD     LIN0RX_Handler            ;  45 LIN 0 RX combined Interrupt
                DCD     LIN0TX_Handler            ;  46 LIN 0 TX combined Interrupt
                DCD     LIN0C_Handler             ;  47 LIN 0 combined Interrupt
                DCD     LIN0PHYTO_Handler         ;  48 LIN 0 PHY TX Timeout Interrupt
                DCD     LIN0PHYOT_Handler         ;  49 LIN PHY over temperature interrupt
                DCD     LIN0PHYOC_Handler         ;  50 LIN PHY over current interrupt
                DCD     EEPROMDONE_Handler        ;  51 EEPROM Done Interrupt
                DCD     HS0_Handler               ;  52 HS0 Interrupt
                DCD     HS1_Handler               ;  53 HS1 Interrupt
                DCD     BDRV0_Handler             ;  54 Bridge Driver 0 Interrupt
                DCD     HVIN0_Handler             ;  55 HVIN0 Interrupt
                DCD     EXTSA_Handler             ;  56 Secondary External GPA Input Interrupt
                DCD     EXTSB_Handler             ;  57 Secondary External GPB Input Interrupt
                DCD     EXTSC_Handler             ;  58 Secondary External GPC Input Interrupt
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors


				AREA    |.text|, CODE, READONLY

; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
				IMPORT	SramEccEnable

				LDR 		R0, =SramEccEnable
				BLX 		R0
                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__main
                BX        R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT EXTA_Handler               [WEAK]
                EXPORT EXTB_Handler               [WEAK]
                EXPORT EXTC_Handler               [WEAK]
                EXPORT IOCPTC_Handler             [WEAK]
                EXPORT ADC0A_Handler              [WEAK]
                EXPORT ADC0B_Handler              [WEAK]
                EXPORT ADC0C_Handler              [WEAK]
                EXPORT ADC0E_Handler              [WEAK]
                EXPORT ADC0CMP_Handler            [WEAK]
                EXPORT ADC1A_Handler              [WEAK]
                EXPORT ADC1B_Handler              [WEAK]
                EXPORT ADC1C_Handler              [WEAK]
                EXPORT ADC1E_Handler              [WEAK]
                EXPORT ADC1CMP_Handler            [WEAK]
                EXPORT TMS0C_Handler              [WEAK]
                EXPORT MFTR0A_Handler             [WEAK]
                EXPORT MFTR0B_Handler             [WEAK]
                EXPORT MFTR0V_Handler             [WEAK]
                EXPORT MFTR0U_Handler             [WEAK]
                EXPORT MFTR1A_Handler             [WEAK]
                EXPORT MFTR1B_Handler             [WEAK]
                EXPORT MFTR1V_Handler             [WEAK]
                EXPORT MFTR1U_Handler             [WEAK]
                EXPORT MFTR2A_Handler             [WEAK]
                EXPORT MFTR2B_Handler             [WEAK]
                EXPORT MFTR2V_Handler             [WEAK]
                EXPORT MFTR2U_Handler             [WEAK]
                EXPORT MFTR3A_Handler             [WEAK]
                EXPORT MFTR3B_Handler             [WEAK]
                EXPORT MFTR3V_Handler             [WEAK]
                EXPORT MFTR3U_Handler             [WEAK]
                EXPORT MFTP0A_Handler             [WEAK]
                EXPORT MFTP0B_Handler             [WEAK]
                EXPORT MFTP0V_Handler             [WEAK]
                EXPORT MFTP0U_Handler             [WEAK]
                EXPORT MFTP0O_Handler             [WEAK]
                EXPORT MFTP1A_Handler             [WEAK]
                EXPORT MFTP1B_Handler             [WEAK]
                EXPORT MFTP1V_Handler             [WEAK]
                EXPORT MFTP1U_Handler             [WEAK]
                EXPORT MFTP1O_Handler             [WEAK]
                EXPORT SPI0_Handler               [WEAK]
                EXPORT SPI1_Handler               [WEAK]
                EXPORT UART0_Handler              [WEAK]
                EXPORT LIN0ERR_Handler            [WEAK]
                EXPORT LIN0RX_Handler             [WEAK]
                EXPORT LIN0TX_Handler             [WEAK]
                EXPORT LIN0C_Handler              [WEAK]
                EXPORT LIN0PHYTO_Handler          [WEAK]
                EXPORT LIN0PHYOT_Handler          [WEAK]
                EXPORT LIN0PHYOC_Handler          [WEAK]
                EXPORT EEPROMDONE_Handler         [WEAK]
                EXPORT HS0_Handler                [WEAK]
                EXPORT HS1_Handler                [WEAK]
                EXPORT BDRV0_Handler              [WEAK]
                EXPORT HVIN0_Handler              [WEAK]
                EXPORT EXTSA_Handler              [WEAK]
                EXPORT EXTSB_Handler              [WEAK]
                EXPORT EXTSC_Handler              [WEAK]


EXTA_Handler
EXTB_Handler
EXTC_Handler
IOCPTC_Handler
ADC0A_Handler
ADC0B_Handler
ADC0C_Handler
ADC0E_Handler
ADC0CMP_Handler
ADC1A_Handler
ADC1B_Handler
ADC1C_Handler
ADC1CMP_Handler
ADC1E_Handler
TMS0C_Handler
MFTR0A_Handler
MFTR0B_Handler
MFTR0V_Handler
MFTR0U_Handler
MFTR1A_Handler
MFTR1B_Handler
MFTR1V_Handler
MFTR1U_Handler
MFTR2A_Handler
MFTR2B_Handler
MFTR2V_Handler
MFTR2U_Handler
MFTR3A_Handler
MFTR3B_Handler
MFTR3V_Handler
MFTR3U_Handler
MFTP0A_Handler
MFTP0B_Handler
MFTP0V_Handler
MFTP0U_Handler
MFTP0O_Handler
MFTP1A_Handler
MFTP1B_Handler
MFTP1V_Handler
MFTP1U_Handler
MFTP1O_Handler
SPI0_Handler
SPI1_Handler
UART0_Handler
LIN0ERR_Handler
LIN0RX_Handler
LIN0TX_Handler
LIN0C_Handler
LIN0PHYTO_Handler
LIN0PHYOT_Handler
LIN0PHYOC_Handler
EEPROMDONE_Handler
HS0_Handler
HS1_Handler
BDRV0_Handler
HVIN0_Handler
EXTSA_Handler
EXTSB_Handler
EXTSC_Handler

                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
