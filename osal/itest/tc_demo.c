/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <string.h>
#include <stdlib.h>

#include "itest.h"
#include "itest_log.h"

static void test_func_001(void)
{
    uassert_true(1);
}

static void test_func_002(void)
{
    uassert_true(1);
}

static void test_func_003(void)
{
    uassert_true(1);
}

static void test_func_004(void)
{
    uassert_true(1);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

ITEST_TC_EXPORT(test_func_001, "test_func_001", utest_tc_init, utest_tc_cleanup, 10, ITEST_TC_EXCE_AUTO);
ITEST_TC_EXPORT(test_func_002, "test_func_002", utest_tc_init, utest_tc_cleanup, 10, ITEST_TC_EXCE_MANUAL);
ITEST_TC_EXPORT(test_func_003, "test_func_003", utest_tc_init, utest_tc_cleanup, 10, ITEST_TC_EXCE_AUTO);
ITEST_TC_EXPORT(test_func_004, "test_func_004", utest_tc_init, utest_tc_cleanup, 10, ITEST_TC_EXCE_MANUAL);
