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

#include "rtdebug.h"
#include "rtdef.h"
#include "cmm_headh.h"
#include "rtthread.h"

/** Func: initialize cmm service system
 *
 * Param: none
 * Return: none
 */
struct ax_zone platform_cmm_cache_zone;

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    struct ax_zone platform_cmm_noncache_zone;
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    struct ax_zone platform_cmm_noncache_zone_npu;
    struct ax_zone platform_cmm_noncache_zone_isp;
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/


#ifdef RT_USING_MEMHEAP
static struct rt_memheap __cache_heap;

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    static struct rt_memheap __noncache_heap;
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    static struct rt_memheap __noncache_heap_npu;
    static struct rt_memheap __noncache_heap_isp;
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

static rt_size_t __get_heap_size(enum ax_heap_type heap_type)
{
    rt_size_t zone_size = 0;
#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    if (heap_type == AX_CACHE_HEAP) {
        zone_size = platform_cmm_cache_zone.size;
    } else if (heap_type == AX_NONCACHE_HEAP) {
        zone_size = platform_cmm_noncache_zone.size;
    }
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    if (heap_type == AX_CACHE_HEAP) {
        zone_size = platform_cmm_cache_zone.size;
    } else if (heap_type == AX_NPU_NONCACHE_HEAP) {
        zone_size = platform_cmm_noncache_zone_npu.size;
    } else if (heap_type == AX_ISP_NONCACHE_HEAP) {
        zone_size = platform_cmm_noncache_zone_isp.size;
    }
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    RT_ASSERT(zone_size != 0);

    return zone_size;
}
static void *__get_heap_start(enum ax_heap_type heap_type)
{
    void *addr = RT_NULL;

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    if (heap_type == AX_CACHE_HEAP) {
        addr = (void *) platform_cmm_cache_zone.phy_addr;
    } else if (heap_type == AX_NONCACHE_HEAP) {
        addr = (void *) platform_cmm_noncache_zone.phy_addr;
    }
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    if (heap_type == AX_CACHE_HEAP) {
        addr = (void *) platform_cmm_cache_zone.phy_addr;
    } else if (heap_type == AX_NPU_NONCACHE_HEAP) {
        addr = (void *) platform_cmm_noncache_zone_npu.phy_addr;
    } else if (heap_type == AX_ISP_NONCACHE_HEAP) {
        addr = (void *) platform_cmm_noncache_zone_isp.phy_addr;
    }

#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    RT_ASSERT(addr != RT_NULL);

    return addr;
}

void *get_cache_heap()
{
#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    RT_ASSERT(__cache_heap.pool_size != 0);
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    return (void *) &__cache_heap;
}

void *get_noncache_heap(const char *name)
{
#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    RT_ASSERT(__noncache_heap.pool_size != 0);
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    return (void *) &__noncache_heap;
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    //rt_kprintf("Function[%s, %d] get heap(%s)\n", __FUNCTION__, __LINE__, name);

    if (strcmp(name, AX_NPU_NAME) == 0) {
        //rt_kprintf("Function[%s, %d] get heap(%s), enter\n", __FUNCTION__, __LINE__, AX_NPU_NAME);

        //RT_ASSERT(__noncache_heap_npu.pool_size != 0);

        if (__noncache_heap_npu.pool_size > 0) {
            return (void *) &__noncache_heap_npu;
        } else {
            return RT_NULL;
        }

        //return (void *) &__noncache_heap_npu;
    } else if (strcmp(name, AX_ISP_NAME) == 0) {
        //rt_kprintf("Function[%s, %d] get heap(%s), enter\n", __FUNCTION__, __LINE__, AX_ISP_NAME);

        //RT_ASSERT(__noncache_heap_isp.pool_size != 0);
        if (__noncache_heap_isp.pool_size > 0) {
            return (void *) &__noncache_heap_isp;
        } else {
            return RT_NULL;
        }
        //return (void *) &__noncache_heap_isp;
    } else {
        //rt_kprintf("Warning, Func[%s, %d] block name is invalid (only is 'isp' and 'npu' in preisp) '%s'\n", __FUNCTION__, __LINE__, name);

        if (__noncache_heap_isp.pool_size > 0) {
            //rt_kprintf("Function[%s, %d] get heap(%s), enter\n", __FUNCTION__, __LINE__, AX_ISP_NAME);
            return (void *) &__noncache_heap_isp;
        }

        if (__noncache_heap_npu.pool_size > 0) {
            //rt_kprintf("Function[%s, %d] get heap(%s), enter\n", __FUNCTION__, __LINE__, AX_NPU_NAME);
            return (void *) &__noncache_heap_npu;
        }
    }
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    rt_kprintf("Warning, Func[%s, %d] Not find valid heap '%s'\n", __FUNCTION__, \
               __LINE__, name);

    return RT_NULL;
}

