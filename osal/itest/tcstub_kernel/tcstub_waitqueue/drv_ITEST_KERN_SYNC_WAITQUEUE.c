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

#include "itest_public_cmd.h"

static int AX_itest_DevOpen(struct inode *inode, struct file *file)
{
    printk("Open file for my future = %p \n", file);
    return 0;
}

static int AX_itest_DevRelease(struct inode *inode, struct file *file)
{
    printk("Release file for my future = %p \n", file);
    return 0;
}


/*--------------------prepare_to_wait---------------------------*/
static wait_queue_head_t *g_wq;

int threadProduct(void *data)
{
    int index = 0;
    long ret = 5; //5s

    DEFINE_WAIT(__wait);

    for (; index < 1; index++) {
        prepare_to_wait(g_wq, &__wait, TASK_INTERRUPTIBLE);
        //schedule();

        ret = schedule_timeout(msecs_to_jiffies(ret * 1000));
        printk("schedule_timeout return value, ret = %ld \n", ret);

        ret = jiffies_to_msecs(ret);
        printk("jiffies_to_msecs return value, ret = %ld \n", ret);

        finish_wait(g_wq, &__wait);
        printk("<<<<<<<<<get msg. threadProduct(index = %d) is called	\n", index);
    }

    printk("exit thread ---threadProduct \n");

    return 0;
}

int threadConsume(void *data)
{
    int index = 0;
    for (; index < 1; index++) {
        printk("wait for 6s \n");
        ssleep(10);
        wake_up_all(g_wq);
        printk(">>>>>>>send msg. threadConsume(index = %d) is called	\n", index);
    }

    printk("exit thread ---threadConsume \n");

    return 0;
}

void sample_list_001(void)
{
    struct task_struct *k, *p;

    char *data = NULL;
    char *nameP = "my_threadProduct";
    char *nameC = "my_threadConsume";

    g_wq = (wait_queue_head_t *)kmalloc(sizeof(wait_queue_head_t), GFP_ATOMIC);
    init_waitqueue_head(g_wq);

    k = kthread_run(threadProduct, data, nameP);
    p = kthread_run(threadConsume, (void *)data, nameC);
}


/*--------------------wait event---------------------------*/
static wait_queue_head_t g_wq_002;

int g_wait_condition = 0;

int threadProduct_002(void *data)
{
    int index = 0;

    long ret = 5; //5s

    DEFINE_WAIT(__wait);

    for (; index < 1; index++) {
        printk("wait event, g_wait_condition = %d , msecs_to_jiffies	\n",  g_wait_condition);

        //wait_event(g_wq_002, g_wait_condition);

        wait_event_timeout(g_wq_002, g_wait_condition, msecs_to_jiffies(ret * 1000));
        printk("timeout *********wait_event_timeout, g_wait_condition = %d , msecs_to_jiffies	\n",  g_wait_condition);
        printk("<<<<<<<<<get msg. threadProduct(index = %d) is called	\n", index);
    }

    printk("exit thread ---threadProduct_002 msecs_to_jiffies  \n");
    return 0;
}

int threadConsume_002(void *data)
{
    int index = 0;
    for (; index < 1; index++) {
        printk("wait for 19s \n");
        ssleep(19);
        //g_wait_condition = 1;
        wake_up_all(&g_wq_002);
        printk(">>>>>>>send msg. threadConsume(index = %d) is called	\n", index);
    }

    printk("exit thread ---threadConsume_002 msecs_to_jiffies\n");
    return 0;
}

void sample_list_002(void)
{
    struct task_struct *k, *p;

    char *data = NULL;
    char *nameP = "my_threadProduct";
    char *nameC = "my_threadConsume";

    //g_wq = (wait_queue_head_t *)kmalloc(sizeof(wait_queue_head_t), GFP_ATOMIC);
    //g_wq_002 = (wait_queue_head_t *)kmalloc(sizeof(wait_queue_head_t), GFP_ATOMIC);
    init_waitqueue_head(&g_wq_002);

    k = kthread_run(threadProduct_002, data, nameP);

    p = kthread_run(threadConsume_002, (void *)data, nameC);
}


/*--------------------wait event---------------------------*/
static int itest_userdev_ioctl_list(struct file *file, unsigned int cmd, unsigned long pmi)
{
    int ret = 0;

    switch (cmd) {
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_001:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_001 cmd %x  \n", cmd);
        //sample_list_001();
        //sample_list_002();
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_002:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_002 cmd %x  \n", cmd);
        //sample_list_002();
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_003:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_003 cmd %x  \n", cmd);
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_004:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_004 cmd %x  \n", cmd);
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_005:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_005 cmd %x  \n", cmd);
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_006:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_006 cmd %x  \n", cmd);
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_007:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_007 cmd %x  \n", cmd);
        break;
    case ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_008:
        printk("KERNEL ioctrl -> rcv ioctrl_cmd_ITEST_KERN_SYNC_WAITQUEUE_008 cmd %x  \n", cmd);
        break;
    default:
        printk("KERNEL ioctrl -> rcv default cmd %x  \n", cmd);
        break;
    }

    return ret;
}

long itest_userdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = 0;

    ret = itest_userdev_ioctl_list(file, cmd, arg);

    return ret;
}

static long AX_itest_DevIOCtrl_Unlock(struct file *file, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = itest_userdev_ioctl(file, cmd, arg);

    return ret;
}

static int AX_itest_DevIoctrl_MMap(struct file *file, struct vm_area_struct *vma)
{
    printk("AX_CMM_DevIoctrl_MMap is called.");

    return 0;
}

static struct file_operations ax_itest_userdev_fops = {
    .owner    = THIS_MODULE,
    .open    = AX_itest_DevOpen,
    .release = AX_itest_DevRelease,
    .unlocked_ioctl = AX_itest_DevIOCtrl_Unlock,
    .mmap    = AX_itest_DevIoctrl_MMap,
};

static struct miscdevice itest_userdev = {
    .minor    = MISC_DYNAMIC_MINOR,
    .fops    = &ax_itest_userdev_fops,
    .name    = "my_itest"
};

int itest_userdev_init(void)
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
void __exit itest_userdev_exit(void)

{
    printk(KERN_INFO "unregister my_future Device %d\n", 1);
    misc_deregister(&itest_userdev);

}

module_init(itest_userdev_init);
module_exit(itest_userdev_exit);
