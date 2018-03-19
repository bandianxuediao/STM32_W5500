#include "includes.h"
#include "w5500.h"
#include <stdint.h>
#include "wizchip_conf.h"
#include "socket.h"
#include "w5500_init.h"
														
/* Private macro -------------------------------------------------------------*/
uint8_t gDATABUF[DATA_BUF_SIZE];
// Default Network Configuration
wiz_NetInfo gWIZNETINFO = { .mac = {0x00, 0x08, 0xdc,0x00, 0xab, 0xcd},
                            .ip = {192, 168, 1, 123},
                            .sn = {255,255,255,0},
                            .gw = {192, 168, 1, 1},
                            .dns = {0,0,0,0},
                            .dhcp = NETINFO_STATIC };

	uint8_t tmp;
	int32_t ret = 0;
	uint8_t memsize[2][8] = {{2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};	
	uint8_t DstIP[]={192,168,1,100};



// 		/* Loopback Test */
// 		// TCP server loopback test
// 		if( (ret = loopback_tcps(SOCK_TCPS, gDATABUF, 5000)) < 0) {
// 			printf("SOCKET ERROR : %ld\r\n", ret);
// 		}
//     // UDP server loopback test
// 		if( (ret = loopback_udps(SOCK_UDPS, gDATABUF, 3000)) < 0) {
// 			printf("SOCKET ERROR : %ld\r\n", ret);
// 		}



void phy_link(void)
{
	/* PHY link status check */
	do{
		 if(ctlwizchip(CW_GET_PHYLINK, (void*)&tmp) == -1){
				printf("Unknown PHY Link stauts.\r\n");
		 }
	}while(tmp == PHY_LINK_OFF);
}

void socket_buf_int(void)
{
	/* WIZCHIP SOCKET Buffer initialize */
	if(ctlwizchip(CW_INIT_WIZCHIP,(void*)memsize) == -1){
		 printf("WIZCHIP Initialized fail.\r\n");
		 while(1);
	}
}

void socket_connect(void)
{
	//新建一个Socket并绑定本地端口5000
	ret = socket(SOCK_TCPS,Sn_MR_TCP,5000,0x00);
	if(ret != SOCK_TCPS){
		printf("SOCK_TCPS %d:Socket Error\r\n",SOCK_TCPS);
		while(1);
	}else{
		printf("SOCK_TCPS %d:Opened\r\n",SOCK_TCPS);
	}
	//连接TCP服务器
	ret = connect(SOCK_TCPS,DstIP,6000);
	if(ret != SOCK_OK){
		printf("SOCK_TCPS %d:Socket Connect Error\r\n",SOCK_TCPS);
		while(1);
	}else{
		printf("SOCK_TCPS %d:Socket Connected\r\n",SOCK_TCPS);
	}		
}



void reg_w5500(void)
{
    // First of all, Should register SPI callback functions implemented by user for accessing WIZCHIP 
    /* Critical section callback */
    reg_wizchip_cris_cbfunc(SPI_CrisEnter, SPI_CrisExit);   //注册临界区函数
    /* Chip selection call back */
#if   _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_VDM_
    reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);//注册SPI片选信号函数
#elif _WIZCHIP_IO_MODE_ == _WIZCHIP_IO_MODE_SPI_FDM_
    reg_wizchip_cs_cbfunc(SPI_CS_Select, SPI_CS_Deselect);  // CS must be tried with LOW.
#else
   #if (_WIZCHIP_IO_MODE_ & _WIZCHIP_IO_MODE_SIP_) != _WIZCHIP_IO_MODE_SIP_
      #error "Unknown _WIZCHIP_IO_MODE_"
   #else
      reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
   #endif
#endif
    /* SPI Read & Write callback function */
    reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);    //注册读写函数


}



/**
  * @brief  Intialize the network information to be used in WIZCHIP
  * @retval None
  */
