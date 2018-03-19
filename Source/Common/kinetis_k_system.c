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
#include "includes.h"

#if (defined(MCU_MK40DZ10) || defined(MCU_MK53DZ10) || defined(MCU_MK60DZ10))

/*
 * C2 Bit Fields
 */
#define MCG_C2_EREFS0_MASK                       MCG_C2_EREFS_MASK
#define MCG_C2_EREFS0_SHIFT                      MCG_C2_EREFS_SHIFT
#define MCG_C2_HGO0_MASK                         MCG_C2_HGO_MASK
#define MCG_C2_HGO0_SHIFT                        MCG_C2_HGO_SHIFT
#define MCG_C2_RANGE0_MASK                       MCG_C2_RANGE_MASK
#define MCG_C2_RANGE0_SHIFT                      MCG_C2_RANGE_SHIFT
#define MCG_C2_RANGE0(x)                         MCG_C2_RANGE(x)
#define MCG_C2_LOCRE0_MASK                       MCG_C2_LOCRE_MASK
#define MCG_C2_LOCRE0_SHIFT                      MCG_C2_LOCRE_SHIFT

/*
 * C5 Bit Fields
 */
#define MCG_C5_PRDIV0_MASK                       MCG_C5_PRDIV_MASK
#define MCG_C5_PRDIV0_SHIFT                      MCG_C5_PRDIV_SHIFT
#define MCG_C5_PRDIV0(x)                         MCG_C5_PRDIV(x)
#define MCG_C5_PLLSTEN0_MASK                     MCG_C5_PLLSTEN_MASK
#define MCG_C5_PLLSTEN0_SHIFT                    MCG_C5_PLLSTEN_SHIFT
#define MCG_C5_PLLCLKEN0_MASK                    MCG_C5_PLLCLKEN_MASK
#define MCG_C5_PLLCLKEN0_SHIFT                   MCG_C5_PLLCLKEN_SHIFT

/*
 * C6 Bit Fields
 */
#define MCG_C6_VDIV0_MASK                        MCG_C6_VDIV_MASK
#define MCG_C6_VDIV0_SHIFT                       MCG_C6_VDIV_SHIFT
#define MCG_C6_VDIV0(x)                          MCG_C6_VDIV(x)
#define MCG_C6_CME0_MASK                         MCG_C6_CME_MASK
#define MCG_C6_CME0_SHIFT                        MCG_C6_CME_SHIFT

#define MCG_C6_LOLIE0_MASK                       MCG_C6_LOLIE_MASK
#define MCG_C6_LOLIE0_SHIFT                      MCG_C6_LOLIE_SHIFT

/*
 * S Bit Fields
 */
#define MCG_S_OSCINIT0_MASK                      MCG_S_OSCINIT_MASK
#define MCG_S_OSCINIT0_SHIFT                     MCG_S_OSCINIT_SHIFT

#define MCG_S_LOCK0_MASK                         MCG_S_LOCK_MASK
#define MCG_S_LOCK0_SHIFT                        MCG_S_LOCK_SHIFT
#define MCG_S_LOLS0_MASK                         MCG_S_LOLS_MASK
#define MCG_S_LOLS0_SHIFT                        MCG_S_LOLS_SHIFT

#endif




















#define SYS_LOW_FRQ_MAX                     3000000                     /* Low frequency range maximum  */
#define SYS_HIGH_FRQ_MAX                    8000000                     /* High frequency range maximum */
#define SYS_VERY_HIGH_FRQ_MAX               32000000                    /* Very high frequency range    */
                                                                        /* maximum                      */

#define SYS_FLL_OUTPUT_MIN                  24000000                    /* Minimum frequency of FLL     */


#define SYS_32KIRC_FRQ                      32768                       /* IRC 23.768Hz                 */
#define SYS_4MIRC_FRQ                       4000000                     /* IRC 4MHz                     */


/*
 *  Function return defined
 */
#define SYS_ERR_NONE                        0
#define SYS_ERR_CLK                         1

/*
 *  FLL' or PLL' clock source
 */
#define SYS_CLK_SOURCE_MOSC                 0
#define SYS_CLK_SOURCE_RTC                  1
#define SYS_CLK_SOURCE_4MIRC                2
#define SYS_CLK_SOURCE_32KIRC               3
#define SYS_CLK_SOURCE_FPLL                 4





#define SYS_CLK_TYPE_RC                     0                           /* Clock type is RC             */
#define SYS_CLK_TYPE_OSC                    1                           /* Clock type is oscillator     */


/*********************************************************************************************************
** Function name:           sysDivSet
** Descriptions:            Set system divistion 设置系统分频
** Input parameters:        ulOutDiv1 ：Div1 divistion
**                          ulOutDiv2 : Div2 divistion
**                          ulOutDiv3 : Div3 divistion
**                          ulOutDiv4 : Div4 divistion
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void  sysDivSet (INT32U  ulOutDiv1,
                 INT32U  ulOutDiv2,
                 INT32U  ulOutDiv3,
                 INT32U  ulOutDiv4)
{
    INT32U  ulTmp;
    INT32U  uli;

    ulTmp = FMC_PFAPR;                                                  /* store present value of FMC_P */
                                                                        /* FAPR                         */

    /*
     * set M0PFD through M7PFD to 1 to disable prefetch
     */
    FMC_PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK |
                 FMC_PFAPR_M4PFD_MASK | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK |
                 FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;

    /*
     * set clock dividers to desired value
     */
    SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(ulOutDiv1) | SIM_CLKDIV1_OUTDIV2(ulOutDiv2) |
                  SIM_CLKDIV1_OUTDIV3(ulOutDiv3) | SIM_CLKDIV1_OUTDIV4(ulOutDiv4);


    for (uli = 0; uli < ulOutDiv4; uli++) {                             /* wait for dividers to change  */

    }

  FMC_PFAPR = ulTmp;                                                    /* re-store original value of F */
                                                                        /* MC_PFAPR                     */

}

