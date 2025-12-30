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
#include "osal_cmm_ax.h"
#include "osal_dev_ax.h"
#include "osal_lib_ax.h"
#include "osal_list_ax.h"
#include "osal_logdebug_ax.h"
#include "osal_pm_ax.h"
#include "osal_type_ax.h"
#include "osal_user_ax.h"
#include "cmm_headh.h"
#include "cmm_drv_interface.h"


#define cmm_debug(str, arg...)  AX_OSAL_DBG_CMMLogoutput(AX_LOG_LVL_DBG, "%s(%d): "str, __FUNCTION__, __LINE__, ##arg)
#define cmm_info(str, arg...)   AX_OSAL_DBG_CMMLogoutput(AX_LOG_LVL_INFO, "%s(%d): "str, __FUNCTION__, __LINE__, ##arg)
#define cmm_error(str, arg...)  AX_OSAL_DBG_CMMLogoutput(AX_LOG_LVL_ERROR, "%s(%d): "str, __FUNCTION__, __LINE__, ##arg)
#define cmm_warn(str, arg...)   AX_OSAL_DBG_CMMLogoutput(AX_LOG_LVL_WARNING, "%s(%d): "str, __FUNCTION__, __LINE__, ##arg)

#define AX_CMM_DRIVER_NAME   "ax_cmm"

typedef struct ax_cmm_drvdata {
    AX_DEV_T   *cmm_dev;
} ax_cmm_drvdata_t;

static ax_cmm_drvdata_t *pdrvdata = RT_NULL;

static AX_S32 ax_cmm_pm_prepare(AX_DEV_T *dev)
{
    return 0;
}

struct AX_PMOPS cmm_dev_pmops = {ax_cmm_pm_prepare, NULL, NULL, NULL};

static AX_S32 ax_cmm_userdev_open(AX_VOID *private_data)
{
    //cmm_info("ax_cmm_userdev_open\n");

    return 0;
}

static AX_S32 ax_cmm_userdev_close(AX_VOID *private_data)
{
    //cmm_info("ax_cmm_userdev_close\n");

    return 0;
}

static AX_LONG ax_cmm_userdev_unlocked_ioctl(AX_U32 cmd, AX_ULONG arg, AX_VOID *private_data)
{
    mem_param_t mm_param = { 0 };
    AX_LONG ret = 0;
    enum ax_heap_type memtype = AX_NONCACHE_HEAP;

    if ( AX_OSAL_DEV_copy_from_user(&mm_param, (void *)arg, sizeof(mem_param_t))) {
		cmm_error("copy_from_user fail");
        return -EFAULT;
    }

    //cmm_info("mm_param.align=%d\n",mm_param.align);
    //cmm_info("mm_param.size=%d\n",mm_param.size);
    //cmm_info("mm_param.flags=%d\n",mm_param.flags);
    //cmm_info("mm_param.token=%s\n",mm_param.token);
    //cmm_info("mm_param.phyaddr=0x%lx\n",mm_param.phyaddr);
    //cmm_info("mm_param.viraddr=0x%lx\n",(unsigned int)((unsigned int *)mm_param.viraddr));
    //cmm_info("cmd=0x%x\n",cmd);

    switch (cmd) {
    case SYS_IOC_MEM_ALLOC:
        if (mm_param.flags == MEM_NONCACHED)
        	memtype = AX_NONCACHE_HEAP;
        else
        	memtype = AX_CACHE_HEAP;
        
        ret = cmm_MemAlloc(&mm_param.phyaddr,&mm_param.viraddr,mm_param.size,mm_param.align,mm_param.token,memtype);
        if (ret) {
        	cmm_error("cmm_MemAlloc fail");
        	return -EFAULT;
        }
        
        if ( AX_OSAL_DEV_copy_to_user((void *)arg, &mm_param, sizeof(mem_param_t))) {
        	cmm_error("copy_to_user fail");
        	return -EFAULT;
        }	
        break;
    case SYS_IOC_MEM_FREE:
        ret = cmm_MemFree(mm_param.viraddr);
        if (ret) {
            cmm_error("cmm_MemFree fail");
        	return -EFAULT;
        }
        break;
    case SYS_IOC_MEM_FLUSH_CACHE:
        ret = cmm_MemFlushCache(mm_param.viraddr,mm_param.size);
        if (ret) {
            cmm_error("cmm_MemFlushCache fail");
        	return -EFAULT;
        }
        break;
    case SYS_IOC_MEM_INVALIDATE_CACHE:
        ret = cmm_MemInvalidateCache(mm_param.viraddr,mm_param.size);
        if (ret) {
            cmm_error("cmm_MemInvalidateCache fail");
        	return -EFAULT;
        }
        break;
	//rtos not support mmap/unmap
    case SYS_IOC_MEM_REMAP:
        break;
    case SYS_IOC_MEM_REMAP_CACHED:
        break;
    case SYS_IOC_MEM_UNMAP:
        break;
	default:
		break;
	}

    return 0;
}

static struct AX_FILEOPS cmm_dev_fops = {
    .open    = ax_cmm_userdev_open,
    .release = ax_cmm_userdev_close,
    .unlocked_ioctl = ax_cmm_userdev_unlocked_ioctl,
};

AX_S32 ax_cmm_userdev_init(AX_VOID)
{
    AX_S32 ret = 0;

    pdrvdata = (ax_cmm_drvdata_t *)AX_OSAL_MEM_kmalloc(sizeof(ax_cmm_drvdata_t), 0);
    if (pdrvdata == NULL) {
        cmm_error("AX_OSAL_MEM_kmalloc memory Error!\n");
		return -1;
    } else {
        AX_OSAL_LIB_memset(pdrvdata, 0, sizeof(ax_cmm_drvdata_t));
    }

    pdrvdata->cmm_dev = AX_OSAL_DEV_createdev(AX_CMM_DRIVER_NAME);
    if (pdrvdata->cmm_dev == NULL) {
        cmm_error("cmm device create Error!\n");
        goto EXIT0;
    }

    pdrvdata->cmm_dev->fops = &cmm_dev_fops;
    pdrvdata->cmm_dev->osal_pmops = &cmm_dev_pmops;
    pdrvdata->cmm_dev->minor = 0x105;
    pdrvdata->cmm_dev->private_data = pdrvdata;

    ret = AX_OSAL_DEV_device_register(pdrvdata->cmm_dev);
    if (ret != 0) {
        cmm_error("cmm device register Error!\n");
        goto EXIT1;
    }

    cmm_info("ax_cmm_userdev_init success!\n");
    return 0;

EXIT1:
    AX_OSAL_DEV_destroydev(pdrvdata->cmm_dev);
EXIT0:
    AX_OSAL_MEM_kfree(pdrvdata);
    pdrvdata = NULL;
    return -1;
}

AX_S32 ax_cmm_userdev_exit(AX_VOID)
{
    AX_S32 ret = 0;

    if (pdrvdata) {
        AX_OSAL_DEV_device_unregister(pdrvdata->cmm_dev);

        ret =  AX_OSAL_DEV_destroydev(pdrvdata->cmm_dev);
        if (ret != 0) {
            cmm_error("cmm device destroy Error!\n");
            return -1;
        }

        pdrvdata->cmm_dev = NULL;
        AX_OSAL_MEM_kfree(pdrvdata);
        pdrvdata = NULL;
    }
    cmm_info("ax_cmm_userdev_exit success!\n");
    return 0;
}