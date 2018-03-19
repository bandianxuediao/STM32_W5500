;*********************************************Copyright (c)***********************************************
;*                                Guangzhou ZLG MCU Technology Co., Ltd.
;*
;*                                        http://www.zlgmcu.com
;*
;*      广州周立功单片机科技有限公司所提供的所有服务内容旨在协助客户加速产品的研发进度，在服务过程中所提供
;*  的任何程序、文档、测试结果、方案、支持等资料和信息，都仅供参考，客户有权不使用或自行参考修改，本公司不
;*  提供任何的完整性、可靠性等保证，若在客户使用过程中因任何原因造成的特别的、偶然的或间接的损失，本公司不
;*  承担任何责任。
;*                                                                        ——广州周立功单片机科技有限公司
;*
;*--------------File Info---------------------------------------------------------------------------------
;* File name:               kinetis_k_startup_keil.s
;* Last modified date:      2012-12-11
;* Last version:            V1.0
;* Description:             kinetis k系列 适用于Keil的启动文件
;*
;*--------------------------------------------------------------------------------------------------------
;* Created by:              Fan Linyun
;* Created date:            2012-12-11
;* Version:                 V1.0
;* Descriptions:            The original version 初始版本
;*
;*--------------------------------------------------------------------------------------------------------
;* Modified by:             
;* Modified date:           
;* Version:                 
;* Descriptions:            
;*
;********************************************************************************************************/

;*********************************************************************************************************
;  Flash加密区数值，配置为0x0001则加密，否则不加密
;*********************************************************************************************************
FLASH_SECURITY  EQU     0x0000

;*********************************************************************************************************
; declaration of function for vector table. 中断向量表用户函数声明
;*********************************************************************************************************
                IMPORT  sysInit
                
;*********************************************************************************************************
; Stack Configuration. 栈大小配置，以字节为单位，用于函数调用时变量压栈
;*********************************************************************************************************
STACK_SIZE      EQU     1024

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
STACK_MEM       SPACE   STACK_SIZE
__initial_sp



;*********************************************************************************************************
; Heap Configuration. 堆大小配置，以字节为单位，动态内存分配函数分配内存的区域，程序中没有使用动态内存
; 分配函数，堆大小可以配置为0
;*********************************************************************************************************
HEAP_SIZE       EQU     0

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
HEAP_MEM        SPACE   HEAP_SIZE
__heap_limit


