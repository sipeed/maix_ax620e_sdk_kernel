/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __ITEST_H__
#define __ITEST_H__

#include <stdint.h>

#include "itest_compat.h"

#ifdef ITEST_RTT_ENABLE
    #include "itest_log.h"
    #include <rtthread.h>
    #include "itest_assert.h"
    #include <rtdbg.h>

    #if RT_CONSOLEBUF_SIZE < 256
        #error "RT_CONSOLEBUF_SIZE is less than 256!"
    #endif

    #ifdef ITEST_THR_STACK_SIZE
        #define ITEST_THREAD_STACK_SIZE ITEST_THR_STACK_SIZE
    #else
        #define ITEST_THREAD_STACK_SIZE (4096)
    #endif

    #ifdef ITEST_THR_PRIORITY
        #define ITEST_THREAD_PRIORITY   ITEST_THR_PRIORITY
    #else
        #define ITEST_THREAD_PRIORITY   FINSH_THREAD_PRIORITY
    #endif

#else /*ITEST_LINUX_ENABLE*/

    #include "itest_assert.h"


#endif /*#ifdef ITEST_RTT_ENABLE*/


#ifdef __cplusplus
extern "C" {
#endif

/**
 * itest_error
 *
 * @brief Test result.
 *
 * @member ITEST_PASSED Test success.
 * @member ITEST_FAILED Test failed.
 * @member ITEST_PASSED Test skipped.
 *
*/

enum itest_exec_type {
    ITEST_TC_EXCE_AUTO  = 0,
    ITEST_TC_EXCE_MANUAL  = 1,
    ITEST_TC_EXCE_MAX = 0xFF
};

enum itest_error {
    ITEST_PASSED  = 0,
    ITEST_FAILED  = 1,
    ITEST_SKIPPED = 2
};
typedef enum itest_error itest_err_e;

/**
 * itest
 *
 * @brief itest data structure.
 *
 * @member error      Error number from enum `itest_error`.
 * @member passed_num Total number of tests passed.
 * @member failed_num Total number of tests failed.
 *
*/
struct itest {
    itest_err_e error;
    uint32_t passed_num;
    uint32_t failed_num;
};
typedef struct itest *itest_t;

/**
 * itest_tc_export
 *
 * @brief itest testcase data structure.
 *        Will export the data to `UtestTcTab` section in flash.
 *
 * @member name        Testcase name.
 * @member run_timeout Testcase maximum test time (Time unit: seconds).
 * @member init        Necessary initialization before executing the test case function.
 * @member tc          Total number of tests failed.
 * @member cleanup     Total number of tests failed.
 *
*/
struct itest_tc_export {
    const char  *name;
    uint32_t     run_timeout;
    rt_err_t (*init)(void);
    void (*tc)(void);
    rt_err_t (*cleanup)(void);
    uint32_t   tc_exec_type;
};
typedef struct itest_tc_export *itest_tc_export_t;

/**
 * test_unit_func
 *
 * @brief Unit test handler function pointer.
 *
*/
typedef void (*test_unit_func)(void);

/**
 * itest_unit_run
 *
 * @brief Unit test function executor.
 *        No need for the user to call this function directly
 *
 * @param func           Unit test function.
 * @param unit_func_name Unit test function name.
 *
 * @return void
 *
*/
void itest_unit_run(test_unit_func func, const char *unit_func_name);

/**
 * itest_handle_get
 *
 * @brief Get the itest data structure handle.
 *        No need for the user to call this function directly
 *
 * @param void
 *
 * @return itest_t type. (struct itest *)
 *
*/
itest_t itest_handle_get(void);

/**
 * ITEST_NAME_MAX_LEN
 *
 * @brief Testcase name maximum length.
 *
*/
#define ITEST_NAME_MAX_LEN (128u)

/**
 * ITEST_TC_EXPORT
 *
 * @brief Export testcase function to `UtestTcTab` section in flash.
 *        Used in application layer.
 *
 * @param testcase The testcase function.
 * @param name     The testcase name.
 * @param init     The initialization function of the test case.
 * @param cleanup  The cleanup function of the test case.
 * @param timeout  Testcase maximum test time (Time unit: seconds).
 *
 * @return None
 *
*/
#ifdef ITEST_RTT_ENABLE
#define ITEST_TC_EXPORT(testcase, name, init, cleanup, timeout, tc_exec_type)                \
    static const struct itest_tc_export _itest_testcase_##testcase  __attribute__((used))        \
    SECTION("ItestTcTab") =                                                    \
    {                                                                          \
        name,                                                                  \
        timeout,                                                               \
        init,                                                                  \
        testcase,                                                              \
        cleanup,                                                                \
        tc_exec_type                                                           \
    }

/**
 * ITEST_UNIT_RUN
 *
 * @brief Unit test function executor.
 *        Used in `testcase` function in application.
 * @param test_unit_func Unit test function
*/
#define ITEST_UNIT_RUN(test_unit_func)                                         \
    itest_unit_run(test_unit_func, #test_unit_func);                           \
    if(itest_handle_get()->failed_num != 0) return;

#else /*#ifdef ITEST_LINUX_ENABLE*/
#define __SECTION(x)                  __attribute__((section(x)))
//#define __SECTION(x)                __attribute((section(x)))

#define ITEST_TC_EXPORT(testcase, name, init, cleanup, timeout, tc_exec_type)                \
    static const struct itest_tc_export _itest_testcase_##testcase  __attribute__((used))        \
    __SECTION(".ItestTcTab") =                                                    \
    {                                                                          \
        name,                                                                  \
        timeout,                                                               \
        init,                                                                  \
        testcase,                                                              \
        cleanup,                                                                \
        tc_exec_type                                                           \
    }

#endif /*#ifdef ITEST_RTT_ENABLE*/

#ifdef ITEST_RTT_ENABLE
static inline void *rt_itest_tc_tab_start_get(void)
{
    /* initialize the itest commands table.*/
    /* for GCC Compiler */
    extern  unsigned long __rt_itest_tc_tab_start;
    return (void *)&__rt_itest_tc_tab_start;
}
static inline int rt_itest_tc_number_get(void)
{
    extern  unsigned long __rt_itest_tc_tab_start;
    extern  unsigned long __rt_itest_tc_tab_end;
    itest_tc_export_t tc_table_p = (itest_tc_export_t)&__rt_itest_tc_tab_start;
    return ((itest_tc_export_t) &__rt_itest_tc_tab_end - tc_table_p);
}

#else /*ITEST_LINUX_ENABLE*/
static inline void *rt_itest_tc_tab_start_get(void)
{
    /* initialize the itest commands table.*/
    /* for GCC Compiler */
    extern  unsigned long __rt_itest_tc_tab_start;
    return (void *)&__rt_itest_tc_tab_start;
}
static inline int rt_itest_tc_number_get(void)
{
    extern  unsigned long __rt_itest_tc_tab_start;
    extern  unsigned long __rt_itest_tc_tab_end;
    itest_tc_export_t tc_table_p = (itest_tc_export_t)&__rt_itest_tc_tab_start;
    return ((itest_tc_export_t) &__rt_itest_tc_tab_end - tc_table_p);
}

#endif /*#ifdef ITEST_RTT_ENABLE*/

#ifdef ITEST_RTT_ENABLE
#define ITEST_START
#else
#define ITEST_START  int main(int argc, char** argv) { \
    AX_TEST_Start(argc, argv); \
    return 0; \
    }
#endif /*#ifdef ITEST_RTT_ENABLE*/

#ifdef __cplusplus
}
#endif

#endif /* __ITEST_H__ */
