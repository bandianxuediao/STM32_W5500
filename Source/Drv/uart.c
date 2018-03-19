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
#include "uart.h"
#include "includes.h"

INT8U   GucRecString[4];                                                /* 接收FIFO全局数组             */
INT8U   GucTxString[4];                                                 /* 发送FIFO全局数组             */
INT8U   GucRecFlag     = 0;                                             /* 接收FIFO标志位               */

INT32U  GulBufCounter  = 0;                                             /* 记录FIFO发送个数             */
INT32U  GulFifoCounter = 0;                                             /* 记录FIFO个数                 */

//函数名: UART_Init                                                       
//功  能: 初始化uartx模块,开接收中断                                                
//参  数: uartch:串口号                
//        baud:波特率，如9600，115200等      
//说  明: 在k10芯片上，一共有5个uart，分别为UART0,UART1,UART2,UART3,UART4                                        
/////////////////////////////////////////////////////
void UART_Init(UART_Type *uartch,INT32U baud)
{	    
  //进行传输速率计算
  INT16U sbr;
	INT8U brfa; 
	INT32U clock;
// 	GetProcessorInfo();  //计算系统时钟
  clock=sysClkGet(SYS_BUS);		//获取外设总线时钟
	if((INT32U)uartch==UART0_BASE_PTR ||(INT32U)uartch==UART1_BASE_PTR ) clock=sysClkGet(SYS_CORE);; //UART0 UART1使用CoreClock
	sbr=(INT16U)((clock)/(baud*16));
	brfa=((clock*2)/baud-(sbr*32));
	//与uart相关的引脚的时钟使能
	switch((INT32U)uartch)
    {case UART0_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTA_MASK;  //与uart0相关的引脚的时钟使能，参见手册267页
					  //开启uart0针脚功能 参见手册239页
					  PORTA_PCR14&=~PORT_PCR_MUX_MASK;
					  PORTA_PCR14=PORT_PCR_MUX(0x3);   //在PTD6上使能UART0_TXD功能
	          PORTA_PCR15&=~PORT_PCR_MUX_MASK;
					  PORTA_PCR15|=PORT_PCR_MUX(0x3);  //在PTD7上使能UART0_RXD
					  SIM_SCGC4|=SIM_SCGC4_UART0_MASK;	 //使能uart0时钟模块，参见手册265页
					  NVIC_EnableIRQ(UART0_RX_TX_IRQn);  //开启接受中断，参见手册1221页,函数来自core_cm4.h
					  break; 
					  		
	  case UART1_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTC_MASK;  //与uart1相关的引脚的时钟使能，参见手册267页
					  //开启uart1针脚功能 参见手册239页
					  PORTC_PCR4&=~PORT_PCR_MUX_MASK;
					  PORTC_PCR4=PORT_PCR_MUX(0x3);   //在PTC4上使能UART1_TXD功能
	          PORTC_PCR3&=~PORT_PCR_MUX_MASK;
					  PORTC_PCR3|=PORT_PCR_MUX(0x3);  //在PTC3上使能UART1_RXD
					  SIM_SCGC4|=SIM_SCGC4_UART1_MASK;	 //使能uart1时钟模块，参见手册265页
					  NVIC_EnableIRQ(UART1_RX_TX_IRQn);  //开启接受中断，参见手册1221页,函数来自core_cm4.h
					  break;
	  case UART2_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;  //与uart2相关的引脚的时钟使能，参见手册267页
					  //开启uart2针脚功能 参见手册239页
					  PORTD_PCR3&=~PORT_PCR_MUX_MASK;
					  PORTD_PCR3=PORT_PCR_MUX(0x3);   //在PTD3上使能UART2_TXD功能
	          PORTD_PCR2&=~PORT_PCR_MUX_MASK;
					  PORTD_PCR2|=PORT_PCR_MUX(0x3);  //在PTD2上使能UART2_RXD
					  SIM_SCGC4|=SIM_SCGC4_UART2_MASK;	 //使能uart2时钟模块，参见手册265页
					  NVIC_EnableIRQ(UART2_RX_TX_IRQn);  //开启接受中断，参见手册1221页,函数来自core_cm4.h
					  break; 
	  case UART3_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;  //与uart3相关的引脚的时钟使能，参见手册267页
					  //开启uart3针脚功能 参见手册239页
					  PORTE_PCR4&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR4=PORT_PCR_MUX(0x3);   //在PTB11上使能UART3_TXD功能
	          PORTE_PCR5&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR5|=PORT_PCR_MUX(0x3);  //在PTD10上使能UART3_RXD功能
					  SIM_SCGC4|=SIM_SCGC4_UART3_MASK;	 //使能uart3时钟模块，参见手册265页
					  NVIC_EnableIRQ(UART3_RX_TX_IRQn);  //开启接受中断，参见手册1221页,函数来自core_cm4.h
					  break; 
	  case UART5_BASE_PTR :
	                  SIM_SCGC5|=SIM_SCGC5_PORTE_MASK;  //与uart4相关的引脚的时钟使能，参见手册267页
					  //开启uart4针脚功能 参见手册239页
					  PORTE_PCR8&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR8=PORT_PCR_MUX(0x3);   //在PTE24上使能UART4_TXD功能
	          PORTE_PCR9&=~PORT_PCR_MUX_MASK;
					  PORTE_PCR9|=PORT_PCR_MUX(0x3);  //在PTE25上使能UART4_RXD功能
					  SIM_SCGC1|=SIM_SCGC1_UART5_MASK;	 //使能uart4时钟模块，参见手册262页
					  NVIC_EnableIRQ(UART5_RX_TX_IRQn);  //开启接受中断，参见手册1221页,函数来自core_cm4.h
					  break;
	  default : break;
	}
//配置uart控制寄存器，实现基本的八位传输功能
  uartch->C2&=~(UART_C2_RE_MASK|UART_C2_TE_MASK);	 //禁止发送接受,参见手册1221页
	uartch->C1&=~UART_C1_M_MASK;   //配置数据位数为8位，参见数据手册1220页
	uartch->C1&=~(UART_C1_PE_MASK);//配置为无奇偶校检位，参见数据手册1220页
	uartch->S2&=~UART_S2_MSBF_MASK;//配置为最低位优先传输
//配置传输频率
	uartch->BDH|=((sbr>>8)&UART_BDH_SBR_MASK);//设置高5位的数据，参加手册1218页
	uartch->BDL=(sbr&UART_BDL_SBR_MASK);//设置低8位数据
	uartch->C4|=brfa&(UART_BDL_SBR_MASK>>3);//设置小数位，参见手册1232页

    /*
     * 使能发送和接受FIFO
     */
    uartch->PFIFO  |= (UART_PFIFO_TXFE_MASK |
                     UART_PFIFO_RXFE_MASK);
	   uartch->CFIFO |= UART_CFIFO_RXUFE_MASK;
//     /*
//      * 设置发送和接受FIFO深度
//      */
    uartch->TWFIFO = 0x05;
    uartch->RWFIFO = 0x05;
		
//使能接收器与发送器
	uartch->C2|=(UART_C2_RE_MASK|UART_C2_TE_MASK);	 //开启数据发送接受,参见手册1221页
//接受中断使能
	uartch->C2|=UART_C2_RIE_MASK; //开启接受中断，参见手册1221页
}
//重定义fputc函数 为了使用printf函数
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout; 
int fputc(int ch,FILE *f)
{
	UART_Send1(DEBUG_UART_PORT,ch);
	return ch;
}
///////////////////////////////////////////////////
//函数名: UART_Send1                                                       
//功  能: 串口发送1个字节                                                  
//参  数: uartch: 串口号
//         ch:    要发送的字节                                             
//返  回: 无                                                               
//说  明:                                                                  
///////////////////////////////////////////////////////
void UART_Send1(UART_Type *uartch, INT8U ch)
{
    //等待发送缓冲区空，参见手册1223页
    while(!(uartch->S1 & UART_S1_TDRE_MASK));
    //发送数据,参见手册1230页
    uartch->D=(INT8U)ch;
 }
