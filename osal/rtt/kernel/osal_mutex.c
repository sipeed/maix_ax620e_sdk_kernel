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
#include "rtdef.h"
#include "rtthread.h"

AX_S32 AX_OSAL_SYNC_mutex_init(AX_MUTEX_T *osal_mutex)
{
    struct rt_mutex *rt_mutex;

    RT_ASSERT(osal_mutex != RT_NULL);

    rt_mutex = rt_mutex_create("OSAL_mutex", RT_IPC_FLAG_FIFO);

    if (rt_mutex == NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    osal_mutex->mutex = rt_mutex;

    return RT_EOK;
}

AX_S32 AX_OSAL_SYNC_mutex_lock(AX_MUTEX_T *osal_mutex)
{
    struct rt_mutex *rt_mutex;
    rt_err_t ret;

    RT_ASSERT(osal_mutex != RT_NULL);
    rt_mutex = (struct rt_mutex *)(osal_mutex->mutex);
    RT_ASSERT(rt_mutex != RT_NULL);

    ret = rt_mutex_take(rt_mutex, RT_WAITING_FOREVER);
    return ret;
}

//RTT not support
AX_S32 AX_OSAL_SYNC_mutex_lock_interruptible(AX_MUTEX_T *osal_mutex)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

AX_S32 AX_OSAL_SYNC_mutex_trylock(AX_MUTEX_T *osal_mutex)
{
    struct rt_mutex *rt_mutex;
    rt_err_t ret;

    RT_ASSERT(osal_mutex != RT_NULL);
    rt_mutex = (struct rt_mutex *)(osal_mutex->mutex);
    RT_ASSERT(rt_mutex != RT_NULL);

    ret = rt_mutex_trytake(rt_mutex);

    /*return value compat with linux*/
    if (ret == RT_EOK)
        ret = 1; /*Returns 1 if the mutex has been acquired successfully*/
    else
        ret = 0; /*Returns 0 on contention.*/
    return ret;
}

AX_VOID AX_OSAL_SYNC_mutex_unlock(AX_MUTEX_T *osal_mutex)
{
    struct rt_mutex *rt_mutex;
    rt_err_t ret;

    RT_ASSERT(osal_mutex != RT_NULL);
    rt_mutex = (struct rt_mutex *)(osal_mutex->mutex);
    RT_ASSERT(rt_mutex != RT_NULL);

    ret = rt_mutex_release(rt_mutex);
    RT_ASSERT(ret == RT_EOK);

    return ;
}

AX_VOID AX_OSAL_SYNC_mutex_destroy(AX_MUTEX_T *osal_mutex)
{
    struct rt_mutex *rt_mutex;

    RT_ASSERT(osal_mutex != RT_NULL);
    rt_mutex = (struct rt_mutex *)(osal_mutex->mutex);
    RT_ASSERT(rt_mutex != RT_NULL);

    rt_mutex_delete(rt_mutex);
    osal_mutex->mutex = RT_NULL;

    return ;
}


