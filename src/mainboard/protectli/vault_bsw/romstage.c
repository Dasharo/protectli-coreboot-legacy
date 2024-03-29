/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <console/console.h>
#include <device/pci_ops.h>
#include <soc/lpc.h>
#include <soc/pci_devs.h>
#include <soc/romstage.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8613e/it8613e.h>
#include <spd_bin.h>

#define SERIAL1_DEV PNP_DEV(0x2e, IT8613E_SP1)

void mainboard_after_memory_init(void)
{
	/*
	 * FSP enables internal UART. Disable it and reenable Super I/O UART to
	 * prevent loss of debug information on serial.
	 */
	pci_write_config32(PCI_DEV(0, LPC_DEV, 0), UART_CONT, (u32) 0);
	ite_enable_serial(SERIAL1_DEV, CONFIG_TTYS0_BASE);
}

void mainboard_memory_init_params(struct romstage_params *params,
				  MEMORY_INIT_UPD *memory_params)
{
	struct spd_block blk = {
		.addr_map = { 0x50 },
	};

	get_spd_smbus(&blk);
	if (blk.spd_array[0][0] == 0)
		die("ERROR: SPD empty, DIMM not installed?");
	dump_spd_info(&blk);

	/*
	 * Set SPD and memory configuration:
	 * Memory type: 0=DimmInstalled,
	 *              1=SolderDownMemory,
	 *              2=DimmDisabled
	 */
	memory_params->PcdMemChannel0Config = 0;
	memory_params->PcdMemChannel1Config = 2;
	memory_params->PcdMemorySpdPtr = (uintptr_t)blk.spd_array[0];
}
