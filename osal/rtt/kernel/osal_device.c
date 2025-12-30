/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_ax.h"
#include "osal_dev_ax.h"
#include "rtthread.h"
#include "dfs_file.h"

#include "rthw.h"
#include "power_ax.h"

AX_DEV_T *AX_OSAL_DEV_createdev(AX_S8 *name)
{
    struct rt_device *rt_pdev = RT_NULL;
    AX_DEV_T *osal_pdev = RT_NULL;

    if (name == RT_NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return RT_NULL;
    }

    rt_pdev = (struct rt_device *)rt_malloc(sizeof(struct rt_device));
    if (rt_pdev == RT_NULL) {
        rt_kprintf("%s - rt_malloc error!\n", __FUNCTION__);
        goto errout;
    }
    rt_memset(rt_pdev, 0, sizeof(struct rt_device));

    osal_pdev = (AX_DEV_T *)rt_malloc(sizeof(struct AX_DEV));
    if (osal_pdev == RT_NULL) {
        rt_kprintf("%s - rt_malloc error!\n", __FUNCTION__);
        goto errout;
    }

    rt_memset(osal_pdev, 0, sizeof(struct AX_DEV));
    //rt_snprintf(osal_pdev->name, 48, "/dev/%s", name);

	rt_snprintf(osal_pdev->name, 48, "%s", name);
    osal_pdev->minor = 0;
    osal_pdev->dev = rt_pdev;

    return osal_pdev;

errout:
    if (rt_pdev) {
        rt_free(rt_pdev);
    }
    return RT_NULL;
}

AX_S32 AX_OSAL_DEV_destroydev(AX_DEV_T *osal_dev)
{
    struct rt_device *rt_pdev;

    if (osal_dev == RT_NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    rt_pdev = (struct rt_device *)osal_dev->dev;
    if (rt_pdev == RT_NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }
    rt_free(rt_pdev);
    rt_pdev = RT_NULL;

    rt_free(osal_dev);
    osal_dev = RT_NULL;

    return 0;
}

#ifdef RT_USING_DEVICE_OPS
static rt_err_t __osal_dev_ops_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t __osal_dev_ops_open(rt_device_t dev, rt_uint16_t oflag)
{
    AX_DEV_T *osal_pdev = (AX_DEV_T *)dev->user_data;
    RT_ASSERT(osal_pdev != RT_NULL);
    RT_ASSERT(osal_pdev->fops != RT_NULL);

    //dev->user_data = osal_pdev->private_data;

    if (osal_pdev->fops->open) {
        osal_pdev->fops->open(osal_pdev->private_data);
    }

    return RT_EOK;
}

static rt_err_t __osal_dev_ops_close(rt_device_t dev)
{
    AX_DEV_T *osal_pdev = (AX_DEV_T *)dev->user_data;
    RT_ASSERT(osal_pdev != RT_NULL);
    RT_ASSERT(osal_pdev->fops != RT_NULL);

    //dev->user_data = osal_pdev->private_data;

    if (osal_pdev->fops->release) {
        osal_pdev->fops->release(osal_pdev->private_data);
    }

    return RT_EOK;
}

static rt_err_t __osal_dev_ops_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;
    AX_DEV_T *osal_pdev = (AX_DEV_T *)dev->user_data;
    RT_ASSERT(osal_pdev != RT_NULL);
    RT_ASSERT(osal_pdev->fops != RT_NULL);

    //dev->user_data = osal_pdev->private_data;

    if (osal_pdev->fops->unlocked_ioctl) {
        ret = osal_pdev->fops->unlocked_ioctl(cmd, (AX_ULONG)args, osal_pdev->private_data);
    }

    return ret;
}

