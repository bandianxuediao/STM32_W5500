
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  通用数据类型重定义
*********************************************************************************************************/
typedef unsigned char           BOOLEAN;                                /* 布尔变量                     */
typedef unsigned char           INT8U;                                  /* 无符号8位整型变量            */
typedef signed   char           INT8S;                                  /* 有符号8位整型变量            */
typedef unsigned short          INT16U;                                 /* 无符号16位整型变量           */
typedef signed   short          INT16S;                                 /* 有符号16位整型变量           */
typedef unsigned long           INT32U;                                 /* 无符号32位整型变量           */
typedef signed   long           INT32S;                                 /* 有符号32位整型变量           */
typedef unsigned long long      INT64U;                                 /* 无符号64位整型变量           */
typedef signed long long        INT64S;                                 /* 有符号64位整型变量           */
typedef float                   FP32;                                   /* 单精度浮点数（32位长度）     */
typedef double                  FP64;                                   /* 双精度浮点数（64位长度）     */


/*********************************************************************************************************
  Standard header files 标准头文件
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


/*********************************************************************************************************
  CMSIS 头文件
*********************************************************************************************************/

/* 
 * Configuration of the Cortex-M4 Processor and Core Peripherals
 */
#define __CM4_REV                 0x0000                                /* Core revision r0p0           */
#define __MPU_PRESENT             1                                     /* MPU present or not           */
#define __NVIC_PRIO_BITS          4                                     /* Number of Bits used for      */
                                                                        /* Priority Levels              */
#define __Vendor_SysTickConfig    0                                     /* Set to 1 if different SysTick*/
                                                                        /* Config is used               */
#define __FPU_PRESENT             1                                     /* FPU present or not           */

/* 
 * Interrupt Number Definition
 */
