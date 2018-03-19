#include "..\App\includes.h"

/*********************************************************************************************************
** �û��ӿڲ�
** ���º�������ֲʱ�����޸�
*********************************************************************************************************/


/*********************************************************************************************************
** Function name:           mx25L1606Read
** Descriptions:            MX25L1606�Ķ�����,��ѡ���ID�Ͷ����ݲ���,
**                          ��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
** Input parameters:        
**                          ulDst��         Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��
**                          ulNByte:        Ҫ��ȡ�������ֽ���
**                          pucRcvBuf:      ���ջ����ָ��
** Output parameters:       none
** Returned value:          �����ɹ��򷵻�MX_OK,ʧ���򷵻�MX_ERROR
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
        return (MX_ERROR);                                              /*  �����ڲ���                */
    }
    
    ucTxBuf[0] = 0x0B;                                                  /* ���Ϳ��ٶ�����               */
    ucTxBuf[1] = (INT8U)((ulDst & 0xFFFFFF) >> 16);                     /* ���͵�ַ��Ϣ:�õ�ַΪ3���ֽ� */
    ucTxBuf[2] = (INT8U)((ulDst & 0xFFFFFF) >> 8);                      /* ���͵�ַ��Ϣ:�õ�ַΪ3���ֽ� */
    ucTxBuf[3] = (INT8U)(ulDst & 0xFF);                                 /* ���͵�ַ��Ϣ:�õ�ַΪ3���ֽ� */
    ucTxBuf[4] = 0xFF;                                                  /* ����һ�����ֽ��Զ�ȡ����     */


    SPI_CS_LOW();                                                       /*  CS��Ϊ�͵�ƽ��ʹ��SPIͨ��   */

    /* 
     *  ���ݿ��ٶ������ʱ���ȡ����
     */
    spiTxRxByte(ucTxBuf, 5, pucRcvBuf, ulNByte);                        /* ��������͵�ַ����ȡ����     */

    SPI_CS_HIGH();                                                      /*  CS��Ϊ�ߵ�ƽ������SPIͨ��   */

    return (MX_OK);
}

/*********************************************************************************************************
** Function name:           mx25L1606ReadID
** Descriptions:            MX25L1606�Ķ�ID����,��ѡ���ID�Ͷ����ݲ���
**                          ������Ĳ���������Ҫ���򷵻�MX_ERROR
** Input parameters:        
**                          eIDType:        ID���͡��û�����Jedec_ID,Dev_ID,Manu_ID������ѡ��
**                          pulRcvBuf:      �洢ID������ָ��
** Output parameters:       none
** Returned value:          �����ɹ��򷵻�MX_OK,ʧ���򷵻�MX_ERROR
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
        ucTxBuf[0] = 0x9F;                                              /* ���Ͷ�JEDEC ID����(9Fh)      */

        SPI_CS_LOW();                                                   /*  CS��Ϊ�͵�ƽ��ʹ��SPIͨ��   */

        /* 
         *  ���ݿ��ٶ������ʱ���ȡ����
         */
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 3);                            /* ���������������           */

        SPI_CS_HIGH();                                                  /*  CS��Ϊ�ߵ�ƽ������SPIͨ��   */

        /*
         *  ��ȡIDֵ
         *  �ڱ�����,*pulRcvBuf��ֵΪ0x00c22015
         */
        *pulRcvBuf = ((ucRxBuf[0] << 16)
                    | (ucRxBuf[1] <<  8)
                    | (ucRxBuf[2]));

        return (MX_OK);
    }
    
    if ((eIDType == Manu_ID) || (eIDType == Dev_ID) ) {
        ucTxBuf[0] = 0x90;                                              /* ���Ͷ�ID����(90H or EFH)     */
        ucTxBuf[1] = 0x00;                                              /* ���͵�ַ                     */
        ucTxBuf[2] = 0x00;                                              /* ���͵�ַ                     */
        ucTxBuf[3] = eIDType;                                           /* ���͵�ַ - ����00H����01H    */
        
        SPI_CS_LOW();                                                   /*  CS��Ϊ�͵�ƽ��ʹ��SPIͨ��   */

        /* 
         *  ���ݿ��ٶ������ʱ���ȡ����
         */
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 3);                            /* ���������������           */

        SPI_CS_HIGH();                                                  /*  CS��Ϊ�ߵ�ƽ������SPIͨ��   */
        
        /*
         *  ��ȡIDֵ
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
** Descriptions:            MX25L1606��д��������д1���Ͷ�����ݵ�ָ����ַ
**                          ��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
** Input parameters:        
**                          ulDst��         Ŀ���ַ,��Χ 0x0 - MAX_ADDR��MAX_ADDR = 0x1FFFFF��
**                          pucSendbuf:     ���ͻ�����ָ��
**                          ulNByte:        Ҫд�������ֽ���
** Output parameters:       none
** Returned value:          �����ɹ��򷵻�MX_OK,ʧ���򷵻�MX_ERROR
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
        return (MX_ERROR);                                              /*  �����ڲ���                */
    }

    ucTxBuf[0] = 0x05;                                                  /* ���Ͷ�״̬�Ĵ�������         */
    SPI_CS_LOW();                                                       /*  CS��Ϊ�͵�ƽ��ʹ��SPIͨ��   */
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                                /* ���������������           */
    SPI_CS_HIGH();                                                      /*  CS��Ϊ�ߵ�ƽ������SPIͨ��   */
    ulTmp = ucRxBuf[0];

    ucTxBuf[0] = 0x01;                                                  /* ����д״̬�Ĵ���ָ��         */
    ucTxBuf[1] = 0;                                                     /* ��0BPxλ��ʹFlashоƬȫ����д*/
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();
    
    for(i = 0; i < ulNByte; i++) {

        ucTxBuf[0] = 0x06;                                              /* ����дʹ������               */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        ucTxBuf[0] = 0x02;                                              /* ����ҳ�������               */
        ucTxBuf[1] = (((ulDst+i) & 0xFFFFFF) >> 16);                    /* ����3���ֽڵĵ�ַ��Ϣ        */
        ucTxBuf[2] = (((ulDst+i) & 0xFFFFFF) >>  8);
        ucTxBuf[3] = (((ulDst+i) & 0xFF));
        ucTxBuf[4] = (pucSendbuf[i]);
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 5, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* ���Ͷ�״̬�Ĵ�������         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* ���������������           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];                                   /* ������õ�״̬�Ĵ���ֵ       */
        } while (ulStatRgVal == 0x03);                                  /* һֱ�ȴ���ֱ��оƬ����       */
    }

    ucTxBuf[0] = 0x06;                                                  /* ����дʹ������               */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();

    ucTxBuf[0] = 0x01;                                                  /* ����д״̬�Ĵ���ָ��         */
    ucTxBuf[1] = ulTmp;                                                 /* �ָ�״̬�Ĵ���������Ϣ       */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();
    
    return (MX_OK);
}

