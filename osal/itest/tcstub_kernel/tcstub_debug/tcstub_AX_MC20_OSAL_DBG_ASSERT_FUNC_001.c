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

#include "osal_logdebug_ax.h"


int tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    //printk("func(%s) test warnon.\n", __FUNCTION__);
    //AX_OSAL_DBG_Warnon(1);

	return 0;
}

int tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_002(unsigned int cmd, unsigned long arg)
{
    //printk("func(%s) test bugon.\n", __FUNCTION__);
    //AX_OSAL_DBG_Bugon(1);

	return 0;
}

int tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_003(unsigned int cmd, unsigned long arg)
{
    //printk("func(%s) test assert.\n", __FUNCTION__);
    //AX_OSAL_DBG_Assert(0);

	return 0;
}


