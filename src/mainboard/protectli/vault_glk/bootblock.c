/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <intelblocks/lpc_lib.h>
#include <soc/gpio.h>
#include "variants.h"

void bootblock_mainboard_init(void)
{
	const struct pad_config *pads;
	size_t num;

	lpc_configure_pads();
	pads = variant_early_gpio_table(&num);
	gpio_configure_pads(pads, num);
}
