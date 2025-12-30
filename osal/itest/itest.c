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

#undef DBG_TAG
#undef DBG_LVL

#define DBG_TAG          "itest"
#ifdef itest_DEBUG
    #define DBG_LVL          DBG_LOG
#else
    #define DBG_LVL          DBG_INFO
#endif

static rt_uint8_t itest_log_lv = ITEST_LOG_ALL;
static itest_tc_export_t tc_table = RT_NULL;
static int tc_num;
static rt_uint32_t tc_loop;
static struct itest local_itest = {ITEST_PASSED, 0, 0};


void itest_log_lv_set(rt_uint8_t lv)
{
    if (lv == ITEST_LOG_ALL || lv == ITEST_LOG_ASSERT) {
        itest_log_lv = lv;
    }
}

int itest_init(void)
{
#if 0
    /* initialize the itest commands table.*/
    /* for GCC Compiler */
    extern const int __rt_itest_tc_tab_start;
    extern const int __rt_itest_tc_tab_end;
    tc_table = (itest_tc_export_t)&__rt_itest_tc_tab_start;
    tc_num = (itest_tc_export_t) &__rt_itest_tc_tab_end - tc_table;
#endif
    tc_table = (itest_tc_export_t)rt_itest_tc_tab_start_get();
    tc_num = rt_itest_tc_number_get();


    LOG_I("itest is initialize success.");
    LOG_I("total itest testcase num: (%d)", tc_num);
    return tc_num;
}
INIT_COMPONENT_EXPORT(itest_init);

static const char *__tc_type[3] = {"AUTO", "MANUAL", "NONE"};
static const char *__get_tc_type(uint32_t tc_type)
{
    if (tc_type == ITEST_TC_EXCE_AUTO) {
        return __tc_type[0];
    } else if (tc_type == ITEST_TC_EXCE_MANUAL) {
        return __tc_type[1];
    } else {
        return __tc_type[2];
    }

    return RT_NULL;
}

static void itest_tc_list(void)
{
    rt_size_t i = 0;

    LOG_I("Commands list : ");

    for (i = 0; i < tc_num; i++) {
        LOG_I("[testcase name]:%s; [run timeout]:%d; [type]:%s", \
              tc_table[i].name, \
              tc_table[i].run_timeout, \
              __get_tc_type(tc_table[i].tc_exec_type));
    }
}
MSH_CMD_EXPORT_ALIAS(itest_tc_list, itest_list, output all itest testcase);

static const char *file_basename(const char *file)
{
    char *end_ptr = RT_NULL;
    char *rst = RT_NULL;

    if (!((end_ptr = strrchr(file, '\\')) != RT_NULL || \
          (end_ptr = strrchr(file, '/')) != RT_NULL) || \
        (rt_strlen(file) < 2)) {
        rst = (char *)file;
    } else {
        rst = (char *)(end_ptr + 1);
    }
    return (const char *)rst;
}

static int itest_help(void)
{
    rt_kprintf("\n");
    rt_kprintf("Command: itest_run\n");
    rt_kprintf("   info: Execute test cases.\n");
    rt_kprintf(" format: itest_run [-thread or -help] [testcase name] [loop num]\n");
    rt_kprintf("  usage:\n");
    rt_kprintf("         1. itest_run\n");
    rt_kprintf("            Do not specify a test case name. Run all test cases.\n");
    rt_kprintf("         2. itest_run -thread\n");
    rt_kprintf("            Do not specify a test case name. Run all test cases in threaded mode.\n");
    rt_kprintf("         3. itest_run testcaseA\n");
    rt_kprintf("            Run 'testcaseA'.\n");
    rt_kprintf("         4. itest_run testcaseA 10\n");
    rt_kprintf("            Run 'testcaseA' ten times.\n");
    rt_kprintf("         5. itest_run -thread testcaseA\n");
    rt_kprintf("            Run 'testcaseA' in threaded mode.\n");
    rt_kprintf("         6. itest_run -thread testcaseA 10\n");
    rt_kprintf("            Run 'testcaseA' ten times in threaded mode.\n");
    rt_kprintf("         7. itest_run test*\n");
    rt_kprintf("            support '*' wildcard. Run all test cases starting with 'test'.\n");
    rt_kprintf("         8. itest_run -help\n");
    rt_kprintf("            Show itest help information\n");
    rt_kprintf("\n");
    return 0;
}

