/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_logdebug_ax.h"
#include "osal_ax.h"
#include "rtthread.h"

#include "backtrace.h"
#include "log_ax.h"
#include "ulog.h"

static char osal_log_buf[256];
AX_S32 AX_OSAL_DBG_printk(const AX_S8 *fmt, ...)
{
    rt_int32_t n;
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    n = rt_vsprintf(osal_log_buf, fmt, arg_ptr);
    va_end(arg_ptr);

    rt_kprintf(osal_log_buf);

    return n;
}

AX_VOID AX_OSAL_DBG_panic(const AX_S8 *fmt, const AX_S8 *fun, AX_S32 line, const AX_S8 *cond)
{

	rt_assert_handler(fmt, fun, line);

    return ;
}

extern void ulog_voutput(rt_uint32_t level, const char *tag, rt_bool_t newline, const char *format, va_list args);
AX_VOID AX_OSAL_DBG_LogOutput(AX_S32 target, AX_S32 level, const char *tag, const AX_S8 *fmt, ...)
{
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, fmt);

	ulog_voutput(level, tag, RT_TRUE, fmt,  args);

	va_end(args);

    return ;
}

void AX_OSAL_DBG_ISPLogoutput(int level, const char *fmt,...)
{
	va_list args;
	/* args point to the first variable parameter */
	va_start(args, fmt);
	char * tag = "ISP";

	ulog_voutput(level, tag, RT_TRUE, fmt,	args);

	va_end(args);
	return;
}

void AX_OSAL_DBG_NPULogoutput(int level, const char *fmt,...)
{
	va_list args;
	/* args point to the first variable parameter */
	va_start(args, fmt);
	char * tag = "NPU";

	ulog_voutput(level, tag, RT_TRUE, fmt,	args);

	va_end(args);
	return;
}

void AX_OSAL_DBG_CMMLogoutput(int level, const char *fmt,...)
{
	va_list args;
	/* args point to the first variable parameter */
	va_start(args, fmt);
	char * tag = "CMM";

	ulog_voutput(level, tag, RT_TRUE, fmt,	args);

	va_end(args);
	return;
}

void AX_OSAL_DBG_POOLLogoutput(int level, const char *fmt,...)
{
	va_list args;
	/* args point to the first variable parameter */
	va_start(args, fmt);
	char * tag = "POOL";

	ulog_voutput(level, tag, RT_TRUE, fmt,	args);

	va_end(args);
	return;
}

void AX_OSAL_DBG_APPLogoutput(int level, const char *fmt,...)
{
    va_list args;
    /* args point to the first variable parameter */
    va_start(args, fmt);
    char * tag = "APP";

    ulog_voutput(level, tag, RT_TRUE, fmt,	args);

    va_end(args);
    return;
}

AX_S32 AX_OSAL_DBG_SetLogLevel(AX_S32 level)
{
	RT_ASSERT(level <= LOG_FILTER_LVL_ALL);
	ulog_global_filter_lvl_set((rt_uint32_t) level);

    return 0;
}

AX_S32 AX_OSAL_DBG_SetLogTarget(AX_S32 level)
{
    return 0;
}

AX_S32 AX_OSAL_DBG_EnableTimestamp(AX_S32 enable)
{
    return 0;
}

AX_S32 AX_OSAL_DBG_EnableTraceEvent(AX_S32 module, AX_S32 enable)
{
    return 0;
}

AX_PROC_DIR_ENTRY_T *AX_OSAL_DBG_create_proc_entry(const AX_S8 *name, AX_PROC_DIR_ENTRY_T *parent)
{
    return AX_NULL;
}

AX_PROC_DIR_ENTRY_T *AX_OSAL_DBG_proc_mkdir(const AX_S8 *name, AX_PROC_DIR_ENTRY_T *parent)
{
    return AX_NULL;
}

AX_VOID AX_OSAL_DBG_remove_proc_entry(const AX_S8 *name, AX_PROC_DIR_ENTRY_T *parent)
{
    return ;
}

AX_VOID AX_OSAL_DBG_seq_printf(AX_PROC_DIR_ENTRY_T *entry, const AX_S8 *fmt, ...)
{
    return ;
}


