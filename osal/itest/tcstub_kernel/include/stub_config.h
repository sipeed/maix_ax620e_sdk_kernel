/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _ITEST_STUB_CONFIG_H_ADD
#define _ITEST_STUB_CONFIG_H_ADD

#include "itest_cmd_config.h"

typedef struct tcstub_list {
    unsigned long cmd;
    tcstub_func func;
} tcstub_list_t;

/*OSAL TASK */
extern int tcstub_AX_MC20_OSAL_TASK_FUNC_001_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TASK_FUNC_001_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TASK_FUNC_001_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TASK_FUNC_001_004(unsigned int cmd, unsigned long arg);


/*OSAL DEVICE */
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_001_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_001_002(unsigned int cmd, unsigned long arg);

extern int tcstub_AX_MC20_OSAL_DEV_FUNC_002_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_002_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_002_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_002_004(unsigned int cmd, unsigned long arg);

extern int tcstub_AX_MC20_OSAL_DEV_FUNC_003_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_003_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DEV_FUNC_003_003(unsigned int cmd, unsigned long arg);

/*OSAL ATOMIC */
extern int tcstub_AX_MC20_OSAL_ATOMIC_FUNC_001_001(unsigned int cmd, unsigned long arg);

/*OSAL BARRIER */
extern int tcstub_AX_MC20_OSAL_BARRIER_FUNC_001_001(unsigned int cmd, unsigned long arg);

/*OSAL MUTEX */
extern int tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001(unsigned int cmd, unsigned long arg);

/*OSAL SEMAPHORE */
extern int tcstub_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001(unsigned int cmd, unsigned long arg);

/*OSAL WAITEVENT */
extern int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002(unsigned int cmd, unsigned long arg);

/*OSAL WAITQUEUE */
extern int tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001(unsigned int cmd, unsigned long arg);

/*OSAL WORKQUEUE */
extern int tcstub_AX_MC20_OSAL_WORKQUEUE_FUNC_001_001(unsigned int cmd, unsigned long arg);

/*OSAL DEBUG */
extern int tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_004(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_004(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_004(unsigned int cmd, unsigned long arg);

/*OSAL TIMER */
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_001_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_002_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_003_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_004_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_004_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_004_003(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_005_001(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_005_002(unsigned int cmd, unsigned long arg);
extern int tcstub_AX_MC20_OSAL_TIMER_FUNC_005_003(unsigned int cmd, unsigned long arg);


tcstub_list_t g_tcstub_list[] = {
    /*OSAL TASK */
    {iocmd_AX_MC20_OSAL_TASK_FUNC_001_001, tcstub_AX_MC20_OSAL_TASK_FUNC_001_001},
    {iocmd_AX_MC20_OSAL_TASK_FUNC_001_002, tcstub_AX_MC20_OSAL_TASK_FUNC_001_002},
    {iocmd_AX_MC20_OSAL_TASK_FUNC_001_003, tcstub_AX_MC20_OSAL_TASK_FUNC_001_003},
    {iocmd_AX_MC20_OSAL_TASK_FUNC_001_004, tcstub_AX_MC20_OSAL_TASK_FUNC_001_004},


    /*OSAL DEVICE */
    {iocmd_AX_MC20_OSAL_DEV_FUNC_001_001, tcstub_AX_MC20_OSAL_DEV_FUNC_001_001},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_001_002, tcstub_AX_MC20_OSAL_DEV_FUNC_001_002},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_002_001, tcstub_AX_MC20_OSAL_DEV_FUNC_002_001},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_002_002, tcstub_AX_MC20_OSAL_DEV_FUNC_002_002},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_002_003, tcstub_AX_MC20_OSAL_DEV_FUNC_002_003},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_002_004, tcstub_AX_MC20_OSAL_DEV_FUNC_002_004},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_003_001, tcstub_AX_MC20_OSAL_DEV_FUNC_003_001},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_003_002, tcstub_AX_MC20_OSAL_DEV_FUNC_003_002},
    {iocmd_AX_MC20_OSAL_DEV_FUNC_003_003, tcstub_AX_MC20_OSAL_DEV_FUNC_003_003},

    /*OSAL ATOMIC */
    {iocmd_AX_MC20_OSAL_ATOMIC_FUNC_001_001, tcstub_AX_MC20_OSAL_ATOMIC_FUNC_001_001},

    /*OSAL BARRIER */
    {iocmd_AX_MC20_OSAL_BARRIER_FUNC_001_001, tcstub_AX_MC20_OSAL_BARRIER_FUNC_001_001},

    /*OSAL MUTEX */
    {iocmd_AX_MC20_OSAL_MUTEX_FUNC_001_001, tcstub_AX_MC20_OSAL_MUTEX_FUNC_001_001},

    /*OSAL SEMAPHORE */
    {iocmd_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001, tcstub_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001},

    /*OSAL WAITEVENT */
    {iocmd_AX_MC20_OSAL_WAITEVENT_FUNC_001_001, tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_001},
    {iocmd_AX_MC20_OSAL_WAITEVENT_FUNC_001_002, tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001_002},

    /*OSAL WAITQUEUE */
    {iocmd_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001, tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001_001},

    /*OSAL WORKQUEUE */
    {iocmd_AX_MC20_OSAL_WORKQUEUE_FUNC_001_001, tcstub_AX_MC20_OSAL_WORKQUEUE_FUNC_001_001},

    /*OSAL DEBUG */
    {iocmd_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_001, tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_001},
    {iocmd_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_002, tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_002},
    {iocmd_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_003, tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001_003},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_001, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_001},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_002, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_002},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_003, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_003},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_001_004, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001_004},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_001, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_001},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_002, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_002},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_003, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_003},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_002_004, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002_004},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_001, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_001},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_002, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_002},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_003, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_003},
    {iocmd_AX_MC20_OSAL_DBG_LOG_FUNC_003_004, tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003_004},

    /*OSAL TIMER */
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_001_001, tcstub_AX_MC20_OSAL_TIMER_FUNC_001_001},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_002_001, tcstub_AX_MC20_OSAL_TIMER_FUNC_002_001},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_003_001, tcstub_AX_MC20_OSAL_TIMER_FUNC_003_001},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_004_001, tcstub_AX_MC20_OSAL_TIMER_FUNC_004_001},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_004_002, tcstub_AX_MC20_OSAL_TIMER_FUNC_004_002},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_004_003, tcstub_AX_MC20_OSAL_TIMER_FUNC_004_003},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_005_001, tcstub_AX_MC20_OSAL_TIMER_FUNC_005_001},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_005_002, tcstub_AX_MC20_OSAL_TIMER_FUNC_005_002},
    {iocmd_AX_MC20_OSAL_TIMER_FUNC_005_003, tcstub_AX_MC20_OSAL_TIMER_FUNC_005_003},
};


#endif /*_ITEST_STUB_CONFIG_H_ADD*/
