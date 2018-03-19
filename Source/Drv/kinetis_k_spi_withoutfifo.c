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
** File name:               kinetis_k_spi_withoutfifo.c
** Last modified date:      2013-01-23
** Last version:            V1.0
** Descriptions:            spi 不带FIFO操作驱动程序
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Zhang xingchen
** Created date:            2013-01-15
** Version:                 V0.9
** Descriptions:            初始版本
**--------------------------------------------------------------------------------------------------------
** Modified by:             Hong Haogao
** Modified date:           2013-01-23
** Version:                 V1.0
** Descriptions:            修改部分代码
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
** Descriptions:            spi延时函数
** input parameters:        ulDly：值越大延时越长
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
  * @brief  写1字节数据到SPI总线
  * @param  TxData 写到总线的数据
  * @retval None
  */
void SPI_WriteByte(uint8_t TxData)
{                
//     while((SPI0_SR&SPI_I2S_FLAG_TXE)==0);   //等待发送区空          
//     SPI1->DR=TxData;                                         //发送一个byte 
//     while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
//     SPI1->DR;        


    INT32U  ulTemp;
    
    while(!(SPI0_SR & SPI_SR_TFFF_MASK)) {                              /*  等待发送缓冲区中有空间      */
    }
    
    ulTemp     = SPI0_PUSHR;
    ulTemp    &= ~SPI_PUSHR_TXDATA_MASK;
    ulTemp    |= SPI_PUSHR_TXDATA(TxData);                              /*  发送数据                    */
    SPI0_PUSHR = ulTemp;
    
    while (!(SPI0_SR & SPI_SR_TCF_MASK)) {                              /*  等待数据发送完毕            */
    }    
    SPI0_SR  |= SPI_SR_TCF_MASK;
}
/**
  * @brief  从SPI总线读取1字节数据
  * @retval 读到的数据
  */
uint8_t SPI_ReadByte(void)
{            
//     while((SPI1->SR&SPI_I2S_FLAG_TXE)==0);   //等待发送区空              
//     SPI1->DR=0xFF;                                               //发送一个空数据产生输入数据的时钟 
//     while((SPI1->SR&SPI_I2S_FLAG_RXNE)==0); //等待接收完一个byte  
//     return SPI1->DR;                             

    INT32U ulTemp = 0;

    Send_Byte(0x00);                                                    /* 发送数据，以启动时钟         */
    
    /* 
     *  接收数据
     */
    while (!(SPI0_SR & SPI_SR_RFDF_MASK)) {
    }
    
    ulTemp    = SPI0_POPR;
    SPI0_SR  |= SPI_SR_RFDF_MASK;
    
    return ulTemp;                                                      /* 返回接收到的数据             */
}
/**
  * @brief  进入临界区
  * @retval None
  */
void SPI_CrisEnter(void)
{
    __set_PRIMASK(1);
}
/**
  * @brief  退出临界区
  * @retval None
  */
void SPI_CrisExit(void)
{
    __set_PRIMASK(0);
}
 
/**
  * @brief  片选信号输出低电平
  * @retval None
  */
void SPI_CS_Select(void)
{
	GPIOD_PCOR |= 1ul << 0;spiMsDelay(500);	
}
/**
  * @brief  片选信号输出高电平
  * @retval None
  */
void SPI_CS_Deselect(void)
{
  spiMsDelay(500);GPIOD_PSOR |= 1ul << 0;
}



/*********************************************************************************************************
** Function name:           spiPinInit
** Descriptions:            spi管脚初始化函数
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
    SIM_SCGC5   |= SIM_SCGC5_PORTD_MASK;                                /* 使能PORTA时钟                */
    
    /*
     *  PTA15->SCK; PTA16->SOUT; PTA17->SIN; PTA14->CS;
     */

    PORTD_PCR1 |= PORT_PCR_MUX(2);
    PORTD_PCR2 |= PORT_PCR_MUX(2);
    PORTD_PCR3 |= PORT_PCR_MUX(2);
    
    /*
     *  PTA14配置为普通I/O，作为主机的CS
     */

    PORTD_PCR0 |= PORT_PCR_MUX(1);                                     /* 设置PTA14为GPIO功能          */
    GPIOD_PSOR  |= 1 << 0;
    GPIOD_PDDR  |= 1 << 0;
}

