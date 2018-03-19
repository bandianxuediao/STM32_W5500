#include "..\App\includes.h"

/*********************************************************************************************************
** 用户接口层
** 以下函数在移植时无需修改
*********************************************************************************************************/


/*********************************************************************************************************
** Function name:           mx25L1606Read
** Descriptions:            MX25L1606的读函数,可选择读ID和读数据操作,
**                          若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
** Input parameters:        
**                          ulDst：         目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
**                          ulNByte:        要读取的数据字节数
**                          pucRcvBuf:      接收缓存的指针
** Output parameters:       none
** Returned value:          操作成功则返回MX_OK,失败则返回MX_ERROR
** Created by:              Xiao Jianhao
** Created date:            2012-07-17
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  mx25L1606Read (INT32U  ulDst,
                      INT8U*  pucRcvBuf,
                      INT32U  ulNByte)
{
    INT8U  ucTxBuf[6] ={0};

    if ((ulDst+ulNByte > MAX_ADDR)||(ulNByte == 0)) {
        return (MX_ERROR);                                              /*  检查入口参数                */
    }
    
    ucTxBuf[0] = 0x0B;                                                  /* 发送快速读命令               */
    ucTxBuf[1] = (INT8U)((ulDst & 0xFFFFFF) >> 16);                     /* 发送地址信息:该地址为3个字节 */
    ucTxBuf[2] = (INT8U)((ulDst & 0xFFFFFF) >> 8);                      /* 发送地址信息:该地址为3个字节 */
    ucTxBuf[3] = (INT8U)(ulDst & 0xFF);                                 /* 发送地址信息:该地址为3个字节 */
    ucTxBuf[4] = 0xFF;                                                  /* 发送一个哑字节以读取数据     */


    SPI_CS_LOW();                                                       /*  CS置为低电平，使能SPI通信   */

    /* 
     *  根据快速读命令的时序读取数据
     */
    spiTxRxByte(ucTxBuf, 5, pucRcvBuf, ulNByte);                        /* 发送命令和地址，读取数据     */

    SPI_CS_HIGH();                                                      /*  CS置为高电平，禁能SPI通信   */

    return (MX_OK);
}

/*********************************************************************************************************
** Function name:           mx25L1606ReadID
** Descriptions:            MX25L1606的读ID函数,可选择读ID和读数据操作
**                          若填入的参数不符合要求，则返回MX_ERROR
** Input parameters:        
**                          eIDType:        ID类型。用户可在Jedec_ID,Dev_ID,Manu_ID三者里选择
**                          pulRcvBuf:      存储ID变量的指针
** Output parameters:       none
** Returned value:          操作成功则返回MX_OK,失败则返回MX_ERROR
** Created by:              Xiao Jianhao
** Created date:            2012-07-17
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  mx25L1606ReadID (IDTYPE  eIDType, INT32U*  pulRcvBuf)
{
    INT8U   ucTxBuf[10] ={0}, ucRxBuf[10] ={0};

    if (eIDType == Jedec_ID) {
        ucTxBuf[0] = 0x9F;                                              /* 发送读JEDEC ID命令(9Fh)      */

        SPI_CS_LOW();                                                   /*  CS置为低电平，使能SPI通信   */

        /* 
         *  根据快速读命令的时序读取数据
         */
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 3);                            /* 发送命令，接收数据           */

        SPI_CS_HIGH();                                                  /*  CS置为高电平，禁能SPI通信   */

        /*
         *  获取ID值
         *  在本例中,*pulRcvBuf的值为0x00c22015
         */
        *pulRcvBuf = ((ucRxBuf[0] << 16)
                    | (ucRxBuf[1] <<  8)
                    | (ucRxBuf[2]));

        return (MX_OK);
    }
    
    if ((eIDType == Manu_ID) || (eIDType == Dev_ID) ) {
        ucTxBuf[0] = 0x90;                                              /* 发送读ID命令(90H or EFH)     */
        ucTxBuf[1] = 0x00;                                              /* 发送地址                     */
        ucTxBuf[2] = 0x00;                                              /* 发送地址                     */
        ucTxBuf[3] = eIDType;                                           /* 发送地址 - 不是00H就是01H    */
        
        SPI_CS_LOW();                                                   /*  CS置为低电平，使能SPI通信   */

        /* 
         *  根据快速读命令的时序读取数据
         */
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 3);                            /* 发送命令，接收数据           */

        SPI_CS_HIGH();                                                  /*  CS置为高电平，禁能SPI通信   */
        
        /*
         *  获取ID值
         */
        *pulRcvBuf = ((ucRxBuf[0] << 16)
                    | (ucRxBuf[1] <<  8)
                    | (ucRxBuf[2]));

        return (MX_OK);

    } else {
        return (MX_ERROR);
    }
}