void network_init(void)
{
   uint8_t tmpstr[6];
	ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);
	ctlnetwork(CN_GET_NETINFO, (void*)&gWIZNETINFO);

	// Display Network Information
	ctlwizchip(CW_GET_ID,(void*)tmpstr);
	printf("\r\n=== %s NET CONF ===\r\n",(char*)tmpstr);
	printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",gWIZNETINFO.mac[0],gWIZNETINFO.mac[1],gWIZNETINFO.mac[2],
		  gWIZNETINFO.mac[3],gWIZNETINFO.mac[4],gWIZNETINFO.mac[5]);
	printf("SIP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0],gWIZNETINFO.ip[1],gWIZNETINFO.ip[2],gWIZNETINFO.ip[3]);
	printf("GAR: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0],gWIZNETINFO.gw[1],gWIZNETINFO.gw[2],gWIZNETINFO.gw[3]);
	printf("SUB: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0],gWIZNETINFO.sn[1],gWIZNETINFO.sn[2],gWIZNETINFO.sn[3]);
	printf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0],gWIZNETINFO.dns[1],gWIZNETINFO.dns[2],gWIZNETINFO.dns[3]);
	printf("======================\r\n");
}

/**
  * @brief  Loopback Test Example Code using ioLibrary_BSD	
  * @retval None
  */
int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t port)
{
   int32_t ret;
   uint16_t size = 0, sentsize=0;
   switch(getSn_SR(sn))
   {
      case SOCK_ESTABLISHED :
         if(getSn_IR(sn) & Sn_IR_CON)
         {
//             printf("%d:Connected\r\n",sn);
            setSn_IR(sn,Sn_IR_CON);
         }
         if((size = getSn_RX_RSR(sn)) > 0)
         {
            if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
            ret = recv(sn,buf,size);
            if(ret <= 0) return ret;
            sentsize = 0;
            while(size != sentsize)
            {
               ret = send(sn,buf+sentsize,size-sentsize);
               if(ret < 0)
               {
                  close(sn);
                  return ret;
               }
               sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
            }
         }
         break;
      case SOCK_CLOSE_WAIT :
         printf("%d:CloseWait\r\n",sn);
         if((ret=disconnect(sn)) != SOCK_OK) return ret;
         printf("%d:Closed\r\n",sn);
         break;
      case SOCK_INIT :
    	  printf("%d:Listen, port [%d]\r\n",sn, port);
         if( (ret = listen(sn)) != SOCK_OK) return ret;
         break;
      case SOCK_CLOSED:
         printf("%d:LBTStart\r\n",sn);
         if((ret=socket(sn,Sn_MR_TCP,port,0x00)) != sn)
            return ret;
         printf("%d:Opened\r\n",sn);
         break;
      default:
         break;
   }
   return 1;
}

/**
  * @brief  Loopback Test Example Code using ioLibrary_BSD	
  * @retval None
  */
int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t port)
{
   int32_t  ret;
   uint16_t size, sentsize;
   uint8_t  destip[4];
   uint16_t destport;
   //uint8_t  packinfo = 0;
   switch(getSn_SR(sn))
   {
      case SOCK_UDP :
         if((size = getSn_RX_RSR(sn)) > 0)
         {
            if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
            ret = recvfrom(sn,buf,size,destip,(uint16_t*)&destport);
            if(ret <= 0)
            {
               printf("%d: recvfrom error. %ld\r\n",sn,ret);
               return ret;
            }
            size = (uint16_t) ret;
            sentsize = 0;
            while(sentsize != size)
            {
               ret = sendto(sn,buf+sentsize,size-sentsize,destip,destport);
               if(ret < 0)
               {
                  printf("%d: sendto error. %ld\r\n",sn,ret);
                  return ret;
               }
               sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
            }
         }
         break;
      case SOCK_CLOSED:
         printf("%d:LBUStart\r\n",sn);
         if((ret=socket(sn,Sn_MR_UDP,port,0x00)) != sn)
            return ret;
         printf("%d:Opened, port [%d]\r\n",sn, port);
         break;
      default :
         break;
   }
   return 1;
}



//end