/*********************************************************************************************************
** Function name:           mx25L1606Erase
** Descriptions:            ����ָ����������ѡȡ���Ч���㷨����
**                          ��ĳ������,ĳһ��ڲ�����Ч,���ڸ���ڲ�������Invalid���ò�����������
** Input parameters:        
**                          ulsec1����ʼ������,��Χ(0~511)
**                          ulsec2����ֹ������,��Χ(0~511)
** Output parameters:       none
** Returned value:          �����ɹ��򷵻�MX_OK,ʧ���򷵻�MX_ERROR        
*********************************************************************************************************/
INT8U  mx25L1606Erase (INT32U  ulsec1, INT32U  ulsec2)
{
    INT8U   ulTmp1 = 0, ulTmp2 = 0, ulStatRgVal = 0;
    INT32U  ulSecnHdAddr = 0;
    INT32U  ulNoSecsToEr = 0;                                           /* Ҫ������������Ŀ             */
    INT32U  ulCurSecToEr = 0;                                           /* ��ǰҪ������������           */
    INT8U   ucTxBuf[6] ={0}, ucRxBuf[6] ={0};

    /*
    *  �����ڲ���
    */
    if ((ulsec1 > SEC_MAX)||(ulsec2 > SEC_MAX)) {
        return (MX_ERROR);
    }
    
    ucTxBuf[0] = 0x05;                                                  /* ���Ͷ�״̬�Ĵ�������         */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                                /* ���������������           */
    SPI_CS_HIGH();
    ulTmp1 = ucRxBuf[0];                                                /* ������õ�״̬�Ĵ���ֵ       */
    
    ucTxBuf[0] = 0x01;                                                  /* ����д״̬�Ĵ���ָ��         */
    ucTxBuf[1] = 0;                                                     /* ��0BPxλ��ʹFlashоƬȫ����д*/
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();
    
    ucTxBuf[0] = 0x06;                                                  /* ����дʹ������               */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();
    
    /*
    * ����û��������ʼ�����Ŵ�����ֹ�����ţ������ڲ���������
    */
    if (ulsec1 > ulsec2) {
        ulTmp2 = ulsec1;
        ulsec1  = ulsec2;
        ulsec2  = ulTmp2;
    }

    /*
    * ����ֹ����������������������
    */
    if (ulsec1 == ulsec2) {
        ulSecnHdAddr = SEC_SIZE * ulsec1;                               /* ������������ʼ��ַ           */
        
        ucTxBuf[0] = 0x20;                                              /* ������������ָ��             */
        ucTxBuf[1] = ((ulSecnHdAddr & 0xFFFFFF) >> 16);                 /* ����3���ֽڵĵ�ַ��Ϣ        */
        ucTxBuf[2] = ((ulSecnHdAddr & 0xFFFF) >> 8);
        ucTxBuf[3] = ulSecnHdAddr & 0xFF;

        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();

        do {
            ucTxBuf[0] = 0x05;                                          /* ���Ͷ�״̬�Ĵ�������         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* ���������������           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];                                   /* ������õ�״̬�Ĵ���ֵ       */
        } while (ulStatRgVal & 0x01);                                   /* һֱ�ȴ���ֱ��оƬ����       */
        
        return (MX_OK);
    }
    
    /*
    * ������ʼ��������ֹ��������������ٵĲ�������
    */
    
    if (ulsec2 - ulsec1 == SEC_MAX) {
        ucTxBuf[0] = 0x60;                                              /* ����оƬ����ָ��(60h or C7h) */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* ���Ͷ�״̬�Ĵ�������         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* ���������������           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];                                   /* ������õ�״̬�Ĵ���ֵ       */
        } while (ulStatRgVal & 0x01);                                   /* һֱ�ȴ���ֱ��оƬ����       */
        return (MX_OK);
    }
    
    ulNoSecsToEr = ulsec2 - ulsec1 + 1;                                 /* ��ȡҪ������������Ŀ         */
    ulCurSecToEr  = ulsec1;                                             /* ����ʼ������ʼ����           */
    
    /*
    * ����������֮��ļ���������ȡ16���������㷨
    */
    while (ulNoSecsToEr >= 16) {
        ucTxBuf[0] = 0x06;                                              /* ��������д����               */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        ulSecnHdAddr = SEC_SIZE * ulCurSecToEr;                         /* ������������ʼ��ַ           */

        ucTxBuf[0] = 0xD8;                                              /* ����64KB�����ָ��           */
        ucTxBuf[1] = ((ulSecnHdAddr & 0xFFFFFF) >> 16);                 /* ����3���ֽڵĵ�ַ��Ϣ        */
        ucTxBuf[2] = ((ulSecnHdAddr & 0xFFFFFF) >>  8);
        ucTxBuf[3] = ulSecnHdAddr & 0xFF;
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* ���Ͷ�״̬�Ĵ�������         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* ���������������           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];
        } while (ulStatRgVal & 0x01);                                   /* һֱ�ȴ���ֱ��оƬ����       */
        
        ulCurSecToEr  += 16;                                            /* ���������16��������Ͳ����� */
                                                                        /* �����ڵĴ�����������         */
        ulNoSecsToEr -=  16;                                            /* �������������������������   */
    }
    
    /*
    * �������������㷨����ʣ�������
    */
    while (ulNoSecsToEr >= 1) {
        ucTxBuf[0] = 0x06;                                              /* ��������д����               */
        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        ulSecnHdAddr = SEC_SIZE * ulCurSecToEr;                         /* ������������ʼ��ַ           */

        ucTxBuf[0] = 0x20;                                              /* ������������ָ��             */
        ucTxBuf[1] = ((ulSecnHdAddr & 0xFFFFFF) >> 16);                 /* ����3���ֽڵĵ�ַ��Ϣ        */
        ucTxBuf[2] = ((ulSecnHdAddr & 0xFFFFFF) >>  8);
        ucTxBuf[3] = ulSecnHdAddr & 0xFF;

        SPI_CS_LOW();
        spiTxRxByte(ucTxBuf, 4, ucRxBuf, 0);                            /* ���������������           */
        SPI_CS_HIGH();
        
        do {
            ucTxBuf[0] = 0x05;                                          /* ���Ͷ�״̬�Ĵ�������         */
            SPI_CS_LOW();
            spiTxRxByte(ucTxBuf, 1, ucRxBuf, 1);                        /* ���������������           */
            SPI_CS_HIGH();
            ulStatRgVal = ucRxBuf[0];
        } while (ulStatRgVal & 0x01 );                                  /* һֱ�ȴ���ֱ��оƬ����       */
    
        ulCurSecToEr += 1;
        ulNoSecsToEr -= 1;
    }

    /*
    * ��������,�ָ�״̬�Ĵ�����Ϣ
    */
    ucTxBuf[0] = 0x06;                                                  /* ����дʹ������               */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 1, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();

    ucTxBuf[0] = 0x01;                                                  /* ����д״̬�Ĵ���ָ��         */
    ucTxBuf[1] = ulTmp1;                                                /* �ָ�״̬�Ĵ���������Ϣ       */
    SPI_CS_LOW();
    spiTxRxByte(ucTxBuf, 2, ucRxBuf, 0);                                /* ���������������           */
    SPI_CS_HIGH();

    return (MX_OK);
}

/*********************************************************************************************************
** End File
*********************************************************************************************************/
