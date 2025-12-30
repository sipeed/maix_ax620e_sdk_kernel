/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <string.h>
#include <stdlib.h>

#include "osal_type_ax.h"
#include "rtdebug.h"
#include "rtdef.h"
#include "rtthread.h"
#include "cmm_headh.h"

#if 0
    extern void *get_cache_heap();
    extern void *get_noncache_heap(const char *name);
#endif

#define AX_ARMV7_CACHELINE (64)

static ax_zone_t *__get_zone(enum ax_heap_type HEAP_TYPE)
{
    struct ax_zone *zone;

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    if (HEAP_TYPE == AX_CACHE_HEAP) {
        zone = &platform_cmm_cache_zone;
    } else if (HEAP_TYPE == AX_NONCACHE_HEAP) {
        zone = &platform_cmm_noncache_zone;
    }
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    if (HEAP_TYPE == AX_CACHE_HEAP) {
        zone = &platform_cmm_cache_zone;
    } else if (HEAP_TYPE == AX_NPU_NONCACHE_HEAP) {
        zone = &platform_cmm_noncache_zone_npu;
    } else if (HEAP_TYPE == AX_ISP_NONCACHE_HEAP) {
        zone = &platform_cmm_noncache_zone_isp;
    } else {
        rt_kprintf("Warning, Func[%s, %d] Not found zone type '%d'\n", __FUNCTION__, __LINE__, HEAP_TYPE);
    }

#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    return zone;
}

ax_zone_block_t *__alloc_zone_block(AX_U32 fromuser_size, AX_U32 size, AX_VOID *rtt_vir_addr, AX_S8 *token,
                                    AX_U32 align)
{
    ax_zone_block_t *block = rt_malloc(sizeof(ax_zone_block_t));
    if (RT_NULL == block) {
        return RT_NULL;
    }

    rt_memset(block, 0, sizeof(ax_zone_block_t));

    rt_list_init(&block->block_list);
    block->real_size = fromuser_size;
    block->rtt_vir_addr = rtt_vir_addr;
    block->vir_addr = (AX_VOID *) RT_ALIGN((AX_U32)((AX_U32 *)rtt_vir_addr), align);

    //rt_kprintf("Function[%s, %d] block->vir_addr=0x%x\n", __FUNCTION__,__LINE__,(unsigned int)((unsigned int *)(block->vir_addr)));
    return block;
}

ax_zone_block_t *__get_zone_block(AX_VOID *vir_addr)
{
    ax_zone_block_t *block;
    struct ax_zone *pzone = __get_zone(AX_CACHE_HEAP);;

    rt_list_for_each_entry(block, &pzone->list, block_list) {
        //rt_kprintf("Function[%s, %d] vir_addr=0x%x\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(vir_addr)));
        RT_ASSERT(block != RT_NULL);
        //rt_kprintf("Function[%s, %d] block->vir_addr=0x%x\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(block->vir_addr)));
        if ((AX_U32)block->vir_addr == (AX_U32)vir_addr)
            return block;
    }
#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    pzone = __get_zone(AX_NONCACHE_HEAP);
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    unsigned int k_addr = (unsigned int)vir_addr;
    if (k_addr >= (unsigned int)SYS_NPU_CMM_NONCACHE_ADDRESS_FST &&
        k_addr <= (unsigned int)SYS_NPU_CMM_NONCACHE_ADDRESS_END) {
        //rt_kprintf("Info, Function[%s, %d] vir_addr=0x%x, in NPU heap\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(vir_addr)));
        pzone = __get_zone(AX_NPU_NONCACHE_HEAP);
    } else if (k_addr >= (unsigned int)SYS_ISP_CMM_NONCACHE_ADDRESS_FST &&
               k_addr <= (unsigned int)SYS_ISP_CMM_NONCACHE_ADDRESS_END) {
        //rt_kprintf("Info, Function[%s, %d] vir_addr=0x%x, in ISP heap\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(vir_addr)));
        pzone = __get_zone(AX_ISP_NONCACHE_HEAP);
    } else {
        rt_kprintf("Warning, Func[%s, %d] invalid address '0x%x'\n", __FUNCTION__, __LINE__, k_addr);
        return RT_NULL;
    }
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    rt_list_for_each_entry(block, &pzone->list, block_list) {
        //rt_kprintf("Function[%s, %d] vir_addr=0x%x\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(vir_addr)));
        RT_ASSERT(block != RT_NULL);
        //rt_kprintf("Function[%s, %d] block->vir_addr=0x%x\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(block->vir_addr)));
        if ((AX_U32)block->vir_addr == (AX_U32)vir_addr)
            return block;
    }

    //rt_kprintf("Warning, Function[%s, %d] vir_addr=0x%x, Not found block\n", __FUNCTION__, __LINE__,(unsigned int)((unsigned int *)(vir_addr)));

    return RT_NULL;
}

