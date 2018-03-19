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
#include "uart.h"
#include "includes.h"

INT8U   GucRecString[4];                                                /* ����FIFOȫ������             */
INT8U   GucTxString[4];                                                 /* ����FIFOȫ������             */
INT8U   GucRecFlag     = 0;                                             /* ����FIFO��־λ               */

INT32U  GulBufCounter  = 0;                                             /* ��¼FIFO���͸���             */
INT32U  GulFifoCounter = 0;                                             /* ��¼FIFO����                 */

//������: UART_Init                                                       
//��  ��: ��ʼ��uartxģ��,�������ж�                                                
//��  ��: uartch:���ں�                
//        baud:�����ʣ���9600��115200��      
//˵  ��: ��k10оƬ�ϣ�һ����5��uart���ֱ�ΪUART0,UART1,UART2,UART3,UART4                                        
/////////////////////////////////////////////////////
void UART_Init(UART_Type *uartch,INT32U baud)
{	    
  //���д������ʼ���
  INT16U sbr;
	INT8U brfa; 
	INT32U clock;
// 	GetProcessorInfo();  //����ϵͳʱ��
  clock=sysClkGet(SYS_BUS);		//��ȡ��������ʱ��
	if((INT32U)uartch==UART0_BASE_PTR ||(INT32U)uartch==UART1_BASE_PTR ) clock=sysClkGet(SYS_CORE);; //UART0 UART1ʹ��CoreClock
	sbr=(INT16U)((clock)/(baud*16));
	brfa=((clock*2)/baud-(sbr*32));
	//��uart��ص����ŵ�ʱ��ʹ��
	switch((INT32U)uartch)
    {case UART0_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTA_MASK;  //��uart0��ص����ŵ�ʱ��ʹ�ܣ��μ��ֲ�267ҳ
					  //����uart0��Ź��� �μ��ֲ�239ҳ
					  PORTA_PCR14&=~PORT_PCR_MUX_MASK;
					  PORTA_PCR14=PORT_PCR_MUX(0x3);   //��PTD6��ʹ��UART0_TXD����
	          PORTA_PCR15&=~PORT_PCR_MUX_MASK;
					  PORTA_PCR15|=PORT_PCR_MUX(0x3);  //��PTD7��ʹ��UART0_RXD
					  SIM_SCGC4|=SIM_SCGC4_UART0_MASK;	 //ʹ��uart0ʱ��ģ�飬�μ��ֲ�265ҳ
					  NVIC_EnableIRQ(UART0_RX_TX_IRQn);  //���������жϣ��μ��ֲ�1221ҳ,��������core_cm4.h
					  break; 
					  		
	  case UART1_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTC_MASK;  //��uart1��ص����ŵ�ʱ��ʹ�ܣ��μ��ֲ�267ҳ
					  //����uart1��Ź��� �μ��ֲ�239ҳ
					  PORTC_PCR4&=~PORT_PCR_MUX_MASK;
					  PORTC_PCR4=PORT_PCR_MUX(0x3);   //��PTC4��ʹ��UART1_TXD����
	          PORTC_PCR3&=~PORT_PCR_MUX_MASK;
					  PORTC_PCR3|=PORT_PCR_MUX(0x3);  //��PTC3��ʹ��UART1_RXD
					  SIM_SCGC4|=SIM_SCGC4_UART1_MASK;	 //ʹ��uart1ʱ��ģ�飬�μ��ֲ�265ҳ
					  NVIC_EnableIRQ(UART1_RX_TX_IRQn);  //���������жϣ��μ��ֲ�1221ҳ,��������core_cm4.h
					  break;
	  case UART2_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;  //��uart2��ص����ŵ�ʱ��ʹ�ܣ��μ��ֲ�267ҳ
					  //����uart2��Ź��� �μ��ֲ�239ҳ
					  PORTD_PCR3&=~PORT_PCR_MUX_MASK;
					  PORTD_PCR3=PORT_PCR_MUX(0x3);   //��PTD3��ʹ��UART2_TXD����
	          PORTD_PCR2&=~PORT_PCR_MUX_MASK;
					  PORTD_PCR2|=PORT_PCR_MUX(0x3);  //��PTD2��ʹ��UART2_RXD
					  SIM_SCGC4|=SIM_SCGC4_UART2_MASK;	 //ʹ��uart2ʱ��ģ�飬�μ��ֲ�265ҳ
					  NVIC_EnableIRQ(UART2_RX_TX_IRQn);  //���������жϣ��μ��ֲ�1221ҳ,��������core_cm4.h
					  break; 
	  case UART3_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;  //��uart3��ص����ŵ�ʱ��ʹ�ܣ��μ��ֲ�267ҳ
					  //����uart3��Ź��� �μ��ֲ�239ҳ
					  PORTE_PCR4&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR4=PORT_PCR_MUX(0x3);   //��PTB11��ʹ��UART3_TXD����
	          PORTE_PCR5&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR5|=PORT_PCR_MUX(0x3);  //��PTD10��ʹ��UART3_RXD����
					  SIM_SCGC4|=SIM_SCGC4_UART3_MASK;	 //ʹ��uart3ʱ��ģ�飬�μ��ֲ�265ҳ
					  NVIC_EnableIRQ(UART3_RX_TX_IRQn);  //���������жϣ��μ��ֲ�1221ҳ,��������core_cm4.h
					  break; 
	  case UART5_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;  //��uart4��ص����ŵ�ʱ��ʹ�ܣ��μ��ֲ�267ҳ
					  //����uart4��Ź��� �μ��ֲ�239ҳ
					  PORTE_PCR8&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR8=PORT_PCR_MUX(0x3);   //��PTE24��ʹ��UART4_TXD����
	          PORTE_PCR9&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR9|=PORT_PCR_MUX(0x3);  //��PTE25��ʹ��UART4_RXD����
					  SIM_SCGC1|=SIM_SCGC1_UART5_MASK;	 //ʹ��uart4ʱ��ģ�飬�μ��ֲ�262ҳ
					  NVIC_EnableIRQ(UART5_RX_TX_IRQn);  //���������жϣ��μ��ֲ�1221ҳ,��������core_cm4.h
					  break;
	  default : break;
	}
//����uart���ƼĴ�����ʵ�ֻ����İ�λ���书��
  uartch->C2&=~(UART_C2_RE_MASK|UART_C2_TE_MASK);	 //��ֹ���ͽ���,�μ��ֲ�1221ҳ
	uartch->C1&=~UART_C1_M_MASK;   //��������λ��Ϊ8λ���μ������ֲ�1220ҳ
	uartch->C1&=~(UART_C1_PE_MASK);//����Ϊ����żУ��λ���μ������ֲ�1220ҳ
	uartch->S2&=~UART_S2_MSBF_MASK;//����Ϊ���λ���ȴ���
//���ô���Ƶ��
	uartch->BDH|=((sbr>>8)&UART_BDH_SBR_MASK);//���ø�5λ�����ݣ��μ��ֲ�1218ҳ
	uartch->BDL=(sbr&UART_BDL_SBR_MASK);//���õ�8λ����
	uartch->C4|=brfa&(UART_BDL_SBR_MASK>>3);//����С��λ���μ��ֲ�1232ҳ

    /*
     * ʹ�ܷ��ͺͽ���FIFO
     */
    uartch->PFIFO  |= (UART_PFIFO_TXFE_MASK |
                     UART_PFIFO_RXFE_MASK);
	   uartch->CFIFO |= UART_CFIFO_RXUFE_MASK;
//     /*
//      * ���÷��ͺͽ���FIFO���
//      */
    uartch->TWFIFO = 0x05;
    uartch->RWFIFO = 0x05;
		
//ʹ�ܽ������뷢����
	uartch->C2|=(UART_C2_RE_MASK|UART_C2_TE_MASK);	 //�������ݷ��ͽ���,�μ��ֲ�1221ҳ
//�����ж�ʹ��
	uartch->C2|=UART_C2_RIE_MASK; //���������жϣ��μ��ֲ�1221ҳ
}
//�ض���fputc���� Ϊ��ʹ��printf����
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout; 
int fputc(int ch,FILE *f)
{
	UART_Send1(DEBUG_UART_PORT,ch);
	return ch;
}
///////////////////////////////////////////////////
//������: UART_Send1                                                       
//��  ��: ���ڷ���1���ֽ�                                                  
//��  ��: uartch: ���ں�
//         ch:    Ҫ���͵��ֽ�                                             
//��  ��: ��                                                               
//˵  ��:                                                                  
///////////////////////////////////////////////////////
void UART_Send1(UART_Type *uartch, INT8U ch)
{
    //�ȴ����ͻ������գ��μ��ֲ�1223ҳ
    while(!(uartch->S1 & UART_S1_TDRE_MASK));
    //��������,�μ��ֲ�1230ҳ
    uartch->D=(INT8U)ch;
 }