/*********************************************************************************************************
** Function name:           spi0Init
** Descriptions:            spi0初始化
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
    
    SIM_SCGC6   |= SIM_SCGC6_DSPI0_MASK;                                /* 使能DSPI0时钟                */
    
    SPI0_MCR    |= SPI_MCR_MSTR_MASK    |                               /* 选择SPI主机模式              */
                   SPI_MCR_DIS_TXF_MASK |                               /* 禁能TX FIFO                  */
                   SPI_MCR_DIS_RXF_MASK |                               /* 禁能RX FIFO                  */
                   SPI_MCR_ROOE_MASK;

    /*
     *  数据帧为8位 ，高位在前
     *  Tcsc、Tasc、Tdt均采用默认值
     */
    SPI0_CTAR0   &= ~SPI_CTAR_FMSZ_MASK;
    SPI0_CTAR0   |= SPI_CTAR_FMSZ(7) |
                    SPI_CTAR_PASC(3) |
                    SPI_CTAR_ASC(12);
    
    SPI0_CTAR0   |= SPI_CTAR_CPOL_MASK |                                /* POLY = 1; PHA = 1            */
                    SPI_CTAR_CPHA_MASK;
                      
    /*
     *  DBR为0，PBR为3，BR为32768
     *  SCK baud rate = (Fsys / PBR ) * [(1 + DBR) / BR]
     */
    SPI0_CTAR0   |= SPI_CTAR_PBR(1) |
                    SPI_CTAR_BR(1);

    /*
     * 使能SPI
     */
    SPI0_MCR    &= ~(SPI_MCR_MDIS_MASK |
                     SPI_MCR_HALT_MASK);
                     
    /*
     *  发送一个空数据，以使时钟线变为高电平，注意此时CS = 1
     */
    Send_Byte(0xFF);
    spiMsDelay(100);
                     
}

/*********************************************************************************************************
** Function name:           Send_Byte
** Descriptions:            SPI发送一个字节
** input parameters:        ucData：数据
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
    
    while(!(SPI0_SR & SPI_SR_TFFF_MASK)) {                              /*  等待发送缓冲区中有空间      */
    }
    
    ulTemp     = SPI0_PUSHR;
    ulTemp    &= ~SPI_PUSHR_TXDATA_MASK;
    ulTemp    |= SPI_PUSHR_TXDATA(ucData);                              /*  发送数据                    */
    SPI0_PUSHR = ulTemp;
    
    while (!(SPI0_SR & SPI_SR_TCF_MASK)) {                              /*  等待数据发送完毕            */
    }    
    SPI0_SR  |= SPI_SR_TCF_MASK;
}

/*********************************************************************************************************
** Function name:           Get_Byte
** Descriptions:            SPI获取一个字节
** input parameters:        none
** output parameters:       none
** Returned value:          读取的数据
** Created by:              Zhang xingchen
** Created Date:            2013-01-15
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT32U  Get_Byte (void)
{
    INT32U ulTemp = 0;

    Send_Byte(0x00);                                                    /* 发送数据，以启动时钟         */
    
    /* 
     *  接收数据
     */
    while (!(SPI0_SR & SPI_SR_RFDF_MASK)) {
    }
    
    ulTemp    = SPI0_POPR;
    SPI0_SR  |= SPI_SR_RFDF_MASK;
    
    return ulTemp;                                                      /* 返回接收到的数据             */
}

/*********************************************************************************************************
** Function name:           spiTxRxByte
** Descriptions:            SPI发送读取数据
** input parameters:        pucTxBuf：发送数据指针
**                          pucRxBuf：接收数据指针
**                          ucTxNum： 发送数据的长度
**                          ucRxNum： 接收数据的长度
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
    volatile  INT8U  ucTmp = 0;                                         /* 用于接收无效（不需要）数据   */

    /*
     *  清除接收缓冲区中的数据
     *  保证接收缓冲区数据为有效数据
     */
    while ((SPI0_SR & SPI_SR_RFDF_MASK)) {                              /* 接收是否满 RDRF =1           */
        ucTmp     = SPI0_POPR;                                          /* 清除接收缓冲区中的数据       */
        SPI0_SR  |= SPI_SR_RFDF_MASK;
    }
    
    while (ucTxNum--) {
        Send_Byte(*pucTxBuf++);                                         /* 连续写发送FIFO               */
    }
    
    /*
     *  清除接收缓冲区中的数据
     *  保证接收缓冲区数据为有效数据
     */
    while ((SPI0_SR & SPI_SR_RFDF_MASK)) {                              /* 接收是否满 RDRF =1           */
        ucTmp     = SPI0_POPR;                                          /* 清除接收缓冲区中的数据       */
        SPI0_SR  |= SPI_SR_RFDF_MASK;
    }
    
    while (ucRxNum--) {
        *pucRxBuf++ = Get_Byte();
    }
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
