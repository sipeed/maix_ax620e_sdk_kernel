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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include <pthread.h>
#include <poll.h>
#include <semaphore.h>

#include "itest_public.h"

static int g_dev_my_fd = -1;

int dev_my_future_open(void)
{
    printf("dev_my_future_open is called!\n");

    g_dev_my_fd = open("/dev/my_itest", O_RDWR);
    if (g_dev_my_fd < 0) {
        printf("ERROR, open /dev/my_itest failed.\n");
        return -1;
    }
    printf("sys dev_my_future_open success!\n");
    return 0;
}

int dev_my_future_close(void)
{
    printf("dev_my_future_close is called!\n");

    if (g_dev_my_fd >= 0) {
        close(g_dev_my_fd);
        g_dev_my_fd = -1;
    } else {
        printf("ERROR, There is no dev [/dev/my_future] \n");
        return -1;
    }

    printf("sys dev_my_future_close success!\n");

    return 0;
}

int dev_my_future_ioctl(unsigned int cmd, void *param)
{
    int retval = 0;

    printf("dev_my_future_ioctl is called!\n");

    retval = ioctl(g_dev_my_fd, cmd, param);
    if (0 != retval) {
        printf("ERROR, ioctl /dev/my_itest failed, ioctl retval = %d.\n", retval);
        return -1;
    }

    return 0;
}

