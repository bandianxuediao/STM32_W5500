//*******************************************************************************	 
//硬件    :超核电子Kinetis核心板 V2.2
//处理器  :K10DN512VLL10  K60X256VLL10
//作者    :YANDLD @ UPC
//E-MAIL  :yandld@126.com
//修改日期:2012/6/10
//版本：V2.2
//淘宝：http://upcmcu.taobao.com
//论坛: http://www.tinychip.net
//Copyright(C) YANDLD 2012-2022
//All rights reserved
//********************************************************************************
#ifndef __UART_H__
#define __UART_H__
#include "includes.h"

//定义printf打印口
#define DEBUG_UART_PORT  UART0       //指定那个串口作为printf输出口
#define DEBUG_UART_BAUD  (115200)    //printf 波特率

//本构件实现的接口函数列表
void UART_Init(UART_Type *uartch,INT32U baud);
void UART_Send1(UART_Type *uartch, INT8U ch);                                                                 
void UART_SendN (UART_Type *uartch,INT8U *buff,INT16U len);
INT8U UART_Re1 (UART_Type *uartch,INT8U *ch);
void UART1_RX_TX_IRQHandler(void);
void interrupt_pro(void);
void  uart3TxIntEnable (void);
void  uart3RxIntEnable (void);
void  uart3TxIntDisable (void);
void  uart3RxIntDisable (void);
void  uart3FIFOClear (void);
void  uart3IntInit (void);
void  uart3TxStr (INT8U  *pucBuffer);
void  uart3TxData (INT8U  ucChar);




#endif