//////////////////////////////////////////////////
//函数名: UART_SendN                                                       
//功  能: 串行发送n个字节                                                  
//参  数: uartch: 串口号                                                   
//        buff: 发送缓冲区                                                 
//		  len:发送长度                                                     
//说  明: 发送一串字符                                                                 
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
** Descriptions:            UART0的发送字符串
** input parameters:        pucBuffer:      字符串基址
*********************************************************************************************************/
void  uart3TxStr (INT8U  *pucBuffer)
{
    while (*pucBuffer != '\0')
    { 
        uart3TxData(*pucBuffer ++);                                     /* 发送字符串                   */
    }
}
/*********************************************************************************************************
** Function name:           uart0TxData
** Descriptions:            发送一个字符
** input parameters:        ucChar:单个字符
*********************************************************************************************************/
void  uart3TxData (INT8U  ucChar)
{
    while (!(UART0->S1 & UART_S1_TC_MASK));                              /* 等待发送Buf为空              */ 
        UART0->D = ucChar;                                               /* 发送数据                     */
    
    if ('\n' == ucChar) {
        while (!(UART0->S1 & UART_S1_TC_MASK));                          /* 等待发送Buf为空              */
        UART0->D = '\r';                                                 /* 发送结束符'/r'               */
    }
}

////////////////////////////////////////////
//函数名: UART_Re1                                                         
//功  能: 串口接受1个字节                                                  
//参  数: uartch: 串口号                                                   
//         ch:    接收到的字节                                             
//返  回: 成功:1;失败:0                                                    
//说  明: 此处采用查询的方式进行数据接收，有不利因素，尽量使用中断接收的方式                                                                 
///////////////////////////////////////////
INT8U UART_Re1 (UART_Type *uartch,INT8U *ch)
{
    INT32U k;
    for (k = 0; k <= 0xfbbb; k++)//在这里进行的是接受时间限制
	 {	
	     if((uartch->S1 & UART_S1_RDRF_MASK)!= 0)//判断接收缓冲区是否满,参见手册1223页
		 {
		   *ch =(uartch->D);	//接受数据,参见手册1230页
		   return 1; 			//接受成功
		 } 
     }
    return 0;			//如果超时，接受失败
}

