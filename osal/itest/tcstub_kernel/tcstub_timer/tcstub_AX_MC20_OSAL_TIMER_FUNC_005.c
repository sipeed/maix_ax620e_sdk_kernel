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
#include <asm/div64.h>

#include "stub_public.h"
#include "osal_ax.h"
#include "osal_dev_ax.h"


/*
*  /TR Type: OSAL -> Timer -> Function
*  @ TC: AX_OSAL_TM_mdelay test
*  @ TC: msecs < tick
*/
int tcstub_AX_MC20_OSAL_TIMER_FUNC_005_001(unsigned int cmd, unsigned long arg)
{
	unsigned int msecs = 0;
	unsigned long long httimer = 0;
	unsigned long long httimer_total = 0;
	int i = 0;

	msecs = 0;

	for(i = 0; i < 10; i++){
		httimer = AX_OSAL_TM_get_microseconds();
		AX_OSAL_TM_mdelay(msecs);
		httimer = AX_OSAL_TM_get_microseconds() - httimer;
		httimer_total += httimer;
	}

	do_div(httimer_total, 10);
	printk("--- AX_MC20_OSAL_TIMER_FUNC_005_001 httimer = %llu ---\n", httimer_total);

	if((httimer_total > 0) && (httimer_total < 100))
		return 0;
	else
		return -1;
}

/*
*  /TR Type: OSAL -> Timer -> Function
*  @ TC: AX_OSAL_TM_mdelay test
*  @ TC: msecs = tick
*/
int tcstub_AX_MC20_OSAL_TIMER_FUNC_005_002(unsigned int cmd, unsigned long arg)
{
	unsigned int msecs = 0;
    unsigned long long httimer = 0;
    unsigned long long httimer_total = 0;
    int i = 0;

	msecs = 1;

    for(i = 0; i < 10; i++){
		httimer = AX_OSAL_TM_get_microseconds();
		AX_OSAL_TM_mdelay(msecs);
		httimer = AX_OSAL_TM_get_microseconds() - httimer;
		httimer_total += httimer;
	}

	do_div(httimer_total, 10);
    printk("--- AX_MC20_OSAL_TIMER_FUNC_005_002 httimer = %llu ---\n", httimer_total);

    if((httimer_total > 1000) && (httimer_total < 1300)){
		printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_TIMER_FUNC_005_002 is passed\n", __FUNCTION__, __LINE__);
		return 0;
    }
    else{
		printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_TIMER_FUNC_005_002 is failed\n", __FUNCTION__, __LINE__);
		return -1;
    }
}

/*
*  /TR Type: OSAL -> Timer -> Function
*  @ TC: AX_OSAL_TM_mdelay test
*  @ TC: msecs > tick
*/
int tcstub_AX_MC20_OSAL_TIMER_FUNC_005_003(unsigned int cmd, unsigned long arg)
{
	unsigned int msecs = 0;
    unsigned long long httimer = 0;
    unsigned long long httimer_total = 0;
    int i = 0;

	msecs = 100;

    for(i = 0; i < 10; i++){
		httimer = AX_OSAL_TM_get_microseconds();
		AX_OSAL_TM_mdelay(msecs);
		httimer = AX_OSAL_TM_get_microseconds() - httimer;
		httimer_total += httimer;
	}

	do_div(httimer_total, 10);
    printk("--- AX_MC20_OSAL_TIMER_FUNC_005_003 httimer = %llu ---\n", httimer_total);

    if((httimer_total > 10000) && (httimer_total < 105000))
		return 0;
	else
		return -1;
}