//////////////////////////////////////////////////
//������: UART_SendN                                                       
//��  ��: ���з���n���ֽ�                                                  
//��  ��: uartch: ���ں�                                                   
//        buff: ���ͻ�����                                                 
//		  len:���ͳ���                                                     
//˵  ��: ����һ���ַ�                                                                 
////////////////////////////////////////////////
void UART_SendN (UART_Type *uartch,INT8U *buff,INT16U len)
{
    int i;
	for(i=0;i<len;i++)
    {
		UART_Send1(uartch,buff[i]);
    }
}
/*********************************************************************************************************
** Function name:           uart0TxStr
** Descriptions:            UART0�ķ����ַ���
** input parameters:        pucBuffer:      �ַ�����ַ
*********************************************************************************************************/
void  uart3TxStr (INT8U  *pucBuffer)
{
    while (*pucBuffer != '\0')
    { 
        uart3TxData(*pucBuffer ++);                                     /* �����ַ���                   */
    }
}
/*********************************************************************************************************
** Function name:           uart0TxData
** Descriptions:            ����һ���ַ�
** input parameters:        ucChar:�����ַ�
*********************************************************************************************************/
void  uart3TxData (INT8U  ucChar)
{
    while (!(UART0->S1 & UART_S1_TC_MASK));                              /* �ȴ�����BufΪ��              */ 
        UART0->D = ucChar;                                               /* ��������                     */
    
    if ('\n' == ucChar) {
        while (!(UART0->S1 & UART_S1_TC_MASK));                          /* �ȴ�����BufΪ��              */
        UART0->D = '\r';                                                 /* ���ͽ�����'/r'               */
    }
}