static rt_size_t __osal_dev_ops_read(rt_device_t dev,
                                     rt_off_t    pos,
                                     void       *buffer,
                                     rt_size_t   size)
{
    AX_DEV_T *osal_pdev = (AX_DEV_T *)dev->user_data;
    RT_ASSERT(osal_pdev != RT_NULL);
    RT_ASSERT(osal_pdev->fops != RT_NULL);

    //dev->user_data = osal_pdev->private_data;
	rt_size_t rd_size = 0;

    if (osal_pdev->fops->read) {
        rd_size = osal_pdev->fops->read(buffer, size, &pos, osal_pdev->private_data);
    }

    //return 0;
    return rd_size;
}

static rt_size_t __osal_dev_ops_write(rt_device_t dev,
                                      rt_off_t    pos,
                                      const void *buffer,
                                      rt_size_t   size)
{
    AX_DEV_T *osal_pdev = (AX_DEV_T *)dev->user_data;
    RT_ASSERT(osal_pdev != RT_NULL);
    RT_ASSERT(osal_pdev->fops != RT_NULL);

    //dev->user_data = osal_pdev->private_data;
	rt_size_t wt_size = 0;

    if (osal_pdev->fops->write) {
        wt_size = osal_pdev->fops->write(buffer, size, &pos, osal_pdev->private_data);
    }

    return wt_size;
}

static int __osal_dev_ops_poll(rt_device_t dev,
                               rt_pollreq_t *req)
{
  AX_DEV_T *osal_pdev = (AX_DEV_T *)dev->user_data;
  RT_ASSERT(osal_pdev != RT_NULL);
  RT_ASSERT(osal_pdev->fops != RT_NULL);

  int mask = 0;
  if (osal_pdev->fops->poll) {
	  osal_pdev->dev_poll.poll_table = req;
	  osal_pdev->dev_poll.data = osal_pdev;
	  osal_pdev->dev_wait.wait = &(dev->wait_queue);
	  mask = osal_pdev->fops->poll(&osal_pdev->dev_poll, osal_pdev->private_data);
  }

  return mask;
}

const static struct rt_device_ops _osal_dev_ops = {
    __osal_dev_ops_init,
    __osal_dev_ops_open,
    __osal_dev_ops_close,
    __osal_dev_ops_read,
    __osal_dev_ops_write,
    __osal_dev_ops_control,
    __osal_dev_ops_poll
};
#endif

#ifdef RT_USING_POSIX
#include <dfs_posix.h>
#include <dfs_poll.h>

static int __osal_vfs_fops_open(struct dfs_fd *fd)
{
    rt_err_t ret = 0;
    rt_uint16_t flags = 0;
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    ret = rt_device_open(device, flags);
    if (ret == RT_EOK) return 0;

    return ret;
}

static int __osal_vfs_fops_close(struct dfs_fd *fd)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    rt_device_close(device);
    return 0;
}

static int __osal_vfs_fops_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    return rt_device_control(device, cmd, args);
}

static int __osal_vfs_fops_read(struct dfs_fd *fd, void *buf, size_t count)
{
    int size = 0;
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    size = rt_device_read(device, -1, buf, count);

    return size;
}

static int __osal_vfs_fops_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    return rt_device_write(device, -1, buf, count);
}

static int __osal_vfs_fops_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    rt_device_t device;

    device = (rt_device_t)fd->data;
    RT_ASSERT(device != RT_NULL);

    return rt_device_poll(device, req);
}

const static struct dfs_file_ops _osal_vfs_fops = {
    __osal_vfs_fops_open,
    __osal_vfs_fops_close,
    __osal_vfs_fops_ioctl,
    __osal_vfs_fops_read,
    __osal_vfs_fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    __osal_vfs_fops_poll,
};
#endif


