/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_lib_ax.h"
#include "rtthread.h"


//string api
AX_S8 *AX_OSAL_LIB_strcpy(AX_S8 *dest, const AX_S8 *src)
{
    return (AX_S8 *)rt_strncpy(dest, src, rt_strlen(src) + 1);
}

AX_S8 *AX_OSAL_LIB_strncpy(AX_S8 *dest, const AX_S8 *src, AX_S32 count)
{
    return (AX_S8 *)rt_strncpy(dest, src, count);
}

//RTT not support
AX_S32 AX_OSAL_LIB_strlcpy(AX_S8 *dest, const AX_S8 *src, AX_S32 count)
{
    return 0;
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strcat(AX_S8 *dest, const AX_S8 *src)
{
    return AX_NULL;
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strncat(AX_S8 *dest, const AX_S8 *src, AX_S32 count)
{
    return AX_NULL;
}

//RTT not support
AX_S32 AX_OSAL_LIB_strlcat(AX_S8 *dest, const AX_S8 *src, AX_S32 count)
{
    return 0;
}

AX_S32 AX_OSAL_LIB_strcmp(const AX_S8 *cs, const AX_S8 *ct)
{
    return (AX_S32)rt_strcmp(cs, ct);
}

AX_S32 AX_OSAL_LIB_strncmp(const AX_S8 *cs, const AX_S8 *ct, AX_S32 count)
{
    return (AX_S32)rt_strncmp(cs, ct, count);
}

//RTT not support
AX_S32 AX_OSAL_LIB_strnicmp(const AX_S8 *s1, const AX_S8 *s2, AX_S32 len)
{
    return 0;
}

AX_S32 AX_OSAL_LIB_strcasecmp(const AX_S8 *s1, const AX_S8 *s2)
{
    return (AX_S32)rt_strcasecmp(s1, s2);
}

//RTT not support
AX_S32 AX_OSAL_LIB_strncasecmp(const AX_S8 *s1, const AX_S8 *s2, AX_S32 len)
{
    return 0;
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strchr(const AX_S8 *s, AX_S32 c)
{
    return AX_NULL;
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strnchr(const AX_S8 *s, AX_S32 count, AX_S32 c)
{
    return AX_NULL;
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strrchr(const AX_S8 *s, AX_S32 c)
{
    return AX_NULL;
}

AX_S8 *AX_OSAL_LIB_strstr(const AX_S8 *s1, const AX_S8 *s2)
{
    return (AX_S8 *)rt_strstr(s1, s2);
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strnstr(const AX_S8 *s1, const AX_S8 *s2, AX_S32 len)
{
    return AX_NULL;
}

AX_S32 AX_OSAL_LIB_strlen(const AX_S8 *s)
{
    return (AX_S32)rt_strlen(s);
}

AX_S32 AX_OSAL_LIB_strnlen(const AX_S8 *s, AX_S32 count)
{
    return (AX_S32)rt_strnlen(s, count);
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strpbrk(const AX_S8 *cs, const AX_S8 *ct)
{
    return AX_NULL;
}

//RTT not support
AX_S8 *AX_OSAL_LIB_strsep(const AX_S8 **s, const AX_S8 *ct)
{
    return AX_NULL;
}

//RTT not support
AX_S32 AX_OSAL_LIB_strspn(const AX_S8 *s, const AX_S8 *accept)
{
    return 0;
}

//RTT not support
AX_S32 AX_OSAL_LIB_strcspn(const AX_S8 *s, const AX_S8 *reject)
{
    return 0;
}


//memory api
AX_VOID *AX_OSAL_LIB_memset(AX_VOID *str, AX_S32 c, AX_S32 count)
{
    return (AX_VOID *)rt_memset(str, c, count);
}

AX_VOID *AX_OSAL_LIB_memmove(AX_VOID *dest, const AX_VOID *src, AX_S32 count)
{
    return (AX_VOID *)rt_memmove(dest, src, count);
}

//RTT not support
AX_VOID *AX_OSAL_LIB_memscan(AX_VOID *addr, AX_S32 c, AX_S32 seze)
{
    return AX_NULL;
}

AX_VOID *AX_OSAL_LIB_memcpy(AX_VOID *ct, const AX_VOID *cs, AX_S32 count)
{
    return (AX_VOID *)rt_memcpy(ct, cs, count);
}

//RTT not support
AX_VOID *AX_OSAL_LIB_memchr(const AX_VOID *s, AX_S32 c, AX_S32 n)
{
    return AX_NULL;
}

//RTT not support
AX_VOID *AX_OSAL_LIB_memchar_inv(const AX_VOID *start, AX_S32 c, AX_S32 bytes)
{
    return AX_NULL;
}

//simple string translate
//RTT not support
AX_U64 AX_OSAL_LIB_simple_strtoull(const AX_S8 *cp,  AX_S8 **endp,  AX_U32 base)
{
    return 0;
}

//RTT not support
AX_ULONG AX_OSAL_LIB_simple_strtoul(const AX_S8 *cp,  AX_S8 **endp,  AX_U32 base)
{
    return 0;
}

//RTT not support
AX_LONG AX_OSAL_LIB_simple_strtol(const AX_S8 *cp,  AX_S8 **endp,  AX_U32 base)
{
    return 0;
}

//RTT not support
AX_S64 AX_OSAL_LIB_simple_strtoll(const AX_S8 *cp,  AX_S8 **endp,  AX_U32 base)
{
    return 0;
}

AX_S32 AX_OSAL_LIB_snprintf(AX_S8 *buf, AX_S32 size, const AX_S8 *fmt, ...)
{
    AX_S32 n;
    AX_VA_LIST args;

    va_start(args, fmt);
    n = rt_vsnprintf(buf, size, fmt, args);
    va_end(args);

    return n;
}

//RTT not support
AX_S32 AX_OSAL_LIB_scnprintf(AX_S8 *buf, AX_S32 size, const AX_S8 *fmt, ...)
{
    return 0;
}

AX_S32 AX_OSAL_LIB_sprintf(AX_S8 *buf, const AX_S8 *fmt, ...)
{
    AX_S32 n;
    AX_VA_LIST arg_ptr;

    va_start(arg_ptr, fmt);
    n = rt_vsprintf(buf, fmt, arg_ptr);
    va_end(arg_ptr);

    return n;
}

//RTT not support
AX_S32 AX_OSAL_LIB_vsscanf(AX_S8 *buf, const AX_S8 *fmt, ...)
{
    return 0;
}

AX_S32 AX_OSAL_LIB_vsnprintf(AX_S8 *str, AX_S32 size, const AX_S8 *fmt, AX_VA_LIST args)
{
    return (AX_S32)rt_vsnprintf(str, size, fmt, args);
}