////////////////////////////////////////////
//������: UART_Re1                                                         
//��  ��: ���ڽ���1���ֽ�                                                  
//��  ��: uartch: ���ں�                                                   
//         ch:    ���յ����ֽ�                                             
//��  ��: �ɹ�:1;ʧ��:0                                                    
//˵  ��: �˴����ò�ѯ�ķ�ʽ�������ݽ��գ��в������أ�����ʹ���жϽ��յķ�ʽ                                                                 
///////////////////////////////////////////
INT8U UART_Re1 (UART_Type *uartch,INT8U *ch)
{
    INT32U k;
    for (k = 0; k <= 0xfbbb; k++)//��������е��ǽ���ʱ������
	 {	
	     if((uartch->S1 & UART_S1_RDRF_MASK)!= 0)//�жϽ��ջ������Ƿ���,�μ��ֲ�1223ҳ
		 {
		   *ch =(uartch->D);	//��������,�μ��ֲ�1230ҳ
		   return 1; 			//���ܳɹ�
		 } 
     }
    return 0;			//�����ʱ������ʧ��
}

///////////////////////////////////////////////
//������: UART3_RX_TX_IRQHandler                                                         
//��  ��: UART3���ڽ����뷢���жϷ�����                                                 
//��  ��: ��                                                 
//��  ��: ��                                                    
//˵  ��: �����ڲ���һ�����ջ��߷����ź�ʱ��������һ���ж��źţ�����˺����������жϴ���
//         �жϱ���Զ����                                                                   
//////////////////////////////////////////////
void UART0_RX_TX_IRQHandler(void)
{ 
    INT16U  uiFifoEmpty = 1;
    INT8U   ucChar,ucCnt;

    INT8U  ucDatCnt = 0;

    if (UART0->S1 & UART_S1_RDRF_MASK) {
        
        for (ucCnt = 0;ucCnt < UART0->RWFIFO;ucCnt++) {                  /* ����FIFO����                 */
 
            GucRecString[ucDatCnt] = UART0->D;               
            ucDatCnt++;
        }
        GucRecFlag = 1;
    } 
		
		else if (UART0->S1 & UART_S1_TDRE_MASK) {
    
        while(uiFifoEmpty) {     
            /*
             *  ��������
             */
            ucChar = GucTxString[GulBufCounter];
            /*
             *  Tx FIFO �Ƿ����� �� �����ֽ���('\0')?
             */
            if ('\0' == ucChar) {
                GulFifoCounter = 0;
            }
            
            if ( (GulFifoCounter >= UART0->TWFIFO) || ('\0' == ucChar) ) {
                GulFifoCounter = 0;
                uiFifoEmpty    = 0; 
                uart3TxIntDisable();  
            } else {
                UART0->D = ucChar;                                       /* ��� Tx FIFO                 */
                GulFifoCounter++; 
                GulBufCounter++;
            }
        }
    }
		interrupt_pro();				        
		
}
//�жϳ���

void interrupt_pro(void){
// 				INT8U i;
	        /*
         *  ��������ݽ���
         */
// 	  unsigned int amount=0;    

        if(GucRecFlag == 1) {
            uart3RxIntDisable();                                        /* ��ʼ�������ݣ��رս����ж�   */
//             for (i = 0; i < 5; i ++) {
// 								GucTxString[i] = GucRecString[i];
//             }
            GulBufCounter  = 0;
            GulFifoCounter = 0;

            uart3TxIntEnable();                                         /* UART0 �����ж�ʹ��           */
           /*
            *  ��������ͨ�������жϷ��ͣ������FIFOΪ��ʱ�����FIFO��������
            */
//             while(!(uart0GetTxStatus() == 1) );                         /* �ȴ�������ϣ�TC = 1?        */
// //             while(*GucTxString != '\n'){
//             for (i = 0; i < 5; i ++) {
// //                 i=0;
// 								GucTxString[i] = 0;
//                 GucRecString[i] = 0;
// // 								i++;
//             }
						printf("\r\n %d \r\n", GucRecString);                             /* ����ַ���                   */
// 						amount=atoi(GucRecString);
//             lcd_display(amount);
						uart3TxIntDisable();                                        /* �жϷ�����ϣ��رշ����ж�   */
            uart3RxIntEnable ();                                        /* �жϷ�����ϣ����������ж�   */
            GucRecFlag = 0;                                             
            uart3FIFOClear();                                           /* ������ͺͽ���FIFO           */
        }

}
/*********************************************************************************************************
** Function name:           uart0FIFOClear
** Descriptions:            ������ͺͽ���FIFO
*********************************************************************************************************/
void  uart3FIFOClear (void)
{
    UART0->CFIFO |= UART_CFIFO_RXFLUSH_MASK;                             /* ���UART0����FIFO            */
    UART0->CFIFO |= UART_CFIFO_TXFLUSH_MASK;                             /* ���UART0����FIFO            */
}

/*********************************************************************************************************
** Function name:           uart0IntInit
** Descriptions:            UART0 �жϳ�ʼ������
*********************************************************************************************************/
void  uart3IntInit (void)
{
    /*
     *  ����UART0 �ж�
     */
    NVIC_ClearPendingIRQ(UART3_RX_TX_IRQn);                             /* ���UART0 ���ͺͽ����ж�     */
    NVIC_EnableIRQ(UART3_RX_TX_IRQn);                                   /* ʹ��UART0 �����ж�           */
    NVIC_SetPriority(UART3_RX_TX_IRQn, 1);                              /* ����UART0 �����ж����ȼ�     */
}

/*********************************************************************************************************
** Function name:           uart0TxIntEnable 
** Descriptions:            ʹ��UART0 Tx�ж�
*********************************************************************************************************/
void  uart3TxIntEnable (void)
{
    /*
     *  ʹ��UART0 Tx�ж�
     */
    UART0->C2 |= UART_C2_TIE_MASK;
}
/*********************************************************************************************************
** Function name:           uart0RxIntEnable 
** Descriptions:            ʹ��UART0 Rx�ж�
*********************************************************************************************************/
void  uart3RxIntEnable (void)
{
    /*
     *  ʹ��UART0 Rx�ж�
     */
    UART0->C2 |= UART_C2_RIE_MASK;
}
/*********************************************************************************************************
** Function name:           uart0TxIntDisable 
** Descriptions:            ����UART0 Tx�ж�
*********************************************************************************************************/
void  uart3TxIntDisable (void)
{
    /*
     *  ����UART0 Tx�ж�
     */
    UART0->C2 &= ~UART_C2_TIE_MASK;
}
/*********************************************************************************************************
** Function name:           uart0RxIntDisable 
** Descriptions:            ����UART0 Rx�ж�
*********************************************************************************************************/
void  uart3RxIntDisable (void)
{
    /*
     *  ����UART0 Rx�ж�
     */
    UART0->C2 &= ~UART_C2_TIE_MASK;
}
