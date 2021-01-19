/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <soc/ramstage.h>
#include <baseboard/variants.h>
#include <variant/gpio.h>

void mainboard_silicon_init_params(FSP_SIL_UPD *params)
{
	variant_mainboard_silicon_init_params(FSP_SIL_UPD *params);
}
