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
#include "osal_dev_ax.h"

unsigned int g_test_timer_count2 = 0;
AX_TIMER_T *g_osal_timer = AX_NULL;

static void AX_Timer2_callback(void)
{
    unsigned long __attribute__ ((unused)) lastTick;

    g_test_timer_count2++;
    lastTick = jiffies;
    printk("g_test_timer_count2=%d, tick_last2=%lu\n", g_test_timer_count2, lastTick);

    // restart timer
    AX_OSAL_TMR_mod_timer((AX_TIMER_T *)g_osal_timer, (AX_ULONG)100);
}

/*
*  /TR Type: OSAL -> Timer -> Function
*  @ TC: cycle timer, destory_timer
*/
int tcstub_AX_MC20_OSAL_TIMER_FUNC_002_001(unsigned int cmd, unsigned long arg)
{
	int osal_ret = 0;
	unsigned int ax_test_timer_count2 = 0;

	// init timer
	g_osal_timer = (struct AX_TIMER *)kmalloc(sizeof(struct AX_TIMER), GFP_KERNEL);
	if (g_osal_timer == AX_NULL) {
		printk("Function[%s] Line[%d] AX_OSAL_malloc is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	g_osal_timer->function = (AX_VOID *)&AX_Timer2_callback;
	g_osal_timer->data = 0;

	osal_ret = AX_OSAL_TMR_init_timers(g_osal_timer);
	if ((osal_ret != 0) || (g_osal_timer->timer == AX_NULL)) {
		printk("Function[%s] Line[%d] AX_OSAL_init_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	ax_test_timer_count2 = g_test_timer_count2;

	// active timer
	osal_ret = AX_OSAL_TMR_mod_timer((AX_TIMER_T *)g_osal_timer, (AX_ULONG)100);
	if (osal_ret != 0) {
		printk("Function[%s] Line[%d] AX_OSAL_active_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	// wait for timer work
	AX_OSAL_TM_msleep(600);

	printk("Function[%s] Line[%d] g_test_timer_count2 = %d, ax_test_timer_count2 + 5 = %d \n", __FUNCTION__, __LINE__, 
													g_test_timer_count2, ax_test_timer_count2 + 5);

	if (g_test_timer_count2 < ax_test_timer_count2 + 5) {
		printk("Function[%s] Line[%d] AX_OSAL_active_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	// del timer
	osal_ret = AX_OSAL_TMR_destory_timer(g_osal_timer);
	if (osal_ret != 0) {
		printk("Function[%s] Line[%d] AX_OSAL_del_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	if (g_osal_timer) {
		kfree(g_osal_timer);
	}

	printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_TIMER_FUNC_002_001 is passed\n", __FUNCTION__, __LINE__);
	return 0;

errout:
	if (g_osal_timer) {
		kfree(g_osal_timer);
	}
	printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_TIMER_FUNC_002_001 is failed\n", __FUNCTION__, __LINE__);
	return -1;
}

