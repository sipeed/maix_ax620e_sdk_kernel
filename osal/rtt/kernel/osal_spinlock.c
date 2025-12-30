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
#include "rthw.h"

#ifdef RT_USING_SMP

AX_S32 AX_OSAL_SYNC_spin_lock_init(AX_SPINLOCK_T *osal_lock)
{
    struct rt_spinlock *rt_spinlock;
    RT_ASSERT(osal_lock != RT_NULL);

    rt_spinlock = (struct rt_spinlock *)rt_malloc(sizeof(struct rt_spinlock));
    if (rt_spinlock == NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    rt_spin_lock_init(rt_spinlock);
    osal_lock->lock = rt_spinlock;

    return RT_EOK;
}

AX_VOID AX_OSAL_SYNC_spin_lock(AX_SPINLOCK_T *osal_lock)
{
    struct rt_spinlock *rt_spinlock;

    RT_ASSERT(osal_lock != RT_NULL);
    rt_spinlock = (struct rt_spinlock *)osal_lock->lock;
    RT_ASSERT(rt_spinlock != RT_NULL);

    rt_spin_lock(rt_spinlock);
    return;
}

AX_S32 AX_OSAL_SYNC_spin_trylock(AX_SPINLOCK_T *osal_lock)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

AX_VOID AX_OSAL_SYNC_spin_unlock(AX_SPINLOCK_T *osal_lock)
{
    struct rt_spinlock *rt_spinlock;

    RT_ASSERT(osal_lock != RT_NULL);
    rt_spinlock = (struct rt_spinlock *)osal_lock->lock;
    RT_ASSERT(rt_spinlock != RT_NULL);

    rt_spin_unlock(rt_spinlock);
    return ;
}

AX_VOID AX_OSAL_SYNC_spin_lock_irqsave(AX_SPINLOCK_T *osal_lock, AX_U32 *flags)
{
    struct rt_spinlock *rt_spinlock;

    RT_ASSERT(osal_lock != RT_NULL);
    RT_ASSERT(flags != RT_NULL);
    rt_spinlock = (struct rt_spinlock *)osal_lock->lock;
    RT_ASSERT(rt_spinlock != RT_NULL);

    *flags = rt_spin_lock_irqsave(rt_spinlock);

    return ;
}

AX_VOID AX_OSAL_SYNC_spin_unlock_irqrestore(AX_SPINLOCK_T *osal_lock, AX_U32 *flags)
{
    struct rt_spinlock *rt_spinlock;

    RT_ASSERT(osal_lock != RT_NULL);
    RT_ASSERT(flags != RT_NULL);
    rt_spinlock = (struct rt_spinlock *)osal_lock->lock;
    RT_ASSERT(rt_spinlock != RT_NULL);

    rt_spin_unlock_irqrestore(rt_spinlock, *flags);

    return ;
}

AX_VOID AX_OSAL_SYNC_spinLock_destory(AX_SPINLOCK_T *osal_lock)
{
    struct rt_spinlock *rt_spinlock;

    RT_ASSERT(osal_lock != RT_NULL);
    rt_spinlock = (struct rt_spinlock *)osal_lock->lock;
    RT_ASSERT(rt_spinlock != RT_NULL);

    rt_free(rt_spinlock);
    osal_lock->lock = RT_NULL;

    return ;
}

#else /*RT_USING_SMP*/

AX_S32 AX_OSAL_SYNC_spin_lock_init(AX_SPINLOCK_T *osal_lock)
{
    return RT_EOK;
}

AX_VOID AX_OSAL_SYNC_spin_lock(AX_SPINLOCK_T *osal_lock)
{

    rt_spin_lock(RT_NULL);

    return;
}

AX_S32 AX_OSAL_SYNC_spin_trylock(AX_SPINLOCK_T *osal_lock)
{
    rt_kprintf("ERR, Function[%s] not support in RTT\n", __FUNCTION__, __LINE__);

    return 0;
}

AX_VOID AX_OSAL_SYNC_spin_unlock(AX_SPINLOCK_T *osal_lock)
{
    rt_spin_unlock(RT_NULL);

    return ;
}

AX_VOID AX_OSAL_SYNC_spin_lock_irqsave(AX_SPINLOCK_T *osal_lock, AX_U32 *flags)
{
    RT_ASSERT(flags != RT_NULL);

    *flags = rt_spin_lock_irqsave(RT_NULL);

    return ;
}

AX_VOID AX_OSAL_SYNC_spin_unlock_irqrestore(AX_SPINLOCK_T *osal_lock, AX_U32 *flags)
{
    RT_ASSERT(flags != RT_NULL);

    rt_spin_unlock_irqrestore(RT_NULL, *flags);

    return ;
}

AX_VOID AX_OSAL_SYNC_spinLock_destory(AX_SPINLOCK_T *osal_lock)
{
    return ;
}

#endif  /*RT_USING_SMP*/
