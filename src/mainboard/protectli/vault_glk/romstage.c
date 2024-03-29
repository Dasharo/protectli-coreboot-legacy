/* SPDX-License-Identifier: GPL-2.0-only */
#include <string.h>
#include <soc/meminit.h>
#include <soc/romstage.h>
#include "variants.h"

#define BOARD_ID_GLK_RVP1_DDR4	0x5 /* GLK RVP1 - DDR4 */
#define BOARD_ID_GLK_RVP2_LP4SD	0x7 /* GLK RVP2 - LP4 Solder Down */
#define BOARD_ID_GLK_RVP2_LP4	0x8 /* RVP2 - LP4 Socket */

/* DDR4 specific swizzling data start */

/* Channel 0 PHY 0 to DUnit DQ mapping */
static const uint8_t swizzling_ch0_ddr4[] = {
	15, 14, 10, 11,  8,  9, 13, 12,  2,  7,  3,  6,  4,  0,  1,  5,
	29, 31, 27, 26, 24, 28, 25, 30, 19, 22, 18, 21, 23, 16, 17, 20,
};

/* Channel 1 PHY 0 to DUnit DQ mapping */
static const uint8_t swizzling_ch1_ddr4[] = {
	 1,  0,  4,  5,  7,  2,  6,  3, 24, 25, 28, 30, 26, 27, 31, 29,
	21, 20, 17, 16, 23, 22, 19, 18,  8, 12, 11, 15, 10,  9, 13, 14,
};

/* Channel 1 PHY 1 to DUnit DQ mapping */
static const uint8_t swizzling_ch2_ddr4[] = {
	14, 12,  9, 13, 10, 15, 11,  8,  1,  3,  7,  5,  2,  6,  0,  4,
	27, 24, 29, 28, 30, 26, 31, 25, 19, 20, 18, 22, 16, 21, 23, 17,
};

/* Channel 0 PHY 1 to DUnit DQ mapping */
static const uint8_t swizzling_ch3_ddr4[] = {
	12,  8, 13,  9, 15, 11, 14, 10,  0,  5,  1,  4,  7,  2,  6,  3,
	20, 16, 21, 17, 19, 18, 22, 23, 29, 24, 28, 26, 25, 30, 31, 27
};
/* DDR4 specific swizzling data end*/

static void fill_ddr4_params(FSP_M_CONFIG *cfg)
{
	cfg->Package = 0;		/* 0x1:BGA */
	cfg->MemoryDown = 0;
	cfg->DDR3LPageSize = 1;
	cfg->DDR3LASR = 0;
	cfg->ScramblerSupport = 0;
	cfg->ChannelHashMask = 0x36;
	cfg->SliceHashMask = 0x9;
	cfg->InterleavedMode = 0;
	cfg->ChannelsSlicesEnable = 0;
	cfg->MinRefRate2xEnable = 0;
	cfg->DualRankSupportEnable = 1;
	cfg->DisableFastBoot = 0;
	cfg->RmtMode = 0;
	cfg->RmtCheckRun = 0;
	cfg->RmtMarginCheckScaleHighThreshold = 0;
	cfg->MemorySizeLimit = 0;
	cfg->LowMemoryMaxValue = 0;
	cfg->HighMemoryMaxValue = 0;
	cfg->Profile = 11;
	cfg->DIMM0SPDAddress = 0xA0;
	cfg->DIMM1SPDAddress = 0xA4;
	cfg->Ch0_RankEnable = 0x3;
	cfg->Ch0_DeviceWidth = 0x1;
	cfg->Ch0_DramDensity = 0x0;
	cfg->Ch0_Option = 0x3;		/* Bank Address Hashing enabled */
	cfg->Ch0_TristateClk1 = 0;
	cfg->Ch0_Mode2N = 0;
	cfg->Ch0_OdtLevels = 0;
	cfg->Ch1_RankEnable = 0x3;
	cfg->Ch1_DeviceWidth = 0x1;
	cfg->Ch1_DramDensity = 0x2;
	cfg->Ch1_Option = 0x3;		/* Bank Address Hashing enabled */
	cfg->Ch1_TristateClk1 = 0;
	cfg->Ch1_Mode2N = 0;
	cfg->Ch1_OdtLevels = 0;
	cfg->Ch2_RankEnable = 0x0;
	cfg->Ch2_DeviceWidth = 0x1;
	cfg->Ch2_DramDensity = 0x2;
	cfg->Ch2_Option = 0x3;		/* Bank Address Hashing enabled */
	cfg->Ch2_TristateClk1 = 0;
	cfg->Ch2_Mode2N = 0;
	cfg->Ch2_OdtLevels = 0;
	cfg->Ch3_RankEnable = 0x0;
	cfg->Ch3_DeviceWidth = 0x1;
	cfg->Ch3_DramDensity = 0x2;
	cfg->Ch3_Option = 0x3;		/* Bank Address Hashing enabled */
	cfg->Ch3_TristateClk1 = 0;
	cfg->Ch3_Mode2N = 0;
	cfg->Ch3_OdtLevels = 0;

	/* phy0 ch0 */
	memcpy(cfg->Ch0_Bit_swizzling, swizzling_ch0_ddr4,
		sizeof(swizzling_ch0_ddr4));
	/* phy0 ch1 */
	memcpy(cfg->Ch1_Bit_swizzling, swizzling_ch1_ddr4,
		sizeof(swizzling_ch1_ddr4));
	/* phy1 ch1 */
	memcpy(cfg->Ch2_Bit_swizzling, swizzling_ch2_ddr4,
		sizeof(swizzling_ch2_ddr4));
	/* phy1 ch0 */
	memcpy(cfg->Ch3_Bit_swizzling, swizzling_ch3_ddr4,
		sizeof(swizzling_ch3_ddr4));
}

void mainboard_memory_init_params(FSPM_UPD *memupd)
{
	FSP_M_CONFIG *cfg = &memupd->FspmConfig;
	fill_ddr4_params(cfg);
}

void mainboard_save_dimm_info(void)
{
}
