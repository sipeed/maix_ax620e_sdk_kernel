/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __ITEST_PUBLIC_COMPAT_H__
#define __ITEST_PUBLIC_COMPAT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int dev_my_future_open(void);
int dev_my_future_close(void);
int dev_my_future_ioctl(unsigned int cmd, void *param);


#endif /* __ITEST_PUBLIC_COMPAT_H__ */
