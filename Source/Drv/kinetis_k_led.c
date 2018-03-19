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
** File name:               Led.c
** Last modified date:      2012-12-12
** Last version:            V1.0
** Description:             LED�����ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Hong Haogao
** Created date:            2012-12-12
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
#include "..\App\Includes.h"

/*********************************************************************************************************
** Function name:           ledInit
** Descriptions:            LED ��ʼ��
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created date:            2012-12-12
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  ledInit (void)
{
    SIM_SCGC5  |= LED_SIM_SCGC5;                                        /* ʹ�ܶ˿�ʱ��                 */
    
    LED_PCR     = PORT_PCR_MUX(1);                                      /* ��������ΪGPIO����           */
    LED_DOR    &= ~(1ul << LED_PIN);                                    /* LED��                        */ 
    LED_DDR    |= 1ul << LED_PIN;                                       /* ����LED����Ϊ�������        */
}

/*********************************************************************************************************
** Function name:           ledOn
** Descriptions:            ��LED���� 
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created date:            2012-12-12
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void   ledOn (void)
{
    LED_SET = 1ul << LED_PIN;
}

/*********************************************************************************************************
** Function name:           ledOff
** Descriptions:            �ر�LED����
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created date:            2012-12-12
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  ledOff (void)
{
    LED_CLR = 1ul << LED_PIN;
}

/*********************************************************************************************************
** Function name:           ledTog
** Descriptions:            LED״̬ȡ������
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created date:            2012-12-12
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  ledTog (void)
{
    LED_TOG = 1ul << LED_PIN;
}

/*********************************************************************************************************
** Function name:           ledBlink
** Descriptions:            LED������˸����
** Input parameters:        ulDly����˸������ֵԽ����˸Խ��
** Output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created date:            2013-01-10
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  ledBlink (INT32U  ulDly)
{
    volatile INT32U  i, j;
    
    while (1) {
        for (i = 0; i < ulDly; i++) {
            for (j = 0; j < 500; j++) {
            }
        }
        ledTog();
    };
}

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/