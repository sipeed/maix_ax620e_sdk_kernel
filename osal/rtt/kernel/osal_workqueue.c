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
#include "workqueue.h"
#include "rtservice.h"

static struct rt_workqueue *__osal_wq = RT_NULL;

static struct rt_list_node __osal_workqueue_head;

static rt_err_t __create_workqueue_osal(void)
{
    rt_uint16_t stack_size = 4 * 1024; /*stack size is 4KB*/
    rt_uint8_t priority = RT_THREAD_PRIORITY_MAX / 4;

    if (__osal_wq == RT_NULL) {
        __osal_wq = rt_workqueue_create("OSAL_workqueue", stack_size, priority);
        if (__osal_wq == NULL) {
            rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
            return -1;
        }

		rt_list_init(&__osal_wq->work_list);
        rt_list_init(&__osal_workqueue_head);
    }

    return RT_EOK;
}

static void __rt_work_func(struct rt_work *work, void *work_data)
{
    AX_WORK_T *osal_work = (AX_WORK_T *)work_data;
    RT_ASSERT(osal_work != RT_NULL);
    RT_ASSERT(osal_work->func != RT_NULL);

    osal_work->func(osal_work);

    return;
}

struct osal_worknode_t {
    struct AX_WORK *ax_work;
    struct rt_list_node list;
};

static int __add_osal_work(struct AX_WORK *osal_work)
{
    struct osal_worknode_t *work_node;

    work_node = (struct osal_worknode_t *)rt_malloc(sizeof(struct osal_worknode_t));
    if (work_node == NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }
    work_node->ax_work = osal_work;

    rt_list_insert_after(&__osal_workqueue_head, &work_node->list);

    return 0;
}
static struct AX_WORK *__find_osal_work(struct AX_WORK *osal_work)
{
    struct osal_worknode_t *pos;

    rt_list_for_each_entry(pos, &__osal_workqueue_head, list) {
        if (pos->ax_work == osal_work)
            return pos->ax_work;
    }

    rt_kprintf("%s - not found osal work node\n", __FUNCTION__);
    return 0;
}

static int __delete_osal_work(struct AX_WORK *osal_work)
{
    RT_ASSERT(! rt_list_isempty(&__osal_workqueue_head));

    struct osal_worknode_t *pos;

    rt_list_for_each_entry(pos, &__osal_workqueue_head, list) {
        if (pos->ax_work == osal_work)
            break;
    }

    RT_ASSERT(pos != RT_NULL);

    rt_list_remove(&pos->list);

    rt_free(pos);
    return 0;
}

AX_S32 AX_OSAL_SYNC_init_work(AX_WORK_T *osal_work, AX_WORK_FUNC_T osal_func)
{
    RT_ASSERT(osal_work != RT_NULL);
    RT_ASSERT(osal_func != RT_NULL);

    rt_err_t ret = __create_workqueue_osal();
    RT_ASSERT(ret == RT_EOK);

    struct rt_work *work = (struct rt_work *)rt_malloc(sizeof(struct rt_work));
    RT_ASSERT(work != RT_NULL);

/*
	rt_memset(work, 0, sizeof(struct rt_work) );

    work->work_func = __rt_work_func;
    work->work_data = (void *)osal_work;
    work->workqueue = __osal_wq;
	rt_list_init(&work->list);	
*/

	rt_work_init(work, __rt_work_func, (void *)osal_work);

    osal_work->work = work;
    osal_work->func = osal_func;

    /*add osal_work to workqueue list*/
    __add_osal_work(osal_work);

    return 0;
}

AX_S32 AX_OSAL_SYNC_schedule_work(AX_WORK_T *osal_work)
{
    RT_ASSERT(osal_work != RT_NULL);
    RT_ASSERT(__osal_wq != RT_NULL);

    struct AX_WORK *find_osal_work;

    /*find work from workqueue list*/
    find_osal_work = __find_osal_work(osal_work);

    RT_ASSERT(find_osal_work != RT_NULL);
    RT_ASSERT(find_osal_work->work != RT_NULL);
    RT_ASSERT(find_osal_work->func != RT_NULL);

    rt_err_t ret = rt_workqueue_dowork(__osal_wq, (struct rt_work *)find_osal_work->work);

    return ret;
}

AX_VOID AX_OSAL_SYNC_destory_work(AX_WORK_T *osal_work)
{
    RT_ASSERT(osal_work != RT_NULL);
    RT_ASSERT(osal_work->work != RT_NULL);

    /*delete osal_work from workqueue list*/
    __delete_osal_work(osal_work);

    rt_free(osal_work->work);
    osal_work->work = RT_NULL;

    return ;
}