static AX_S32 __memAllocFromHeap(struct rt_memheap *heap, AX_U64 *phyaddr, AX_VOID **ppviraddr, AX_U32 size,
                                 AX_U32 align, AX_S8 *token, enum ax_heap_type HEAP_TYPE)
{
    AX_VOID *rtt_vir_addr = RT_NULL;
    rt_size_t fromuser_size = size;
    /*ARMA7 cacheline is 64byte*/

    size = RT_ALIGN(size, AX_ARMV7_CACHELINE);
    if (align <= AX_ARMV7_CACHELINE) {
        align = AX_ARMV7_CACHELINE;
    } else {
        align = RT_ALIGN(align, AX_ARMV7_CACHELINE);
    }
    //size = RT_ALIGN(size, align);
    rtt_vir_addr = rt_memheap_alloc(heap, (rt_size_t)size + (rt_size_t)align);
    //rtt_vir_addr = rt_memheap_alloc(heap, (rt_size_t)size);
    if (RT_NULL == rtt_vir_addr) {
        return -1;
    }

    //if(HEAP_TYPE == AX_CACHE_HEAP)
    //  rt_kprintf("Function[%s, %d] type=cached\n", __FUNCTION__, __LINE__);
    //else if(HEAP_TYPE == AX_NONCACHE_HEAP)
    //  rt_kprintf("Function[%s, %d] type=noncached\n", __FUNCTION__, __LINE__);

    //rt_kprintf("Function[%s, %d] token=%s\n", __FUNCTION__, __LINE__,token);
    //rt_kprintf("Function[%s, %d] fromuser_size=%d\n", __FUNCTION__, __LINE__,fromuser_size);
    //rt_kprintf("Function[%s, %d] size=%d\n", __FUNCTION__, __LINE__,size);
    //rt_kprintf("Function[%s, %d] align=%d\n", __FUNCTION__, __LINE__,align);
    //rt_kprintf("Function[%s, %d] rtt_vir_addr=0x%x\n", __FUNCTION__,__LINE__,(unsigned int)((unsigned int *)rtt_vir_addr));

    ax_zone_block_t *block = __alloc_zone_block(fromuser_size, size, rtt_vir_addr, token, align);
    if (RT_NULL == block) {
        return -1;
    }

#if 0
    //*phyaddr = (AX_U64) ((AX_U64 *)vaddr);
    *phyaddr = (AX_U32)((AX_U32 *)vaddr);
    *ppviraddr = (AX_VOID *)vaddr;
#endif
    *phyaddr = (AX_U32)((AX_U32 *)block->vir_addr);
    *ppviraddr = (AX_VOID *)block->vir_addr;

    struct ax_zone *pzone = __get_zone(HEAP_TYPE);
    RT_ASSERT(pzone != RT_NULL);
    rt_list_insert_after(&pzone->list, &block->block_list);

    return 0;
}

static enum ax_heap_type __heap_type_changed(const AX_S8 *token)
{
    if (token) {
        if (strcmp(token, AX_NPU_NAME) == 0) {
            //rt_kprintf("Function[%s, %d] change heap(%s), enter\n", __FUNCTION__, __LINE__, AX_NPU_NAME);
            return AX_NPU_NONCACHE_HEAP;
        } else if (strcmp(token, AX_ISP_NAME) == 0) {
            //rt_kprintf("Function[%s, %d] get heap(%s), enter\n", __FUNCTION__, __LINE__, AX_ISP_NAME);
            return AX_ISP_NONCACHE_HEAP;
        }
    }

