#include "includes.h"

/*********************************************************************************************************
** Function name:           main
*********************************************************************************************************/
int  main (void)
{
  __disable_irq();                                                    /* 禁止中断                     */
	UART_Init(DEBUG_UART_PORT,DEBUG_UART_BAUD); //初始化调试串口
	spi0Init();                                                         /* SPI初始化                    */
	reg_w5500();                 //register SPI callback functions implemented by user for accessing WIZCHIP
	__enable_irq();                                                     /* 使能中断                     */
	
	socket_buf_int();
	phy_link();	
	/* Network initialization */
	network_init();
	socket_connect();	
	while(1)
	{		
// 		//接收TCP服务器发送的数据
// 		ret = recv(SOCK_TCPS,gDATABUF,DATA_BUF_SIZE);
// 		if(ret <= 0){
// 			continue;
// 		}
// 		//将接收的数据原样返回给TCP服务器
// 		ret = send(SOCK_TCPS,gDATABUF,ret);
		send(SOCK_TCPS,"\r\n12345\r\n",7);
	} // end of Main loop
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
