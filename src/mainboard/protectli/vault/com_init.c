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

#include <bootblock_common.h>
#include <superio/ite/common/ite.h>
#include <superio/ite/it8613e/it8613e.h>

#define SERIAL1_DEV PNP_DEV(0x2e, IT8613E_SP1)
#define CLKIN_DEV PNP_DEV(0x2e, IT8613E_GPIO)

void bootblock_mainboard_early_init(void)
{
	ite_reg_write(CLKIN_DEV, 0x2c, 0x41); // disable K8 power seq
	ite_reg_write(CLKIN_DEV, 0x2d, 0x20); // select 25MHz PCICLK
	ite_enable_serial(SERIAL1_DEV, CONFIG_TTYS0_BASE);
}
