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
#include "rtthread.h"
#include "rtdebug.h"

//kmalloc , memory
AX_VOID *AX_OSAL_MEM_kmalloc(AX_SIZE_T size, AX_U32 osal_gfp_flag)
{
    AX_VOID *ptr = rt_malloc(size);

    return ptr;
}

AX_VOID *AX_OSAL_MEM_kzalloc(AX_SIZE_T size, AX_U32 osal_gfp_flag)
{
    AX_VOID *ptr = rt_malloc(size);

    /* zero the memory */
    if (ptr)
        rt_memset(ptr, 0, size);

    return ptr;
}

AX_VOID AX_OSAL_MEM_kfree(const AX_VOID *addr)
{
    const AX_VOID *ptr = addr;
    rt_free(ptr);

    return ;
}

AX_VOID *AX_OSAL_MEM_vmalloc(AX_SIZE_T size)
{
    AX_VOID *ptr = rt_malloc(size);

    return ptr;
}

AX_VOID AX_OSAL_MEM_vfree(const AX_VOID *addr)
{
    const AX_VOID *ptr = addr;
    rt_free(ptr);

    return ;
}

