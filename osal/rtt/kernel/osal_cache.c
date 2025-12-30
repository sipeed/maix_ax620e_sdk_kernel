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
#include "osal_dev_ax.h"
#include "rtthread.h"

AX_VOID AX_OSAL_DEV_invalidate_dcache_area(AX_VOID  *addr, AX_S32 size)
{
    extern void rt_hw_cpu_dcache_invalidate(void *addr, int size);

    rt_hw_cpu_dcache_invalidate(addr, size);

    return ;
}

AX_VOID AX_OSAL_DEV_flush_dcache_area(AX_VOID *kvirt, AX_ULONG length)
{
    extern void rt_hw_cpu_dcache_clean(void *addr, int size);

    rt_hw_cpu_dcache_clean(kvirt, length);

    return ;
}

//RTT not support
AX_VOID AX_OSAL_DEV_flush_dcache_all()
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return ;
}


