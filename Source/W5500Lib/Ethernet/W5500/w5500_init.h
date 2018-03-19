#ifndef  _W5500_init_H_
#define  _W5500_init_H_

#include <stdint.h>
#include "wizchip_conf.h"
#include "w5500.h"
#include "socket.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SOCK_TCPS        0
#define SOCK_UDPS        1
#define DATA_BUF_SIZE   2048


void reg_w5500(void);
void network_init(void);
int32_t loopback_tcps(uint8_t sn, uint8_t* buf, uint16_t port);
int32_t loopback_udps(uint8_t sn, uint8_t* buf, uint16_t port);
void socket_connect(void);
void socket_buf_int(void);
void phy_link(void);



#endif   // _W5500_init_H_
//end
