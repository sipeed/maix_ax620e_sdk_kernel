/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __ITEST_LOG_H__
#define __ITEST_LOG_H__


#ifdef ITEST_RTT_ENABLE
    #include <rtthread.h>
#endif /*#ifdef ITEST_RTT_ENABLE*/

#define ITEST_DEBUG

#undef DBG_TAG
#undef DBG_LVL

#define DBG_TAG              "testcase"

#ifdef ITEST_RTT_ENABLE

    #ifdef ITEST_DEBUG
        #define DBG_LVL              DBG_LOG
    #else
        #define DBG_LVL              DBG_INFO
    #endif

#else /*ITEST_LINUX_ENABLE*/

    #define DBG_LVL              7

#endif  /*#ifdef ITEST_RTT_ENABLE*/


#ifdef ITEST_RTT_ENABLE
    #include <rtdbg.h>
#endif /*#ifdef ITEST_RTT_ENABLE*/

#define ITEST_LOG_ALL    (1u)
#define ITEST_LOG_ASSERT (2u)

void itest_log_lv_set(rt_uint8_t lv);

#endif /* __ITEST_LOG_H__ */
