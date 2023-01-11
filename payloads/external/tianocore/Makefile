##
##
## Copyright (C) 2017 Google Inc.
##
## SPDX-License-Identifier: GPL-2.0-only

# force the shell to bash - the edksetup.sh script doesn't work with dash
export SHELL := env bash

project_name=Tianocore
project_dir=$(CURDIR)/tianocore
project_git_repo=https://github.com/Dasharo/edk2
project_git_branch=dasharo
upstream_git_repo=https://github.com/tianocore/edk2

bootloader=UefiPayloadPkg
logo_pkg=MdeModulePkg
build_flavor=-D BOOTLOADER=COREBOOT -D PCIE_BASE=$(CONFIG_MMCONF_BASE_ADDRESS) 
bootloader=UefiPayloadPkg
logo_pkg=MdeModulePkg
# STABLE revision is MrChromebox's coreboot framebuffer (coreboot_fb) branch
TAG=origin/$(project_git_branch)

ifneq ($(CONFIG_TIANOCORE_REVISION_ID),)
TAG=$(CONFIG_TIANOCORE_REVISION_ID)
endif

export EDK_TOOLS_PATH=$(project_dir)/BaseTools

ifeq ($(CONFIG_TIANOCORE_DEBUG),y)
BUILD_TYPE=DEBUG
else
BUILD_TYPE=RELEASE
endif

ifneq ($(CONFIG_TIANOCORE_USE_8254_TIMER), y)
TIMER=-DUSE_HPET_TIMER
endif

build_flavor += -D SERIAL_TERMINAL=TRUE
build_flavor += -D PS2_KEYBOARD_ENABLE=FALSE
build_flavor += -D PLATFORM_BOOT_TIMEOUT=6
build_flavor += -D SHELL_TYPE=BUILD_SHELL
build_flavor += -D USE_CBMEM_FOR_CONSOLE=FALSE
build_flavor += -D SECURE_BOOT_ENABLE=TRUE
build_flavor += -D TPM_ENABLE=FALSE
build_flavor += -D NETWORK_LAN_ROM=TRUE
build_flavor += -D DISABLE_MTRR_PROGRAMMING=TRUE
build_flavor += -D DASHARO_SYSTEM_FEATURES_ENABLE=TRUE
build_flavor += -D BOOT_MENU_KEY=0x0015
build_flavor += -D SETUP_MENU_KEY=0x0008
build_flavor += -D LOAD_OPTION_ROMS=FALSE
build_flavor += -D BOOTLOADER=COREBOOT
build_flavor += --pcd gDasharoSystemFeaturesTokenSpaceGuid.PcdShowMenu=TRUE
build_flavor += --pcd gDasharoSystemFeaturesTokenSpaceGuid.PcdDefaultNetworkBootEnable=TRUE
build_flavor += --pcd gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow=0
build_flavor += --pcd gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn=0
build_flavor += --pcd gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow=0
build_flavor += --pcd gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn=0

# NETWORK_IPXE                  = FALSE
ifeq ($(CONFIG_EDK2_IPXE),y)
build_flavor += -D NETWORK_IPXE=TRUE
build_flavor += --pcd gUefiPayloadPkgTokenSpaceGuid.PcdiPXEOptionName=L"Network Boot and Utilities"
endif

ifeq ($(CONFIG_TIANOCORE_TARGET_IA32), y)
	BUILD_STR=-q -s -a IA32 -t COREBOOT -p $(bootloader)/$(bootloader)Ia32.dsc -b $(BUILD_TYPE) $(TIMER) $(build_flavor)
else
	BUILD_STR=-q -s -a IA32 -a X64 -t COREBOOT -p $(bootloader)/$(bootloader).dsc -b $(BUILD_TYPE) $(TIMER) $(build_flavor)
endif

all: clean build

$(project_dir):
	echo "    Cloning $(project_name) from Git"
	git clone --branch $(project_git_branch) $(project_git_repo) $(project_dir); \
		cd $(project_dir); \
		git remote add upstream $(upstream_git_repo)

