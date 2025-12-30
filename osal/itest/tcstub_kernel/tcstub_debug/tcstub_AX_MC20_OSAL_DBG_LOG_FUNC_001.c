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


int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    /*
    rt_kprintf("Assert  : 0\n");
    rt_kprintf("Error   : 3\n");
    rt_kprintf("Warning : 4\n");
    rt_kprintf("Info    : 6\n");
    rt_kprintf("Debug   : 7\n");
	#define LOG_LVL_ERROR				   3
	#define LOG_LVL_WARNING 			   4
	#define LOG_LVL_INFO				   6
	#define LOG_LVL_DBG 				   7
    */
//    AX_OSAL_DBG_ISPLogoutput(AX_LOG_LVL_ERROR, "error, I'am ISP");

	return 0;
}

int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_002(unsigned int cmd, unsigned long arg)
{
	return 0;
}

int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_003(unsigned int cmd, unsigned long arg)
{
	return 0;
}

int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_004(unsigned int cmd, unsigned long arg)
{
	return 0;
}