///////////////////////////////////////////////
//函数名: UART3_RX_TX_IRQHandler                                                         
//功  能: UART3串口接收与发送中断服务函数                                                 
//参  数: 无                                                 
//返  回: 无                                                    
//说  明: 当串口产生一个接收或者发送信号时，将产生一个中断信号，进入此函数，进行中断处理
//         中断标记自动清除                                                                   
//////////////////////////////////////////////
void UART0_RX_TX_IRQHandler(void)
{ 
    INT16U  uiFifoEmpty = 1;
    INT8U   ucChar,ucCnt;

    INT8U  ucDatCnt = 0;

    if (UART0->S1 & UART_S1_RDRF_MASK) {
        
        for (ucCnt = 0;ucCnt < UART0->RWFIFO;ucCnt++) {                  /* 接收FIFO数据                 */
 
            GucRecString[ucDatCnt] = UART0->D;               
            ucDatCnt++;
        }
        GucRecFlag = 1;
    } 
		
		else if (UART0->S1 & UART_S1_TDRE_MASK) {
    
        while(uiFifoEmpty) {     
            /*
             *  发送数据
             */
            ucChar = GucTxString[GulBufCounter];
            /*
             *  Tx FIFO 是否满了 或 最后的字节是('\0')?
             */
            if ('\0' == ucChar) {
                GulFifoCounter = 0;
            }
            
            if ( (GulFifoCounter >= UART0->TWFIFO) || ('\0' == ucChar) ) {
                GulFifoCounter = 0;
                uiFifoEmpty    = 0; 
                uart3TxIntDisable();  
            } else {
                UART0->D = ucChar;                                       /* 填充 Tx FIFO                 */
                GulFifoCounter++; 
                GulBufCounter++;
            }
        }
    }
		interrupt_pro();				        
		
}
//中断程序

