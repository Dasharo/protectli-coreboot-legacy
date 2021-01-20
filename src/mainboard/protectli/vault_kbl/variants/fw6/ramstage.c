/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <soc/ramstage.h>
#include <baseboard/variants.h>
#include <baseboard/gpio.h>

void variant_mainboard_silicon_init_params(FSP_SIL_UPD *params)
{
	gpio_configure_pads(gpio_table, ARRAY_SIZE(gpio_table));

	params->TurboMode = 1;
	params->PchThermalDeviceEnable = 0;
	params->PchPort61hEnable = 1;
	params->CdClock = 3;
}
