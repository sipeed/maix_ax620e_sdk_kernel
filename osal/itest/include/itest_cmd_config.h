/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __ITEST_PUBLIC_CMD_TYPE_COMPAT_H__haha
#define __ITEST_PUBLIC_CMD_TYPE_COMPAT_H__haha

enum itest_kernel_ioctrl_cmd_type {
    /*OSAL TASK */
    iocmd_AX_MC20_OSAL_TASK_FUNC_001_001 = 0x01,
    iocmd_AX_MC20_OSAL_TASK_FUNC_001_002,
    iocmd_AX_MC20_OSAL_TASK_FUNC_001_003,
    iocmd_AX_MC20_OSAL_TASK_FUNC_001_004,

    /*OSAL DEVICE */
    iocmd_AX_MC20_OSAL_DEV_FUNC_001_001,
    iocmd_AX_MC20_OSAL_DEV_FUNC_001_002,
    iocmd_AX_MC20_OSAL_DEV_FUNC_002_001,
    iocmd_AX_MC20_OSAL_DEV_FUNC_002_002,
    iocmd_AX_MC20_OSAL_DEV_FUNC_002_003,
    iocmd_AX_MC20_OSAL_DEV_FUNC_002_004,
    iocmd_AX_MC20_OSAL_DEV_FUNC_003_001,
    iocmd_AX_MC20_OSAL_DEV_FUNC_003_002,
    iocmd_AX_MC20_OSAL_DEV_FUNC_003_003,

    /*OSAL ATOMIC */
    iocmd_AX_MC20_OSAL_ATOMIC_FUNC_001_001,

    /*OSAL BARRIER */
    iocmd_AX_MC20_OSAL_BARRIER_FUNC_001_001,

    /*OSAL MUTEX */
    iocmd_AX_MC20_OSAL_MUTEX_FUNC_001_001,

    /*OSAL SEMAPHORE */
    iocmd_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001,
    iocmd_AX_MC20_OSAL_SEMAPHORE_FUNC_001_002,
    iocmd_AX_MC20_OSAL_SEMAPHORE_FUNC_001_003,

    /*OSAL WAITEVENT */
    iocmd_AX_MC20_OSAL_WAITEVENT_FUNC_001_001,
    iocmd_AX_MC20_OSAL_WAITEVENT_FUNC_001_002,

    /*OSAL WAITQUEUE */
    iocmd_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001,

    /*OSAL WORKQUEUE */
    iocmd_AX_MC20_OSAL_WORKQUEUE_FUNC_001_001,

    /*OSAL DEBUG */
    iocmd_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_001,
    iocmd_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_002,
    iocmd_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_003,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_001,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_002,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_003,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_004,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_001,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_002,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_003,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_004,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_001,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_002,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_003,
    iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_004,

    /*OSAL TIMER */
    iocmd_AX_MC20_OSAL_TIMER_FUNC_001_001,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_002_001,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_003_001,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_004_001,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_004_002,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_004_003,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_005_001,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_005_002,
    iocmd_AX_MC20_OSAL_TIMER_FUNC_005_003,
};

#endif /* __ITEST_PUBLIC_CMD_TYPE_COMPAT_H__haha */
