/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_ax.h"
#include "rtdef.h"
#include "rtthread.h"


typedef volatile int     atomic_t;

static inline AX_S32 __atomic_read(atomic_t *v)
{
    return *(volatile int *)v;
}


static inline void __atomic_set(atomic_t *p, AX_S32 val)
{
    *(volatile int *)p = val;
}

#ifdef RT_USING_SMP
static inline AX_S32 __atomic_inc_return(atomic_t *v)
{
    int val;
    unsigned int status;

    do {
        __asm__ __volatile__("ldrex   %0, [%3]\n"
                             "add   %0, %0, #1\n"
                             "strex   %1, %0, [%3]"
                             : "=&r"(val), "=&r"(status), "+m"(*v)
                             : "r"(v)
                             : "cc");
    } while (__builtin_expect(status != 0, 0));

    return val;
}

static inline AX_S32 __atomic_dec_return(atomic_t *v)
{
    int val;
    unsigned int status;

    do {
        __asm__ __volatile__("ldrex   %0, [%3]\n"
                             "sub   %0, %0, #1\n"
                             "strex   %1, %0, [%3]"
                             : "=&r"(val), "=&r"(status), "+m"(*v)
                             : "r"(v)
                             : "cc");
    } while (__builtin_expect(status != 0, 0));

    return val;
}
#else
static inline AX_S32 __atomic_inc_return(atomic_t *v)
{
    int val;
    unsigned int status;

        __asm__ __volatile__("ldr   %0, [%3]\n"
                             "add   %0, %0, #1\n"
                             "str   %0, [%3]"
                             : "=&r"(val), "=&r"(status), "+m"(*v)
                             : "r"(v)
                             : "cc");

    return val;
}

static inline AX_S32 __atomic_dec_return(atomic_t *v)
{
    int val;
    unsigned int status;

        __asm__ __volatile__("ldr   %0, [%3]\n"
                             "sub   %0, %0, #1\n"
                             "str   %0, [%3]"
                             : "=&r"(val), "=&r"(status), "+m"(*v)
                             : "r"(v)
                             : "cc");

    return val;
}
#endif

AX_S32 AX_OSAL_SYNC_atomic_init(AX_ATOMIC_T *atomic)
{
    atomic_t *p;
    RT_ASSERT(atomic != RT_NULL);

    p = (atomic_t *)rt_malloc(sizeof(atomic_t));
    if (p == NULL) {
        rt_kprintf("%s - kmalloc error!\n", __FUNCTION__);
        return -1;
    }

    atomic->atomic = (void *)p;
    return 0;
}

AX_S32 AX_OSAL_SYNC_atomic_read(AX_ATOMIC_T *atomic)
{
    atomic_t *p;
    RT_ASSERT(atomic != RT_NULL);

    p = (atomic_t *)(atomic->atomic);
    return __atomic_read(p);
}

AX_VOID AX_OSAL_SYNC_atomic_set(AX_ATOMIC_T *atomic, AX_S32 val)
{
    atomic_t *p;
    RT_ASSERT(atomic != RT_NULL);

    p = (atomic_t *)(atomic->atomic);
    __atomic_set(p, val);

    return ;
}

AX_S32 AX_OSAL_SYNC_atomic_inc_return(AX_ATOMIC_T *atomic)
{
    atomic_t *p;
    RT_ASSERT(atomic != RT_NULL);

    p = (atomic_t *)(atomic->atomic);
    return __atomic_inc_return(p);
}

AX_S32 AX_OSAL_SYNC_atomic_dec_return(AX_ATOMIC_T *atomic)
{
    atomic_t *p;
    RT_ASSERT(atomic != RT_NULL);

    p = (atomic_t *)(atomic->atomic);
    return __atomic_dec_return(p);
}

AX_VOID AX_OSAL_SYNC_atomic_destroy(AX_ATOMIC_T *atomic)
{
    RT_ASSERT(atomic != RT_NULL);
    rt_free(atomic->atomic);
    atomic->atomic = NULL;

    return ;
}