/*********************************************************************************************************
** Function name:           sysFllDivSet
** Descriptions:            Set FLL divistion 设置PLL分频
** Input parameters:        ucRefClkType   ：Clock type ??考虑删去
**                          ulInputClkFrq  : Input clock frequency
**                          ulOutputClkFrq : Output clock frequency
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysFllDivSet (INT8U  ucRefClkType, INT32U  ulInputClkFrq, INT32U  ulOutputClkFrq)
{
    INT32U  ulDivMax;
    INT32U  ulDivMin;
    INT32U  ulDivAct;

    INT8U   ucFrdiv;
    INT8U   ucRange;

    ulDivMin = ulInputClkFrq / 39062;
    ulDivMax = ulInputClkFrq / 31250;

    if (ulInputClkFrq <= SYS_LOW_FRQ_MAX) {                             /* Low frequency range          */

        if (ulDivMin <= 1 && ulDivMax >= 1) {
            ucFrdiv  = 0;                                               /* Set FRDIV bits               */
            ulDivAct = 1;

        } else if (ulDivMin <= 2 && ulDivMax >= 2) {
            ucFrdiv  = 1;                                               /* Set FRDIV bits               */
            ulDivAct = 2;

        } else if (ulDivMin <= 4 && ulDivMax >= 4) {
            ucFrdiv  = 2;                                               /* Set FRDIV bits               */
            ulDivAct = 4;

        } else if (ulDivMin <= 8 && ulDivMax >= 8) {
            ucFrdiv  = 3;                                               /* Set FRDIV bits               */
            ulDivAct = 8;

        } else if (ulDivMin <= 16 && ulDivMax >= 16) {
            ucFrdiv  = 4;                                               /* Set FRDIV bits               */
            ulDivAct = 16;

        } else if (ulDivMin <= 32 && ulDivMax >= 32) {
            ucFrdiv  = 5;                                               /* Set FRDIV bits               */
            ulDivAct = 32;

        } else if (ulDivMin <= 64 && ulDivMax >= 64) {
            ucFrdiv  = 6;                                               /* Set FRDIV bits               */
            ulDivAct = 64;

        } else if (ulDivMin <= 128 && ulDivMax >= 128) {
            ucFrdiv  = 7;                                               /* Set FRDIV bits               */
            ulDivAct = 128;

        } else {
            return (SYS_ERR_CLK);                                       /* Not support                  */
        }
        ucRange = 0;

    } else {

        if (ulDivMin <= 32 && ulDivMax >= 32) {
            ucFrdiv  = 0;                                               /* Set FRDIV bits               */
            ulDivAct = 32;

        } else if (ulDivMin <= 64 && ulDivMax >= 64) {
            ucFrdiv  = 1;                                               /* Set FRDIV bits               */
            ulDivAct = 64;

        } else if (ulDivMin <= 128 && ulDivMax >= 128) {
            ucFrdiv  = 2;                                               /* Set FRDIV bits               */
            ulDivAct = 128;

        } else if (ulDivMin <= 256 && ulDivMax >= 256) {
            ucFrdiv  = 3;                                               /* Set FRDIV bits               */
            ulDivAct = 256;

        } else if (ulDivMin <= 512 && ulDivMax >= 512) {
            ucFrdiv  = 4;                                               /* Set FRDIV bits               */
            ulDivAct = 512;

        } else if (ulDivMin <= 1024 && ulDivMax >= 1024) {
            ucFrdiv  = 5;                                               /* Set FRDIV bits               */
            ulDivAct = 1024;

        } else {
            return (SYS_ERR_CLK);                                       /* Not support                  */
        }

        if (ulInputClkFrq <= SYS_HIGH_FRQ_MAX) {                        /* High frequency range         */
            ucRange = 1;
        } else if (ulInputClkFrq <= SYS_VERY_HIGH_FRQ_MAX) {            /* Very High frequency range    */
            ucRange = 2;
        } else {
            return (SYS_ERR_CLK);                                       /* Not support                  */
        }
    }
    MCG_C2 = (MCG_C2 & (~MCG_C2_RANGE0_MASK)) | (ucRange << MCG_C2_RANGE0_SHIFT);
                                                                        /* Set RANGE bits               */

    MCG_C1 = (MCG_C1 & (~MCG_C1_FRDIV_MASK)) | (ucFrdiv << MCG_C1_FRDIV_SHIFT);
                                                                        /* Set FRDIV bits               */


    if (ucRefClkType == SYS_CLK_TYPE_OSC &&
        ((ulDivAct * ((INT32U)(32768 * 0.99))) < ulInputClkFrq &&
         (ulDivAct * ((INT32U)(32768 * 1.01))) > ulInputClkFrq)) {      /* Consider a narrow clock      */
        MCG_C4 |=  (1u << MCG_C4_DMX32_SHIFT);
    } else {
        MCG_C4 &= ~(1u << MCG_C4_DMX32_SHIFT);
    }

    if (ulOutputClkFrq < 36000000) {
        MCG_C4 = (MCG_C4 & (~MCG_C4_DRST_DRS_MASK)) | (0 << MCG_C4_DRST_DRS_SHIFT);
                                                                        /* Set DRST_DRS bits            */
    } else if (ulOutputClkFrq < 54000000) {
        MCG_C4 = (MCG_C4 & (~MCG_C4_DRST_DRS_MASK)) | (1 << MCG_C4_DRST_DRS_SHIFT);
                                                                        /* Set DRST_DRS bits            */

    } else if (ulOutputClkFrq < 78000000) {
        MCG_C4 = (MCG_C4 & (~MCG_C4_DRST_DRS_MASK)) | (2 << MCG_C4_DRST_DRS_SHIFT);
                                                                        /* Set DRST_DRS bits            */

    } else {
        MCG_C4 = (MCG_C4 & (~MCG_C4_DRST_DRS_MASK)) | (3 << MCG_C4_DRST_DRS_SHIFT);
                                                                        /* Set DRST_DRS bits            */

    }

    return (SYS_ERR_NONE);
}

