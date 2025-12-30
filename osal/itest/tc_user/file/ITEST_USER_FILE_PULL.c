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

#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>
#define TIMEOUT 5


#include "itest.h"
#include "itest_log.h"
static void test_func_0011(void)
{
    struct pollfd fds[2];
    int ret;

    /* watch stdin for input */
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    /* watch stdout for ability to write */
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    printf("test pool");

    ret = poll(fds, 2, TIMEOUT * 1000);

    if (ret == -1) {
        perror("poll");
        return ;
    }

    if (!ret) {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return ;
    }

    if (fds[0].revents & POLLIN)
        printf("stdin is readable\n");

    if (fds[1].revents & POLLOUT)
        printf("stdout is writable\n");



    uassert_true(1);

    return ;
}

static void test_func_0021(void)
{
    uassert_true(1);
}

static rt_err_t utest_tc_init1(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup1(void)
{
    return RT_EOK;
}

ITEST_TC_EXPORT(test_func_0011, "test_func_0011", utest_tc_init1, utest_tc_cleanup1, 10, ITEST_TC_EXCE_AUTO);
ITEST_TC_EXPORT(test_func_0021, "test_func_0021", utest_tc_init1, utest_tc_cleanup1, 10, ITEST_TC_EXCE_MANUAL);

