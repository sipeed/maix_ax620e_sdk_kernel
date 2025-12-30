MKFILE_PATH        := $(abspath $(lastword $(MAKEFILE_LIST)))
HOME_PATH          := $(dir $(MKFILE_PATH))../../../..
BUILD_PATH         := $(HOME_PATH)/build
ROOTFS_PATH        := $(HOME_PATH)/rootfs
ROOTFS_TARGET_PATH ?= $(HOME_PATH)/kernel/osdrv/out

include $(BUILD_PATH)/config.mak

KDIR = $(HOME_PATH)/kernel/linux/$(KERNEL_DIR)

MODULE_NAME := my_itest

EXTRA_CFLAGS += -I$(HOME_PATH)/kernel/osdrv/private_drv/include \
				-I$(src)/include \
				-I$(src)/../sys/include \
				-I$(src)/../include \
				-I$(HOME_PATH)/msp/component/common/include \
				-I$(HOME_PATH)/msp/sample/itest/include \
				-I$(HOME_PATH)/kernel/osal/include

SRCS := tcstub_common/tcstub_core.c \
        tcstub_task/tcstub_AX_MC20_OSAL_TASK_FUNC_001.c \
        tcstub_device/tcstub_AX_MC20_OSAL_DEV_FUNC_001.c \
        tcstub_device/tcstub_AX_MC20_OSAL_DEV_FUNC_002.c \
        tcstub_device/tcstub_AX_MC20_OSAL_DEV_FUNC_003.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_ATOMIC_FUNC_001.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_BARRIER_FUNC_001.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_MUTEX_FUNC_001.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_SEMAPHORE_FUNC_001.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_WAITEVENT_FUNC_001.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_WAITQUEUE_FUNC_001.c \
        tcstub_sync/tcstub_AX_MC20_OSAL_WORKQUEUE_FUNC_001.c \
        tcstub_debug/tcstub_AX_MC20_OSAL_DBG_ASSERT_FUNC_001.c \
        tcstub_debug/tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_001.c \
        tcstub_debug/tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_002.c \
        tcstub_debug/tcstub_AX_MC20_OSAL_DBG_LOG_FUNC_003.c \
        tcstub_timer/tcstub_AX_MC20_OSAL_TIMER_FUNC_001.c \
        tcstub_timer/tcstub_AX_MC20_OSAL_TIMER_FUNC_002.c \
        tcstub_timer/tcstub_AX_MC20_OSAL_TIMER_FUNC_003.c \
        tcstub_timer/tcstub_AX_MC20_OSAL_TIMER_FUNC_004.c \
        tcstub_timer/tcstub_AX_MC20_OSAL_TIMER_FUNC_005.c


target:
	echo $(EXTRA_CFLAGS)

$(MODULE_NAME)-objs := $(SRCS:%.c=%.o)

obj-m := $(MODULE_NAME).o

clean-objs := $(SRCS:%.c=%.o)
clean-objs += $(join $(dir $(SRCS)), $(patsubst %.c, .%.o.cmd, $(notdir $(SRCS))))

include $(BUILD_PATH)/krules.mak