int ax_cmm_cache_init(rt_uint32_t phy_addr, rt_size_t size, const char *name)
{

    RT_ASSERT(phy_addr != 0);
    RT_ASSERT(size != 0);
    RT_ASSERT(name != RT_NULL);

    char *pname = (char *)platform_cmm_cache_zone.name;

    platform_cmm_cache_zone.phy_addr = phy_addr;
    platform_cmm_cache_zone.size = size;
    rt_strncpy(pname, name, AX_CMM_NAME_LEN);

    rt_list_init(&platform_cmm_cache_zone.list);

    return 0;
}


int ax_cmm_noncache_init(rt_uint32_t phy_addr, rt_size_t size, const char *name)
{
    RT_ASSERT(phy_addr != 0);
    RT_ASSERT(size != 0);
    RT_ASSERT(name != RT_NULL);

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    char *pname = (char *)platform_cmm_noncache_zone.name;

    platform_cmm_noncache_zone.phy_addr = phy_addr;
    platform_cmm_noncache_zone.size = size;
    rt_strncpy(pname, name, AX_CMM_NAME_LEN);

    rt_list_init(&platform_cmm_noncache_zone.list);
#else  /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    if (strcmp(name, AX_NPU_NAME) == 0) {
        char *pname = (char *)platform_cmm_noncache_zone_npu.name;
        platform_cmm_noncache_zone_npu.phy_addr = phy_addr;
        platform_cmm_noncache_zone_npu.size = size;
        rt_strncpy(pname, name, AX_CMM_NAME_LEN);

        rt_list_init(&platform_cmm_noncache_zone_npu.list);
    } else {
        rt_kprintf("Warning, Func[%s, %d] Not found heap name '%s'\n", __FUNCTION__, __LINE__, name);
    }

    /*
        rt_kprintf("Warning, addr = 0x%x, size = 0x%x,  name =%s \n", \
                   platform_cmm_noncache_zone_npu.phy_addr, \
                   platform_cmm_noncache_zone_npu.size, name);
    */
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    return 0;
}

int ax_cmm_isp_noncache_init(rt_uint32_t phy_addr, rt_size_t size, const char *name)
{
#ifdef AX_SYS_MEMLAYOUT_AX170_PREISP
    char *pname;

    pname = (char *)platform_cmm_noncache_zone_isp.name;

    platform_cmm_noncache_zone_isp.phy_addr = phy_addr;
    platform_cmm_noncache_zone_isp.size = size;
    rt_strncpy(pname, name, AX_CMM_NAME_LEN);
    rt_list_init(&platform_cmm_noncache_zone_isp.list);

    /*initialize non-cache heap*/
    rt_memheap_init(&__noncache_heap_isp, "ISP_noncache_heap", \
                    __get_heap_start(AX_ISP_NONCACHE_HEAP), \
                    __get_heap_size(AX_ISP_NONCACHE_HEAP));

#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    return 0;
}

int ax_cmm_isp_noncache_deinit(void)
{
    int ret = -1;
#ifdef AX_SYS_MEMLAYOUT_AX170_PREISP
    if (platform_cmm_noncache_zone_isp.size > 0) {
        platform_cmm_noncache_zone_isp.phy_addr = 0;
        platform_cmm_noncache_zone_isp.size = 0;
        rt_list_init(&platform_cmm_noncache_zone_isp.list);

        ret = rt_memheap_detach(&__noncache_heap_isp);
    }
#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/
    return ret;
}

static int __ax_cmm_sys_init(void)
{
    /*initialize cache heap*/
    rt_memheap_init(&__cache_heap, "ax_cache_heap", \
                    __get_heap_start(AX_CACHE_HEAP), \
                    __get_heap_size(AX_CACHE_HEAP));

#ifndef AX_SYS_MEMLAYOUT_AX170_PREISP
    //rt_kprintf("Warning, Func[%s, %d] Not found heap name '%s'\n",__FUNCTION__, __LINE__, "2");

    /*initialize non-cache heap*/
    rt_memheap_init(&__noncache_heap, "ax_noncache_heap", \
                    __get_heap_start(AX_NONCACHE_HEAP), \
                    __get_heap_size(AX_NONCACHE_HEAP));
#else
    /*initialize non-cache heap*/
    //rt_kprintf("Warning, Func[%s, %d] Not found heap name '%s'\n",__FUNCTION__, __LINE__, "3");

    rt_kprintf("Info noncache, addr = 0x%x, size = 0x%x, \n", \
               (unsigned int) __get_heap_start(AX_NPU_NONCACHE_HEAP), \
               (unsigned int) __get_heap_size(AX_NPU_NONCACHE_HEAP));

    rt_memheap_init(&__noncache_heap_npu, "NPU_noncache_heap", \
                    __get_heap_start(AX_NPU_NONCACHE_HEAP), \
                    __get_heap_size(AX_NPU_NONCACHE_HEAP));

#endif /*AX_SYS_MEMLAYOUT_AX170_PREISP*/

    return 0;
}

INIT_PREV_EXPORT(__ax_cmm_sys_init);
#endif



