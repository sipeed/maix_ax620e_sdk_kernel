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

static AX_MUTEX_T TEST_osal_mutex;
static int TEST_T1_IS_STOPPED = 0;
static int TEST_T2_IS_STOPPED = 0;
static int TEST_AX_MC20_OSAL_MUTEX_FUNC_001_001_RESULT = 0;

/* 线程1入口 */
static int tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001_entry_1(void *parameter)
{

    /* 1.T1很快进入临界区，然后故意在临界区delay 10个tick;； */

    AX_OSAL_SYNC_mutex_lock(&TEST_osal_mutex);

    AX_OSAL_TM_msleep(100);

    AX_OSAL_SYNC_mutex_unlock(&TEST_osal_mutex);


    TEST_T1_IS_STOPPED = 1;

    return 0;
}

/* 线程2入口 */
static int tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001_entry_2(void *parameter)
{
    AX_U32 tick = 0;
    AX_U32 delta = 0;

    AX_OSAL_TM_msleep(5);

    tick = jiffies;
    printk("Function[%s] tick start = %u \n", __FUNCTION__, tick);

    AX_OSAL_SYNC_mutex_lock(&TEST_osal_mutex);

    AX_OSAL_SYNC_mutex_unlock(&TEST_osal_mutex);

    delta = jiffies - tick;

    printk("Function[%s] tick end   = %u \n", __FUNCTION__, tick + delta);

    if (delta < 5u) {
        printk("Function[%s] fail, not meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_AX_MC20_OSAL_MUTEX_FUNC_001_001_RESULT = -1;
    } else {
        printk("Function[%s] right, meet our expection, delta = %u \n", __FUNCTION__, delta);
        TEST_AX_MC20_OSAL_MUTEX_FUNC_001_001_RESULT = 1;
    }

    TEST_T2_IS_STOPPED = 1;

    return 0;
}

/*
* /TR类型,OSAL->TASK SYNC->功能->semaphore
* @ TC:两个task之间的互斥。
        1.T1很快进入临界区，然后故意在临界区delay 10个tick;
        2.T2在进入临界区前故意delay 2个tick，确保T1顺利进入临界区
*/
int tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    TEST_T1_IS_STOPPED = 0;
    TEST_T2_IS_STOPPED = 0;
    TEST_AX_MC20_OSAL_MUTEX_FUNC_001_001_RESULT = 0;

    AX_OSAL_SYNC_mutex_init(&TEST_osal_mutex);

    /* 创建线程1 */
    tid1 = AX_OSAL_TASK_kthread_run(tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001_entry_1,
                            AX_NULL, "t1");
    if (tid1 == AX_NULL){
		printk(" creat thread1 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    /* 创建线程2 */
    tid2 = AX_OSAL_TASK_kthread_run(tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001_entry_2,
                            AX_NULL, "t2");
    if (tid2 == AX_NULL){
		printk(" creat thread2 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    printk("Function[%s] main thread pending ... \n", __FUNCTION__);

    while (TEST_T1_IS_STOPPED == 0 || TEST_T2_IS_STOPPED == 0) {
        AX_OSAL_TM_msleep(100);
    }

    printk("Function[%s]  main thread exit\n", __FUNCTION__);
    AX_OSAL_SYNC_mutex_destroy(&TEST_osal_mutex);

    if (TEST_AX_MC20_OSAL_MUTEX_FUNC_001_001_RESULT == 1)
        return 0;
    else
        return -1;
}


