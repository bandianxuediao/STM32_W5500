#include "includes.h"

/*********************************************************************************************************
** Function name:           main
*********************************************************************************************************/
int  main (void)
{
  __disable_irq();                                                    /* ��ֹ�ж�                     */
	UART_Init(DEBUG_UART_PORT,DEBUG_UART_BAUD); //��ʼ�����Դ���
	spi0Init();                                                         /* SPI��ʼ��                    */
	reg_w5500();                 //register SPI callback functions implemented by user for accessing WIZCHIP
	__enable_irq();                                                     /* ʹ���ж�                     */
	
	socket_buf_int();
	phy_link();	
	/* Network initialization */
	network_init();
	socket_connect();	
	while(1)
	{		
// 		//����TCP���������͵�����
// 		ret = recv(SOCK_TCPS,gDATABUF,DATA_BUF_SIZE);
// 		if(ret <= 0){
// 			continue;
// 		}
// 		//�����յ�����ԭ�����ظ�TCP������
// 		ret = send(SOCK_TCPS,gDATABUF,ret);
		send(SOCK_TCPS,"\r\n12345\r\n",7);
	} // end of Main loop
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