int __device_suspend(struct rt_device *rt_dev)
{
	int ret = RT_EOK;
	RT_ASSERT(rt_dev != RT_NULL);
	RT_ASSERT(rt_dev->user_data  != RT_NULL);
	AX_DEV_T *osal_dev = (AX_DEV_T *)rt_dev->user_data;

	if (osal_dev->osal_pmops && osal_dev->osal_pmops->pm_suspend )
		ret = osal_dev->osal_pmops->pm_suspend(osal_dev);


	return ret;
}
int __device_suspend_late(struct rt_device *rt_dev)
{
	int ret = RT_EOK;
	RT_ASSERT(rt_dev != RT_NULL);
	RT_ASSERT(rt_dev->user_data  != RT_NULL);

	AX_DEV_T *osal_dev = (AX_DEV_T *)rt_dev->user_data;

	if (osal_dev->osal_pmops && osal_dev->osal_pmops->pm_suspend_late )
		ret = osal_dev->osal_pmops->pm_suspend_late(osal_dev);


	return ret;
}

int __device_resume_early(struct rt_device *rt_dev)
{
	int ret = RT_EOK;
	RT_ASSERT(rt_dev != RT_NULL);
	RT_ASSERT(rt_dev->user_data  != RT_NULL);

	AX_DEV_T *osal_dev = (AX_DEV_T *)rt_dev->user_data;

	if (osal_dev->osal_pmops && osal_dev->osal_pmops->pm_resume_early )
		ret = osal_dev->osal_pmops->pm_resume_early(osal_dev);


	return ret;
}

int __device_resume(struct rt_device *rt_dev)
{
	int ret = RT_EOK;
	RT_ASSERT(rt_dev != RT_NULL);
	RT_ASSERT(rt_dev->user_data  != RT_NULL);

	AX_DEV_T *osal_dev = (AX_DEV_T *)rt_dev->user_data;

	if (osal_dev->osal_pmops && osal_dev->osal_pmops->pm_resume )
		ret = osal_dev->osal_pmops->pm_resume(osal_dev);

	return ret;
}

static int __register_device_pmops(struct rt_device *rt_pdev, AX_OSAL_PMOPS_T* osal_pmops)
{
	RT_ASSERT(rt_pdev != RT_NULL);

	if (osal_pmops) {
		AX_PM_DEV_OPS_T *pm_dev_ops = (AX_PM_DEV_OPS_T *)rt_malloc(sizeof(AX_PM_DEV_OPS_T));
		RT_ASSERT(pm_dev_ops != RT_NULL);

		/*Step 1/2, Package node of pm_dev_ops*/
		pm_dev_ops->suspend = __device_suspend;
		pm_dev_ops->suspend_late = __device_suspend_late;
		pm_dev_ops->resume_early = __device_resume_early;
		pm_dev_ops->resume = __device_resume;
		
		rt_list_init(&(pm_dev_ops->dev_suspend_list));
		rt_list_init(&(pm_dev_ops->dev_suspend_late_list));
		pm_dev_ops->status = PM_NODE_IDLE;

		/*Step 2/2, register device PM OPS into PowerManagement Framework*/
		AX_DRV_PM_DevRegister(rt_pdev, pm_dev_ops);
		rt_pdev->pmops = pm_dev_ops;
	}

	return RT_EOK;
}

static int __unregister_device_pmops(struct rt_device *rt_pdev)
{
	RT_ASSERT(rt_pdev != RT_NULL);

	AX_DRV_PM_DevUnregister(rt_pdev);

	AX_PM_DEV_OPS_T *pm_dev_ops = rt_pdev->pmops;
	if (pm_dev_ops) {
		rt_free(pm_dev_ops);
		rt_pdev->pmops = RT_NULL;
	}

	return RT_EOK;
}


