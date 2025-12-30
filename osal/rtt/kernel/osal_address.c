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


AX_VOID *AX_OSAL_DEV_ioremap(AX_ULONG phys_addr, AX_ULONG size)
{
    return (AX_ULONG *)phys_addr;
}

AX_VOID *AX_OSAL_DEV_ioremap_nocache(AX_ULONG phys_addr, AX_ULONG size)
{
    return (AX_ULONG *)phys_addr;
}

AX_VOID *AX_OSAL_DEV_ioremap_cache(AX_ULONG phys_addr, AX_ULONG size)
{
    return (AX_ULONG *)phys_addr;
}

//RTT not support
AX_VOID AX_OSAL_DEV_iounmap(AX_VOID *addr)
{
    RT_ASSERT(addr != RT_NULL);
    return ;
}

AX_ULONG AX_OSAL_DEV_copy_from_user(AX_VOID *to, const AX_VOID *from, AX_ULONG n)
{
	RT_ASSERT(to != RT_NULL);
	RT_ASSERT(from != RT_NULL);

    rt_memcpy(to, from, n);

    return 0;
}

AX_ULONG AX_OSAL_DEV_copy_to_user(AX_VOID *to, const AX_VOID *from, AX_ULONG n)
{
	RT_ASSERT(to != RT_NULL);
	RT_ASSERT(from != RT_NULL);

    rt_memcpy(to, from, n);
    return 0;
}


