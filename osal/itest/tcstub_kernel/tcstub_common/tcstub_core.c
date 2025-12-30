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
#include <linux/slab.h>

#include "stub_public.h"
#include "stub_config.h"

struct list_head g_tcstub_list_head;

static int __itest_DevOpen(struct inode *inode, struct file *file)
{
    printk("Open file for my future = %p \n", file);
    INIT_LIST_HEAD(&g_tcstub_list_head);
    return 0;
}

static int __itest_DevRelease(struct inode *inode, struct file *file)
{
    printk("Release file for my future = %p \n", file);
    return 0;
}

static tcstub_func __tcstub_get(unsigned int cmd)
{

    int index = 0;

    while (index < sizeof(g_tcstub_list) / sizeof(g_tcstub_list[0])) {
        if (cmd == g_tcstub_list[index].cmd)
            return g_tcstub_list[index].func;

        index++;
    }

    return NULL;
}

static long _userdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = 0;
    tcstub_func func = __tcstub_get(cmd);
    if (func) {
        printk("KERNEL ioctrl -> rcv cmd [%x] \n", cmd);
        ret = func(cmd, arg);
    } else {
        printk("KERNEL ioctrl -> not found cmd = [%x] \n", cmd);
        ret = -1;
    }

    return ret;
}

static long __itest_DevIOCtrl_Unlock(struct file *file, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = _userdev_ioctl(file, cmd, arg);

    return ret;
}

static int __itest_DevIoctrl_MMap(struct file *file, struct vm_area_struct *vma)
{
    printk("AX_CMM_DevIoctrl_MMap is called.");

    return 0;
}

static struct file_operations ax_itest_userdev_fops = {
    .owner    = THIS_MODULE,
    .open    = __itest_DevOpen,
    .release = __itest_DevRelease,
    .unlocked_ioctl = __itest_DevIOCtrl_Unlock,
    .mmap    = __itest_DevIoctrl_MMap,
};

static struct miscdevice itest_userdev = {
    .minor    = MISC_DYNAMIC_MINOR,
    .fops    = &ax_itest_userdev_fops,
    .name    = "my_itest"
};

static int itest_userdev_init(void)
{
    int ret;
    printk(KERN_INFO "Register my_future Device %d \n", 1);
    ret = misc_register(&itest_userdev);
    if (ret)    {
        printk(KERN_ERR "register my_future dev failure! %d \n", 1);
        return -1;
    }

    return 0;
}

static void __exit itest_userdev_exit(void)
{
    printk(KERN_INFO "unregister my_future Device %d\n", 1);
    misc_deregister(&itest_userdev);

}

module_init(itest_userdev_init);
module_exit(itest_userdev_exit);
