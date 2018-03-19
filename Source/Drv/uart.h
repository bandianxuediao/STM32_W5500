//*******************************************************************************	 
//Ӳ��    :���˵���Kinetis���İ� V2.2
//������  :K10DN512VLL10  K60X256VLL10
//����    :YANDLD @ UPC
//E-MAIL  :yandld@126.com
//�޸�����:2012/6/10
//�汾��V2.2
//�Ա���http://upcmcu.taobao.com
//��̳: http://www.tinychip.net
//Copyright(C) YANDLD 2012-2022
//All rights reserved
//********************************************************************************
#ifndef __UART_H__
#define __UART_H__
#include "includes.h"

//����printf��ӡ��
#define DEBUG_UART_PORT  UART0       //ָ���Ǹ�������Ϊprintf�����
#define DEBUG_UART_BAUD  (115200)    //printf ������

//������ʵ�ֵĽӿں����б�
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
