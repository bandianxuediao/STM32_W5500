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
** File name:               kinetis_k_system.h
** Last modified date:      2012-12-11
** Last version:            V1.0
** Description:             系统初始化
** 
**--------------------------------------------------------------------------------------------------------
** Created by:              Fan Linyun
** Created date:            2012-12-11
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

#ifndef __KINETIS_K_SYSTEM_H
#define __KINETIS_K_SYSTEM_H


#ifdef __cplusplus
extern "C"
{
#endif
    
/*********************************************************************************************************
    以下加“//”的注释为Keil4.53或以上版本支持的配置向导，在Keil（4.53或以上版本）下，可直接使用
    Configuration Wizard直接配置。使用其它开发环境可手动修改配置宏定义。
///<<< Use Configuration Wizard in Context Menu >>>
    配置向导开始
*********************************************************************************************************/


/*********************************************************************************************************
  Clock Configuration 时钟配置
*********************************************************************************************************/
//  <e0> Clock Configuration Enable
#define SYS_CLK_EN                          1                           /* 时钟配置使能情况: 0禁能 1使能*/
//      <e0> Main Clock Oscillation Enable
//          <o1> MOSC_FRQ: main clock oscillation frequency (pins EXTAL and XTAL)
//              <1000-80000000>
//          <e2> Add 2pF capacitor to the oscillator load
//          </e>
//          <e3> Add 4pF capacitor to the oscillator load
//          </e>
//          <e4> Add 8pF capacitor to the oscillator load
//          </e>
//          <e5> Add 16pF capacitor to the oscillator load
//          </e>
//      </e>
#define SYS_MOSC_EN                         1                           /* 主时钟使能情况 : 0禁能 1使能 */
#define SYS_MOSC_FRQ                        4000000                     /* 主时钟频率，单位 Hz          */
#define SYS_MOSC_2PF_EN                     0                           /* 增加2pF电容使能：0禁能 1使能 */
#define SYS_MOSC_4PF_EN                     0                           /* 增加4pF电容使能：0禁能 1使能 */
#define SYS_MOSC_8PF_EN                     0                           /* 增加8pF电容使能：0禁能 1使能 */
#define SYS_MOSC_16PF_EN                    0                           /* 增加16pF电容使能：0禁能 1使能*/

//      <e0> RTC Clock Oscillation Enable
//          <o1> RTC_FRQ: RTC clock oscillation frequency (pins EXTAL32 and XTAL32)
//              <20000-50000>
//          <e2> Add 2pF capacitor to the RTC load
//          </e>
//          <e3> Add 4pF capacitor to the RTC load
//          </e>
//          <e4> Add 8pF capacitor to the RTC load
//          </e>
//          <e5> Add 16pF capacitor to the RTC load
//          </e>
//      </e>
#define SYS_RTC_EN                          0                           /* 副时钟使能情况 : 0禁能 1使能 */
#define SYS_RTC_FRQ                         32768                       /* 副时钟频率，单位 Hz          */
#define SYS_RTC_2PF_EN                      0                           /* 增加2pF电容使能：0禁能 1使能 */
#define SYS_RTC_4PF_EN                      0                           /* 增加4pF电容使能：0禁能 1使能 */
#define SYS_RTC_8PF_EN                      0                           /* 增加8pF电容使能：0禁能 1使能 */
#define SYS_RTC_16PF_EN                     0                           /* 增加16pF电容使能：0禁能 1使能*/

//      <e0> FPLL_EN: FLL or PLL oscillation enable
//          <o1> FPLL_INPUT: FLL or PLL input clock
//              <0=> MOSC: main clock oscillation (pins EXTAL and XTAL)
//              <1=> RTC: RTC clock oscillation (pins EXTAL32 and XTAL32)
//              <2=> 4MIRC: internal 4MHz RC oscillator
//              <3=> 32KIRC: internal 32KHz RC oscillator
//          <o2> FPLL_FRQ: FLL or PLL output clock frequency
//              <24000000=> ~24MHz
//              <48000000=> ~48MHz
//              <50000000=> ~50MHz
//              <72000000=> ~72MHz
//              <96000000=> ~96MHz
//              <100000000=> ~100MHz
//              <120000000=> ~120MHz
//              <150000000=> ~150MHz
//      </e>
#define SYS_FPLL_EN                         1                           /* FPLL使能情况 : 0禁能 1使能   */
#define SYS_FPLL_INPUT                      0                           /* FLL or PLL时钟输入源选择     */
                                                                        /* 0: main OSC 主时钟，外部输入 */
                                                                        /* 1: RTC OSC RTC时钟，外部输入 */
                                                                        /* 2: 4MHz 内部RC               */
                                                                        /* 3: 32KHz 内部RC              */
#define SYS_FPLL_FRQ                        100000000                    /* FLL or PLL输出时钟           */

//      <h> Core clock configuration
//          <o0> MCGOUTCLK_INPUT: MCGOUTCLK (Core/System/Bus/FlexBus/Flash clock) input clock
//              <0=> MOSC: main clock oscillation (pins EXTAL and XTAL)
//              <1=> RTC: RTC clock oscillation (pins EXTAL32 and XTAL32)
//              <2=> 4MIRC: internal 4MHz RC oscillator
//              <3=> 32KIRC: internal 32KHz RC oscillator
//              <4=> FPLL: FLL or PLL output
//          <o1> CORE_DIV: Core/System clock's division
//              <0=> Core/System clock = MCGOUTCLK
//              <1=> Core/System clock = MCGOUTCLK / 2
//              <2=> Core/System clock = MCGOUTCLK / 3
//              <3=> Core/System clock = MCGOUTCLK / 4
//              <4=> Core/System clock = MCGOUTCLK / 5
//              <5=> Core/System clock = MCGOUTCLK / 6
//              <6=> Core/System clock = MCGOUTCLK / 7
//              <7=> Core/System clock = MCGOUTCLK / 8
//              <8=> Core/System clock = MCGOUTCLK / 9
//              <9=> Core/System clock = MCGOUTCLK / 10
//              <10=> Core/System clock = MCGOUTCLK / 11
//              <11=> Core/System clock = MCGOUTCLK / 12
//              <12=> Core/System clock = MCGOUTCLK / 13
//              <13=> Core/System clock = MCGOUTCLK / 14
//              <14=> Core/System clock = MCGOUTCLK / 15
//              <15=> Core/System clock = MCGOUTCLK / 16
//      </h>
#define SYS_MCGOUTCLK_INPUT                 4                           /* MCGOUTCLK_INPUT 时钟输入选择 */
                                                                        /* 0: main OSC 主时钟，外部输入 */
                                                                        /* 1: RTC OSC RTC时钟，外部输入 */
                                                                        /* 2: 4MHz 内部RC               */
                                                                        /* 3: 32KHz 内部RC              */
                                                                        /* 4: FLL or PLL输出时钟        */
#define SYS_CORE_DIV                        0                           /* Core/System clock分频系数    */
                                                                        /* n: 分频系数: n+1             */

//      <h> Bus clock input
//          <o0> BUS_DIV: Bus clock's division
//              <0=> Bus clock = MCGOUTCLK
//              <1=> Bus clock = MCGOUTCLK / 2
//              <2=> Bus clock = MCGOUTCLK / 3
//              <3=> Bus clock = MCGOUTCLK / 4
//              <4=> Bus clock = MCGOUTCLK / 5
//              <5=> Bus clock = MCGOUTCLK / 6
//              <6=> Bus clock = MCGOUTCLK / 7
//              <7=> Bus clock = MCGOUTCLK / 8
//              <8=> Bus clock = MCGOUTCLK / 9
//              <9=> Bus clock = MCGOUTCLK / 10
//              <10=> Bus clock = MCGOUTCLK / 11
//              <11=> Bus clock = MCGOUTCLK / 12
//              <12=> Bus clock = MCGOUTCLK / 13
//              <13=> Bus clock = MCGOUTCLK / 14
//              <14=> Bus clock = MCGOUTCLK / 15
//              <15=> Bus clock = MCGOUTCLK / 16
//      </h>
#define SYS_BUS_DIV                         1                           /* Bus clock 分频系数           */
                                                                        /* n: 分频系数: n+1             */
//      <h> FlexBus clock input
//          <o0> FLEXBUS_DIV: FlexBus clock's division
//              <0=> FlexBus clock = MCGOUTCLK
//              <1=> FlexBus clock = MCGOUTCLK / 2
//              <2=> FlexBus clock = MCGOUTCLK / 3
//              <3=> FlexBus clock = MCGOUTCLK / 4
//              <4=> FlexBus clock = MCGOUTCLK / 5
//              <5=> FlexBus clock = MCGOUTCLK / 6
//              <6=> FlexBus clock = MCGOUTCLK / 7
//              <7=> FlexBus clock = MCGOUTCLK / 8
//              <8=> FlexBus clock = MCGOUTCLK / 9
//              <9=> FlexBus clock = MCGOUTCLK / 10
//              <10=> FlexBus clock = MCGOUTCLK / 11
//              <11=> FlexBus clock = MCGOUTCLK / 12
//              <12=> FlexBus clock = MCGOUTCLK / 13
//              <13=> FlexBus clock = MCGOUTCLK / 14
//              <14=> FlexBus clock = MCGOUTCLK / 15
//              <15=> FlexBus clock = MCGOUTCLK / 16
//      </h>
#define SYS_FLEXBUS_DIV                     1                           /* FlexBus clock 分频系数       */
                                                                        /* n: 分频系数: n+1             */
//      <h> Flash clock input
//          <o0> FLASH_DIV: Flash clock's division
//              <0=> Flash clock = MCGOUTCLK
//              <1=> Flash clock = MCGOUTCLK / 2
//              <2=> Flash clock = MCGOUTCLK / 3
//              <3=> Flash clock = MCGOUTCLK / 4
//              <4=> Flash clock = MCGOUTCLK / 5
//              <5=> Flash clock = MCGOUTCLK / 6
//              <6=> Flash clock = MCGOUTCLK / 7
//              <7=> Flash clock = MCGOUTCLK / 8
//              <8=> Flash clock = MCGOUTCLK / 9
//              <9=> Flash clock = MCGOUTCLK / 10
//              <10=> Flash clock = MCGOUTCLK / 11
//              <11=> Flash clock = MCGOUTCLK / 12
//              <12=> Flash clock = MCGOUTCLK / 13
//              <13=> Flash clock = MCGOUTCLK / 14
//              <14=> Flash clock = MCGOUTCLK / 15
//              <15=> Flash clock = MCGOUTCLK / 16
//      </h>
#define SYS_FLASH_DIV                       3                           /* Flash clock 分频系数         */
                                                                        /* n: 分频系数: n+1             */



//      <e0> MCGIRCLK clock enable
//          <o1> MCGIRCLK_INPUT: MCGIRCLK input clock
//              <2=> 4MIRC: internal 4MHz RC oscillator
//              <3=> 32KIRC: internal 32KHz RC oscillator
//      </e>
#define SYS_MCGIRCLK_EN                     1                           /* MCGIRCLK时钟使能             */
#define SYS_MCGIRCLK_INPUT                  2                           /* MCGIRCLK时钟输入选择         */
                                                                        /* 2: 4MHz 内部RC               */
                                                                        /* 3: 32KHz 内部RC              */
//      <e0> OSCERCLK clock enable
//      </e>
#define SYS_OSCERCLK_EN                     1                           /* OSCERCLK时钟使能             */

//      <h> ERCLK32K clock input
//          <o0> ERCLK32K_INPUT: ERCLK32K input clock  
//              <0=> MOSC: main clock oscillation (pins EXTAL and XTAL)
//              <1=> RTC: RTC clock oscillation (pins EXTAL32 and XTAL32)
//      </h>
#define SYS_ERCLK32K_INPUT                  1                           /* ERCLK32K时钟输入选择         */
                                                                        /* 0: main OSC 主时钟，外部输入 */
                                                                        /* 1: RTC OSC RTC时钟，外部输入 */

// </e>


/*********************************************************************************************************
  WatchDog Configuration 硬件看门狗配置
*********************************************************************************************************/
//  <e0>  Watchdog enable
//  </e0>
#define SYS_WD_EN                           0                           /* 硬件特看门狗使能情况         */


/*********************************************************************************************************
///<<< end of configuration section >>>
    配置向导结束
*********************************************************************************************************/




/*********************************************************************************************************
  函数sysClkGet()输入参数的宏定义
*********************************************************************************************************/

#define SYS_CORE                            0                           /* Core clock        in Kinetis */
#define SYS_SYSTEM                          0                           /* System clock      in Kinetis */
#define SYS_BUS                             1                           /* Bus clock         in Kinetis */
#define SYS_FLEXBUS                         2                           /* FlexBus clock     in Kinetis */
#define SYS_FLASH                           3                           /* Flash clock       in Kinetis */
#define SYS_MCGIRCLK                        4                           /* MCGIRCLK clock    in Kinetis */
#define SYS_MCGFFCLK                        5                           /* MCGFFCLK clock    in Kinetis */
#define SYS_MCGFPLLCLK                      6                           /* FLL or PLL clock  in Kinetis */
#define SYS_OSCERCLK                        7                           /* OSCERCLK clock    in Kinetis */
#define SYS_ERCLK32K                        8                           /* ERCLK32K clock    in Kinetis */
#define SYS_LPO                             9                           /* LPO clock         in Kinetis */

#define SYS_CLK_KERN                        SYS_CORE                    /* 系统内核时钟                 */
#define SYS_CLK_PERI                        SYS_BUS                     /* Bus clock         in Kinetis */



/*********************************************************************************************************
  函数声明
*********************************************************************************************************/
void  sysInit(void);
INT32U  sysClkGet(INT32U  ulClk);



#ifdef __cplusplus
}
#endif

#endif                                                                  /* __KINETIS_K_SYSTEM_H         */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