    //rt_kprintf("Warning, Func[%s, %d] change name is invalid (only is 'isp' and 'npu' in preisp) '%s'\n", __FUNCTION__,  __LINE__, token);
#if 0
    if (__noncache_heap_npu.pool_size > 0) {
        rt_kprintf("Function[%s, %d] change heap(%s), enter\n", __FUNCTION__, __LINE__, AX_NPU_NAME);
        return (unsigned int)AX_NPU_NONCACHE_HEAP;
    }

    if (__noncache_heap_isp.pool_size > 0) {
        rt_kprintf("Function[%s, %d] change heap(%s), enter\n", __FUNCTION__, __LINE__, AX_ISP_NAME);
        return (unsigned int)AX_ISP_NONCACHE_HEAP;
    }

    rt_kprintf("Warning, Func[%s, %d] change name   '%s' , last decision\n", __FUNCTION__, \
               __LINE__, token);
#endif
    return AX_ISP_NONCACHE_HEAP;
}

AX_S32 cmm_MemAlloc(AX_U64 *phyaddr, AX_VOID **ppviraddr, AX_U32 size, AX_U32 align, AX_S8 *token,
                    enum ax_heap_type HEAP_TYPE)
{
    struct rt_memheap *heap = RT_NULL;

    //rt_kprintf("Function[%s, %d] block name is '%s' , HEAP_TYPE = %d\n", __FUNCTION__, __LINE__, token, HEAP_TYPE);

    if (HEAP_TYPE == AX_CACHE_HEAP) {
        heap = get_cache_heap();
    } else if (HEAP_TYPE == AX_NONCACHE_HEAP) {
        //rt_kprintf("Function[%s, %d] block name is '%s'\n", __FUNCTION__, __LINE__, token);
        heap = get_noncache_heap(token);
    }

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    RT_ASSERT(heap != RT_NULL);
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    //rt_kprintf("Function[%s, %d] get heap, enter\n", __FUNCTION__, __LINE__);

    if (heap == RT_NULL)
        return RT_NULL;
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    //rt_kprintf("Function[%s, %d] get heap, exit\n", __FUNCTION__, __LINE__);

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    return __memAllocFromHeap(heap, phyaddr, ppviraddr, size, align, token, HEAP_TYPE);
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    if (HEAP_TYPE == AX_CACHE_HEAP) {
        return __memAllocFromHeap(heap, phyaddr, ppviraddr, size, align, token, HEAP_TYPE);
    } else {
        enum ax_heap_type heaptype_c = __heap_type_changed(token);

        //rt_kprintf("Function[%s, %d] get heap, change heap type from '%d' to '%d'\n", __FUNCTION__, __LINE__, HEAP_TYPE, heaptype_c);
        return __memAllocFromHeap(heap, phyaddr, ppviraddr, size, align, token, heaptype_c);
    }

#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
}

AX_S32 cmm_MemFree(AX_VOID *pviraddr)
{
    if (pviraddr == RT_NULL)
        return -1;

    ax_zone_block_t *block = __get_zone_block(pviraddr);
    RT_ASSERT(block != RT_NULL);

    rt_memheap_free(block->rtt_vir_addr);
    rt_list_remove(&block->block_list);
    rt_free(block);
    return 0;
}

AX_S32 cmm_MemFlushCache(AX_VOID *pviraddr, AX_U32 size)
{
    if (pviraddr == RT_NULL)
        return -1;

    extern void rt_hw_cpu_dcache_clean(void *addr, int size);

    rt_hw_cpu_dcache_clean(pviraddr, size);
    return 0;
}

AX_S32 cmm_MemInvalidateCache(AX_VOID *pviraddr, AX_U32 size)
{
    if (pviraddr == RT_NULL)
        return -1;

    extern void rt_hw_cpu_dcache_invalidate(void *addr, int size);

    rt_hw_cpu_dcache_invalidate(pviraddr, size);
    return 0;
}