static int _is_auto_testcause(uint32_t tc_exec_type, rt_bool_t forced)
{
    return tc_exec_type == ITEST_TC_EXCE_AUTO || forced;
}

static void _init_each_tc()
{
    // LOG_I("[==========] itest unit name: (%s)", unit_func_name);
    local_itest.error = ITEST_PASSED;
    local_itest.passed_num = 0;
    local_itest.failed_num = 0;
}

static void itest_run(const char *itest_name)
{
    rt_size_t i;
    rt_uint32_t index;
    rt_bool_t is_find;

    rt_bool_t is_force_auto = RT_FALSE;

    rt_thread_mdelay(1000);
    LOG_I("[==========] [ itest    ] tc_num = %d, tc_loop = %u ", tc_num, tc_loop);

    for (index = 0; index < tc_loop; index ++) {
        i = 0;
        is_find = RT_FALSE;
        LOG_I("[==========] [ itest    ] loop %d/%d", index + 1, tc_loop);
        LOG_I("[==========] [ itest    ] started");
        while (i < tc_num) {
            is_force_auto = RT_FALSE;

            if (itest_name) {
                int len = strlen(itest_name);
                if (itest_name[len - 1] == '*') {
                    len -= 1;
                } else {
                    is_force_auto = RT_TRUE;
                }
                if (rt_memcmp(tc_table[i].name, itest_name, len) != 0) {
                    i++;
                    continue;
                }
            }
            is_find = RT_TRUE;

            if (_is_auto_testcause(tc_table[i].tc_exec_type, is_force_auto))
                LOG_I("[----------] [ testcase ] (%s) started", tc_table[i].name);

            if (tc_table[i].init != RT_NULL) {
                if (tc_table[i].init() != RT_EOK) {
                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
                    goto __tc_continue;
                }
            }

            if ((tc_table[i].tc != RT_NULL) && (_is_auto_testcause(tc_table[i].tc_exec_type, is_force_auto))) {
                _init_each_tc();

                tc_table[i].tc();
                if (local_itest.failed_num == 0) {
                    LOG_I("[  PASSED  ] [ result   ] testcase (%s)", tc_table[i].name);
                } else {

                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
                }
            } else {
                if (_is_auto_testcause(tc_table[i].tc_exec_type, is_force_auto))
                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
            }

            if (tc_table[i].cleanup != RT_NULL) {
                if (tc_table[i].cleanup() != RT_EOK) {
                    LOG_E("[  FAILED  ] [ result   ] testcase (%s)", tc_table[i].name);
                    goto __tc_continue;
                }
            }

__tc_continue:
            if (_is_auto_testcause(tc_table[i].tc_exec_type, is_force_auto))
                LOG_I("[----------] [ testcase ] (%s) finished", tc_table[i].name);

            i++;
        }

        if (i == tc_num && is_find == RT_FALSE && itest_name != RT_NULL) {
            LOG_I("[==========] [ itest    ] Not find (%s)", itest_name);
            LOG_I("[==========] [ itest    ] finished");
            break;
        }

        LOG_I("[==========] [ itest    ] finished");
    }
}

