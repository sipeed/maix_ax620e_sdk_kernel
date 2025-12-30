/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_ax.h"
#include "barrier.h"

AX_VOID AX_OSAL_SYNC_mb(AX_VOID)
{
#ifdef RT_USING_SMP
    __smp_mb();
#else /*RT_USING_SMP*/
    mb();
#endif  /*RT_USING_SMP*/

    return ;
}

AX_VOID AX_OSAL_SYNC_rmb(AX_VOID)
{
#ifdef RT_USING_SMP
    __smp_rmb();
#else /*RT_USING_SMP*/
    rmb();
#endif  /*RT_USING_SMP*/

    return ;
}

AX_VOID AX_OSAL_SYNC_wmb(AX_VOID)
{
#ifdef RT_USING_SMP
    __smp_wmb();
#else /*RT_USING_SMP*/
    wmb();
#endif  /*RT_USING_SMP*/

    return ;
}

AX_VOID AX_OSAL_SYNC_isb(AX_VOID)
{
    //asm volatile ("isb");
    //__asm__ volatile ("isb 0xF":::"memory");
    __asm__ __volatile__("isb "  : : : "memory");

    return ;
}

AX_VOID AX_OSAL_SYNC_dsb(AX_VOID)
{
    //asm volatile ("dsb");
    //dsb(option);
    __asm__ __volatile__("dsb "  : : : "memory");

    return ;
}

AX_VOID AX_OSAL_SYNC_dmb(AX_VOID)
{
    //asm volatile ("dmb");
    //dmb(option);
    __asm__ __volatile__("dmb "  : : : "memory");

    return ;
}


