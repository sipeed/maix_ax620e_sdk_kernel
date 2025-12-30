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

static int itest_sample_thread_entry(void *data)
{
    int index = 0;

    printk("enter child thread [%s]---  \n", __FUNCTION__);

    for (; index < 10; index++) {
        printk("I am sample kernel thread ,index =%d \n",  index);
    }

    printk("exit child thread [%s]--- \n", __FUNCTION__);
    return 0;
}

//typedef int (* tcstub_func)(unsigned int cmd, unsigned long arg);

int tcstub_AX_MC20_OSAL_TASK_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    //struct task_struct *k;

    char *nameP = "my_threadProduct";

    printk("create new thread [%s]---	\n", __FUNCTION__);

    //AX_TASK_T * osal_task = AX_OSAL_TASK_kthread_run(itest_sample_thread_entry, NULL, nameP);
    AX_OSAL_TASK_kthread_run(itest_sample_thread_entry, NULL, nameP);

    AX_OSAL_TM_msleep(2000); /*2000ms*/

    printk("exit new thread [%s]---	\n", __FUNCTION__);

    return 0;
}

int tcstub_AX_MC20_OSAL_TASK_FUNC_001_002(unsigned int cmd, unsigned long arg)
{
    printk("create new thread [%s]---	\n", __FUNCTION__);

    printk("exit new thread [%s]---	\n", __FUNCTION__);

    return 0;
}

int tcstub_AX_MC20_OSAL_TASK_FUNC_001_003(unsigned int cmd, unsigned long arg)
{
    printk("create new thread [%s]---	\n", __FUNCTION__);

    printk("exit new thread [%s]---	\n", __FUNCTION__);

    return 0;
}

int tcstub_AX_MC20_OSAL_TASK_FUNC_001_004(unsigned int cmd, unsigned long arg)
{
    printk("create new thread [%s]---	\n", __FUNCTION__);

    printk("exit new thread [%s]---	\n", __FUNCTION__);

    return 0;
}
