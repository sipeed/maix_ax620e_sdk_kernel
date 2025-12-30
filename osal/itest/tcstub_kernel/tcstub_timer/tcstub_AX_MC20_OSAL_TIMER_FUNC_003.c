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
*  @ TC: high-resolution timer count test
*/
int tcstub_AX_MC20_OSAL_TIMER_FUNC_003_001(unsigned int cmd, unsigned long arg)
{
    unsigned long long httimer = 0;
    unsigned long long httimer1 = 0;
    unsigned long long httimer2 = 0;
    int i = 0;

    for(i = 0; i < 10; i++){
        httimer1 = AX_OSAL_TM_get_microseconds();
        AX_OSAL_TM_msleep(100);
        httimer2 = AX_OSAL_TM_get_microseconds();

        httimer += httimer2 - httimer1;
    }

	do_div(httimer, 10000);
    printk("--- average delta 222 = %llu ---\n", httimer);

    if((httimer>100) && (httimer<130)){
		printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_TIMER_FUNC_003_001 is passed\n", __FUNCTION__, __LINE__);
		return 0;
    }
    else{
		printk("Function[%s] Line[%d] tcstub_AX_MC20_OSAL_TIMER_FUNC_003_001 is failed\n", __FUNCTION__, __LINE__);
		return -1;
    }
}


