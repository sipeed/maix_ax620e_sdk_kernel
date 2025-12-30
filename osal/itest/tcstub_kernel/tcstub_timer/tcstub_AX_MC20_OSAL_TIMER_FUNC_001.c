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

unsigned int g_test_timer_count1 = 0;

void AX_Timer1_callback(void)
{
    unsigned long lastTick;

    g_test_timer_count1++;
    lastTick = jiffies;
    printk("g_test_timer_count1=%d, tick_last1=%lu\n", g_test_timer_count1, lastTick);
}

/*
*  /TR Type: OSAL -> Timer -> Function
*  @ TC: init_timers, mod_timer, del_timer, AX_OSAL_TM_msleep
*/
int tcstub_AX_MC20_OSAL_TIMER_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
	AX_TIMER_T *osal_timer = AX_NULL;
	int osal_ret = 0;
	unsigned int ax_test_timer_count1 = 0;

	// init timer
	osal_timer = (struct AX_TIMER *)kmalloc(sizeof(struct AX_TIMER), GFP_KERNEL);
	if (osal_timer == AX_NULL) {
		printk("Function[%s] Line[%d] AX_OSAL_malloc is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	osal_timer->function = (AX_VOID *)&AX_Timer1_callback;
	osal_timer->data = 0;

	osal_ret = AX_OSAL_TMR_init_timers(osal_timer);
	if ((osal_ret != 0) || (osal_timer->timer == AX_NULL)) {
		printk("Function[%s] Line[%d] AX_OSAL_init_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	ax_test_timer_count1 = g_test_timer_count1;

	// active timer
	osal_ret = AX_OSAL_TMR_mod_timer(osal_timer, 100);
	if (osal_ret != 0) {
		printk("Function[%s] Line[%d] AX_OSAL_active_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	// for timer act
	AX_OSAL_TM_msleep(300);
	if (g_test_timer_count1 != ax_test_timer_count1 + 1) {
		printk("Function[%s] Line[%d] AX_OSAL_active_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	// del timer
	osal_ret = AX_OSAL_TMR_del_timer(osal_timer);
	if (osal_ret != 0) {
		printk("Function[%s] Line[%d] AX_OSAL_del_timers is failed\n", __FUNCTION__, __LINE__);
		goto errout;
	}

	if (osal_timer) {
		kfree(osal_timer);
	}
	return 0;

errout:
	if (osal_timer) {
		kfree(osal_timer);
	}
	return -1;
}

