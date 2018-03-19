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
** File name:               kinetis_k_spi_withoutfifo.c
** Last modified date:      2013-01-23
** Last version:            V1.0
** Descriptions:            spi ����FIFO������������
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Zhang xingchen
** Created date:            2013-01-15
** Version:                 V0.9
** Descriptions:            ��ʼ�汾
**--------------------------------------------------------------------------------------------------------
** Modified by:             Hong Haogao
** Modified date:           2013-01-23
** Version:                 V1.0
** Descriptions:            �޸Ĳ��ִ���
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#include "..\App\includes.h"

/*********************************************************************************************************
** Function name:           spiMsDelay
** Descriptions:            spi��ʱ����
** input parameters:        ulDly��ֵԽ����ʱԽ��
** output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created Date:            2013-01-23
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  spiMsDelay (INT32U  ulDly)
{
    volatile INT32U  i, j;

    for (i = 0; i < ulDly; i++) {
        for (j = 0; j < 500; j++) {
        }
    }
}


/**
  * @brief  д1�ֽ����ݵ�SPI����
  * @param  TxData д�����ߵ�����
  * @retval None
  */
void SPI_WriteByte(uint8_t TxData)
{                
//     while((SPI0_SR&SPI_I2S_FLAG_TXE)==0);   //�ȴ���������          
//     SPI1->DR=TxData;                                         //����һ��byte 
//     while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte  
//     SPI1->DR;        


    INT32U  ulTemp;
    
    while(!(SPI0_SR & SPI_SR_TFFF_MASK)) {                              /*  �ȴ����ͻ��������пռ�      */
    }
    
    ulTemp     = SPI0_PUSHR;
    ulTemp    &= ~SPI_PUSHR_TXDATA_MASK;
    ulTemp    |= SPI_PUSHR_TXDATA(TxData);                              /*  ��������                    */
    SPI0_PUSHR = ulTemp;
    
    while (!(SPI0_SR & SPI_SR_TCF_MASK)) {                              /*  �ȴ����ݷ������            */
    }    
    SPI0_SR  |= SPI_SR_TCF_MASK;
}
/**
  * @brief  ��SPI���߶�ȡ1�ֽ�����
  * @retval ����������
  */
uint8_t SPI_ReadByte(void)
{            
//     while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);   //�ȴ���������              
//     SPI1->DR=0xFF;                                               //����һ�������ݲ����������ݵ�ʱ�� 
//     while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //�ȴ�������һ��byte  
//     return SPI1->DR;                             

    INT32U ulTemp = 0;

    Send_Byte(0x00);                                                    /* �������ݣ�������ʱ��         */
    
    /* 
     *  ��������
     */
    while (!(SPI0_SR & SPI_SR_RFDF_MASK)) {
    }
    
    ulTemp    = SPI0_POPR;
    SPI0_SR  |= SPI_SR_RFDF_MASK;
    
    return ulTemp;                                                      /* ���ؽ��յ�������             */
}
/**
  * @brief  �����ٽ���
  * @retval None
  */
void SPI_CrisEnter(void)
{
    __set_PRIMASK(1);
}
/**
  * @brief  �˳��ٽ���
  * @retval None
  */
void SPI_CrisExit(void)
{
    __set_PRIMASK(0);
}
 
/**
  * @brief  Ƭѡ�ź�����͵�ƽ
  * @retval None
  */
void SPI_CS_Select(void)
{
	GPIOD_PCOR |= 1ul << 0;spiMsDelay(500);	
}
/**
  * @brief  Ƭѡ�ź�����ߵ�ƽ
  * @retval None
  */
void SPI_CS_Deselect(void)
{
  spiMsDelay(500);GPIOD_PSOR |= 1ul << 0;
}



/*********************************************************************************************************
** Function name:           spiPinInit
** Descriptions:            spi�ܽų�ʼ������
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              Hong Haogao
** Created Date:            2013-01-23
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  spiPinInit (void)
{
    SIM_SCGC5   |= SIM_SCGC5_PORTD_MASK;                                /* ʹ��PORTAʱ��                */
    
    /*
     *  PTA15->SCK; PTA16->SOUT; PTA17->SIN; PTA14->CS;
     */

    PORTD_PCR1 |= PORT_PCR_MUX(2);
    PORTD_PCR2 |= PORT_PCR_MUX(2);
    PORTD_PCR3 |= PORT_PCR_MUX(2);
    
    /*
     *  PTA14����Ϊ��ͨI/O����Ϊ������CS
     */

    PORTD_PCR0 |= PORT_PCR_MUX(1);                                     /* ����PTA14ΪGPIO����          */
    GPIOD_PSOR  |= 1 << 0;
    GPIOD_PDDR  |= 1 << 0;
}