/*********************************************************************************************************
** Function name:           mx25L1606Write
** Descriptions:            MX25L1606的写函数，可写1个和多个数据到指定地址
**                          若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
** Input parameters:        
**                          ulDst：         目标地址,范围 0x0 - MAX_ADDR（MAX_ADDR = 0x1FFFFF）
**                          pucSendbuf:     发送缓存区指针
**                          ulNByte:        要写的数据字节数
** Output parameters:       none
** Returned value:          操作成功则返回MX_OK,失败则返回MX_ERROR
** Created by:              Xiao Jianhao
** Created date:            2012-07-17
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
INT8U  mx25L1606Write (INT32U  ulDst,
                       INT8U*  pucSendbuf,
                       INT32U  ulNByte)
{
    INT32U  ulTmp = 0, i = 0, ulStatRgVal = 0;
    INT8U   ucTxBuf[6] ={0}, ucRxBuf[6] ={0};

    if (( (ulDst+ulNByte-1 > MAX_ADDR)||(ulNByte == 0) )) {
        return (MX_ERROR);                                              /*  检查入口参数                */
    }

    ucTxBuf[0] = 0x05;                                                  /* 发送读状态寄存器命令         */
    SPI_CS_LOW();                                                       /*  CS置为低电平，使能SPI通信   */
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();                                                      /*  CS置为高电平，禁能SPI通信   */
    ulTmp = ucRxBuf[0];

    ucTxBuf[0] = 0x01;                                                  /* 发送写状态寄存器指令         */
    ucTxBuf[1] = 0;                                                     /* 清0BPx位，使Flash芯片全区可写*/
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();
    
    for(i = 0; i < ulNByte; i++) {

        ucTxBuf[0] = 0x06;                                              /* 发送写使能命令               */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        ucTxBuf[0] = 0x02;                                              /* 发送页编程命令               */
        ucTxBuf[1] = (((ulDst+i) & 0xFFFFFF) >> 16);                    /* 发送3个字节的地址信息        */
        ucTxBuf[2] = (((ulDst+i) & 0xFFFFFF) >>  8);
        ucTxBuf[3] = (((ulDst+i) & 0xFF));
        ucTxBuf[4] = (pucSendbuf[i]);
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 5, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* 发送读状态寄存器命令         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* 发送命令，接收数据           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];                                   /* 保存读得的状态寄存器值       */
        } while (ulStatRgVal == 0x03);                                  /* 一直等待，直到芯片空闲       */
    }

    ucTxBuf[0] = 0x06;                                                  /* 发送写使能命令               */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();

    ucTxBuf[0] = 0x01;                                                  /* 发送写状态寄存器指令         */
    ucTxBuf[1] = ulTmp;                                                 /* 恢复状态寄存器设置信息       */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();
    
    return (MX_OK);
}

