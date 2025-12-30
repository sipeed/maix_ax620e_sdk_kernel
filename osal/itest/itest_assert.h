/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __ITEST_ASSERT_H__
#define __ITEST_ASSERT_H__

#include "itest.h"

#ifdef ITEST_RTT_ENABLE
    #include <rtthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* No need for the user to use this function directly */
void itest_assert(int value, const char *file, int line, const char *func, const char *msg);

/* No need for the user to use this function directly */
void itest_assert_string(const char *a, const char *b, rt_bool_t equal, const char *file, int line, const char *func,
                         const char *msg);
void itest_assert_buf(const char *a, const char *b, rt_size_t sz, rt_bool_t equal, const char *file, int line,
                      const char *func, const char *msg);

/* No need for the user to use this macro directly */
#define __itest_assert(value, msg) itest_assert(value, __FILE__, __LINE__, __func__, msg)

/**
 * uassert_x macros
 *
 * @brief Get the itest data structure handle.
 *        No need for the user to call this function directly.
 *
 * @macro uassert_true          if @value is true,     not assert, means passing.
 * @macro uassert_false         if @value is false,    not assert, means passing.
 * @macro uassert_null          if @value is null,     not assert, means passing.
 * @macro uassert_not_null      if @value is not null, not assert, means passing.
 * @macro uassert_int_equal     if @a equal to @b,     not assert, means passing. Integer type test.
 * @macro uassert_int_not_equal if @a not equal to @b, not assert, means passing. Integer type test.
 * @macro uassert_str_equal     if @a equal to @b,     not assert, means passing. String type test.
 * @macro uassert_str_not_equal if @a not equal to @b, not assert, means passing. String type test.
 * @macro uassert_buf_equal     if @a equal to @b,     not assert, means passing. buf type test.
 * @macro uassert_buf_not_equal if @a not equal to @b, not assert, means passing. buf type test.
 * @macro uassert_in_range      if @value is in range of min and max,     not assert, means passing.
 * @macro uassert_not_in_range  if @value is not in range of min and max, not assert, means passing.
 *
*/
#define uassert_true(value)      __itest_assert(value, "(" #value ") is false")
#define uassert_false(value)     __itest_assert(!(value), "(" #value ") is true")
#define uassert_null(value)      __itest_assert((const char *)(value) == NULL, "(" #value ") is not null")
#define uassert_not_null(value)  __itest_assert((const char *)(value) != NULL, "(" #value ") is null")

#define uassert_int_equal(a, b)      __itest_assert((a) == (b), "(" #a ") not equal to (" #b ")")
#define uassert_int_not_equal(a, b)  __itest_assert((a) != (b), "(" #a ") equal to (" #b ")")

#define uassert_str_equal(a, b)      itest_assert_string((const char*)(a), (const char*)(b), RT_TRUE, __FILE__, __LINE__, __func__, "string not equal")
#define uassert_str_not_equal(a, b)  itest_assert_string((const char*)(a), (const char*)(b), RT_FALSE, __FILE__, __LINE__, __func__, "string equal")

#define uassert_buf_equal(a, b, sz)      itest_assert_buf((const char*)(a), (const char*)(b), (sz), RT_TRUE, __FILE__, __LINE__, __func__, "buf not equal")
#define uassert_buf_not_equal(a, b, sz)  itest_assert_buf((const char*)(a), (const char*)(b), (sz), RT_FALSE, __FILE__, __LINE__, __func__, "buf equal")

#define uassert_in_range(value, min, max)     __itest_assert(((value >= min) && (value <= max)), "(" #value ") not in range("#min","#max")")
#define uassert_not_in_range(value, min, max) __itest_assert(!((value >= min) && (value <= max)), "(" #value ") in range("#min","#max")")

#ifdef __cplusplus
}
#endif

#endif /* __ITEST_ASSERT_H__ */
