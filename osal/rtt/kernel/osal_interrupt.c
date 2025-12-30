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
#include "osal_dev_ax.h"
#include "osal_type_ax.h"
#include "rthw.h"

AX_S32 AX_OSAL_DEV_request_threaded_irq_ex(AX_U32 irq, AX_IRQ_HANDLER_T handler, AX_IRQ_HANDLER_T thread_fn,
                                        AX_ULONG flags, const AX_S8 *name, AX_VOID *dev)
{
    ax_hw_interrupt_install(irq, (rt_isr_handler_t)handler, (rt_isr_handler_t)thread_fn, dev, name);
    rt_hw_interrupt_umask(irq);
    return 0;
}

AX_S32 AX_OSAL_DEV_request_threaded_irq(AX_U32 irq, AX_IRQ_HANDLER_T handler, AX_IRQ_HANDLER_T thread_fn,
                                        const AX_S8 *name, AX_VOID *dev)
{
    ax_hw_interrupt_install(irq, (rt_isr_handler_t)handler, (rt_isr_handler_t)thread_fn, dev, name);
    rt_hw_interrupt_umask(irq);
    return 0;
}

const AX_VOID *AX_OSAL_DEV_free_irq(AX_U32 irq, AX_VOID *dev)
{
    rt_hw_interrupt_mask(irq);

    return AX_NULL;
}

AX_S32 AX_OSAL_DEV_in_interrupt()
{
    return rt_interrupt_get_nest();
}

AX_VOID AX_OSAL_DEV_enable_irq(AX_U32 irq)
{
	rt_hw_interrupt_umask(irq);
}

AX_VOID AX_OSAL_DEV_disable_irq(AX_U32 irq)
{
	rt_hw_interrupt_mask(irq);
}

AX_VOID AX_OSAL_DEV_disable_irq_nosync(AX_U32 irq)
{
	rt_hw_interrupt_mask(irq);
}