/*********************************************************************************************************
** Function name:           mx25L1606Erase
** Descriptions:            根据指定的扇区号选取最高效的算法擦除
**                          若某功能下,某一入口参数无效,可在该入口参数处填Invalid，该参数将被忽略
** Input parameters:        
**                          ulsec1：起始扇区号,范围(0~511)
**                          ulsec2：终止扇区号,范围(0~511)
** Output parameters:       none
** Returned value:          操作成功则返回MX_OK,失败则返回MX_ERROR        
*********************************************************************************************************/
INT8U  mx25L1606Erase (INT32U  ulsec1, INT32U  ulsec2)
{
    INT8U   ulTmp1 = 0, ulTmp2 = 0, ulStatRgVal = 0;
    INT32U  ulSecnHdAddr = 0;
    INT32U  ulNoSecsToEr = 0;                                           /* 要擦除的扇区数目             */
    INT32U  ulCurSecToEr = 0;                                           /* 当前要擦除的扇区号           */
    INT8U   ucTxBuf[6] ={0}, ucRxBuf[6] ={0};

    /*
    *  检查入口参数
    */
    if ((ulsec1 > SEC_MAX)||(ulsec2 > SEC_MAX)) {
        return (MX_ERROR);
    }
    
    ucTxBuf[0] = 0x05;                                                  /* 发送读状态寄存器命令         */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();
    ulTmp1 = ucRxBuf[0];                                                /* 保存读得的状态寄存器值       */
    
    ucTxBuf[0] = 0x01;                                                  /* 发送写状态寄存器指令         */
    ucTxBuf[1] = 0;                                                     /* 清0BPx位，使Flash芯片全区可写*/
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();
    
    ucTxBuf[0] = 0x06;                                                  /* 发送写使能命令               */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();
    
    /*
    * 如果用户输入的起始扇区号大于终止扇区号，则在内部作出调整
    */
    if (ulsec1 > ulsec2) {
        ulTmp2 = ulsec1;
        ulsec1  = ulsec2;
        ulsec2  = ulTmp2;
    }

    /*
    * 若起止扇区号相等则擦除单个扇区
    */
    if (ulsec1 == ulsec2) {
        ulSecnHdAddr = SEC_SIZE * ulsec1;                               /* 计算扇区的起始地址           */
        
        ucTxBuf[0] = 0x20;                                              /* 发送扇区擦除指令             */
        ucTxBuf[1] = ((ulSecnHdAddr & 0xFFFFFF) >> 16);                 /* 发送3个字节的地址信息        */
        ucTxBuf[2] = ((ulSecnHdAddr & 0xFFFF) >> 8);
        ucTxBuf[3] = ulSecnHdAddr & 0xFF;

        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();

        do {
            ucTxBuf[0] = 0x05;                                          /* 发送读状态寄存器命令         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* 发送命令，接收数据           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];                                   /* 保存读得的状态寄存器值       */
        } while (ulStatRgVal & 0x01);                                   /* 一直等待，直到芯片空闲       */
        
        return (MX_OK);
    }
    
    /*
    * 根据起始扇区和终止扇区间距调用最快速的擦除功能
    */
    
    if (ulsec2 - ulsec1 == SEC_MAX) {
        ucTxBuf[0] = 0x60;                                              /* 发送芯片擦除指令(60h or C7h) */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* 发送读状态寄存器命令         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* 发送命令，接收数据           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];                                   /* 保存读得的状态寄存器值       */
        } while (ulStatRgVal & 0x01);                                   /* 一直等待，直到芯片空闲       */
        return (MX_OK);
    }
    
    ulNoSecsToEr = ulsec2 - ulsec1 + 1;                                 /* 获取要擦除的扇区数目         */
    ulCurSecToEr  = ulsec1;                                             /* 从起始扇区开始擦除           */
    
    /*
    * 若两个扇区之间的间隔够大，则采取16扇区擦除算法
    */
    while (ulNoSecsToEr >= 16) {
        ucTxBuf[0] = 0x06;                                              /* 发送允许写命令               */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        ulSecnHdAddr = SEC_SIZE * ulCurSecToEr;                         /* 计算扇区的起始地址           */

        ucTxBuf[0] = 0xD8;                                              /* 发送64KB块擦除指令           */
        ucTxBuf[1] = ((ulSecnHdAddr & 0xFFFFFF) >> 16);                 /* 发送3个字节的地址信息        */
        ucTxBuf[2] = ((ulSecnHdAddr & 0xFFFFFF) >>  8);
        ucTxBuf[3] = ulSecnHdAddr & 0xFF;
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* 发送读状态寄存器命令         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* 发送命令，接收数据           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];
        } while (ulStatRgVal & 0x01);                                   /* 一直等待，直到芯片空闲       */
        
        ulCurSecToEr  += 16;                                            /* 计算擦除了16个扇区后和擦除区 */
                                                                        /* 域相邻的待擦除扇区号         */
        ulNoSecsToEr -=  16;                                            /* 对需擦除的扇区总数作出调整   */
    }
    
    /*
    * 采用扇区擦除算法擦除剩余的扇区
    */
    while (ulNoSecsToEr >= 1) {
        ucTxBuf[0] = 0x06;                                              /* 发送允许写命令               */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        ulSecnHdAddr = SEC_SIZE * ulCurSecToEr;                         /* 计算扇区的起始地址           */

        ucTxBuf[0] = 0x20;                                              /* 发送扇区擦除指令             */
        ucTxBuf[1] = ((ulSecnHdAddr & 0xFFFFFF) >> 16);                 /* 发送3个字节的地址信息        */
        ucTxBuf[2] = ((ulSecnHdAddr & 0xFFFFFF) >>  8);
        ucTxBuf[3] = ulSecnHdAddr & 0xFF;

        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 0);                            /* 发送命令，接收数据           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* 发送读状态寄存器命令         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* 发送命令，接收数据           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];
        } while (ulStatRgVal & 0x01 );                                  /* 一直等待，直到芯片空闲       */
    
        ulCurSecToEr += 1;
        ulNoSecsToEr -= 1;
    }

    /*
    * 擦除结束,恢复状态寄存器信息
    */
    ucTxBuf[0] = 0x06;                                                  /* 发送写使能命令               */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();

    ucTxBuf[0] = 0x01;                                                  /* 发送写状态寄存器指令         */
    ucTxBuf[1] = ulTmp1;                                                /* 恢复状态寄存器设置信息       */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* 发送命令，接收数据           */
    SPI_CS_HIGH();

    return (MX_OK);
}

/*********************************************************************************************************
** End File
*********************************************************************************************************/
