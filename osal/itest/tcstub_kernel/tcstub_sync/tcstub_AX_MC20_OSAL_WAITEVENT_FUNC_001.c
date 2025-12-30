/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include "stub_public.h"
#include "osal_ax.h"
#include "osal_dev_ax.h"


static AX_TASK_T *tid1 = AX_NULL;
static AX_TASK_T *tid2 = AX_NULL;

static AX_WAIT_T TEST_osal_wait_event;
static int TEST_WAITEVENT_T1_IS_STOPPED = 0;
static int TEST_WAITEVENT_T2_IS_STOPPED = 0;
static int TEST_WAITEVENT_TEST_RESULT = 0;


static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001_entry_3(void *parameter)
{
    return TEST_WAITEVENT_T2_IS_STOPPED;
}

static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001_entry_2(void *parameter)
{
    AX_U32 tick = 0;

	tick = jiffies;
    printk("Function[%s] 111 tick start = %u \n", __FUNCTION__, tick);

    AX_OSAL_TM_msleep(100);

	tick = jiffies;
    printk("Function[%s] 222 tick start = %u \n", __FUNCTION__, tick);
    TEST_WAITEVENT_T2_IS_STOPPED = 1;
    AX_OSAL_SYNC_wakeup(&TEST_osal_wait_event, AX_NULL);

    return 0;
}

