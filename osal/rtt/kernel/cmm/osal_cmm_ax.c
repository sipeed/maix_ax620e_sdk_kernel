/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_cmm_ax.h"
#include "cmm_headh.h"

#include "mem_stat.h"

/* Physical continuous memory, no cache. */
AX_S32 AX_OSAL_MemAlloc(AX_U64 *phyaddr, AX_VOID **ppviraddr, AX_U32 size, AX_U32 align, AX_S8 *token)
{
    AX_S32 ret = cmm_MemAlloc(phyaddr, ppviraddr, size, align, token, AX_NONCACHE_HEAP);

    AX_SYS_DBG_MEMSTAT_SET(*ppviraddr, size, rt_tick_get(), token, MEMSTAT_FLAG_CMMNONCACHEHEAP);

    return ret;
}

/* Physical continuous memory, cached */
AX_S32 AX_OSAL_MemAllocCached(AX_U64 *phyaddr, AX_VOID **pviraddr, AX_U32 size, AX_U32 align, AX_S8 *token)
{
    AX_S32 ret = cmm_MemAlloc(phyaddr, pviraddr, size, align, token, AX_CACHE_HEAP);
    AX_SYS_DBG_MEMSTAT_SET(*pviraddr, size, rt_tick_get(), token, MEMSTAT_FLAG_CMMCACHEHEAP);

    return ret;

}
AX_S32 AX_OSAL_MemFlushCache(AX_U64 phyaddr, AX_VOID *pviraddr, AX_U32 size)
{
    AX_S32 ret = cmm_MemFlushCache(pviraddr, size);

    return ret;
}
AX_S32 AX_OSAL_MemInvalidateCache(AX_U64 phyaddr, AX_VOID *pviraddr, AX_U32 size)
{
    AX_S32 ret = cmm_MemInvalidateCache(pviraddr, size);

    return ret;
}
AX_S32 AX_OSAL_MemFree(AX_U64 phyaddr, AX_VOID *pviraddr)
{
    AX_S32 ret = cmm_MemFree(pviraddr);

    AX_SYS_DBG_MEMSTAT_PUT(pviraddr);

    return ret;
}

/* RTOS not support. */
AX_VOID *AX_OSAL_Mmap(AX_U64 phyaddr, AX_U32 size)
{
    return NULL;
}

/* RTOS not support. */
AX_VOID *AX_OSAL_MmapCache(AX_U64 phyaddr, AX_U32 size)
{
    return NULL;
}

/* RTOS not support. */
AX_S32 AX_OSAL_Munmap(AX_VOID *pviraddr)
{
    return -1;
}

/* RTOS not support. */
AX_S32 AX_OSAL_MemGetBlockInfoByPhy(AX_U64 phyaddr, AX_S32 *pmemType, AX_VOID **pviraddr, AX_U32 *pblockSize)
{
    return -1;
}

/* RTOS not support. */
AX_S32 AX_OSAL_MemGetBlockInfoByVirt(AX_VOID *pviraddr, AX_U64 *phyaddr, AX_S32 *pmemType)
{
    return -1;
}



