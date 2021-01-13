/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <soc/ramstage.h>

#include "gpio.h"

void mainboard_silicon_init_params(FSP_SIL_UPD *params)
{
	/*
	 * Configure pads prior to SiliconInit() in case there's any
	 * dependencies during hardware initialization.
	 */
	if (CONFIG(BOARD_PROTECTLI_FW6) {
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));

	params->TurboMode = 1;
	params->PchThermalDeviceEnable = 0;
	params->PchPort61hEnable = 1;
	params->CdClock = 3;
	}

	if (CONFIG(BOARD_PROTECTLI_FW6D)) {
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));

	params->TurboMode = 1;
	params->PchPort61hEnable = 1;
	params->CdClock	= 3;
	}
}