void interrupt_pro(void){
// 				INT8U i;
	        /*
         *  检测有数据接收
         */
// 	  unsigned int amount=0;    

        if(GucRecFlag == 1) {
            uart3RxIntDisable();                                        /* 开始发送数据，关闭接收中断   */
//             for (i = 0; i < 5; i ++) {
// 								GucTxString[i] = GucRecString[i];
//             }
            GulBufCounter  = 0;
            GulFifoCounter = 0;

            uart3TxIntEnable();                                         /* UART0 发送中断使能           */
           /*
            *  发送数据通过发送中断发送，当检测FIFO为空时，填充FIFO发送数据
            */
//             while(!(uart0GetTxStatus() == 1) );                         /* 等待发送完毕，TC = 1?        */
// //             while(*GucTxString != '\n'){
//             for (i = 0; i < 5; i ++) {
// //                 i=0;
// 								GucTxString[i] = 0;
//                 GucRecString[i] = 0;
// // 								i++;
//             }
						printf("\r\n %d \r\n", GucRecString);                             /* 输出字符串                   */
// 						amount=atoi(GucRecString);
//             lcd_display(amount);
						uart3TxIntDisable();                                        /* 中断发送完毕，关闭发送中断   */
            uart3RxIntEnable ();                                        /* 中断发送完毕，开启接收中断   */
            GucRecFlag = 0;                                             
            uart3FIFOClear();                                           /* 清除发送和接受FIFO           */
        }

}
/*********************************************************************************************************
** Function name:           uart0FIFOClear
** Descriptions:            清除发送和接受FIFO
*********************************************************************************************************/
void  uart3FIFOClear (void)
{
    UART0->CFIFO |= UART_CFIFO_RXFLUSH_MASK;                             /* 清除UART0接受FIFO            */
    UART0->CFIFO |= UART_CFIFO_TXFLUSH_MASK;                             /* 清除UART0发送FIFO            */
}

/*********************************************************************************************************
** Function name:           uart0IntInit
** Descriptions:            UART0 中断初始化函数
*********************************************************************************************************/
void  uart3IntInit (void)
{
    /*
     *  配置UART0 中断
     */
    NVIC_ClearPendingIRQ(UART3_RX_TX_IRQn);                             /* 清除UART0 发送和接受中断     */
    NVIC_EnableIRQ(UART3_RX_TX_IRQn);                                   /* 使能UART0 发送中断           */
    NVIC_SetPriority(UART3_RX_TX_IRQn, 1);                              /* 设置UART0 发送中断优先级     */
}

/*********************************************************************************************************
** Function name:           uart0TxIntEnable 
** Descriptions:            使能UART0 Tx中断
*********************************************************************************************************/
void  uart3TxIntEnable (void)
{
    /*
     *  使能UART0 Tx中断
     */
    UART0->C2 |= UART_C2_TIE_MASK;
}
/*********************************************************************************************************
** Function name:           uart0RxIntEnable 
** Descriptions:            使能UART0 Rx中断
*********************************************************************************************************/
void  uart3RxIntEnable (void)
{
    /*
     *  使能UART0 Rx中断
     */
    UART0->C2 |= UART_C2_RIE_MASK;
}
/*********************************************************************************************************
** Function name:           uart0TxIntDisable 
** Descriptions:            禁用UART0 Tx中断
*********************************************************************************************************/
void  uart3TxIntDisable (void)
{
    /*
     *  禁用UART0 Tx中断
     */
    UART0->C2 &= ~UART_C2_TIE_MASK;
}
/*********************************************************************************************************
** Function name:           uart0RxIntDisable 
** Descriptions:            禁用UART0 Rx中断
*********************************************************************************************************/
void  uart3RxIntDisable (void)
{
    /*
     *  禁用UART0 Rx中断
     */
    UART0->C2 &= ~UART_C2_TIE_MASK;
}
