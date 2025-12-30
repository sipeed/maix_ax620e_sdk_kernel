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

AX_VOID *AX_OSAL_FS_filp_open(const AX_S8 *filename, AX_S32 flags, AX_S32 mode)
{
    return AX_NULL;
}

AX_VOID AX_OSAL_FS_filp_close(AX_VOID * filp)
{
    return ;
}

AX_S32 AX_OSAL_FS_filp_write(AX_S8 *buf, AX_S32 len, AX_VOID * filp)
{
    return 0;
}

AX_S32 AX_OSAL_FS_filp_read(AX_S8 *buf, AX_S32 len, AX_VOID * filp)
{
    return 0;
}



