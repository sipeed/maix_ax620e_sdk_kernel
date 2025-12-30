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

AX_S32 AX_OSAL_SYNC_sema_init(AX_SEMAPHORE_T *osal_sem, AX_S32 val)
{
    struct rt_semaphore *rt_sem;

    RT_ASSERT(osal_sem != RT_NULL);


    rt_sem = rt_sem_create("OSAL_SEMA", val, RT_IPC_FLAG_FIFO);
    if (rt_sem == NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    osal_sem->sem = rt_sem;

    return RT_EOK;
}

//RTT not support
AX_S32 AX_OSAL_SYNC_sema_down_interruptible(AX_SEMAPHORE_T *osal_sem)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

AX_S32 AX_OSAL_SYNC_sema_down(AX_SEMAPHORE_T *osal_sem)
{
    struct rt_semaphore *rt_sem;
    rt_err_t ret;

    RT_ASSERT(osal_sem != RT_NULL);
    rt_sem = (struct rt_semaphore *)(osal_sem->sem);
    RT_ASSERT(rt_sem != RT_NULL);

    ret = rt_sem_take(rt_sem, RT_WAITING_FOREVER);

    return ret;
}

AX_S32 AX_OSAL_SYNC_sema_down_trylock(AX_SEMAPHORE_T *osal_sem)
{
    struct rt_semaphore *rt_sem;
    rt_err_t ret;

    RT_ASSERT(osal_sem != RT_NULL);
    rt_sem = (struct rt_semaphore *)(osal_sem->sem);
    RT_ASSERT(rt_sem != RT_NULL);

    ret = rt_sem_trytake(rt_sem);

    return ret;
}

AX_VOID AX_OSAL_SYNC_sema_up(AX_SEMAPHORE_T *osal_sem)
{
    struct rt_semaphore *rt_sem;
    rt_err_t ret;

    RT_ASSERT(osal_sem != RT_NULL);
    rt_sem = (struct rt_semaphore *)(osal_sem->sem);
    RT_ASSERT(rt_sem != RT_NULL);

    ret = rt_sem_release(rt_sem);

    RT_ASSERT(ret == RT_EOK);
    return;
}

AX_VOID AX_OSAL_SYNC_sema_destroy(AX_SEMAPHORE_T *osal_sem)
{
    struct rt_semaphore *rt_sem;

    RT_ASSERT(osal_sem != RT_NULL);
    rt_sem = (struct rt_semaphore *)(osal_sem->sem);
    RT_ASSERT(rt_sem != RT_NULL);

    rt_sem_delete(rt_sem);
    osal_sem->sem = RT_NULL;

    return;
}