;*********************************************************************************************************
; vector table. 中断向量表
;*********************************************************************************************************
                PRESERVE8
                THUMB

                AREA    RESET, DATA, READONLY
                
                IMPORT  __main

                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                    ; Top of Stack
                DCD     resetHandler                    ; Reset
                DCD     nmiHandler                      ; Non-maskable Interrupt (NMI)
                DCD     hardFaultHandler                ; Hard Fault
                DCD     intDefaultHandler               ; MPU Fault
                DCD     intDefaultHandler               ; Bus Fault
                DCD     intDefaultHandler               ; Use Fault
                DCD     intDefaultHandler               ; Reserved
                DCD     intDefaultHandler               ; Reserved
                DCD     intDefaultHandler               ; Reserved
                DCD     intDefaultHandler               ; Reserved
                DCD     intDefaultHandler               ; Supervisor call (SVCall)
                DCD     intDefaultHandler               ; Debug Monitor
                DCD     intDefaultHandler               ; Reserved
                DCD     intDefaultHandler               ; Pendable request for system service (PendableSrvReq)
                DCD     intDefaultHandler               ; System tick timer (SysTick)



                DCD     intDefaultHandler               ; 0: DMA Channel 0 transfer complete
                DCD     intDefaultHandler               ; 1: DMA Channel 1 transfer complete
                DCD     intDefaultHandler               ; 2: DMA Channel 2 transfer complete
                DCD     intDefaultHandler               ; 3: DMA Channel 3 transfer complete
                DCD     intDefaultHandler               ; 4: DMA Channel 4 transfer complete
                DCD     intDefaultHandler               ; 5: DMA Channel 5 transfer complete
                DCD     intDefaultHandler               ; 6: DMA Channel 6 transfer complete
                DCD     intDefaultHandler               ; 7: DMA Channel 7 transfer complete
                DCD     intDefaultHandler               ; 8: DMA Channel 8 transfer complete
                DCD     intDefaultHandler               ; 9: DMA Channel 9 transfer complete
                DCD     intDefaultHandler               ; 10: DMA Channel 10 transfer complete
                DCD     intDefaultHandler               ; 11: DMA Channel 11 transfer complete
                DCD     intDefaultHandler               ; 12: DMA Channel 12 transfer complete
                DCD     intDefaultHandler               ; 13: DMA Channel 13 transfer complete
                DCD     intDefaultHandler               ; 14: DMA Channel 14 transfer complete
                DCD     intDefaultHandler               ; 15: DMA Channel 15 transfer complete
                DCD     intDefaultHandler               ; 16: DMA Error Interrupt Channels 0-15
                DCD     intDefaultHandler               ; 17: MCM Normal Interrupt
                DCD     intDefaultHandler               ; 18: Flash Memory Command Complete
                DCD     intDefaultHandler               ; 19: Flash Memory Read Collision
                DCD     intDefaultHandler               ; 20: Mode Controller(Low Voltage Detect,Low 
                                                        ;     Voltage Warning, Low Leakage Wakeup)
                DCD     intDefaultHandler               ; 21: LLWU
                DCD     intDefaultHandler               ; 22: WDOG
                DCD     intDefaultHandler               ; 23: RNGB
                DCD     intDefaultHandler               ; 24: I2C0
                DCD     intDefaultHandler               ; 25: I2C1
                DCD     intDefaultHandler               ; 26: SPI0
                DCD     intDefaultHandler               ; 27: SPI1
                DCD     intDefaultHandler               ; 28: SPI2
                DCD     intDefaultHandler               ; 29: CAN0 OR'ed Message buffer (0-15)
                DCD     intDefaultHandler               ; 30: CAN0 Bus Off
                DCD     intDefaultHandler               ; 31: CAN0 Error
                DCD     intDefaultHandler               ; 32: CAN0 Transmit Warning
                DCD     intDefaultHandler               ; 33: CAN0 Receive Warning
                DCD     intDefaultHandler               ; 34: CAN0 Wake Up
                DCD     intDefaultHandler               ; 35: CAN0 Individual Matching Elements Update (IMEU)
                DCD     intDefaultHandler               ; 36: CAN0 Lost receive
                DCD     intDefaultHandler               ; 37: CAN1 OR'ed Message buffer (0-15)
                DCD     intDefaultHandler               ; 38: CAN1 Bus off
                DCD     intDefaultHandler               ; 39: CAN1 Error
                DCD     intDefaultHandler               ; 40: CAN1 Transmit Warning
                DCD     intDefaultHandler               ; 41: CAN1 Receive Warning
                DCD     intDefaultHandler               ; 42: CAN1 Wake Up
                DCD     intDefaultHandler               ; 43: CAN1 Individual Matching Elements Update (IMEU)
                DCD     intDefaultHandler               ; 44: CAN1 Lost receive
                DCD     intDefaultHandler               ; 45: UART0 Status
                DCD     intDefaultHandler               ; 46: UART0 Error
                DCD     intDefaultHandler               ; 47: UART1 Status
                DCD     intDefaultHandler               ; 48: UART1 Error
                DCD     intDefaultHandler               ; 49: UART2 Status
                DCD     intDefaultHandler               ; 50: UART2 Error
                DCD     intDefaultHandler               ; 51: UART3 Status
                DCD     intDefaultHandler               ; 52: UART3 Error
                DCD     intDefaultHandler               ; 53: UART4 Status
                DCD     intDefaultHandler               ; 54: UART4 Error
                DCD     intDefaultHandler               ; 55: UART5 Status
                DCD     intDefaultHandler               ; 56: UART5 Error
                DCD     intDefaultHandler               ; 57: ADC0
                DCD     intDefaultHandler               ; 58: ADC1
                DCD     intDefaultHandler               ; 59: CMP0
                DCD     intDefaultHandler               ; 60: CMP1
                DCD     intDefaultHandler               ; 61: CMP2
                DCD     intDefaultHandler               ; 62: FTM0
                DCD     intDefaultHandler               ; 63: FTM1
                DCD     intDefaultHandler               ; 64: FTM2
                DCD     intDefaultHandler               ; 65: CMT
                DCD     intDefaultHandler               ; 66: RTC Timer interrupt
                DCD     intDefaultHandler               ; 67: Reserved
                DCD     intDefaultHandler               ; 68: PIT0
                DCD     intDefaultHandler               ; 69: PIT1
                DCD     intDefaultHandler               ; 70: PIT2
                DCD     intDefaultHandler               ; 71: PIT3
                DCD     intDefaultHandler               ; 72: PDB
                DCD     intDefaultHandler               ; 73: USB OTG
                DCD     intDefaultHandler               ; 74: USB Charger Detect
                DCD     intDefaultHandler               ; 75: ENET IEEE 1588 Timer interrupt
                DCD     intDefaultHandler               ; 76: ENET Transmit interrupt
                DCD     intDefaultHandler               ; 77: ENET Receive interrupt
                DCD     intDefaultHandler               ; 78: ENET Error and miscellaneous interrupt
                DCD     intDefaultHandler               ; 79: I2S
                DCD     intDefaultHandler               ; 80: SDHC
                DCD     intDefaultHandler               ; 81: DAC0
                DCD     intDefaultHandler               ; 82: DAC1
                DCD     intDefaultHandler               ; 83: TSI
                DCD     intDefaultHandler               ; 84: MCG
                DCD     intDefaultHandler               ; 85: Low Power Timer
                DCD     intDefaultHandler               ; 86: Segment LCD
                DCD     intDefaultHandler               ; 87: Port A control module Pin Detect
                DCD     intDefaultHandler               ; 88: Port B control module Pin Detect
                DCD     intDefaultHandler               ; 89: Port C control module Pin Detect
                DCD     intDefaultHandler               ; 90: Port D control module Pin Detect
                DCD     intDefaultHandler               ; 91: Port E control module Pin Detect
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     intDefaultHandler               ; 48: Reserved
                DCD     0xFFFFFFFF                      ; 48: Reserved 1
                DCD     0xFFFFFFFF                      ; 48: Reserved 2
                DCD     0xFFFFFFFF                      ; 48: Reserved 3
                DCD     0xFFFFFFFE                      ; 48: Reserved 4
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


