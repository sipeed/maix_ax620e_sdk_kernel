/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __UTEST_COMPAT_H__
#define __UTEST_COMPAT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#ifdef ITEST_RTT_ENABLE

#else /*ITEST_LINUX_ENABLE*/

    typedef signed   char                   rt_int8_t;      /**<  8bit integer type */
    typedef signed   short                  rt_int16_t;     /**< 16bit integer type */
    typedef signed   int                    rt_int32_t;     /**< 32bit integer type */
    typedef unsigned char                   rt_uint8_t;     /**<  8bit unsigned integer type */
    typedef unsigned short                  rt_uint16_t;    /**< 16bit unsigned integer type */
    typedef unsigned int                    rt_uint32_t;    /**< 32bit unsigned integer type */

    typedef int                             rt_bool_t;      /**< boolean type */
    typedef long                            rt_base_t;      /**< Nbit CPU related date type */
    typedef unsigned long                   rt_ubase_t;     /**< Nbit unsigned CPU related data type */

    typedef rt_base_t                       rt_err_t;       /**< Type for error number */
    typedef rt_uint32_t                     rt_time_t;      /**< Type for time stamp */
    typedef rt_uint32_t                     rt_tick_t;      /**< Type for tick count */
    typedef rt_base_t                       rt_flag_t;      /**< Type for flags */
    typedef rt_ubase_t                      rt_size_t;      /**< Type for size number */
    typedef rt_ubase_t                      rt_dev_t;       /**< Type for device */
    typedef rt_base_t                       rt_off_t;       /**< Type for offset */
    /* boolean type definitions */
    #define RT_TRUE                         1               /**< boolean true  */
    #define RT_FALSE                        0               /**< boolean fails */
    #define RT_NULL 0

    /*
    #define rt_kprintf printf
    #define LOG_I printf
    #define LOG_E printf
    #define LOG_D printf
    */

    #define rt_kprintf(fmt, ...)  printf(fmt "\n", ##__VA_ARGS__)
    #define LOG_I(fmt, ...)       printf(fmt "\n", ##__VA_ARGS__)
    #define LOG_E(fmt, ...)       printf(fmt "\n", ##__VA_ARGS__)
    #define LOG_D(fmt, ...)       printf(fmt "\n", ##__VA_ARGS__)

    #define rt_memcmp memcmp
    #define rt_memset memset
    #define rt_strcmp strcmp
    #define rt_strncpy strncpy
    #define rt_strlen strlen

    #define rt_thread_mdelay(ms) sleep(ms/1000)

    #define MSH_CMD_EXPORT_ALIAS(a,b,c)
    #define INIT_COMPONENT_EXPORT(a)

    #define RT_EOK                          0               /**< There is no error */
    #define RT_ERROR                        1               /**< A generic error happens */
    #define RT_ETIMEOUT                     2               /**< Timed out */
    #define RT_EFULL                        3               /**< The resource is full */
    #define RT_EEMPTY                       4               /**< The resource is empty */
    #define RT_ENOMEM                       5               /**< No memory */
    #define RT_ENOSYS                       6               /**< No system */
    #define RT_EBUSY                        7               /**< Busy */
    #define RT_EIO                          8               /**< IO error */
    #define RT_EINTR                        9               /**< Interrupted system call */
    #define RT_EINVAL                       10              /**< Invalid argument */

#endif /*#ifdef ITEST_RTT_ENABLE*/

#endif /* __UTEST_COMPAT_H__ */
