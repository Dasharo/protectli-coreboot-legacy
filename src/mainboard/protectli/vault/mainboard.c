/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2019 Protectli
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
#include <device/device.h>
#include <soc/iomap.h>

#define BIOS_CONTROL_REG	0xFC
#define   BIOS_CONTROL_WPD	(1 << 0)

#define IRQEN_REG		0x88
#define   UART_IRQ4_EN		0x10

static void mainboard_enable(struct device *dev)
{
	volatile void *addr = (void *)(SPI_BASE_ADDRESS + BIOS_CONTROL_REG);

	/* set Bios Write Protect Disable bit to allow saving MRC cache */
	write8(addr, read8(addr) | BIOS_CONTROL_WPD);

	addr = (void *)(ILB_BASE_ADDRESS + IRQEN_REG);
	write8(addr, read8(addr) | UART_IRQ4_EN);
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};