update: $(project_dir)
	cd  $(project_dir); \
		echo "    Fetching new commits from the $(project_name) repo"; \
		git fetch --multiple origin upstream 2>/dev/null; \
		if ! git rev-parse --verify -q $(TAG) >/dev/null; then \
			echo "    $(TAG) is not a valid git reference"; \
			exit 1; \
		fi; \
		if git status --ignore-submodules=dirty | grep -qv clean; then \
			echo "    Checking out $(project_name) revision $(TAG)"; \
			git checkout --detach $(TAG); \
		else \
			echo "    Working directory not clean; will not overwrite"; \
		fi; \
		git submodule update --init --recursive

checktools:
	echo "Checking uuid-dev..."
	echo "#include <uuid/uuid.h>" > libtest.c
	echo "int main(int argc, char **argv) { (void) argc; (void) argv; return 0; }" >> libtest.c
	$(HOSTCC) $(HOSTCCFLAGS) libtest.c -o libtest >/dev/null 2>&1 && echo " found uuid-dev." || \
		( echo " Not found."; echo "ERROR: please_install uuid-dev (libuuid-devel)"; exit 1 )
	rm -rf libtest.c libtest
	echo "Checking nasm..."
	type nasm > /dev/null 2>&1 && echo " found nasm." || \
		( echo " Not found."; echo "Error: Please install nasm."; exit 1 )

lan_rom: $(project_dir)
	echo "    Including external LAN driver"; \
	mkdir -p $(project_dir)/UefiPayloadPkg/NetworkDrivers; \
	case "$(CONFIG_EDK2_LAN_ROM_DRIVER)" in \
		"") ;; \
		/*) mkdir -p $(project_dir)/UefiPayloadPkg/NetworkDrivers; \
		    cp $(CONFIG_EDK2_LAN_ROM_DRIVER) \
				$(project_dir)/UefiPayloadPkg/NetworkDrivers/LanRom.efi;; \
		*) mkdir -p $(EDK2_PATH)/UefiPayloadPkg/NetworkDrivers; \
		   cp $(top)/$(CONFIG_EDK2_LAN_ROM_DRIVER) \
				$(project_dir)/UefiPayloadPkg/NetworkDrivers/LanRom.efi;; \
	esac \

ipxe_rom: $(project_dir)
	if [ "$(CONFIG_EDK2_IPXE)" == "y" ]; then \
		echo "    Including externally built iPXE"; \
		mkdir -p $(project_dir)/UefiPayloadPkg/NetworkDrivers; \
		cp $(top)/payloads/external/iPXE/ipxe/ipxe.rom \
			$(project_dir)/UefiPayloadPkg/NetworkDrivers/ipxe.efi; \
	fi \


build: update checktools lan_rom ipxe_rom
	unset CC; $(MAKE) -C $(project_dir)/BaseTools
	echo " build $(project_name) $(TAG)"
	if [ -n "$(CONFIG_TIANOCORE_BOOTSPLASH_FILE)" ]; then \
		echo "    Copying custom bootsplash image"; \
		case "$(CONFIG_TIANOCORE_BOOTSPLASH_FILE)" in \
			/*) cp $(CONFIG_TIANOCORE_BOOTSPLASH_FILE) \
				$(project_dir)/$(logo_pkg)/Logo/Logo.bmp;; \
			*) cp $(top)/$(CONFIG_TIANOCORE_BOOTSPLASH_FILE) \
				$(project_dir)/$(logo_pkg)/Logo/Logo.bmp;; \
		esac \
	fi; \
	cd $(project_dir); \
		export EDK_TOOLS_PATH=$(project_dir)/BaseTools; \
		export WORKSPACE=$(project_dir); \
		. ./edksetup.sh BaseTools; \
		grep -q "COREBOOT" $(project_dir)/Conf/tools_def.txt; \
		if [ $$? -ne 0 ]; then \
			cat ../tools_def.txt >> $(project_dir)/Conf/tools_def.txt; \
		fi; \
		build $(BUILD_STR); \
		mv $(project_dir)/Build/$(bootloader)*/*/FV/UEFIPAYLOAD.fd $(project_dir)/Build/UEFIPAYLOAD.fd; \
		git checkout $(logo_pkg)/Logo/Logo.bmp > /dev/null 2>&1 || true

clean:
	test -d $(project_dir) && (cd $(project_dir); rm -rf Build; rm -f Conf/tools_def.txt) || exit 0

distclean:
	rm -rf $(project_dir)

.PHONY: all update checktools config build clean distclean