/*********************************************************************************************************
** Function name:           spi0Init
** Descriptions:            spi0��ʼ��
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              Zhang xingchen
** Created Date:            2013-01-15
**--------------------------------------------------------------------------------------------------------
** Modified by:             Hong Haogao
** Modified date:           2013-01-23
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  spi0Init (void)
{
    spiPinInit();
    
    SIM_SCGC6   |= SIM_SCGC6_DSPI0_MASK;                                /* ʹ��DSPI0ʱ��                */
    
    SPI0_MCR    |= SPI_MCR_MSTR_MASK    |                               /* ѡ��SPI����ģʽ              */
                   SPI_MCR_DIS_TXF_MASK |                               /* ����TX FIFO                  */
                   SPI_MCR_DIS_RXF_MASK |                               /* ����RX FIFO                  */
                   SPI_MCR_ROOE_MASK;

    /*
     *  ����֡Ϊ8λ ����λ��ǰ
     *  Tcsc��Tasc��Tdt������Ĭ��ֵ
     */
    SPI0_CTAR0   &= ~SPI_CTAR_FMSZ_MASK;
    SPI0_CTAR0   |= SPI_CTAR_FMSZ(7) |
                    SPI_CTAR_PASC(3) |
                    SPI_CTAR_ASC(12);
    
    SPI0_CTAR0   |= SPI_CTAR_CPOL_MASK |                                /* POLY = 1; PHA = 1            */
                    SPI_CTAR_CPHA_MASK;
                      
    /*
     *  DBRΪ0��PBRΪ3��BRΪ32768
     *  SCK baud rate = (Fsys / PBR ) * [(1 + DBR) / BR]
     */
    SPI0_CTAR0   |= SPI_CTAR_PBR(1) |
                    SPI_CTAR_BR(1);

    /*
     * ʹ��SPI
     */
    SPI0_MCR    &= ~(SPI_MCR_MDIS_MASK |
                     SPI_MCR_HALT_MASK);
                     
    /*
     *  ����һ�������ݣ���ʹʱ���߱�Ϊ�ߵ�ƽ��ע���ʱCS = 1
     */
    Send_Byte(0xFF);
    spiMsDelay(100);
                     
}

/*********************************************************************************************************
** Function name:           Send_Byte
** Descriptions:            SPI����һ���ֽ�
** input parameters:        ucData������
** output parameters:       none
** Returned value:          none
** Created by:              Zhang xingchen
** Created Date:            2013-01-15
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  Send_Byte (INT8U ucData)
{
    INT32U  ulTemp;
    
    while(!(SPI0_SR & SPI_SR_TFFF_MASK)) {                              /*  �ȴ����ͻ��������пռ�      */
    }
    
    ulTemp     = SPI0_PUSHR;
    ulTemp    &= ~SPI_PUSHR_TXDATA_MASK;
    ulTemp    |= SPI_PUSHR_TXDATA(ucData);                              /*  ��������                    */
    SPI0_PUSHR = ulTemp;
    
    while (!(SPI0_SR & SPI_SR_TCF_MASK)) {                              /*  �ȴ����ݷ������            */
    }    
    SPI0_SR  |= SPI_SR_TCF_MASK;
}

/*********************************************************************************************************
** Function name:           Get_Byte
** Descriptions:            SPI��ȡһ���ֽ�
** input parameters:        none
** output parameters:       none
** Returned value:          ��ȡ������
** Created by:              Zhang xingchen
** Created Date:            2013-01-15
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT32U  Get_Byte (void)
{
    INT32U ulTemp = 0;

    Send_Byte(0x00);                                                    /* �������ݣ�������ʱ��         */
    
    /* 
     *  ��������
     */
    while (!(SPI0_SR & SPI_SR_RFDF_MASK)) {
    }
    
    ulTemp    = SPI0_POPR;
    SPI0_SR  |= SPI_SR_RFDF_MASK;
    
    return ulTemp;                                                      /* ���ؽ��յ�������             */
}

/*********************************************************************************************************
** Function name:           spiTxRxByte
** Descriptions:            SPI���Ͷ�ȡ����
** input parameters:        pucTxBuf����������ָ��
**                          pucRxBuf����������ָ��
**                          ucTxNum�� �������ݵĳ���
**                          ucRxNum�� �������ݵĳ���
** output parameters:       none
** Returned value:          none
** Created by:              Zhang xingchen
** Created Date:            2013-01-15
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void  spiTxRxByte (INT8U  *pucTxBuf, INT8U  ucTxNum,
                   INT8U  *pucRxBuf, INT8U  ucRxNum)
{
    volatile  INT8U  ucTmp = 0;                                         /* ���ڽ�����Ч������Ҫ������   */

    /*
     *  ������ջ������е�����
     *  ��֤���ջ���������Ϊ��Ч����
     */
    while ((SPI0_SR & SPI_SR_RFDF_MASK)) {                              /* �����Ƿ��� RDRF =1           */
        ucTmp     = SPI0_POPR;                                          /* ������ջ������е�����       */
        SPI0_SR  |= SPI_SR_RFDF_MASK;
    }
    
    while (ucTxNum--) {
        Send_Byte(*pucTxBuf++);                                         /* ����д����FIFO               */
    }
    
    /*
     *  ������ջ������е�����
     *  ��֤���ջ���������Ϊ��Ч����
     */
    while ((SPI0_SR & SPI_SR_RFDF_MASK)) {                              /* �����Ƿ��� RDRF =1           */
        ucTmp     = SPI0_POPR;                                          /* ������ջ������е�����       */
        SPI0_SR  |= SPI_SR_RFDF_MASK;
    }
    
    while (ucRxNum--) {
        *pucRxBuf++ = Get_Byte();
    }
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
