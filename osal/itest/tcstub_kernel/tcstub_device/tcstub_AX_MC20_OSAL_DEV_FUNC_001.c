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

AX_S32 TEST_OSAL_DEV_open(AX_VOID *private_data)
{
    printk("Function[%s : %d] is called\n", __FUNCTION__, __LINE__);
    return 0;
}

AX_S32 TEST_OSAL_DEV_read(AX_S8 *buf, AX_S32 size, AX_LONG *offset, AX_VOID *private_data)
{
    printk("Function[%s : %d] is called\n", __FUNCTION__, __LINE__);

    return size;
}

AX_S32 TEST_OSAL_DEV_write(const AX_S8 *buf, AX_S32 size, AX_LONG *offset, AX_VOID *private_data)
{
    printk("Function[%s : %d] is called\n", __FUNCTION__, __LINE__);

    return size;
}

AX_S32 TEST_OSAL_DEV_release(AX_VOID *private_data)
{
    printk("Function[%s : %d] is called\n", __FUNCTION__, __LINE__);
    return 0;
}

struct AX_FILEOPS  TEST_dev_fileops = {TEST_OSAL_DEV_open, /*open*/
           TEST_OSAL_DEV_read,  /*read*/
           TEST_OSAL_DEV_write,  /*write*/
           AX_NULL,  /*llseek*/
           TEST_OSAL_DEV_release,  /*release*/
           AX_NULL,  /*unlocked_ioctl*/
           AX_NULL /*poll*/
};

int tcstub_AX_MC20_OSAL_DEV_FUNC_001_001(unsigned int cmd, unsigned long arg)
{
    char *dev_name = "TEST_dev_001";
    AX_DEV_T *osal_dev;
    AX_S32 ret = 0;

    printk("create new device [%s]---	\n", dev_name);

    osal_dev = AX_OSAL_DEV_createdev(dev_name);

    if (osal_dev == AX_NULL) {
        printk("Function[%s : %d] create device is ERROR\n", __FUNCTION__, __LINE__);
        ret = -1;
    }

    osal_dev->fops = &TEST_dev_fileops;
    osal_dev->osal_pmops = AX_NULL;
    osal_dev->minor = 0x101;

	printk("register new device [%s]---	\n", dev_name);

    ret = AX_OSAL_DEV_device_register(osal_dev);
    if (ret != 0) {
        printk("Function[%s : %d] register device is ERROR\n", __FUNCTION__, __LINE__);
        ret = -1;
    }
    printk("exit register new device [%s]---	\n", __FUNCTION__);

    return ret;
}

int tcstub_AX_MC20_OSAL_DEV_FUNC_001_002(unsigned int cmd, unsigned long arg)
{
    printk("create new thread [%s]---	\n", __FUNCTION__);

    printk("exit new thread [%s]---	\n", __FUNCTION__);

    return 0;
}

