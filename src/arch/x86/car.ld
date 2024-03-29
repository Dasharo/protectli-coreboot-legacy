/* SPDX-License-Identifier: GPL-2.0-only */

/* CACHE_ROM_SIZE defined here. */
#include <cpu/x86/mtrr.h>

/* This file is included inside a SECTIONS block */
. = CONFIG_DCACHE_RAM_BASE;
.car.data . (NOLOAD) : {
	_car_region_start = . ;
#if CONFIG(PAGING_IN_CACHE_AS_RAM)
	/* Page table pre-allocation. CONFIG_DCACHE_RAM_BASE should be 4KiB
	 * aligned when using this option. */
	_pagetables = . ;
	.  += 4096 * CONFIG_NUM_CAR_PAGE_TABLE_PAGES;
	_epagetables = . ;
#endif
	/* Vboot work buffer only needs to be available when verified boot
	 * starts in bootblock. */
#if CONFIG(VBOOT_STARTS_IN_BOOTBLOCK)
	VBOOT2_WORK(., 12K)
#endif
	/* Vboot measured boot TCPA log measurements.
	 * Needs to be transferred until CBMEM is available
	 */
#if CONFIG(TPM_MEASURED_BOOT)
	TPM_TCPA_LOG(., 2K)
#endif
	/* Stack for CAR stages. Since it persists across all stages that
	 * use CAR it can be reused. The chipset/SoC is expected to provide
	 * the stack size. */
	_car_stack = .;
	. += CONFIG_DCACHE_BSP_STACK_SIZE;
	_ecar_stack = .;
	/* The pre-ram cbmem console as well as the timestamp region are fixed
	 * in size. Therefore place them above the car global section so that
         * multiple stages (romstage and verstage) have a consistent
         * link address of these shared objects. */
	PRERAM_CBMEM_CONSOLE(., CONFIG_PRERAM_CBMEM_CONSOLE_SIZE)
#if CONFIG(PAGING_IN_CACHE_AS_RAM)
	. = ALIGN(32);
	/* Page directory pointer table resides here. There are 4 8-byte entries
	 * totalling 32 bytes that need to be 32-byte aligned. The reason the
	 * pdpt are not colocated with the rest of the page tables is to reduce
	 * fragmentation of the CAR space that persists across stages. */
	_pdpt = .;
	. += 32;
	_epdpt = .;
#endif

	TIMESTAMP(., 0x200)

#if !CONFIG(NO_FMAP_CACHE)
	FMAP_CACHE(., FMAP_SIZE)
#endif

	_car_ehci_dbg_info = .;
	/* Reserve sizeof(struct ehci_dbg_info). */
        . += 80;
        _ecar_ehci_dbg_info = .;

	/* _bss and _ebss provide symbols to per-stage
	 * variables that are not shared like the timestamp and the pre-ram
	 * cbmem console. This is useful for clearing this area on a per-stage
	 * basis when more than one stage uses cache-as-ram. */

	. = ALIGN(ARCH_POINTER_ALIGN_SIZE);
	_bss = .;
	/* Allow global uninitialized variables for stages without CAR teardown. */
	*(.bss)
	*(.bss.*)
	*(.sbss)
	*(.sbss.*)
	. = ALIGN(ARCH_POINTER_ALIGN_SIZE);
	_ebss = .;
	_car_unallocated_start = .;

	_car_fsp_reserved_start = . + CONFIG_DCACHE_RAM_SIZE - (. - _car_region_start)
				  - CONFIG_FSP_T_RESERVED_SIZE;

	_car_region_end = . + CONFIG_DCACHE_RAM_SIZE - (. - _car_region_start);
}
. = _car_region_end;
.car.mrc_var . (NOLOAD) : {
	. += CONFIG_DCACHE_RAM_MRC_VAR_SIZE;
}

#if ENV_BOOTBLOCK
_car_mtrr_end = .;
_car_mtrr_start = _car_region_start;

_car_mtrr_size = _car_mtrr_end - _car_mtrr_start;
_car_mtrr_sz_log2 = 1 << LOG2CEIL(_car_mtrr_size);
_car_mtrr_mask = ~(MAX(4096, _car_mtrr_sz_log2) - 1);

#if !CONFIG(NO_XIP_EARLY_STAGES)
_xip_program_sz_log2 = 1 << LOG2CEIL(_ebootblock - _bootblock);
_xip_mtrr_mask = ~(MAX(4096, _xip_program_sz_log2) - 1);
#endif

_rom_mtrr_mask = ~(CACHE_ROM_SIZE - 1);
_rom_mtrr_base = _rom_mtrr_mask;
#endif

/* Global variables are not allowed in romstage
 * This section is checked during stage creation to ensure
 * that there are no global variables present
 */

. = 0xffffff00;
.illegal_globals . : {
	*(EXCLUDE_FILE ("*/libagesa.*.a:" "*/romstage*/buildOpts.o" "*/romstage*/agesawrapper.o" "*/vendorcode/amd/agesa/*" "*/vendorcode/amd/cimx/*") .data)
		*(EXCLUDE_FILE ("*/libagesa.*.a:" "*/romstage*/buildOpts.o" "*/romstage*/agesawrapper.o" "*/vendorcode/amd/agesa/*" "*/vendorcode/amd/cimx/*") .data.*)
}

_bogus = ASSERT((CONFIG_DCACHE_RAM_SIZE == 0) || (SIZEOF(.car.data) <= CONFIG_DCACHE_RAM_SIZE), "Cache as RAM area is too full");
#if CONFIG(PAGING_IN_CACHE_AS_RAM)
_bogus2 = ASSERT(_pagetables == ALIGN(_pagetables, 4096), "_pagetables aren't 4KiB aligned");
#endif
_bogus3 = ASSERT(CONFIG_DCACHE_BSP_STACK_SIZE > 0x0, "BSP stack size not configured");
