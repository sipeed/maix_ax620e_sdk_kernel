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

#include "waitqueue.h"

AX_S32 AX_OSAL_SYNC_waitqueue_init(AX_WAIT_T *osal_wait)
{
    RT_ASSERT(osal_wait != RT_NULL);

    struct rt_wqueue *rt_wait;
    rt_wait = (struct rt_wqueue *)rt_malloc(sizeof(struct rt_wqueue));
    if (rt_wait == NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

	rt_list_init(&rt_wait->waiting_list);
	rt_wait->flag = RT_WQ_FLAG_CLEAN;

    osal_wait->wait = (void *)rt_wait;
    return 0;
}

AX_U32 AX_OSAL_SYNC_wait_uninterruptible(AX_WAIT_T *osal_wait, AX_WAIT_COND_FUNC_T func, AX_VOID *param)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;
    int condition = 0;

    if (func) {
        condition = func(param);
    }

    rt_wqueue_wait(wait_queue, condition, RT_WAITING_FOREVER);

    return 0;
}

//AX_OSAL_SYNC_wait_interruptible is the same as AX_OSAL_SYNC_wait_uninterruptible in RTT
AX_U32 AX_OSAL_SYNC_wait_interruptible(AX_WAIT_T *osal_wait, AX_WAIT_COND_FUNC_T func, AX_VOID *param)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;
    int condition = 0;

    if (func) {
        condition = func(param);
    }

    rt_wqueue_wait(wait_queue, condition, RT_WAITING_FOREVER);

    return 0;
}

AX_U32 AX_OSAL_SYNC_wait_uninterruptible_timeout(AX_WAIT_T *osal_wait, AX_WAIT_COND_FUNC_T func, AX_VOID *param,
        AX_ULONG timeout)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;
    int condition = 0;

    if (func) {
        condition = func(param);
    }

    return rt_wqueue_wait(wait_queue, condition, (int)timeout);
}

//AX_OSAL_SYNC_wait_interruptible_timeout is the same as AX_OSAL_SYNC_wait_uninterruptible_timeout in RTT
AX_U32 AX_OSAL_SYNC_wait_interruptible_timeout(AX_WAIT_T *osal_wait, AX_WAIT_COND_FUNC_T func, AX_VOID *param,
        AX_ULONG timeout)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;
    int condition = 0;

    if (func) {
        condition = func(param);
    }

    return rt_wqueue_wait(wait_queue, condition, (int)timeout);
}

AX_VOID AX_OSAL_SYNC_wakeup(AX_WAIT_T *osal_wait, AX_VOID *key)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;

    rt_wqueue_wakeup(wait_queue, key);

    return ;
}

AX_VOID AX_OSAL_SYNC_wake_up_interruptible(AX_WAIT_T *osal_wait, AX_VOID *key)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;

    rt_wqueue_wakeup(wait_queue, key);

    return ;
}

AX_VOID AX_OSAL_SYNC_wake_up_interruptible_all(AX_WAIT_T *osal_wait, AX_VOID *key)
{
	RT_ASSERT(osal_wait != RT_NULL);
	RT_ASSERT(osal_wait->wait != RT_NULL);
	struct rt_wqueue *wait_queue = (struct rt_wqueue *)osal_wait->wait;
	rt_wqueue_wakeup(wait_queue, key);
	return ;
}
AX_VOID AX_OSAL_SYNC_wait_destroy(AX_WAIT_T *osal_wait)
{
    RT_ASSERT(osal_wait != RT_NULL);
    RT_ASSERT(osal_wait->wait != RT_NULL);

    rt_free(osal_wait->wait);
    osal_wait->wait = RT_NULL;

    return ;
}