static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001_entry_1(void *parameter)
{
    AX_U32 tick = 0;
    AX_U32 delta = 0;

    tick = jiffies;

    printk("Function[%s] tick start = %u \n", __FUNCTION__, tick);
    AX_OSAL_SYNC_wait_event(&TEST_osal_wait_event, tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001_entry_3, AX_NULL);
    delta = jiffies - tick;

    printk("Function[%s] tick end = %u \n", __FUNCTION__, tick + delta );

    if (delta < 5u) {
        printk("Function[%s] fail, not meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITEVENT_TEST_RESULT = -1;
    } else {
        printk("Function[%s] right, meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITEVENT_TEST_RESULT = 1;
    }

    TEST_WAITEVENT_T1_IS_STOPPED = 1;

    return 0;
}


/*
*  /TR Type: OSAL -> WaitEvent -> Function
*  @ TC: wait_event
*/int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    AX_S32 stack_priority = 10;

    TEST_WAITEVENT_T1_IS_STOPPED = 0;
    TEST_WAITEVENT_T2_IS_STOPPED = 0;
    TEST_WAITEVENT_TEST_RESULT = 0;

    AX_OSAL_SYNC_waitqueue_init(&TEST_osal_wait_event);

    /* 创建线程1 */
    tid1 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001_entry_1,
                            AX_NULL, "t1", stack_priority);
    if (tid1 == AX_NULL){
		printk(" creat thread1 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    /* 创建线程2 */
    tid2 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001_entry_2,
                            AX_NULL, "t2", stack_priority - 2);

    if (tid2 == AX_NULL){
		printk(" creat thread2 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    printk("Function[%s] main thread pending ... \n", __FUNCTION__);

    while (TEST_WAITEVENT_T1_IS_STOPPED == 0 || TEST_WAITEVENT_T2_IS_STOPPED == 0) {
        AX_OSAL_TM_msleep(100);
    }

    printk("Function[%s]  main thread exit\n", __FUNCTION__);
    AX_OSAL_SYNC_wait_destroy(&TEST_osal_wait_event);

    if (TEST_WAITEVENT_TEST_RESULT == 1)
        return 0;
    else
        return -1;
}

static AX_TASK_T *tid2_1 = AX_NULL;
static AX_TASK_T *tid2_2 = AX_NULL;
static AX_TASK_T *tid2_3 = AX_NULL;

static AX_WAIT_T TEST_osal_wait_event_2;
static int TEST_WAITEVENT_T2_1_IS_STOPPED = 0;
static int TEST_WAITEVENT_T2_2_IS_STOPPED = 0;
static int TEST_WAITEVENT_T2_3_IS_STOPPED = 0;
static int TEST_WAITEVENT_TEST_RESULT_2_1 = 0;
static int TEST_WAITEVENT_TEST_RESULT_2_2 = 0;

static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_5(void *parameter)
{
    return TEST_WAITEVENT_T2_2_IS_STOPPED;
}

static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_4(void *parameter)
{
    return TEST_WAITEVENT_T2_1_IS_STOPPED;
}

static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_3(void *parameter)
{
    AX_U32 tick = 0;

    tick = jiffies;
    printk("Function[%s] 111 tick start = %u \n", __FUNCTION__, tick);

    AX_OSAL_TM_msleep(100);

    tick = jiffies;
    printk("Function[%s] 222 tick start = %u \n", __FUNCTION__, tick);

    TEST_WAITEVENT_T2_2_IS_STOPPED = 1;
    TEST_WAITEVENT_T2_1_IS_STOPPED = 1;

//	AX_OSAL_TM_msleep(100);

    AX_OSAL_SYNC_wakeup(&TEST_osal_wait_event_2, AX_NULL);
    printk("Function[%s] 333 entry_3 send wakeup \n", __FUNCTION__);

    TEST_WAITEVENT_T2_3_IS_STOPPED = 1;

    return 0;
}

static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_2(void *parameter)
{
    AX_U32 tick = 0;
    AX_U32 delta = 0;

    tick = jiffies;

    printk("Function[%s] tick start = %u \n", __FUNCTION__, tick);
    AX_OSAL_SYNC_wait_event_interruptible(&TEST_osal_wait_event_2, tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_5, AX_NULL);

    delta = jiffies - tick;

    printk("Function[%s] tick end = %u \n", __FUNCTION__, tick + delta);

    if (delta < 5u) {
        printk("Function[%s] fail, not meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITEVENT_TEST_RESULT_2_2 = -1;
    } else {
        printk("Function[%s] right, meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITEVENT_TEST_RESULT_2_2 = 1;
    }

    TEST_WAITEVENT_T2_2_IS_STOPPED = 1;

    return 0;
}
static int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_1(void *parameter)
{
    AX_U32 tick = 0;
    AX_U32 delta = 0;

    tick = jiffies;

    printk("Function[%s] tick start = %u \n", __FUNCTION__, tick);
    AX_OSAL_SYNC_wait_event_interruptible(&TEST_osal_wait_event_2, tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_4, AX_NULL);

    delta = jiffies - tick;

    printk("Function[%s] tick end = %u \n", __FUNCTION__, tick + delta);

    if (delta < 5u) {
        printk("Function[%s] fail, not meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITEVENT_TEST_RESULT_2_1 = -1;
    } else {
        printk("Function[%s] right, meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITEVENT_TEST_RESULT_2_1 = 1;
    }

    TEST_WAITEVENT_T2_1_IS_STOPPED = 1;

    return 0;
}

/*
*  /TR Type: OSAL -> WaitEvent -> Function
*  @ TC: two thread wait one event
*/
int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002(unsigned int cmd, unsigned long arg)
{
    AX_S32  stack_priority = 10;

    TEST_WAITEVENT_T2_1_IS_STOPPED = 0;
    TEST_WAITEVENT_T2_2_IS_STOPPED = 0;
    TEST_WAITEVENT_T2_3_IS_STOPPED = 0;
    TEST_WAITEVENT_TEST_RESULT_2_1 = 0;
    TEST_WAITEVENT_TEST_RESULT_2_2 = 0;

    AX_OSAL_SYNC_waitqueue_init(&TEST_osal_wait_event_2);

    tid2_1 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_1,
                            AX_NULL, "t2_1", stack_priority);
    if (tid2_1 == AX_NULL){
		printk(" creat thread2_1 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    tid2_2 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_2,
                            AX_NULL, "t2_2", stack_priority);
    if (tid2_2 == AX_NULL){
		printk(" creat thread2_2 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    tid2_3 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002_entry_3,
                            AX_NULL, "t2_1", stack_priority - 2);
    if (tid2_3 == AX_NULL){
		printk(" creat thread2_3 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    printk("Function[%s] main thread pending ... \n", __FUNCTION__);

    while (TEST_WAITEVENT_T2_1_IS_STOPPED == 0 || TEST_WAITEVENT_T2_2_IS_STOPPED == 0
								|| TEST_WAITEVENT_T2_3_IS_STOPPED == 0) {
        AX_OSAL_TM_msleep(100);
    }

    printk("Function[%s]  main thread exit\n", __FUNCTION__);
    AX_OSAL_SYNC_wait_destroy(&TEST_osal_wait_event_2);

    if ((TEST_WAITEVENT_TEST_RESULT_2_1 == 1) && (TEST_WAITEVENT_TEST_RESULT_2_2 == 1))
        return 0;
    else
        return -1;
}