AX_S32 AX_OSAL_DEV_device_register(AX_DEV_T *osal_dev)
{
    AX_S32 rt_err = RT_EOK;
    struct rt_device *rt_pdev;

	RT_ASSERT(osal_dev);
	RT_ASSERT(osal_dev->fops);
	
    if (osal_dev == RT_NULL || osal_dev->fops == RT_NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    rt_pdev = (struct rt_device *)osal_dev->dev;
    rt_pdev->user_data = (AX_VOID *)osal_dev;

#ifdef RT_USING_DEVICE_OPS
    rt_pdev->ops  = &_osal_dev_ops;
#endif
    rt_err = rt_device_register((rt_device_t)osal_dev->dev,
                                osal_dev->name,
                                RT_DEVICE_FLAG_RDWR);

#if defined(RT_USING_POSIX)
    /* set fops */
    rt_pdev->fops = &_osal_vfs_fops;
#endif

	__register_device_pmops(rt_pdev, osal_dev->osal_pmops);
    return rt_err;
}

AX_VOID AX_OSAL_DEV_device_unregister(AX_DEV_T *osal_dev)
{
    if (osal_dev == NULL || osal_dev->dev == RT_NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return;
    }
	
	__unregister_device_pmops((struct rt_device *)osal_dev->dev);
    rt_device_unregister((struct rt_device *)osal_dev->dev);

    return;
}

/*
wait->wait is waitqueue, dev->wait_queue => wait->wait
*/
AX_VOID AX_OSAL_DEV_poll_wait(AX_POLL_T *table, AX_WAIT_T *wait)
{
	RT_ASSERT(table);
	RT_ASSERT(wait);
	//AX_DEV_T *osal_pdev = (AX_DEV_T *)table->data;
	//rt_device_t dev = (rt_device_t)osal_pdev->dev;

	//rt_poll_add(&(dev->wait_queue), (rt_pollreq_t *)table->poll_table);
	rt_poll_add((rt_wqueue_t *)(wait->wait), (rt_pollreq_t *)table->poll_table);

    return ;
}

//RTT not support
AX_VOID AX_OSAL_DEV_pgprot_noncached(AX_VM_T *vm)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return ;
}

//RTT not support
AX_VOID AX_OSAL_DEV_pgprot_cached(AX_VM_T *vm)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return ;
}

//RTT not support
AX_VOID AX_OSAL_DEV_pgprot_writecombine(AX_VM_T *vm)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return ;
}

//RTT not support
AX_VOID AX_OSAL_DEV_pgprot_stronglyordered(AX_VM_T *vm)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return ;
}

//RTT not support
AX_S32 AX_OSAL_DEV_remap_pfn_range(AX_VM_T *vm, AX_ULONG addr, AX_ULONG pfn, AX_ULONG size)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

//RTT not support
AX_S32 AX_OSAL_DEV_io_remap_pfn_range(AX_VM_T *vm, AX_ULONG addr, AX_ULONG pfn, AX_ULONG size)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

/*device framework(platform) API*/
//RTT not support
AX_S32 AX_OSAL_DEV_platform_driver_register(AX_VOID *drv)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

//RTT not support
AX_VOID AX_OSAL_DEV_platform_driver_unregister(AX_VOID *drv)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return;
}

//RTT not support
AX_VOID *AX_OSAL_DEV_platform_get_resource_byname(AX_VOID *dev, AX_U32 type, const AX_S8 *name,struct AXERA_RESOURCE *res)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return AX_NULL;
}

//RTT not support
AX_VOID *AX_OSAL_DEV_platform_get_resource(AX_VOID *dev, AX_U32 type, AX_U32 num,struct AXERA_RESOURCE *res)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return AX_NULL;
}

//RTT not support
AX_S32 AX_OSAL_DEV_platform_get_irq(AX_VOID *dev, AX_U32 num)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

//RTT not support
AX_S32 AX_OSAL_DEV_platform_get_irq_byname(AX_VOID *dev, const AX_S8 *name)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}


void AX_OSAL_IO_bit_set(AX_U32 *bitmap, AX_S32 pos)
{
    if (bitmap == RT_NULL) {
        return;
    }

    *bitmap |= 1U << (pos & 0x1FU);
}

void AX_OSAL_IO_bit_clean(AX_U32 *bitmap, AX_S32 pos)
{
    if (bitmap == RT_NULL) {
        return;
    }

    *bitmap &= ~(1U << (pos & 0x1FU));
}


