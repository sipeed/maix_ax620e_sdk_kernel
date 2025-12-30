
CURDIR = ap6256_wifi
SUBDIRS = bcmdhd

################################################################################
#	prepare param
################################################################################
LOCAL_PATH        := $(shell pwd)
HOME_PATH         := $(abspath $(LOCAL_PATH)/../../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

BUILD_PATH         := $(HOME_PATH)/build
OBJ_OUT_DIR        := $(BUILD_PATH)/out/$(PROJECT)/objs
ROOTFS_TARGET_PATH := $(HOME_PATH)/kernel/osdrv/out/$(ARCH)
KERNEL_SRC         := $(OBJ_OUT_DIR)/kernel/linux/$(KERNEL_DIR)

################################################################################
#	set task
################################################################################
SUBDIRS_CLEAN   = $(addsuffix .clean, $(SUBDIRS))
SUBDIRS_INSTALL = $(addsuffix .install, $(SUBDIRS))

.PHONY: $(SUBDIRS) $(SUBDIRS_INSTALL) $(SUBDIRS_CLEAN)
.NOTPARALLEL: clean install

all: $(SUBDIRS)
	@echo -e $(GREEN)"\nBuild All $(CURDIR) Modules success!!\n"  $(DONE)

install: $(SUBDIRS_INSTALL)
	@echo -e $(GREEN)"\nInstall $(CURDIR) success!!\n"  $(DONE)

clean:	$(SUBDIRS_CLEAN)
	@echo -e $(GREEN)"\nClean $(CURDIR) success!!\n"  $(DONE)

$(SUBDIRS):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $@ ..." $(DONE)
	cd $(basename $@ ) && make bcmdhd_sdio ARCH=$(ARCH) CROSS_COMPILE=$(CROSS) LINUXDIR=$(KERNEL_SRC) -j8

$(SUBDIRS_INSTALL):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
#   cp $(basename $@ )/*.ko $(ROOTFS_TARGET_PATH)/ko/
	cp $(basename $@ )/*.ko .

$(SUBDIRS_CLEAN):
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	cd $(basename $@ ) && make clean
	rm ./*.ko -f
