/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "rtthread.h"

#include "rtconfig.h"
#include "osal_ax.h"
#include "rthw.h"

extern rt_err_t rt_thread_sleep(rt_tick_t tick);

AX_TASK_T *AX_OSAL_TASK_kthread_run(AX_THREAD_FUNC_T thread, AX_VOID *data, AX_S8 *name)
{
    struct rt_thread *rtt_pthread = RT_NULL;

    AX_TASK_T *osal_pthread = RT_NULL;

    osal_pthread = (AX_TASK_T *)rt_malloc(sizeof(AX_TASK_T));
    if (osal_pthread == NULL) {
        rt_kprintf("%s - rt_malloc error!\n", __FUNCTION__);
        return RT_NULL;
    }
    rt_memset(osal_pthread, 0, sizeof(AX_TASK_T));

    rtt_pthread = (struct rt_thread *)rt_thread_create(name, (void *)thread, data,
                  IDLE_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);
    if (rtt_pthread == RT_NULL) {
        rt_kprintf("%s - rt_thread_create error!\n", __FUNCTION__);
        goto errout;
    }

    rtt_pthread->ax_flag = 0;
    osal_pthread->task_struct = rtt_pthread;
    rt_thread_startup(osal_pthread->task_struct);

    return (struct AX_TASK *) osal_pthread;

errout:
    if (osal_pthread) {
        rt_free(osal_pthread);
    }
    return RT_NULL;
}

AX_TASK_T *AX_OSAL_TASK_kthread_create_ex(AX_THREAD_FUNC_T thread, AX_VOID *data,
        AX_S8 *name, AX_S32 prioirty)
{
    struct rt_thread *rtt_pthread = RT_NULL;

    AX_TASK_T *osal_pthread = RT_NULL;
    if (prioirty > RT_THREAD_PRIORITY_MAX - 2)
        prioirty = RT_THREAD_PRIORITY_MAX - 2;

    osal_pthread = (AX_TASK_T *)rt_malloc(sizeof(AX_TASK_T));
    if (osal_pthread == NULL) {
        rt_kprintf("%s - rt_malloc error!\n", __FUNCTION__);
        return RT_NULL;
    }
    rt_memset(osal_pthread, 0, sizeof(AX_TASK_T));

    rtt_pthread = (struct rt_thread *)rt_thread_create(name, (void *)thread, data,
                  IDLE_THREAD_STACK_SIZE, prioirty, 10);
    if (rtt_pthread == RT_NULL) {
        rt_kprintf("%s - rt_thread_create error!\n", __FUNCTION__);
        goto errout;
    }

    rtt_pthread->ax_flag = 0;
    osal_pthread->task_struct = rtt_pthread;
    rt_thread_startup(osal_pthread->task_struct);

    return (struct AX_TASK *) osal_pthread;

errout:
    if (osal_pthread) {
        rt_free(osal_pthread);
    }
    return RT_NULL;
}

AX_S32 AX_OSAL_TASK_kthread_stop(AX_TASK_T *osal_thread, AX_U32 stop_flag)
{
    rt_err_t ret = 0;
    AX_TASK_T *osal_pthread = osal_thread;
    if (osal_pthread == RT_NULL)
        return -1;
    rt_thread_t rt_thread = (struct rt_thread *)(osal_pthread->task_struct);

    rt_thread->ax_flag = AX_THREAD_SHOULD_STOP;

    rt_thread_sleep(10);
    return ret;
}

AX_S32 AX_OSAL_TASK_cond_resched()
{
    rt_err_t ret = 0;

    ret = rt_thread_yield();
    if (ret == RT_EOK) return 0;

    return ret;
}

AX_BOOL AX_OSAL_TASK_kthread_should_stop(AX_VOID)
{
    rt_thread_t rt_thread = rt_thread_self();

    if (rt_thread->ax_flag == AX_THREAD_SHOULD_STOP)
        return AX_TRUE;

    return AX_FALSE;
}

AX_VOID AX_OSAL_TASK_schedule(void)
{
    /* do schedule */
    rt_schedule();
    return;
}

AX_VOID AX_OSAL_set_current_state(AX_S32 state_value)
{
    rt_thread_t thread = rt_thread_self();
    if (state_value == AX_TASK_RUNNING) {
        thread->stat = RT_THREAD_READY | (thread->stat & ~RT_THREAD_STAT_MASK);
    } else if (state_value == AX_TASK_INTERRUPTIBLE) {
        thread->stat = RT_THREAD_SUSPEND | (thread->stat & ~RT_THREAD_STAT_MASK);
    } else if (state_value == AX_TASK_UNINTERRUPTIBLE) {
        thread->stat = RT_THREAD_SUSPEND | (thread->stat & ~RT_THREAD_STAT_MASK);
    } else {
        RT_ASSERT(0);
    }

    return;
}

AX_S32 AX_OSAL_sched_setscheduler(AX_TASK_T *osal_thread, AX_S32 policy,
                                  const struct AX_TASK_SCHED_PARAM *param)
{
/*
    if (param == RT_NULL) {
        return 0;
    }
	AX_TASK_T *osal_pthread = osal_thread;

    RT_ASSERT(osal_pthread != RT_NULL);
    rt_thread_t rt_thread = (struct rt_thread *)(osal_pthread->task_struct);

    int priority = param->sched_priority;

    if (priority > RT_THREAD_PRIORITY_MAX-2) {
        priority = RT_THREAD_PRIORITY_MAX-2;
    }

	rt_thread_control(rt_thread, RT_THREAD_CTRL_CHANGE_PRIORITY, (void *)priority);
*/
    return 0;
}
