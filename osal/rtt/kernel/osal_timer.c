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
#include "rtthread.h"

AX_S32 AX_OSAL_TMR_init_timers(AX_TIMER_T *timer)
{
    struct rt_timer *rt_ptimer = RT_NULL;

    if (timer == RT_NULL || timer->function== RT_NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        goto errout;
    }

    rt_ptimer = (struct rt_timer *)rt_malloc(sizeof(struct rt_timer));
    if (rt_ptimer == RT_NULL) {
        rt_kprintf("%s - rt_malloc error!\n", __FUNCTION__);
        goto errout;
    }
    rt_memset(rt_ptimer, 0, sizeof(struct rt_timer));

    //do not use RT_TIMER_FLAG_PERIODIC (periodic timer) for sync with linux kernel
    rt_ptimer = rt_timer_create("osal_timer",
                             (void *)timer->function,
                             (void *)timer->data,
                             RT_TICK_PER_SECOND,
                             RT_TIMER_FLAG_SOFT_TIMER);

    if (rt_ptimer == RT_NULL) {
        rt_kprintf("%s - rt_timer_create error!\n", __FUNCTION__);
        goto errout;
    }

    timer->timer = rt_ptimer;

    return 0;

errout:
    if (rt_ptimer) {
        rt_free(rt_ptimer);
    }
    return -1;
}

AX_U32 AX_OSAL_TMR_mod_timer(AX_TIMER_T *timer, AX_ULONG interval)
{
    AX_S32 rt_err = RT_EOK;
    struct rt_timer *rt_ptimer;
    AX_U32 rt_delay_ticks = 0;

    if (timer == NULL || timer->timer == NULL || timer->function == NULL || interval == 0) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    // set timer delay jiffies
    rt_ptimer = (struct rt_timer *)timer->timer;
    rt_delay_ticks = rt_tick_from_millisecond((rt_int32_t)interval);
    rt_err = rt_timer_control(rt_ptimer, RT_TIMER_CTRL_SET_TIME, &rt_delay_ticks);
    if (rt_err != RT_EOK) {
        rt_kprintf("%s - rt_timer_control error!\n", __FUNCTION__);
        return -1;
    }

    // start timer
    rt_err = rt_timer_start(rt_ptimer);
    if (rt_err != RT_EOK) {
        rt_kprintf("%s - rt_timer_start error!\n", __FUNCTION__);
        return -1;
    }

    return 0;
}

AX_U32 AX_OSAL_TMR_del_timer(AX_TIMER_T *timer)
{
    AX_S32 rt_err = RT_EOK;
    struct rt_timer *rt_ptimer;

    if (timer == NULL || timer->timer == NULL || timer->function == NULL) {
        rt_kprintf("%s - parameter invalid!\n", __FUNCTION__);
        return -1;
    }

    rt_ptimer = (struct rt_timer *)timer->timer;
    rt_err = rt_timer_delete(rt_ptimer);
    if (rt_err != RT_EOK) {
        rt_kprintf("%s - rt_timer_delete error!\n", __FUNCTION__);
        return -1;
    }

    return 0;
}

AX_S32 AX_OSAL_TMR_destory_timer(AX_TIMER_T *timer)
{
    return AX_OSAL_TMR_del_timer(timer);
}

AX_ULONG AX_OSAL_TM_msleep(AX_U32 msecs)
{
    return rt_thread_mdelay((rt_int32_t)msecs);
}

//the >= tick_time part of usecs, use rt_thread_mdelay for release the CPU
//the remainder time use rt_hrtimer_udelay for hold the CPU
AX_VOID AX_OSAL_TM_udelay(AX_U32 usecs)
{
	AX_U32 tick_usecs = 0;
	AX_U32 rt_msecs = 0;
	AX_U32 rt_usecs = 0;

	tick_usecs = 1000000 / RT_TICK_PER_SECOND;

	if(usecs >= tick_usecs){
		rt_msecs = usecs / tick_usecs;
		rt_usecs = usecs % tick_usecs;
		rt_thread_mdelay((rt_int32_t)rt_msecs);
		rt_hrtimer_udelay((rt_int64_t)rt_usecs);
	}
	else{
		rt_hrtimer_udelay((rt_int64_t)usecs);
	}

    return ;
}

//the >= tick_time part of msecs, use rt_thread_mdelay for release the CPU
//the remainder time use rt_hrtimer_mdelay for hold the CPU
AX_VOID AX_OSAL_TM_mdelay(AX_U32 msecs)
{
	AX_U32 tick_msecs = 0;
	AX_U32 quotient_msecs = 0;
	AX_U32 remainder_usecs = 0;

	tick_msecs = 1000 / RT_TICK_PER_SECOND;
	if(msecs >= tick_msecs){
		quotient_msecs = msecs / tick_msecs;
		remainder_usecs = msecs % tick_msecs;
		rt_thread_mdelay((rt_int32_t)quotient_msecs);
		rt_hrtimer_mdelay((rt_int32_t)remainder_usecs);
	}
	else{
		rt_hrtimer_mdelay((rt_int32_t)msecs);
	}

    return ;
}

AX_U32 AX_OSAL_TM_jiffies_to_msecs()
{
    return (AX_U32)rt_tick_get_millisecond();
}

//it should be modify when RTT provide high-precision timers
AX_U64 AX_OSAL_TM_sched_clock()
{
    return (AX_U64)(rt_tick_get_millisecond()*1000000);
}

//RTT not support
AX_VOID AX_OSAL_TM_do_gettimeofday(AX_TIMERVAL_T *tm)
{
    return ;
}

//RTT not support
AX_VOID AX_OSAL_TM_rtc_time_to_tm(AX_ULONG time, AX_RTC_TIMER_T *tm)
{
    return ;
}

//RTT not support
AX_VOID AX_OSAL_TM_rtc_tm_to_time(AX_RTC_TIMER_T *tm, AX_ULONG *time)
{
    return ;
}

AX_VOID AX_OSAL_TM_get_jiffies(AX_U64 *pjiffies)
{
    *pjiffies = rt_tick_get();
}

//RTT not support
AX_S32 AX_OSAL_TM_rtc_valid_tm(AX_RTC_TIMER_T *tm)
{
    return 0;
}

AX_U64 AX_OSAL_TM_get_microsecond(void)
{
    return (AX_U64)rt_hrtimer_get_microseconds();
}

AX_VOID AX_OSAL_TM_hrtimer_mdelay(AX_U32 msecs)
{
    rt_hrtimer_mdelay(msecs);
    return ;
}

AX_VOID AX_OSAL_TM_hrtimer_udelay(AX_U64 usecs)
{
    rt_hrtimer_udelay(usecs);
    return ;
}
