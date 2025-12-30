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


int tcstub_AX_MC20_OSAL_BARRIER_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    AX_U32 osal_barrier_num1 = 0;
    AX_U32 osal_barrier_num2 = 0;

    osal_barrier_num1 = 1;
    AX_OSAL_SYNC_wmb();

    osal_barrier_num2 = osal_barrier_num1 + 1;
    AX_OSAL_SYNC_rmb();

    osal_barrier_num1 = osal_barrier_num2 + 1;
    AX_OSAL_SYNC_mb();

    osal_barrier_num2 = osal_barrier_num1 + 1;
    AX_OSAL_SYNC_dsb();

    osal_barrier_num1 = osal_barrier_num2 + 1;
    AX_OSAL_SYNC_isb();

    osal_barrier_num2 = osal_barrier_num1 + 1;
    AX_OSAL_SYNC_dmb();

	return 0;
}


