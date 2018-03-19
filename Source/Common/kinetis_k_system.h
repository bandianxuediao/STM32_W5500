/*********************************************Copyright (c)***********************************************
**                                Guangzhou ZLG MCU Technology Co., Ltd.
**
**                                        http://www.zlgmcu.com
**
**      ������������Ƭ���Ƽ����޹�˾���ṩ�����з�������ּ��Э���ͻ����ٲ�Ʒ���з����ȣ��ڷ�����������ṩ
**  ���κγ����ĵ������Խ����������֧�ֵ����Ϻ���Ϣ���������ο����ͻ���Ȩ��ʹ�û����вο��޸ģ�����˾��
**  �ṩ�κε������ԡ��ɿ��Եȱ�֤�����ڿͻ�ʹ�ù��������κ�ԭ����ɵ��ر�ġ�żȻ�Ļ��ӵ���ʧ������˾��
**  �е��κ����Ρ�
**                                                                        ����������������Ƭ���Ƽ����޹�˾
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               kinetis_k_system.h
** Last modified date:      2012-12-11
** Last version:            V1.0
** Description:             ϵͳ��ʼ��
** 
**--------------------------------------------------------------------------------------------------------
** Created by:              Fan Linyun
** Created date:            2012-12-11
** Version:                 V1.0
** Descriptions:            The original version ��ʼ�汾
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
    ���¼ӡ�//����ע��ΪKeil4.53�����ϰ汾֧�ֵ������򵼣���Keil��4.53�����ϰ汾���£���ֱ��ʹ��
    Configuration Wizardֱ�����á�ʹ�����������������ֶ��޸����ú궨�塣
///<<< Use Configuration Wizard in Context Menu >>>
    �����򵼿�ʼ
*********************************************************************************************************/


/*********************************************************************************************************
  Clock Configuration ʱ������
*********************************************************************************************************/
//  <e0> Clock Configuration Enable
#define SYS_CLK_EN                          1                           /* ʱ������ʹ�����: 0���� 1ʹ��*/
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
#define SYS_MOSC_EN                         1                           /* ��ʱ��ʹ����� : 0���� 1ʹ�� */
#define SYS_MOSC_FRQ                        4000000                     /* ��ʱ��Ƶ�ʣ���λ Hz          */
#define SYS_MOSC_2PF_EN                     0                           /* ����2pF����ʹ�ܣ�0���� 1ʹ�� */
#define SYS_MOSC_4PF_EN                     0                           /* ����4pF����ʹ�ܣ�0���� 1ʹ�� */
#define SYS_MOSC_8PF_EN                     0                           /* ����8pF����ʹ�ܣ�0���� 1ʹ�� */
#define SYS_MOSC_16PF_EN                    0                           /* ����16pF����ʹ�ܣ�0���� 1ʹ��*/

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
#define SYS_RTC_EN                          0                           /* ��ʱ��ʹ����� : 0���� 1ʹ�� */
#define SYS_RTC_FRQ                         32768                       /* ��ʱ��Ƶ�ʣ���λ Hz          */
#define SYS_RTC_2PF_EN                      0                           /* ����2pF����ʹ�ܣ�0���� 1ʹ�� */
#define SYS_RTC_4PF_EN                      0                           /* ����4pF����ʹ�ܣ�0���� 1ʹ�� */
#define SYS_RTC_8PF_EN                      0                           /* ����8pF����ʹ�ܣ�0���� 1ʹ�� */
#define SYS_RTC_16PF_EN                     0                           /* ����16pF����ʹ�ܣ�0���� 1ʹ��*/

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
#define SYS_FPLL_EN                         1                           /* FPLLʹ����� : 0���� 1ʹ��   */
#define SYS_FPLL_INPUT                      0                           /* FLL or PLLʱ������Դѡ��     */
                                                                        /* 0: main OSC ��ʱ�ӣ��ⲿ���� */
                                                                        /* 1: RTC OSC RTCʱ�ӣ��ⲿ���� */
                                                                        /* 2: 4MHz �ڲ�RC               */
                                                                        /* 3: 32KHz �ڲ�RC              */
#define SYS_FPLL_FRQ                        100000000                    /* FLL or PLL���ʱ��           */

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
#define SYS_MCGOUTCLK_INPUT                 4                           /* MCGOUTCLK_INPUT ʱ������ѡ�� */
                                                                        /* 0: main OSC ��ʱ�ӣ��ⲿ���� */
                                                                        /* 1: RTC OSC RTCʱ�ӣ��ⲿ���� */
                                                                        /* 2: 4MHz �ڲ�RC               */
                                                                        /* 3: 32KHz �ڲ�RC              */
                                                                        /* 4: FLL or PLL���ʱ��        */
#define SYS_CORE_DIV                        0                           /* Core/System clock��Ƶϵ��    */
                                                                        /* n: ��Ƶϵ��: n+1             */

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
#define SYS_BUS_DIV                         1                           /* Bus clock ��Ƶϵ��           */
                                                                        /* n: ��Ƶϵ��: n+1             */
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
#define SYS_FLEXBUS_DIV                     1                           /* FlexBus clock ��Ƶϵ��       */
                                                                        /* n: ��Ƶϵ��: n+1             */
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
#define SYS_FLASH_DIV                       3                           /* Flash clock ��Ƶϵ��         */
                                                                        /* n: ��Ƶϵ��: n+1             */



//      <e0> MCGIRCLK clock enable
//          <o1> MCGIRCLK_INPUT: MCGIRCLK input clock
//              <2=> 4MIRC: internal 4MHz RC oscillator
//              <3=> 32KIRC: internal 32KHz RC oscillator
//      </e>
#define SYS_MCGIRCLK_EN                     1                           /* MCGIRCLKʱ��ʹ��             */
#define SYS_MCGIRCLK_INPUT                  2                           /* MCGIRCLKʱ������ѡ��         */
                                                                        /* 2: 4MHz �ڲ�RC               */
                                                                        /* 3: 32KHz �ڲ�RC              */
//      <e0> OSCERCLK clock enable
//      </e>
#define SYS_OSCERCLK_EN                     1                           /* OSCERCLKʱ��ʹ��             */

//      <h> ERCLK32K clock input
//          <o0> ERCLK32K_INPUT: ERCLK32K input clock  
//              <0=> MOSC: main clock oscillation (pins EXTAL and XTAL)
//              <1=> RTC: RTC clock oscillation (pins EXTAL32 and XTAL32)
//      </h>
#define SYS_ERCLK32K_INPUT                  1                           /* ERCLK32Kʱ������ѡ��         */
                                                                        /* 0: main OSC ��ʱ�ӣ��ⲿ���� */
                                                                        /* 1: RTC OSC RTCʱ�ӣ��ⲿ���� */

// </e>


/*********************************************************************************************************
  WatchDog Configuration Ӳ�����Ź�����
*********************************************************************************************************/
//  <e0>  Watchdog enable
//  </e0>
#define SYS_WD_EN                           0                           /* Ӳ���ؿ��Ź�ʹ�����         */


/*********************************************************************************************************
///<<< end of configuration section >>>
    �����򵼽���
*********************************************************************************************************/




/*********************************************************************************************************
  ����sysClkGet()��������ĺ궨��
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

#define SYS_CLK_KERN                        SYS_CORE                    /* ϵͳ�ں�ʱ��                 */
#define SYS_CLK_PERI                        SYS_BUS                     /* Bus clock         in Kinetis */



/*********************************************************************************************************
  ��������
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