/*********************************************************************************************************
** Function name:           sysPllDivSet
** Descriptions:            Set PLL divistion 设置PLL分频
** Input parameters:        ucRefClkType   ：Clock type ??考虑删去
**                          ulInputClkFrq  : Input clock frequency
**                          ulOutputClkFrq : Output clock frequency
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysPllDivSet (INT8U  ucRefClkType, INT32U  ulInputClkFrq, INT32U  ulOutputClkFrq)
{
    INT32U  ulDivMax;
    INT32U  ulDivMin;
    INT32U  ulTmp;

    INT32U  ulVdiv;

    INT32U  ulPrdiv;
    INT8U   ucRange;

    if (ulInputClkFrq <= SYS_LOW_FRQ_MAX) {                             /* Low frequency range          */
        ucRange = 0;

    } else if (ulInputClkFrq <= SYS_HIGH_FRQ_MAX) {                     /* High frequency range         */
        ucRange = 1;

    } else if (ulInputClkFrq <= SYS_VERY_HIGH_FRQ_MAX) {                /* Very High frequency range    */
        ucRange = 2;

    } else {
        return (SYS_ERR_CLK);                                           /* Not support                  */
    }

    ulDivMin = (ulInputClkFrq + (4000000 - 1))/ 4000000;
    ulDivMax = ulInputClkFrq / 2000000;

    if (ulDivMax < 1 || ulDivMin < 1 || ulDivMin > (2 ^ 5)) {
        return (SYS_ERR_CLK);                                           /* Not support                  */
    }

    for (ulPrdiv = ulDivMax; ulPrdiv >= ulDivMin; ulPrdiv--) {
        ulTmp = ulInputClkFrq / ulPrdiv;                                /* ulTmp range from 2M to 4M    */

        ulVdiv = (ulOutputClkFrq + ulTmp - 1) / ulTmp;

        if (ulVdiv >= 24 && ulVdiv <= 55) {
            break;
        }
    }

    if (ulVdiv < 24) {
        ulPrdiv = ulDivMax;
        ulVdiv  = 24;
    }
    if (ulVdiv > 55) {
        ulPrdiv = ulDivMin;
        ulVdiv  = 55;
    }
    if (ulPrdiv == 0) {
        ulPrdiv = 1;
    }
    ulPrdiv -= 1;
    ulVdiv  -= 24;                                                      /* ulVdiv range from 0 to 31    */

    MCG_C2 = (MCG_C2 & (~MCG_C2_RANGE0_MASK)) | (ucRange << MCG_C2_RANGE0_SHIFT);
                                                                        /* Set RANGE bits               */

    MCG_C5 = (MCG_C5 & (~MCG_C5_PRDIV0_MASK)) | (ulPrdiv << MCG_C5_PRDIV0_SHIFT);
                                                                        /* Set PRDIV bits               */

    MCG_C6 = (MCG_C6 & (~MCG_C6_VDIV0_MASK)) | (ulVdiv << MCG_C6_VDIV0_SHIFT);
                                                                        /* Set VDIV bits                */

    return (SYS_ERR_NONE);
}