typedef enum IRQn
{
    NMI_IRQn                    = -14,              /*  2 Non Maskable      */
    HardFault_IRQn              = -13,              /*  3 Hard Fault        */
    MemManage_IRQn              = -12,              /*  4 Memory Management */
    BusFault_IRQn               = -11,              /*  5 Bus Fault         */
    UsageFault_IRQn             = -10,              /*  6 Usage Fault       */
    SVCall_IRQn                 = -5,               /* 11 SV Call           */
    DebugMonitor_IRQn           = -4,               /* 12 Debug Monitor     */
    PendSV_IRQn                 = -2,               /* 14 Pend SV           */
    SysTick_IRQn                = -1,               /* 15 System Tick       */
    
    DMA0_IRQn                   = 0,                /* DMA Channel 0 Transfer Complete */
    DMA1_IRQn                   = 1,                /* DMA Channel 1 Transfer Complete */
    DMA2_IRQn                   = 2,                /* DMA Channel 2 Transfer Complete */
    DMA3_IRQn                   = 3,                /* DMA Channel 3 Transfer Complete */
    DMA4_IRQn                   = 4,                /* DMA Channel 4 Transfer Complete */
    DMA5_IRQn                   = 5,                /* DMA Channel 5 Transfer Complete */
    DMA6_IRQn                   = 6,                /* DMA Channel 6 Transfer Complete */
    DMA7_IRQn                   = 7,                /* DMA Channel 7 Transfer Complete */
    DMA8_IRQn                   = 8,                /* DMA Channel 8 Transfer Complete */
    DMA9_IRQn                   = 9,                /* DMA Channel 9 Transfer Complete */
    DMA10_IRQn                  = 10,               /* DMA Channel 10 Transfer Complete */
    DMA11_IRQn                  = 11,               /* DMA Channel 11 Transfer Complete */
    DMA12_IRQn                  = 12,               /* DMA Channel 12 Transfer Complete */
    DMA13_IRQn                  = 13,               /* DMA Channel 13 Transfer Complete */
    DMA14_IRQn                  = 14,               /* DMA Channel 14 Transfer Complete */
    DMA15_IRQn                  = 15,               /* DMA Channel 15 Transfer Complete */
    DMA_Error_IRQn              = 16,               /* DMA Error Interrupt */
    MCM_IRQn                    = 17,               /* Normal Interrupt */
    FTFL_IRQn                   = 18,               /* FTFL Interrupt */
    Read_Collision_IRQn         = 19,               /* Read Collision Interrupt */
    LVD_LVW_IRQn                = 20,               /* Low Voltage Detect, Low Voltage Warning */
    LLW_IRQn_IRQn               = 21,               /* Low Leakage Wakeup */
    Watchdog_IRQn               = 22,               /* WDOG Interrupt */
    Reserved39_IRQn             = 23,               /* Reserved interrupt 39 */
    I2C0_IRQn                   = 24,               /* I2C0 interrupt */
    I2C1_IRQn                   = 25,               /* I2C1 interrupt */
    SPI0_IRQn                   = 26,               /* SPI0 Interrupt */
    SPI1_IRQn                   = 27,               /* SPI1 Interrupt */
    SPI2_IRQn                   = 28,               /* SPI2 Interrupt */
    CAN0_ORed_Message_buffer    = 29,               /* CAN0 OR'd Message Buffers Interrupt */
    CAN0_Bus_Off_IRQn           = 30,               /* CAN0 Bus Off Interrupt */
    CAN0_Error_IRQn             = 31,               /* CAN0 Error Interrupt */
    CAN0_Tx_Warning             = 32,               /* CAN0 Tx Warning Interrupt */
    CAN0_Rx_Warning             = 33,               /* CAN0 Rx Warning Interrupt */
    CAN0_Wake_Up_IRQn           = 34,               /* CAN0 Wake Up Interrupt */
    Reserved51_IRQn             = 35,               /* Reserved interrupt 51 */
    Reserved52_IRQn             = 36,               /* Reserved interrupt 52 */
    CAN1_ORed_Message_buffer    = 37,               /* CAN1 OR'd Message Buffers Interrupt */
    CAN1_Bus_Off_IRQn           = 38,               /* CAN1 Bus Off Interrupt */
    CAN1_Error_IRQn             = 39,               /* CAN1 Error Interrupt */
    CAN1_Tx_Warning             = 40,               /* CAN1 Tx Warning Interrupt */
    CAN1_Rx_Warning             = 41,               /* CAN1 Rx Warning Interrupt */
    CAN1_Wake_Up_IRQn           = 42,               /* CAN1 Wake Up Interrupt */
    Reserved59_IRQn             = 43,               /* Reserved interrupt 59 ??fly */
    Reserved60_IRQn             = 44,               /* Reserved interrupt 60 ??fly */
    UART0_RX_TX_IRQn            = 45,               /* UART0 Receive/Transmit interrupt */
    UART0_ERR_IRQn              = 46,               /* UART0 Error interrupt */
    UART1_RX_TX_IRQn            = 47,               /* UART1 Receive/Transmit interrupt */
    UART1_ERR_IRQn              = 48,               /* UART1 Error interrupt */
    UART2_RX_TX_IRQn            = 49,               /* UART2 Receive/Transmit interrupt */
    UART2_ERR_IRQn              = 50,               /* UART2 Error interrupt */
    UART3_RX_TX_IRQn            = 51,               /* UART3 Receive/Transmit interrupt */
    UART3_ERR_IRQn              = 52,               /* UART3 Error interrupt */
    UART4_RX_TX_IRQn            = 53,               /* UART4 Receive/Transmit interrupt */
    UART4_ERR_IRQn              = 54,               /* UART4 Error interrupt */
    UART5_RX_TX_IRQn            = 55,               /* UART5 Receive/Transmit interrupt */
    UART5_ERR_IRQn              = 56,               /* UART5 Error interrupt */
    ADC0_IRQn                   = 57,               /* ADC0 interrupt */
    ADC1_IRQn                   = 58,               /* ADC1 interrupt */
    CMP0_IRQn                   = 59,               /* CMP0 interrupt */
    CMP1_IRQn                   = 60,               /* CMP1 interrupt */
    CMP2_IRQn                   = 61,               /* CMP2 interrupt */
    FTM0_IRQn                   = 62,               /* FTM0 fault, overflow and channels interrupt */
    FTM1_IRQn                   = 63,               /* FTM1 fault, overflow and channels interrupt */
    FTM2_IRQn                   = 64,               /* FTM2 fault, overflow and channels interrupt */
    CMT_IRQn                    = 65,               /* CMT interrupt */
    RTC_IRQn                    = 66,               /* RTC interrupt */
    Reserved                    = 67,               /* Reserved interrupt 83 */
    PIT0_IRQn                   = 68,               /* PIT timer channel 0 interrupt */
    PIT1_IRQn                   = 69,               /* PIT timer channel 1 interrupt */
    PIT2_IRQn                   = 70,               /* PIT timer channel 2 interrupt */
    PIT3_IRQn                   = 71,               /* PIT timer channel 3 interrupt */
    PDB0_IRQn                   = 72,               /* PDB0 Interrupt */
    USB0_IRQn                   = 73,               /* USB0 interrupt */
    USBDCD_IRQn                 = 74,               /* USBDCD Interrupt */
    Reserved91_IRQn             = 75,               /* Reserved interrupt 91  ??fly */
    Reserved92_IRQn             = 76,               /* Reserved interrupt 92  ??fly */
    Reserved93_IRQn             = 77,               /* Reserved interrupt 93  ??fly */
    Reserved94_IRQn             = 78,               /* Reserved interrupt 94  ??fly */
    I2S0_IRQn                   = 79,               /* I2S0 Interrupt */
    SDHC_IRQn                   = 80,               /* SDHC Interrupt */
    DAC0_IRQn                   = 81,               /* DAC0 interrupt */
    DAC1_IRQn                   = 82,               /* DAC1 interrupt */
    TSI0_IRQn                   = 83,               /* TSI0 Interrupt */
    MCG_IRQn                    = 84,               /* MCG Interrupt */
    LPTime_IRQn                 = 85,               /* LPTimer interrupt */
    LC_IRQn                     = 86,               /* Segment LCD Interrupt */
    PORTA_IRQn                  = 87,               /* Port A interrupt */
    PORTB_IRQn                  = 88,               /* Port B interrupt */
    PORTC_IRQn                  = 89,               /* Port C interrupt */
    PORTD_IRQn                  = 90,               /* Port D interrupt */
    PORTE_IRQn                  = 91                /* Port E interrupt */
} IRQn_Type;


#include <core_cm4.h>                                                   /* CMSIS File of Cortex-M4      */


/*********************************************************************************************************
  Common's header files  公共头文件 
*********************************************************************************************************/
#include "..\Common\MK40DZ10.h"
#include "..\Common\kinetis_k_system.h"


/*********************************************************************************************************
  Driver's header files  驱动头文件 
*********************************************************************************************************/
#include "..\Drv\kinetis_k_spi_withoutfifo.h"
#include "..\Drv\mx25L1606Drv.h"
#include "..\Drv\kinetis_k_led.h"
#include "..\W5500Lib\Ethernet\W5500\w5500.h"
#include "w5500.h"
#include <stdint.h>
#include "wizchip_conf.h"
#include "socket.h"
#include "w5500_init.h"
#include "uart.h"

// #include "..\W5500Lib\Ethernet\wizchip_conf.h"
// #include "..\W5500Lib\Ethernet\socket.h"
/*********************************************************************************************************
  User's header files 用户头文件
*********************************************************************************************************/
#include "..\App\main.h"




#ifdef __cplusplus
}
#endif

#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
