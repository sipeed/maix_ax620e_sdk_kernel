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


/* 指向线程控制块的指针 */
static AX_TASK_T *tid1 = AX_NULL;
static AX_TASK_T *tid2 = AX_NULL;

static AX_WAIT_T TEST_osal_wait;
static int TEST_WAITQUEUE_T1_IS_STOPPED = 0;
static int TEST_WAITQUEUE_T2_IS_STOPPED = 0;
static int TEST_WAITQUEUE_TEST_RESULT = 0;


/* 线程1入口 */
static int tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001_entry_1(void *parameter)
{
    AX_U32 tick = 0;
    AX_U32 delta = 0;

    tick = jiffies;

    /* 1.T1在进行wait queue前，计时TM1，被唤醒后计时TM2； */
    printk("Function[%s] tick start = %u \n", __FUNCTION__, tick);
    AX_OSAL_SYNC_wait_uninterruptible(&TEST_osal_wait, AX_NULL, AX_NULL);
    delta = jiffies - tick;

    printk("Function[%s] tick end = %u \n", __FUNCTION__, tick + delta);

    if (delta < 5u) {
        printk("Function[%s] fail, not meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITQUEUE_TEST_RESULT = -1;
    } else {
        printk("Function[%s] right, meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_WAITQUEUE_TEST_RESULT = 1;
    }

    TEST_WAITQUEUE_T1_IS_STOPPED = 1;

    return 0;
}

/* 线程2入口 */
static int tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001_entry_2(void *parameter)
{
    AX_U32 tick = 0;

    /* 2.T2被创建后，故意先delay 10个tick，然后再唤醒T1 */
    tick = jiffies;
    printk("Function[%s] 111 tick start = %u \n", __FUNCTION__, tick);

    AX_OSAL_TM_msleep(100);

    tick = jiffies;
    printk("Function[%s] 222 tick start = %u \n", __FUNCTION__, tick);
    AX_OSAL_SYNC_wakeup(&TEST_osal_wait, AX_NULL);

    tick = jiffies;
    printk("Function[%s] AX_OSAL_SYNC_wakeup = %u \n", __FUNCTION__, tick);

    TEST_WAITQUEUE_T2_IS_STOPPED = 1;

    return 0;
}

/*
* /TR类型,OSAL->TASK SYNC->功能->semaphore
* @ TC:让任务T1主动进入wait queue，然后由任务T2唤醒它。
        1.T1在进行wait queue前，计时TM1，被唤醒后计时TM2;
        2.T2被创建后，故意先delay 10个tick，然后再唤醒T1
*/
int tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    AX_S32 stack_priority = 10;

	TEST_WAITQUEUE_T1_IS_STOPPED = 0;
    TEST_WAITQUEUE_T2_IS_STOPPED = 0;
    TEST_WAITQUEUE_TEST_RESULT = 0;

    AX_OSAL_SYNC_waitqueue_init(&TEST_osal_wait);

    /* 创建线程1 */
    tid1 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001_entry_1,
                            AX_NULL, "t1", stack_priority);
    if (tid1 == AX_NULL){
		printk(" creat thread1 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    /* 创建线程2 */
    tid2 = AX_OSAL_TASK_kthread_create_ex(tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001_entry_2,
                            AX_NULL, "t2", stack_priority - 2);

    if (tid2 == AX_NULL){
		printk(" creat thread2 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    printk("Function[%s] main thread pending ... \n", __FUNCTION__);

    while (TEST_WAITQUEUE_T1_IS_STOPPED == 0 || TEST_WAITQUEUE_T2_IS_STOPPED == 0) {
        AX_OSAL_TM_msleep(100);
    }

    printk("Function[%s]  main thread exit\n", __FUNCTION__);
    AX_OSAL_SYNC_wait_destroy(&TEST_osal_wait);

    if (TEST_WAITQUEUE_TEST_RESULT == 1)
        return 0;
    else
        return -1;
}


