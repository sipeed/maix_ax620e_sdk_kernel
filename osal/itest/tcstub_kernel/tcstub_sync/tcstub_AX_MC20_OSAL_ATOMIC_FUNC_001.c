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
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include "stub_public.h"
#include "osal_ax.h"

static AX_ATOMIC_T g_osal_sum;
static AX_ATOMIC_T g_osal_count;


static AX_U32 TEST_OSAL_Atomic1(void)
{
    AX_S32 i = 0;

    for (i = 0; i < 100; ++i) {
        AX_OSAL_SYNC_atomic_inc_return(&g_osal_sum);
    }

    AX_OSAL_SYNC_atomic_inc_return(&g_osal_count);
    return 0;
}

static AX_U32 TEST_OSAL_Atomic2(void)
{
    AX_S32 i = 0;

    for (i = 0; i < 100; ++i) {
        AX_OSAL_SYNC_atomic_dec_return(&g_osal_sum);
    }

    AX_OSAL_SYNC_atomic_dec_return(&g_osal_count);
    return 0;
}


/*
*  /TR Type: OSAL -> Atomic -> Function
*  @ TC: atomic_inc_return, atomic_dec_return
*/
int tcstub_AX_MC20_OSAL_ATOMIC_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
	AX_TASK_T *osal_atomic_task1 = AX_NULL;
	AX_TASK_T *osal_atomic_task2 = AX_NULL;
	AX_U32 *osal_sum;
	AX_U32 *osal_count;


	g_osal_sum.atomic = kmalloc(sizeof(AX_U32), GFP_KERNEL);
	g_osal_count.atomic = kmalloc(sizeof(AX_U32), GFP_KERNEL);

	osal_sum = kmalloc(sizeof(AX_U32), GFP_KERNEL);
	osal_count = kmalloc(sizeof(AX_U32), GFP_KERNEL);
	*osal_sum = 0;
	*osal_count = 0;

	g_osal_sum.atomic = osal_sum;
	g_osal_count.atomic = osal_count;

	osal_atomic_task1 = kmalloc(sizeof(AX_TASK_T), GFP_KERNEL);
	if (osal_atomic_task1 == AX_NULL) {
		printk("Function[%s] Line[%d] AX_OSAL_malloc_task1 is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	osal_atomic_task2 = kmalloc(sizeof(AX_TASK_T), GFP_KERNEL);
	if (osal_atomic_task2 == AX_NULL) {
		printk("Function[%s] Line[%d] AX_OSAL_malloc_task2 is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	osal_atomic_task1 = AX_OSAL_TASK_kthread_run((AX_THREAD_FUNC_T)TEST_OSAL_Atomic1, AX_NULL,
						"osal_test_atomic_kthread_1");
	if (osal_atomic_task1 == AX_NULL) {
		printk("Function[%s] Line[%d] AX_OSAL_task_atomic_kthread1_run is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	osal_atomic_task2 = AX_OSAL_TASK_kthread_run((AX_THREAD_FUNC_T)TEST_OSAL_Atomic2, AX_NULL,
						"osal_test_atomic_kthread_2");
	if (osal_atomic_task2 == AX_NULL) {
		printk("Function[%s] Line[%d] AX_OSAL_task_atomic_kthread2_run is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	while (AX_OSAL_SYNC_atomic_read(&g_osal_count)) {
		printk("Function[%s] Line[%d] AX_OSAL_SYNC_atomic_read is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_ATOMIC_FUNC_001_001 is passed\n", __FUNCTION__, __LINE__);
	return 0;

errout:
	printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_ATOMIC_FUNC_001_001 is failed\n", __FUNCTION__, __LINE__);
	return -1;
}


