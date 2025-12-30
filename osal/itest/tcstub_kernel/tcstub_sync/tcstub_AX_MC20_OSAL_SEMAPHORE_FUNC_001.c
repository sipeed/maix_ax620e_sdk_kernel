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

static AX_SEMAPHORE_T TEST_osal_sem;
static int TEST_SEMA_T1_IS_STOPPED = 0;
static int TEST_SEMA_T2_IS_STOPPED = 0;
static int TEST_AX_MC20_OSAL_SEMA_FUNC_RESULT = 0;


/* 线程1入口 */
static int tcstub_AX_MC20_OSAL_SEMA_FUNC_001_001_entry_1(void *parameter)
{

    /* 1.T1作为消费者，故意delay 10个tick，然后向消费者T2 传输数据； */
    AX_OSAL_TM_msleep(100);		/*100ms*/
    AX_OSAL_SYNC_sema_up(&TEST_osal_sem);

    TEST_SEMA_T1_IS_STOPPED = 1;

    return 0;
}

/* 线程2入口 */
static int tcstub_AX_MC20_OSAL_SEMA_FUNC_001_001_entry_2(void *parameter)
{
    AX_U32 tick = 0;
    AX_U32 delta = 0;

    tick = jiffies;
    printk("Function[%s] tick start = %u \n", __FUNCTION__, tick);
    AX_OSAL_SYNC_sema_down(&TEST_osal_sem);
    delta = jiffies - tick;

    printk("Function[%s] tick end = %u, delta = %u \n", __FUNCTION__, tick + delta, delta);

    if (delta < 5) {
        TEST_AX_MC20_OSAL_SEMA_FUNC_RESULT = -1;
        printk("Function[%s] fail, not meet our expection \n", __FUNCTION__);
    } else {
        printk("Function[%s] right, meet our expection \n", __FUNCTION__);
        TEST_AX_MC20_OSAL_SEMA_FUNC_RESULT = 1;
    }

    TEST_SEMA_T2_IS_STOPPED = 1;

    return 0;
}


/*
* /TR类型,OSAL->TASK SYNC->功能->semaphore
* @ TC:两个task之间的同步。
       1.T1作为消费者，故意delay 10个tick，然后向消费者T2 传输数据；
       2.T2接收到数据把，统计从开始接收的时间到已经接收的时间
*/
int tcstub_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    TEST_SEMA_T1_IS_STOPPED = 0;
    TEST_SEMA_T2_IS_STOPPED = 0;
    TEST_AX_MC20_OSAL_SEMA_FUNC_RESULT = 0;

    printk("semaphore func 001 [%s]---	\n", __FUNCTION__);

    AX_OSAL_SYNC_sema_init(&TEST_osal_sem, 0);

    /* 创建线程1 */
    tid1 = AX_OSAL_TASK_kthread_run(tcstub_AX_MC20_OSAL_SEMA_FUNC_001_001_entry_1,
                            AX_NULL, "t1");
    if (tid1 == AX_NULL){
		printk(" creat thread1 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    /* 创建线程2 */
    tid2 = AX_OSAL_TASK_kthread_run(tcstub_AX_MC20_OSAL_SEMA_FUNC_001_001_entry_2,
                            AX_NULL, "t2");
    if (tid2 == AX_NULL){
		printk(" creat thread2 failed in [%s]---	\n", __FUNCTION__);
        return -1;
    }

    printk("Function[%s] main thread pending ... \n", __FUNCTION__);

    while (TEST_SEMA_T1_IS_STOPPED == 0 || TEST_SEMA_T2_IS_STOPPED == 0) {
        AX_OSAL_TM_msleep(100);		/*100ms*/
    }

    printk("Function[%s]  main thread exit\n", __FUNCTION__);

    AX_OSAL_SYNC_sema_destroy(&TEST_osal_sem);

    printk("exit  [%s]---	\n", __FUNCTION__);

    if (TEST_AX_MC20_OSAL_SEMA_FUNC_RESULT == 1){
		printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001 is passed\n", __FUNCTION__, __LINE__);
        return 0;
    }
    else{
		printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001 is failed\n", __FUNCTION__, __LINE__);
        return -1;
    }
}


