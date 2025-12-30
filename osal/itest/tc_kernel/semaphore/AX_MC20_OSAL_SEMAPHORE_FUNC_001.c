/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "itest.h"
#include "itest_log.h"
#include "itest_public.h"
#include "itest_cmd_config.h"

static rt_err_t AX_MC20_OSAL_SEMAPHORE_FUNC_001_tc_init(void)
{
    int ret = 0;
    printf("Func [%s] is called.\n", __FUNCTION__);
    ret = dev_my_future_open();
    if (ret < 0) {
        printf("ERROR, open dev failed.\n");
        return ret;
    }

    return RT_EOK;
}

static rt_err_t AX_MC20_OSAL_SEMAPHORE_FUNC_001_tc_cleanup(void)
{
    int ret = 0;
    printf("Func [%s] is called.\n", __FUNCTION__);
    ret = dev_my_future_close();
    if (ret < 0) {
        printf("ERROR, close dev failed.\n");
        return ret;
    }

    return RT_EOK;
}

static void AX_MC20_OSAL_SEMAPHORE_FUNC_001_001(void)
{
    int ret = 0;

    printf("Func [%s] is called.\n", __FUNCTION__);
    ret = dev_my_future_ioctl(iocmd_AX_MC20_OSAL_SEMAPHORE_FUNC_001_001, RT_NULL);
    if (ret < 0) {
        printf("ERROR, ioctrl dev failed.Func [%s]\n", __FUNCTION__);
        uassert_true(0);
    }

    uassert_true(1);
    return;
}


ITEST_TC_EXPORT(AX_MC20_OSAL_SEMAPHORE_FUNC_001_001, "AX_MC20_OSAL_SEMAPHORE_FUNC_001_001",
                AX_MC20_OSAL_SEMAPHORE_FUNC_001_tc_init, AX_MC20_OSAL_SEMAPHORE_FUNC_001_tc_cleanup, 10, ITEST_TC_EXCE_AUTO);
