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


static AX_WORK_T TEST_osal_work;
static int TEST_WORKQUEUE_T1_IS_STOPPED = 0;
//static int TEST_WORKQUEUE_T2_IS_STOPPED = 0;
static int TEST_WORKQUEUE_TEST_RESULT = 0;

static int TEST_worknode_flag_1 = 0;
//static int TEST_worknode_flag_2 = 0;


AX_VOID TEST_worknode_1(AX_WORK_T *work)
{
    printk("Function[%s] start work_1  \n", __FUNCTION__);
    TEST_worknode_flag_1 = 1;
}

/*
AX_VOID TEST_worknode_2(AX_WORK_T *work)
{
    printk("Function[%s] start work_1  \n", __FUNCTION__);
    TEST_worknode_flag_2 = 2;
}
*/
/*
* /TR类型,OSAL->TASK SYNC->功能->semaphore
* @ TC:让任务队列执行两个work.
        一个work修改标识1，另一个work修改标识2
*/
int tcstub_AX_MC20_OSAL_WORKQUEUE_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    TEST_WORKQUEUE_T1_IS_STOPPED = 0;
    //TEST_WORKQUEUE_T2_IS_STOPPED = 0;
    TEST_WORKQUEUE_TEST_RESULT = 0;

    printk("Function[%s] AX_OSAL_SYNC_init_work  \n", __FUNCTION__);
    AX_OSAL_SYNC_init_work(&TEST_osal_work, TEST_worknode_1);

    AX_OSAL_TM_msleep(30);

    printk("Function[%s] AX_OSAL_SYNC_schedule_work  \n", __FUNCTION__);
    AX_OSAL_SYNC_schedule_work(&TEST_osal_work);

    AX_OSAL_TM_msleep(30);

    printk("Function[%s] AX_OSAL_SYNC_destory_work  \n", __FUNCTION__);
    AX_OSAL_SYNC_destroy_work(&TEST_osal_work);
	
    /*
        AX_OSAL_SYNC_init_work(&TEST_osal_work, TEST_worknode_2);
        AX_OSAL_SYNC_schedule_work(&TEST_osal_work);
        AX_OSAL_SYNC_destory_work(&TEST_osal_work);
    */
    printk("Function[%s] delay 30 ticks  \n", __FUNCTION__);
    AX_OSAL_TM_msleep(100);

    if ((TEST_worknode_flag_1 == 1))
        return 0;
    else
        return -1;


    /*
        if ((TEST_worknode_flag_1 == 1) && (TEST_worknode_flag_2 == 2))
				return 0;
			else
				return -1;
    */
}


