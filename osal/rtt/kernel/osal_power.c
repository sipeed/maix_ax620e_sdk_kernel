/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "osal_pm_ax.h"
#include "power_ax.h"
#include "board.h"

AX_S32 AX_OSAL_PM_WakeupLock(AX_S8 *lock_name)
{
    return AX_DRV_PM_WakeLock(lock_name);
}

AX_S32 AX_OSAL_PM_WakeupUnlock(AX_S8 *lock_name)
{
    return AX_DRV_PM_WakeUnlock(lock_name);
}

AX_S32 AX_OSAL_PM_SetLevel(AX_S32 pm_level)
{
    return AX_DRV_PM_SetSleepMode(pm_level);
}

AX_S32 AX_OSAL_PM_GetLevel(AX_S32 *pm_level)
{
    return AX_DRV_PM_GetSleepMode(pm_level);
}

AX_S32 AX_OSAL_PM_SetSysMode(AX_S32 sys, AX_S32 mode)
{
    return AX_DRV_PM_SetSysMode(sys, mode);
}

AX_S32 AX_OSAL_PM_SetWakePin(AX_S32 wake_pin)
{
    return AX_DRV_PM_SetWakePin(wake_pin);
}
