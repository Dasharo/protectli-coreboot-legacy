/*
 * This file is part of the coreboot project.
 *
 * Copyright 2016 Google Inc.
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

#include <arch/io.h>
#include <bootblock_common.h>
#include <superio/ite/it8772f/it8772f.h>
#include <superio/ite/common/ite.h>

#define CLKIN_DEV PNP_DEV(0x2e, IT8772F_GPIO)
#define UART_DEV PNP_DEV(0x2e, IT8772F_SP1)

void bootblock_mainboard_early_init(void)
{
	ite_conf_clkin(CLKIN_DEV, ITE_UART_CLK_PREDIVIDE_24);
	ite_enable_3vsbsw(CLKIN_DEV);
	ite_kill_watchdog(CLKIN_DEV);
	ite_enable_serial(UART_DEV, CONFIG_TTYS0_BASE);
}
