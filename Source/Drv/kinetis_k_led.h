/*********************************************Copyright (c)***********************************************
**                                Guangzhou ZLG MCU Technology Co., Ltd.
**
**                                        http://www.zlgmcu.com
**
**      广州周立功单片机科技有限公司所提供的所有服务内容旨在协助客户加速产品的研发进度，在服务过程中所提供
**  的任何程序、文档、测试结果、方案、支持等资料和信息，都仅供参考，客户有权不使用或自行参考修改，本公司不
**  提供任何的完整性、可靠性等保证，若在客户使用过程中因任何原因造成的特别的、偶然的或间接的损失，本公司不
**  承担任何责任。
**                                                                        ——广州周立功单片机科技有限公司
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               Led.h
** Last modified date:      2012-12-12
** Last version:            V1.0
** Description:             LED驱动头文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Hong Haogao
** Created date:            2012-12-12
** Version:                 V1.0
** Descriptions:            The original version 初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

#ifndef  __LED_H
#define  __LED_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
  LED 宏定义    LED引脚为PE10
*********************************************************************************************************/
#define LED_PORT                        PORTE                           /* 端口                         */
#define LED_PIN                         10                              /* 引脚序号                     */

#define LED_PCR                         PORTE_PCR10                     /* PCR寄存器                    */
#define LED_DDR                         GPIOE_PDDR                      /* 方向寄存器                   */
#define LED_DOR                         GPIOE_PDOR                      /* 数据输出寄存器               */
#define LED_CLR                         GPIOE_PCOR                      /* 清零寄存器                   */
#define LED_SET                         GPIOE_PSOR                      /* 置位寄存器                   */
#define LED_TOG                         GPIOE_PTOR                      /* 取反寄存器                   */
#define LED_SIM_SCGC5                   SIM_SCGC5_PORTE_MASK            /* 时钟使能掩码                 */

/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
void  ledInit(void);

void  ledOn(void);

void  ledOff(void);

void  ledTog(void);

void  ledBlink(INT32U  ulDly);

#ifdef __cplusplus
}
#endif

#endif

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