static void itest_testcase_run(int argc, char **argv)
{
#if ITEST_RTT_ENABLE
    void *thr_param = RT_NULL;
#endif
    static char itest_name[ITEST_NAME_MAX_LEN];
    rt_memset(itest_name, 0x0, sizeof(itest_name));

    tc_loop = 1;

    if (argc == 1) {
        itest_run(RT_NULL);
        return;
    } else if (argc == 2 || argc == 3 || argc == 4) {
        if (rt_strcmp(argv[1], "-thread") == 0) {
#if ITEST_RTT_ENABLE
            rt_thread_t tid = RT_NULL;
            if (argc == 3 || argc == 4) {
                rt_strncpy(itest_name, argv[2], sizeof(itest_name) - 1);
                thr_param = (void *)itest_name;

                if (argc == 4) tc_loop = atoi(argv[3]);
            }
            tid = rt_thread_create("itest",
                                   (void (*)(void *))itest_run, thr_param,
                                   ITEST_THREAD_STACK_SIZE, ITEST_THREAD_PRIORITY, 10);
            if (tid != NULL) {
                rt_thread_startup(tid);
            }
#endif
        } else if (rt_strcmp(argv[1], "-help") == 0) {
            itest_help();
        } else if (rt_strcmp(argv[1], "-list") == 0) {
            itest_tc_list();
        } else {
            rt_strncpy(itest_name, argv[1], sizeof(itest_name) - 1);
            if (argc == 3) tc_loop = atoi(argv[2]);
            itest_run(itest_name);
        }
    } else {
        LOG_E("[  error   ] at (%s:%d), in param error.", __func__, __LINE__);
        itest_help();
    }
}

MSH_CMD_EXPORT_ALIAS(itest_testcase_run, itest_run, itest_run [-thread or - help] [testcase name] [loop num]);

itest_t itest_handle_get(void)
{
    return (itest_t)&local_itest;
}

void itest_unit_run(test_unit_func func, const char *unit_func_name)
{
    // LOG_I("[==========] itest unit name: (%s)", unit_func_name);
    local_itest.error = ITEST_PASSED;
    local_itest.passed_num = 0;
    local_itest.failed_num = 0;

    if (func != RT_NULL) {
        func();
    }
}

void itest_assert(int value, const char *file, int line, const char *func, const char *msg)
{
    if (!(value)) {
        local_itest.error = ITEST_FAILED;
        local_itest.failed_num ++;
        LOG_E("[  ASSERT  ] [ unit     ] at (%s); func: (%s:%d); msg: (%s)", file_basename(file), func, line, msg);
    } else {
        if (itest_log_lv == ITEST_LOG_ALL) {
            LOG_D("[    OK    ] [ unit     ] (%s:%d) is passed", func, line);
        }
        local_itest.error = ITEST_PASSED;
        local_itest.passed_num ++;
    }
}

void itest_assert_string(const char *a, const char *b, rt_bool_t equal, const char *file, int line, const char *func,
                         const char *msg)
{
    if (a == RT_NULL || b == RT_NULL) {
        itest_assert(0, file, line, func, msg);
    }

    if (equal) {
        if (rt_strcmp(a, b) == 0) {
            itest_assert(1, file, line, func, msg);
        } else {
            itest_assert(0, file, line, func, msg);
        }
    } else {
        if (rt_strcmp(a, b) == 0) {
            itest_assert(0, file, line, func, msg);
        } else {
            itest_assert(1, file, line, func, msg);
        }
    }
}

void itest_assert_buf(const char *a, const char *b, rt_size_t sz, rt_bool_t equal, const char *file, int line,
                      const char *func, const char *msg)
{
    if (a == RT_NULL || b == RT_NULL) {
        itest_assert(0, file, line, func, msg);
    }

    if (equal) {
        if (rt_memcmp(a, b, sz) == 0) {
            itest_assert(1, file, line, func, msg);
        } else {
            itest_assert(0, file, line, func, msg);
        }
    } else {
        if (rt_memcmp(a, b, sz) == 0) {
            itest_assert(0, file, line, func, msg);
        } else {
            itest_assert(1, file, line, func, msg);
        }
    }
}

void AX_TEST_Start(int argc, char **argv)
{
    itest_init();

    itest_testcase_run(argc, argv);
    //itest_tc_list();
}
/*begin to start itest*/
ITEST_START