;*********************************************************************************************************
; default function for vector table. 中断向量默认函数
;*********************************************************************************************************
resetHandler    PROC
                EXPORT  resetHandler            [WEAK]
                BL      sysInit
                B       __main
                ENDP

nmiHandler      PROC
                EXPORT  nmiHandler              [WEAK]
                B       .
                ENDP

hardFaultHandler \
                PROC
                EXPORT  hardFaultHandler        [WEAK]
                B       .
                ENDP

intDefaultHandler \
                PROC
                EXPORT  hardFaultHandler        [WEAK]
                B       .
                ENDP

                ALIGN


;*********************************************************************************************************
; User Initial Stack & Heap. 用户初始化堆栈
;*********************************************************************************************************
                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  HEAP_MEM
                LDR     R1, = (STACK_MEM + STACK_SIZE)
                LDR     R2, = (HEAP_MEM +  HEAP_SIZE)
                LDR     R3, =  STACK_MEM
                BX      LR

                ALIGN

                ENDIF

;*********************************************************************************************************
; User Flash Security. 用户加密Flash代码
;*********************************************************************************************************
;                IF      :LNOT::DEF:NO_CRP
;                AREA    |.ARM.__at_0x00100000|, CODE, READONLY
;                DCW     FLASH_SECURITY
;                ENDIF
                
                
                END
                
;*********************************************************************************************************
; END FILE
;*********************************************************************************************************
