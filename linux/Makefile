HOME_PATH  := $(abspath $(shell pwd)/../..)
BUILD_PATH := $(HOME_PATH)/build

include $(BUILD_PATH)/color.mk
include $(BUILD_PATH)/config.mak

.PHONY: all prepare linux dtbs install install_dtb clean clean_dtb install_prvdrv
.NOTPARALLEL: prepare clean install install_prvdrv

all:
	@$(MAKE) p=$(PROJECT) all -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) all -f Makefile.recovery
endif

menuconfig:
	@$(MAKE) p=$(PROJECT) menuconfig -f Makefile.kernel

savedefconfig:
	@$(MAKE) p=$(PROJECT) savedefconfig -f Makefile.kernel

olddefconfig:
	@$(MAKE) p=$(PROJECT) olddefconfig -f Makefile.kernel

prepare:
	@$(MAKE) p=$(PROJECT) prepare -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) prepare -f Makefile.recovery
endif

linux:
	@$(MAKE) p=$(PROJECT) linux -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) linux -f Makefile.recovery
endif

dtbs:
	@$(MAKE) p=$(PROJECT) dtbs -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) dtbs -f Makefile.recovery
endif

install_dtb:
	@$(MAKE) p=$(PROJECT) install_dtb -f Makefile.kernel

install:
	@$(MAKE) p=$(PROJECT) install -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) install -f Makefile.recovery
endif

install_prvdrv:
	@$(MAKE) p=$(PROJECT) install_prvdrv -f Makefile.kernel

clean_dtb:
	@$(MAKE) p=$(PROJECT) clean_dtb -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) clean_dtb -f Makefile.recovery
endif

clean:
	@$(MAKE) p=$(PROJECT) clean -f Makefile.kernel
ifeq ($(SUPPORT_RECOVERY), TRUE)
	@$(MAKE) p=$(PROJECT) clean -f Makefile.recovery
endif
