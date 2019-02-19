/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google Inc.
 * Copyright (C) 2015 Intel Corp.
 * Copyright (C) 2017 Andreas Galauner <andreas@galauner.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <cbfs.h>
#include <console/console.h>
#include <lib.h>
#include <soc/gpio.h>
#include <soc/lpc.h>
#include <soc/pci_devs.h>
#include <soc/romstage.h>
#include <string.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8613e/it8613e.h>

#define SERIAL1_DEV PNP_DEV(0x2e, IT8613E_SP1)
#define CLKIN_DEV PNP_DEV(0x2e, IT8613E_GPIO)

void mainboard_configure_serial_after_raminit(void)
{
	/*
	 * FSP Memory Init enables built-in serial legacy port.
	 * Disable it and reconfigure serial port on SuperIO.
	 */
	pci_write_config32(PCI_DEV(0, LPC_DEV, 0), UART_CONT, (u32) 0);
	ite_reg_write(CLKIN_DEV, 0x2c, 0x41); // disable K8 power seq
	ite_reg_write(CLKIN_DEV, 0x2d, 0x02); // PCICLK 25MHz
	ite_enable_serial(SERIAL1_DEV, CONFIG_TTYS0_BASE);
}

void mainboard_romstage_entry(struct romstage_params *rp)
{
	struct pei_data *ps = rp->pei_data;

	mainboard_fill_spd_data(ps);

	/* Call back into chipset code with platform values updated. */
	romstage_common(rp);
}

void mainboard_memory_init_params(struct romstage_params *params,
	MEMORY_INIT_UPD *memory_params)
{
	/* Update SPD data */
	memory_params->PcdMemorySpdPtr = (u32)params->pei_data->spd_data_ch0;
	memory_params->PcdMemChannel0Config = params->pei_data->spd_ch0_config;
	memory_params->PcdMemChannel1Config = params->pei_data->spd_ch1_config;
}