/*********************************************************************************************************
** Function name:           sysMCGModeFEI
** Descriptions:            Switch to FEI mode 切换到 FEI 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModeFEI (INT8U  ucFllInput)
{
    volatile  INT32U  uli;
              INT8U   ucTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_32KIRC)) {
        return (SYS_ERR_CLK);
    }

    sysFllDivSet(SYS_CLK_TYPE_RC, SYS_32KIRC_FRQ, SYS_FLL_OUTPUT_MIN);  /* Fll's source is always 32K I */
                                                                        /* RC                           */

    MCG_C1 |=  (1u << MCG_C1_IREFS_SHIFT);                              /* FLL source is inner clock    */

    MCG_C6 &= ~(1u << MCG_C6_PLLS_SHIFT);                               /* FLL select,not PLL           */

    MCG_C2 &= ~(1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL enable            */


    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (0u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is FLL clock       */

    while (!(MCG_S & MCG_S_IREFST_MASK));                               /* wait for FLL source          */
    while (MCG_S & MCG_S_PLLST_MASK);                                   /* wait for selecting FLL       */

    while ((MCG_S & MCG_S_CLKST_MASK)!= (0u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */


    ucTmp = sysFllDivSet(SYS_CLK_TYPE_RC, SYS_32KIRC_FRQ, SYS_FPLL_FRQ);
    if (ucTmp != SYS_ERR_NONE) {
       return (ucTmp);
    }

    for (uli = 0; uli < 1000; uli++) {                                  /* waiting time > 1ms           */

    }

    return (SYS_ERR_NONE);
}

/*********************************************************************************************************
** Function name:           sysMCGModeFBI
** Descriptions:            Switch to FBI mode 切换到 FBI 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModeFBI (INT8U  ucFllInput)
{
    INT8U  ulTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_32KIRC || ucFllInput == SYS_CLK_SOURCE_4MIRC)) {
        return (SYS_ERR_CLK);
    }

    sysFllDivSet(SYS_CLK_TYPE_RC, SYS_32KIRC_FRQ, SYS_FLL_OUTPUT_MIN);  /* Fll's source is always 32K I */
                                                                        /* RC                           */

    MCG_C1 |=  (1u << MCG_C1_IREFS_SHIFT);                              /* FLL source is inner clock    */

    MCG_C6 &= ~(1u << MCG_C6_PLLS_SHIFT);                               /* FLL select,not PLL           */

    MCG_C2 &= ~(1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL enable            */


    if (ucFllInput == SYS_CLK_SOURCE_32KIRC) {                          /* 32K IRC                      */

        MCG_C2 &= ~(1u << MCG_C2_IRCS_SHIFT);                           /* 32K IRC                      */

    } else if (ucFllInput == SYS_CLK_SOURCE_4MIRC) {                    /* 4M IRC                       */
        MCG_C2 |=  (1u << MCG_C2_IRCS_SHIFT);                           /* 4M/2 IRC                     */
    }

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (1u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is inner clock     */

    while (!(MCG_S & MCG_S_IREFST_MASK));                               /* wait for FLL source          */
    while (MCG_S & MCG_S_PLLST_MASK);                                   /* wait for selecting FLL       */

    ulTmp = MCG_C1;                                                     /* backup MCG_C1                */
    MCG_C1 |= (1u << MCG_C1_IRCLKEN_SHIFT);                             /* Set IRCLKEN to 1 to checking */
                                                                        /* IRCST                        */

    if (ucFllInput == SYS_CLK_SOURCE_32KIRC) {                          /* 32K IRC                      */
        while(MCG_S & MCG_S_IRCST_MASK);                                /* wait for 32K IRC             */

    } else if (ucFllInput == SYS_CLK_SOURCE_4MIRC) {                    /* 4M IRC                       */
        while(!(MCG_S & MCG_S_IRCST_MASK));                             /* wait for 4M IRC              */
    }
    MCG_C1  =  ulTmp;                                                   /* Recover IRCLKEN state        */

    while ((MCG_S & MCG_S_CLKST_MASK)!= (1u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */

    return (SYS_ERR_NONE);
}

/*********************************************************************************************************
** Function name:           sysMCGModeBLPI
** Descriptions:            Switch to BLPI mode 切换到 BLPI 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModeBLPI (INT8U  ucFllInput)
{
    INT8U  ulTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_32KIRC || ucFllInput == SYS_CLK_SOURCE_4MIRC)) {
        return (SYS_ERR_CLK);
    }

    if (ucFllInput == SYS_CLK_SOURCE_32KIRC) {                          /* 32K IRC                      */

        MCG_C2 &= ~(1u << MCG_C2_IRCS_SHIFT);                           /* 32K IRC                      */
        while(MCG_S & MCG_S_IRCST_MASK);                                /* wait for 32K IRC             */

    } else if (ucFllInput == SYS_CLK_SOURCE_4MIRC) {                    /* 4M IRC                       */
        MCG_C2 |=  (1u << MCG_C2_IRCS_SHIFT);                           /* 4M/2 IRC                     */
        while(!(MCG_S & MCG_S_IRCST_MASK));                             /* wait for 4M IRC              */
    }

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (1u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is inner clock     */

    ulTmp = MCG_C1;                                                     /* backup MCG_C1                */
    MCG_C1 |= (1u << MCG_C1_IRCLKEN_SHIFT);                             /* Set IRCLKEN to 1 to checking */
                                                                        /* IRCST                        */

    if (ucFllInput == SYS_CLK_SOURCE_32KIRC) {                          /* 32K IRC                      */
        while(MCG_S & MCG_S_IRCST_MASK);                                /* wait for 32K IRC             */

    } else if (ucFllInput == SYS_CLK_SOURCE_4MIRC) {                    /* 4M IRC                       */
        while(!(MCG_S & MCG_S_IRCST_MASK));                             /* wait for 4M IRC              */
    }
    MCG_C1  =  ulTmp;                                                   /* Recover IRCLKEN state        */

    while ((MCG_S & MCG_S_CLKST_MASK)!= (1u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */

    MCG_C2 |=  (1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL disable           */

    return (SYS_ERR_NONE);
}
/*********************************************************************************************************
** Function name:           sysMCGModeFEE
** Descriptions:            Switch to FEE mode 切换到 FEE 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModeFEE (INT8U  ucFllInput)
{
    volatile  INT32U  uli;
              INT8U   ucTmp;


    if (!(ucFllInput == SYS_CLK_SOURCE_RTC || ucFllInput == SYS_CLK_SOURCE_MOSC)) {
        return (SYS_ERR_CLK);
    }

    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_RTC_FRQ, SYS_FLL_OUTPUT_MIN);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

        SIM_SCGC6 |= (1u << SIM_SCGC6_RTC_SHIFT);                       /* Enable rtc clock             */
        RTC_CR    |= (1u << RTC_CR_OSCE_SHIFT);                         /* Enable rtc oscillator        */

        SIM_SOPT2 |=  (1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                /* MCG source is rtc            */

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_MOSC_FRQ, SYS_FLL_OUTPUT_MIN);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

        MCG_C2 |= (1u << MCG_C2_HGO0_SHIFT) | (1u << MCG_C2_EREFS0_SHIFT);
                                                                        /* Config extern oscillator     */

        SIM_SOPT2 &= ~(1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                /* MCG source is main oscillator*/
    }

    MCG_C1 &= ~(1u << MCG_C1_IREFS_SHIFT);                              /* FLL source is extern oscilla */
                                                                        /* tor                          */

    MCG_C6 &= ~(1u << MCG_C6_PLLS_SHIFT);                               /* FLL select,not PLL           */

    MCG_C2 &= ~(1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL enable            */

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (0u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is FLL or PLL cloc */
                                                                        /* k                            */

    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        while(!(MCG_S & MCG_S_OSCINIT0_MASK));                          /* wait for stable oscillator   */
    }

    while (MCG_S & MCG_S_IREFST_MASK);                                  /* wait for FLL source          */
    while (MCG_S & MCG_S_PLLST_MASK);                                   /* wait for selecting FLL       */
    while ((MCG_S & MCG_S_CLKST_MASK)!= (0u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */


    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_RTC_FRQ, SYS_FPLL_FRQ);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_MOSC_FRQ, SYS_FPLL_FRQ);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }
    }

    for (uli = 0; uli < 1000; uli++) {                                  /* waiting time > 1ms           */

    }

    return (SYS_ERR_NONE);
}

/*********************************************************************************************************
** Function name:           sysMCGModeFBE
** Descriptions:            Switch to FBE mode 切换到 FBE 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModeFBE (INT8U  ucFllInput)
{
    INT8U   ucTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_RTC || ucFllInput == SYS_CLK_SOURCE_MOSC)) {
        return (SYS_ERR_CLK);
    }

    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_RTC_FRQ, SYS_FLL_OUTPUT_MIN);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

        SIM_SCGC6 |= (1u << SIM_SCGC6_RTC_SHIFT);                       /* Enable rtc clock             */
        RTC_CR    |= (1u << RTC_CR_OSCE_SHIFT);                         /* Enable rtc oscillator        */

        SIM_SOPT2 |=  (1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                /* MCG source is rtc            */

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_MOSC_FRQ, SYS_FLL_OUTPUT_MIN);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

        MCG_C2 |= (1u << MCG_C2_HGO0_SHIFT) | (1u << MCG_C2_EREFS0_SHIFT);
                                                                        /* Config extern oscillator     */

        SIM_SOPT2 &= ~(1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                /* MCG source is main oscillato */
                                                                        /* r                            */
    }

    MCG_C1 &= ~(1u << MCG_C1_IREFS_SHIFT);                              /* FLL source is extern oscilla */
                                                                        /* tor                          */

    MCG_C6 &= ~(1u << MCG_C6_PLLS_SHIFT);                               /* FLL select,not PLL           */

    MCG_C2 &= ~(1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL enable            */

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (2u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is extern clock    */

    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        while(!(MCG_S & MCG_S_OSCINIT0_MASK));                          /* wait for stable oscillator   */
    }
    while (MCG_S & MCG_S_IREFST_MASK);                                  /* wait for FLL source          */
    while (MCG_S & MCG_S_PLLST_MASK);                                   /* wait for selecting FLL       */
    while ((MCG_S & MCG_S_CLKST_MASK)!= (2u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */

    return (SYS_ERR_NONE);
}


/*********************************************************************************************************
** Function name:           sysMCGModeBLPE
** Descriptions:            Switch to BLPE mode 切换到 BLPE 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModeBLPE (INT8U  ucFllInput)
{
    INT8U  ucTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_RTC || ucFllInput == SYS_CLK_SOURCE_MOSC)) {
        return (SYS_ERR_CLK);
    }

    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_RTC_FRQ, SYS_FLL_OUTPUT_MIN);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

        SIM_SCGC6 |= (1u << SIM_SCGC6_RTC_SHIFT);                       /* Enable rtc clock             */
        RTC_CR    |= (1u << RTC_CR_OSCE_SHIFT);                         /* Enable rtc oscillator        */

        SIM_SOPT2 |=  (1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                /* MCG source is rtc            */

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        ucTmp = sysFllDivSet(SYS_CLK_TYPE_OSC, SYS_MOSC_FRQ, SYS_FLL_OUTPUT_MIN);
        if (ucTmp != SYS_ERR_NONE) {
           return (ucTmp);
        }

        MCG_C2 |= (1u << MCG_C2_HGO0_SHIFT) | (1u << MCG_C2_EREFS0_SHIFT);
                                                                        /* Config extern oscillator     */

        SIM_SOPT2 &= ~(1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                /* MCG source is main oscillato */
                                                                        /* r                            */
    }

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (2u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is extern clock    */

    if (ucFllInput == SYS_CLK_SOURCE_RTC) {                             /* rtc                          */

    } else if (ucFllInput == SYS_CLK_SOURCE_MOSC) {                     /* main oscillator              */
        while(!(MCG_S & MCG_S_OSCINIT0_MASK));                          /* wait for stable oscillator   */
    }
    while ((MCG_S & MCG_S_CLKST_MASK)!= (2u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */

    MCG_C2 |=  (1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL disable           */

    return (SYS_ERR_NONE);
}


/*********************************************************************************************************
** Function name:           sysMCGModePBE
** Descriptions:            Switch to PBE mode 切换到 PBE 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModePBE (INT8U  ucFllInput)
{
    INT8U   ucTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_MOSC)) {
        return (SYS_ERR_CLK);
    }
    ucTmp = sysPllDivSet(SYS_CLK_TYPE_OSC, SYS_MOSC_FRQ, SYS_FPLL_FRQ);
    if (ucTmp != SYS_ERR_NONE) {
       return (ucTmp);
    }

    MCG_C2 |= (1u << MCG_C2_HGO0_SHIFT) | (1u << MCG_C2_EREFS0_SHIFT);  /* Config extern oscillator     */

    SIM_SOPT2 &= ~(1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                    /* MCG source is main oscillator*/


    MCG_C6 |=  (1u << MCG_C6_PLLS_SHIFT);                               /* PLL select,not PLL           */

    MCG_C2 &= ~(1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL enable            */

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (2u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is extern clock    */

    while(!(MCG_S & MCG_S_OSCINIT0_MASK));                              /* wait for stable oscillator   */

    while (!(MCG_S & MCG_S_PLLST_MASK));                                /* wait for selecting PLL       */
    while ((MCG_S & MCG_S_CLKST_MASK)!= (2u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */

    return (SYS_ERR_NONE);
}

/*********************************************************************************************************
** Function name:           sysMCGModePEE
** Descriptions:            Switch to PEE mode 切换到 PEE 模式
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
INT8U  sysMCGModePEE (INT8U  ucFllInput)
{
    INT8U   ucTmp;

    if (!(ucFllInput == SYS_CLK_SOURCE_MOSC)) {
        return (SYS_ERR_CLK);
    }
    ucTmp = sysPllDivSet(SYS_CLK_TYPE_OSC, SYS_MOSC_FRQ, SYS_FPLL_FRQ);
    if (ucTmp != SYS_ERR_NONE) {
       return (ucTmp);
    }

    MCG_C2 |= (1u << MCG_C2_HGO0_SHIFT) | (1u << MCG_C2_EREFS0_SHIFT);  /* Config extern oscillator     */

    SIM_SOPT2 &= ~(1u << SIM_SOPT2_MCGCLKSEL_SHIFT);                    /* MCG source is main oscillato */
                                                                        /* r                            */

    MCG_C6 |=  (1u << MCG_C6_PLLS_SHIFT);                               /* PLL select,not PLL           */

    MCG_C2 &= ~(1u << MCG_C2_LP_SHIFT);                                 /* FLL or PLL enable            */

    MCG_C1  =  (MCG_C1 & (~MCG_C1_CLKS_MASK)) | (0u << MCG_C1_CLKS_SHIFT);
                                                                        /* MCGOUTCLK is FLL or PLL cloc */
                                                                        /* k                            */

    while(!(MCG_S & MCG_S_OSCINIT0_MASK));                              /* wait for stable oscillator   */


    while (!(MCG_S & MCG_S_LOCK0_MASK));                                /* wait for PLL locked          */

    while ((MCG_S & MCG_S_CLKST_MASK)!= (3u << MCG_S_CLKST_SHIFT));     /* Wait for clock state update  */

    return (SYS_ERR_NONE);
}


/*********************************************************************************************************
** Function name:           sysClkInit
** Descriptions:            initialize clock 时钟初始化
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void  sysClkInit (INT32U  ulClkConfig)
{
    INT32U  ulTmp;

    ulTmp = ulClkConfig & 0x0000000F;                                   /* Get MCGOUTCLK source clock   */

    if (ulTmp == SYS_CLK_SOURCE_MOSC) {
        sysMCGModeFBE(SYS_CLK_SOURCE_MOSC);
        sysMCGModeBLPE(SYS_CLK_SOURCE_MOSC);

    } else if (ulTmp == SYS_CLK_SOURCE_RTC) {
        sysMCGModeFBE(SYS_CLK_SOURCE_RTC);
        sysMCGModeBLPE(SYS_CLK_SOURCE_RTC);

    } else if (ulTmp == SYS_CLK_SOURCE_4MIRC) {
        sysMCGModeFBI(SYS_CLK_SOURCE_4MIRC);
        sysMCGModeBLPI(SYS_CLK_SOURCE_4MIRC);

    } else if (ulTmp == SYS_CLK_SOURCE_32KIRC) {
        sysMCGModeFBI(SYS_CLK_SOURCE_32KIRC);
        sysMCGModeBLPI(SYS_CLK_SOURCE_32KIRC);

    } else if (ulTmp == SYS_CLK_SOURCE_FPLL) {

        ulTmp = (ulClkConfig >> 4)& 0x0000000F;                         /* Get FLL or PLL source clock  */

        if (ulTmp == SYS_CLK_SOURCE_MOSC) {                             /* Use PLL                      */
            sysMCGModeFBE(SYS_CLK_SOURCE_MOSC);
            sysMCGModePBE(SYS_CLK_SOURCE_MOSC);
            sysMCGModePEE(SYS_CLK_SOURCE_MOSC);

        } else if (ulTmp == SYS_CLK_SOURCE_RTC) {                       /* Use FLL                      */
            sysMCGModeFEE(SYS_CLK_SOURCE_RTC);

        } else if (ulTmp == SYS_CLK_SOURCE_RTC) {                       /* Use FLL                      */
            sysMCGModeFEI(SYS_CLK_SOURCE_4MIRC);

        } else if (ulTmp == SYS_CLK_SOURCE_32KIRC) {                    /* Use FLL                      */
            sysMCGModeFEI(SYS_CLK_SOURCE_32KIRC);
        }
    }
}

/*********************************************************************************************************
** Function name:           sysInit
** Descriptions:            initialize system 系统初始化
** Input parameters:        none
** Output parameters:       none
** Returned value:          none
** Created by:              Fan Linyun
** Created date:            2012-12-11
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
*********************************************************************************************************/
void  sysInit (void)
{
    if (SYS_WD_EN) {                                                    /* Watchdog enable              */
        __disable_irq();                                                /* Disable interrupt            */
        WDOG_UNLOCK   =  0xC520;                                        /* Write 0xC520 and then write  */
                                                                        /* 0xD928 to unlock register    */
        WDOG_UNLOCK   =  0xD928;
        WDOG_STCTRLH |=  (1u << WDOG_STCTRLH_WDOGEN_SHIFT);             /* Enable the watchdog          */
        __enable_irq();                                                 /* end                          */

    } else {                                                            /* Watchdog Disable             */
        __disable_irq();                                                /* Disable interrupt            */
        WDOG_UNLOCK   =  0xC520;                                        /* Write 0xC520 and then write  */
                                                                        /* 0xD928 to unlock register    */
        WDOG_UNLOCK   =  0xD928;
        WDOG_STCTRLH &= ~(1u << WDOG_STCTRLH_WDOGEN_SHIFT);             /* Disable the watchdog         */
        __enable_irq();                                                 /* end                          */
    }

    /*
     *  Config the division of clock
     */
    sysDivSet(SYS_CORE_DIV, SYS_BUS_DIV, SYS_FLEXBUS_DIV, SYS_FLASH_DIV);

    if (SYS_MOSC_EN) {                                                  /* Initialize main oscillation  */
        OSC_CR = (OSC_CR & (~(OSC_CR_SC2P_MASK | OSC_CR_SC4P_MASK | OSC_CR_SC8P_MASK | OSC_CR_SC16P_MASK))) |
                 ((SYS_MOSC_2PF_EN > 0) << OSC_CR_SC2P_SHIFT) |
                 ((SYS_MOSC_4PF_EN > 0) << OSC_CR_SC4P_SHIFT) |
                 ((SYS_MOSC_8PF_EN > 0) << OSC_CR_SC8P_SHIFT) |
                 ((SYS_MOSC_16PF_EN > 0) << OSC_CR_SC16P_SHIFT);

    }
    if (SYS_RTC_EN) {                                                   /* Initialize RTC               */
        SIM_SCGC6 |= (1u << SIM_SCGC6_RTC_SHIFT);                       /* Enable rtc clock             */
        RTC_CR = (RTC_CR & (~(RTC_CR_SC2P_MASK | RTC_CR_SC4P_MASK | RTC_CR_SC8P_MASK | RTC_CR_SC16P_MASK))) |
                 ((SYS_RTC_2PF_EN > 0) << RTC_CR_SC2P_SHIFT) |
                 ((SYS_RTC_4PF_EN > 0) << RTC_CR_SC4P_SHIFT) |
                 ((SYS_RTC_8PF_EN > 0) << RTC_CR_SC8P_SHIFT) |
                 ((SYS_RTC_16PF_EN > 0) << RTC_CR_SC16P_SHIFT);
    }
    if (SYS_FPLL_EN) {                                                  /* Initialize FLL or PLL        */
        if (SYS_FPLL_INPUT == SYS_CLK_SOURCE_MOSC) {                    /* Use PLL                      */

        } else {                                                        /* Use FLL                      */

        }
    }


    if (SYS_CLK_EN) {                                                   /* config clock mode            */
        sysClkInit((SYS_FPLL_INPUT << 4) | (SYS_MCGOUTCLK_INPUT << 0));
    }

    /*
     *  MCGIRCLK clock config
     */
    if (SYS_MCGIRCLK_EN) {                                              /* Enable MCGIRCLK              */
        MCG_C1 |= (1u << MCG_C1_IRCLKEN_SHIFT);                         /* Enable MCGIRCLK              */

        if (!(SYS_MCGOUTCLK_INPUT == SYS_CLK_SOURCE_4MIRC ||
              SYS_MCGOUTCLK_INPUT == SYS_CLK_SOURCE_4MIRC)) {

            if (SYS_MCGIRCLK_INPUT == SYS_CLK_SOURCE_4MIRC) {
                MCG_C2 |= (1u << MCG_C2_IRCS_SHIFT);
                while(!(MCG_S & MCG_S_IRCST_MASK));                     /* wait for 4M IRC              */

            } else if (SYS_MCGIRCLK_INPUT == SYS_CLK_SOURCE_32KIRC) {
                MCG_C2 &= ~(1u << MCG_C2_IRCS_SHIFT);
                while(MCG_S & MCG_S_IRCST_MASK);                        /* wait for 32K IRC             */
            }
        }
    } else {                                                            /* Disable MCGIRCLK             */
        MCG_C1 &= ~(1u << MCG_C1_IRCLKEN_SHIFT);                        /* Disable MCGIRCLK             */
    }

    /*
     * MCGPFLLCLK clock config
     */
    if (MCG_C6 & MCG_C6_PLLS_MASK) {                                    /* PLL is selected              */
        SIM_SOPT2 |=  (1u << SIM_SOPT2_PLLFLLSEL_SHIFT);                /* MCGPLLCLK clock is PLL clock */
    } else {
        SIM_SOPT2 &= ~(1u << SIM_SOPT2_PLLFLLSEL_SHIFT);                /* MCGPLLCLK clock is FLL clock */
    }

    /*
     * OSCERCLK clock config
     */
    if (SYS_OSCERCLK_EN) {                                              /* Enable OSCERCLK              */
        OSC_CR |=  (1u << OSC_CR_ERCLKEN_SHIFT);
    } else {
        OSC_CR &= ~(1u << OSC_CR_ERCLKEN_SHIFT);
    }
    /*
     * ERCLK32K clock config
     */
    if (SYS_ERCLK32K_INPUT == SYS_CLK_SOURCE_RTC) {
        SIM_SOPT1 |=  (1u << SIM_SOPT1_OSC32KSEL_SHIFT);
    } else if (SYS_ERCLK32K_INPUT == SYS_CLK_SOURCE_MOSC) {
        SIM_SOPT1 &= ~(1u << SIM_SOPT1_OSC32KSEL_SHIFT);
    }
}

/*********************************************************************************************************
** Function name:           sysClkGet
** Descriptions:            get clock 获取时钟
** Input parameters:        ulClk   : e.g. SYS_CORE、SYS_BUS.
** Output parameters:       none
** Returned value:          none
** Created by:              Steven Zhou
** Created date:            2011-10-25
**--------------------------------------------------------------------------------------------------------
** Modified by:             Fan Linyun
** Modified date:           2012-07-18
*********************************************************************************************************/
INT32U  sysClkGet (INT32U  ulClk)
{
    INT32U  ulMcgFllClk;
    INT32U  ulMcgFllInputClk;
    INT32U  ulMcgPllClk;
    INT32U  ulMcgOutClk;

    INT32U  ulTmp;
    /*
     * Get MCGFLLCLK
     */
    if (MCG_C1 & MCG_C1_IREFS_MASK) {                                   /* 32K IRC                      */
        ulMcgFllInputClk = SYS_32KIRC_FRQ;                              /* 32K IRC                      */
    } else {
        if (SIM_SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) {
            ulMcgFllInputClk = SYS_RTC_FRQ;                             /* RTC                          */
        } else {
            ulMcgFllInputClk = SYS_MOSC_FRQ;                            /* Main oscillation             */
        }

        switch ((MCG_C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT) {

        case 0:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 32;
            } else {
                ulTmp = 1;
            }
            break;

        case 1:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 64;
            } else {
                ulTmp = 2;
            }
            break;

        case 2:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 128;
            } else {
                ulTmp = 4;
            }
            break;

        case 3:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 256;
            } else {
                ulTmp = 8;
            }
            break;

        case 4:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 512;
            } else {
                ulTmp = 16;
            }
            break;

        case 5:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 1024;
            } else {
                ulTmp = 32;
            }
            break;

        case 6:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 1280;
            } else {
                ulTmp = 64;
            }
            break;

        case 7:
            if (MCG_C2 & MCG_C2_RANGE0_MASK) {
                ulTmp = 1536;
            } else {
                ulTmp = 128;
            }
            break;

        default:
            ulTmp = 1;
            break;
        }
        ulMcgFllInputClk /= ulTmp;
    }
    switch ((MCG_C4 & MCG_C4_DRST_DRS_MASK) >> MCG_C4_DRST_DRS_SHIFT) { /* DRST_DRS                     */

    case 0:
        if (MCG_C4 & MCG_C4_DMX32_MASK) {
            ulMcgFllClk = ulMcgFllInputClk * 732;
        } else {
            ulMcgFllClk = ulMcgFllInputClk * 640;
        }
        break;

    case 1:
        if (MCG_C4 & MCG_C4_DMX32_MASK) {
            ulMcgFllClk = ulMcgFllInputClk * 1464;
        } else {
            ulMcgFllClk = ulMcgFllInputClk * 1280;
        }
        break;

    case 2:
        if (MCG_C4 & MCG_C4_DMX32_MASK) {
            ulMcgFllClk = ulMcgFllInputClk * 2197;
        } else {
            ulMcgFllClk = ulMcgFllInputClk * 1920;
        }
        break;

    case 3:
        if (MCG_C4 & MCG_C4_DMX32_MASK) {
            ulMcgFllClk = ulMcgFllInputClk * 2929;
        } else {
            ulMcgFllClk = ulMcgFllInputClk * 2560;
        }
        break;

    default:
        ulMcgFllClk = 0;
        break;
    }

    /*
     *   Get MCGPLLCLK
     */
    if (SIM_SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) {
        ulMcgPllClk = SYS_RTC_FRQ;                                      /* RTC                          */
    } else {
        ulMcgPllClk = SYS_MOSC_FRQ;                                     /* Main oscillation             */
    }
    ulMcgPllClk /= ((MCG_C5 & MCG_C5_PRDIV0_MASK) >> MCG_C5_PRDIV0_SHIFT) + 1;
                                                                        /* PLL input clock frequency    */
    ulMcgPllClk *= ((MCG_C6 & MCG_C6_VDIV0_MASK) >> MCG_C6_VDIV0_SHIFT) + 24;

    /*
     *   Get MCGOUTCLK
     */
    ulTmp = (MCG_C1 & MCG_C1_CLKS_MASK) >> MCG_C1_CLKS_SHIFT;
    if (ulTmp == 0) {                                                   /* FLL or PLL                   */
        if (MCG_C6 & MCG_C6_PLLS_MASK) {
            ulMcgOutClk = ulMcgPllClk;
        } else {
            ulMcgOutClk = ulMcgFllClk;
        }
    } else if (ulTmp == 1) {                                            /* Internal clock               */
        if (MCG_C2 & MCG_C2_IRCS_MASK) {
            ulMcgOutClk = SYS_4MIRC_FRQ >> 1;                           /* 4M IRC / 2                   */
        } else {
            ulMcgOutClk = SYS_32KIRC_FRQ;                               /* 32K IRC                      */
        }
    } else if (ulTmp == 2) {                                            /* Extern oscillation           */
        if (SIM_SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) {
            ulMcgOutClk = SYS_RTC_FRQ;                                  /* RTC                          */
        } else {
            ulMcgOutClk = SYS_MOSC_FRQ;                                 /* Main oscillation             */
        }
    } else {
        ulMcgOutClk = 0;
    }

    switch (ulClk) {

    case SYS_CORE:                                                      /* Core/System clock in Kinetis */
        return (ulMcgOutClk /
                (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1));

    case SYS_BUS:                                                       /* Bus clock         in Kinetis */
        return (ulMcgOutClk /
                (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> SIM_CLKDIV1_OUTDIV2_SHIFT) + 1));

    case SYS_FLEXBUS:                                                   /* FlexBus clock     in Kinetis */
        return (ulMcgOutClk /
                (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV3_MASK) >> SIM_CLKDIV1_OUTDIV3_SHIFT) + 1));

    case SYS_FLASH:                                                     /* Flash clock       in Kinetis */
        return (ulMcgOutClk /
                (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1));

    case SYS_MCGIRCLK:                                                  /* MCGIRCLK clock    in Kinetis */
        if (MCG_C1 & MCG_C1_IRCLKEN_MASK) {                             /* MCGIRCLK enable              */
            if (MCG_C2 & MCG_C2_IRCS_MASK) {
                return (SYS_4MIRC_FRQ >> 1);
            } else {
                return (SYS_32KIRC_FRQ);
            }
        } else {                                                        /* MCGIRCLK disable             */
            return (0);
        }

    case SYS_MCGFFCLK:                                                  /* MCGFFCLK clock    in Kinetis */
        return (ulMcgFllInputClk >> 1);

    case SYS_MCGFPLLCLK:                                                /* FLL or PLL clock  in Kinetis */
        if (MCG_C2 & MCG_C2_LP_MASK) {                                  /* FLL and PLL disable          */
            return (0);
        }
        if (SIM_SOPT2 & SIM_SOPT2_PLLFLLSEL_MASK) {
            return (ulMcgPllClk);
        } else {
            return (ulMcgFllClk);
        }

    case SYS_OSCERCLK:                                                  /* OSCERCLK clock    in Kinetis */
        if (OSC_CR & OSC_CR_ERCLKEN_MASK) {                             /* OSCERCLK enable              */
            return (SYS_MOSC_FRQ);
        } else {                                                        /* OSCERCLK disable             */
            return (0);
        }

    case SYS_ERCLK32K:                                                  /* ERCLK32K clock    in Kinetis */
        if (SIM_SOPT1 & SIM_SOPT1_OSC32KSEL_MASK) {
            return (SYS_RTC_FRQ);
        } else {
            return (SYS_MOSC_FRQ);
        }

    case SYS_LPO:                                                       /* LPO clock         in Kinetis */
        return (1000);

    default:
        break;
    }
    return (0);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
