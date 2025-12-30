LOCAL_PATH        := $(shell pwd)
HOME_PATH         := $(abspath $(LOCAL_PATH)/../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

CURDIR = third_drv
ifeq ($(PROJECT),AX620E_emmc)
SUBDIRS = ap6256_wifi rtl8188fu_wifi
endif


################################################################################
#	prepare param
################################################################################
BUILD_PATH         := $(HOME_PATH)/build
OBJ_OUT_DIR        := $(BUILD_PATH)/out/$(PROJECT)/objs
ROOTFS_TARGET_PATH := $(HOME_PATH)/kernel/osdrv/out/$(ARCH)

KBUILD_OUTDIR      := $(O)


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
	@$(MAKE) -C $(basename $@ )

$(SUBDIRS_INSTALL):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) install

$(SUBDIRS_CLEAN):
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) clean


# Export val
export ROOTFS_TARGET_PATH
