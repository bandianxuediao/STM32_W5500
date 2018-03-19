;*********************************************Copyright (c)***********************************************
;*                                Guangzhou ZLG MCU Technology Co., Ltd.
;*
;*                                        http://www.zlgmcu.com
;*
;*      ������������Ƭ���Ƽ����޹�˾���ṩ�����з�������ּ��Э���ͻ����ٲ�Ʒ���з����ȣ��ڷ�����������ṩ
;*  ���κγ����ĵ������Խ����������֧�ֵ����Ϻ���Ϣ���������ο����ͻ���Ȩ��ʹ�û����вο��޸ģ�����˾��
;*  �ṩ�κε������ԡ��ɿ��Եȱ�֤�����ڿͻ�ʹ�ù��������κ�ԭ����ɵ��ر�ġ�żȻ�Ļ��ӵ���ʧ������˾��
;*  �е��κ����Ρ�
;*                                                                        ����������������Ƭ���Ƽ����޹�˾
;*
;*--------------File Info---------------------------------------------------------------------------------
;* File name:               kinetis_k_startup_iar.s
;* Last modified date:      2012-11-30
;* Last version:            V1.0
;* Description:             kinetis kϵ�� ������IAR�������ļ�
;*
;*--------------------------------------------------------------------------------------------------------
;* Created by:              Fan Linyun
;* Created date:            2012-11-30
;* Version:                 V1.0
;* Descriptions:            The original version ��ʼ�汾
;*
;*--------------------------------------------------------------------------------------------------------
;* Modified by:             
;* Modified date:           
;* Version:                 
;* Descriptions:            
;*
;********************************************************************************************************/

;*********************************************************************************************************
;  Flash��������ֵ������Ϊ0x0001����ܣ����򲻼���
;*********************************************************************************************************
FLASH_SECURITY  EQU     0x0000
;SECURITY_ADDR   EQU     0x0000
;*********************************************************************************************************
; declaration of function for vector table. �ж��������û���������
;*********************************************************************************************************
                EXTERN  sysInit
                
                
;*********************************************************************************************************
; vector table. �ж�������
;*********************************************************************************************************
                MODULE  ?cstartup

                SECTION CSTACK:DATA:NOROOT(3)
                SECTION .intvec:CODE:NOROOT(2)
                
                EXTERN  __iar_program_start
                PUBLIC  __vector_table

                DATA
__vector_table  DCD     sfe(CSTACK)                     ; Top of Stack
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
                
;*********************************************************************************************************
; default function for vector table. �ж�����Ĭ�Ϻ���
;*********************************************************************************************************
                THUMB

                PUBWEAK resetHandler
                SECTION .text:CODE:REORDER(2)
resetHandler
                BL      sysInit
                B       __iar_program_start

                PUBWEAK nmiHandler
                SECTION .text:CODE:REORDER(1)
nmiHandler
                B       nmiHandler

                PUBWEAK hardFaultHandler
                SECTION .text:CODE:REORDER(1)
hardFaultHandler
                B       hardFaultHandler


                PUBWEAK intDefaultHandler
                SECTION .text:CODE:REORDER(1)
intDefaultHandler
                B       intDefaultHandler

;*********************************************************************************************************
;  This section is for Flash security         ???????????????????????????????????������
;*********************************************************************************************************
;                SECTION SECURITY:CODE(2)
;                data
;SECURITY_ADDR   dcw     FLASH_SECURITY


                END
                
;*********************************************************************************************************
; END FILE
;*********************************************************************************************************
