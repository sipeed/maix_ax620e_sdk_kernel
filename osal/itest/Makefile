CUR_PATH		:= $(shell pwd)
HOME_PATH		:= $(CUR_PATH)/../../..
SRC_PATH		:= $(CUR_PATH)
BASE_PATH		:= $(HOME_PATH)/msp/component
OUT_PATH		:= $(HOME_PATH)/msp/out
LIB_PATH		:= $(HOME_PATH)/msp/out/lib
COMMON_PATH		:= $(BASE_PATH)/common
ROOTFS_TARGET_PATH ?= $(OUT_PATH)

include $(HOME_PATH)/build/config.mak

# output
MOD_NAME                := itest_run
OUTPUT                  := obj

# source
SRCS                    := $(wildcard $(SRC_PATH)/*.c) \
				$(wildcard $(SRC_PATH)/tc_common/*.c) \
				$(wildcard $(SRC_PATH)/tc_user/list/*.c) \
				$(wildcard $(SRC_PATH)/tc_kernel/task/*.c) \
				$(wildcard $(SRC_PATH)/tc_user/file/*.c) \
				$(wildcard $(SRC_PATH)/tc_kernel/device/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/atomic/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/barrier/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/mutex/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/semaphore/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/waitevent/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/waitqueue/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/workqueue/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/debug/*.c) \
                                $(wildcard $(SRC_PATH)/tc_kernel/timer/*.c)


OBJS                    := $(SRCS:%.c=$(OUTPUT)/%.o)
CINCLUDE                := -I$(SRC_PATH) \
				-I$(OUT_PATH)/include \
				-I$(SRC_PATH)/include \
				-I$(HOME_PATH)/kernel/osdrv/private_drv/mydriver/include \
				-I$(BASE_PATH)/../sample/itest/include \
				-I$(BASE_PATH)/../sample/itest/user/include  \
				-I$(BASE_PATH)/../sample/itest/kernel/include

# exec
TARGET                  := $(MOD_NAME)

# build flags
CFLAGS			:= -Wall -Wl,-rpath-link=$(LIB_PATH)
ifeq ($(debug),yes)
CFLAGS			+= -O0 -ggdb3
else
CFLAGS			+= -O2
endif

# dependency
CLIB			+= -L$(LIB_PATH)
CLIB			+= -lm -lpthread

# install
INSTALL_TARGET	:= $(TARGET)
INSTALL_DIR		:= $(ROOTFS_TARGET_PATH)/bin/

# link
LINK = $(CC)
LINK += -T$(SRC_PATH)/AXTest.ld
include $(HOME_PATH)/build/rules.mak
