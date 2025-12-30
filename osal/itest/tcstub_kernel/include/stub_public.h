/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _OSAL_my_driver_public_H_ADD
#define _OSAL_my_driver_public_H_ADD

#include "linux/list.h"
#define _IOC_NRBITS    8
#define _IOC_TYPEBITS    8

/*
 * Let any architecture override either of the following before
 * including this file.
 */
typedef struct cmd_info {
    unsigned long cmd;
    char str_1[20];
    char str_2[20];
    char str_3[20];
} cmd_info_t __attribute__((aligned(8)));

typedef int (* tcstub_func)(unsigned int cmd, unsigned long arg);

/*
typedef struct tcstub_list {
    unsigned long cmd;
    unsigned long arg;
    char tcname[20];
    tcstub_func func;
    struct list_head list;
}tcstub_list_t __attribute__((aligned(8)));
*/

void AX_ITEST_tcstub_add(unsigned int cmd, unsigned long arg, tcstub_func func);
unsigned int AX_ITEST_tcstub_list_size(unsigned int cmd, unsigned long arg);

#if 0
typedef struct tcstub_list {
    unsigned long cmd;
    tcstub_func func;
} tcstub_list_t;


extern int itest_osal_task_func_001_001(unsigned int cmd, unsigned long arg);

tcstub_list_t g_tcstub_list[] = {
    {0, itest_osal_task_func_001_001},
};
#endif

#if 0
#ifndef _IOC_SIZEBITS
    #define _IOC_SIZEBITS    14
#endif

#ifndef _IOC_DIRBITS
    #define _IOC_DIRBITS    2
#endif

#define _IOC_NRMASK    ((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK    ((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK    ((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIRMASK    ((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT    0
#define _IOC_TYPESHIFT    (_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT    (_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT    (_IOC_SIZESHIFT+_IOC_SIZEBITS)

/*
 * Direction bits, which any architecture can choose to override
 * before including this file.
 */

#ifndef _IOC_NONE
    #define _IOC_NONE    0U
#endif

#ifndef _IOC_WRITE
    #define _IOC_WRITE    1U
#endif

#ifndef _IOC_READ
    #define _IOC_READ    2U
#endif

#define _IOC(dir,type,nr,size) \
    (((dir)  << _IOC_DIRSHIFT) | \
     ((type) << _IOC_TYPESHIFT) | \
     ((nr)   << _IOC_NRSHIFT) | \
     ((size) << _IOC_SIZESHIFT))

//#define _IOC_TYPECHECK(t) (sizeof(t))

//#define _IOC_TYPECHECK(t) (sizeof(t))


/* used to create numbers */
#define _IO(type,nr)        _IOC(_IOC_NONE,(type),(nr),0)
#define _IOR(type,nr,size)    _IOC(_IOC_READ,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOW(type,nr,size)    _IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOWR(type,nr,size)    _IOC(_IOC_READ|_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#define _IOR_BAD(type,nr,size)    _IOC(_IOC_READ,(type),(nr),sizeof(size))
#define _IOW_BAD(type,nr,size)    _IOC(_IOC_WRITE,(type),(nr),sizeof(size))
#define _IOWR_BAD(type,nr,size)    _IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))

/* used to decode ioctl numbers.. */
#define _IOC_DIR(nr)        (((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#define _IOC_TYPE(nr)        (((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NR(nr)        (((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_SIZE(nr)        (((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

#define IOC_IN        (_IOC_WRITE << _IOC_DIRSHIFT)
#define IOC_OUT        (_IOC_READ << _IOC_DIRSHIFT)
#define IOC_INOUT    ((_IOC_WRITE|_IOC_READ) << _IOC_DIRSHIFT)
#define IOCSIZE_MASK    (_IOC_SIZEMASK << _IOC_SIZESHIFT)
#define IOCSIZE_SHIFT    (_IOC_SIZESHIFT)


/*----------------we can define CMD by ourselves here-----------------*/
#define IO_AX_SMAPLE_LIST_001        _IOWR('L', 10,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_002        _IOWR('L', 11,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_003        _IOWR('L', 12,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_004        _IOWR('L', 13,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_005        _IOWR('L', 14,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_006        _IOWR('L', 15,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_007        _IOWR('L', 16,  struct cmd_info)
#define IO_AX_SMAPLE_LIST_008        _IOWR('L', 17,  struct cmd_info)
#endif

#endif /*_OSAL_my_driver_public_H_ADD*/
