/*
 * This file is part of the coreboot project.
 *
 * Copyright(C) 2013 Google Inc.
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

#include "irqroute.h"
#include <soc/gpio.h>
#include <stdlib.h>
#include <boardid.h>
#include "onboard.h"
#include "gpio.h"

/* South East Community */
static const struct soc_gpio_map gpse_gpio_map[] = {
	GPIO_NC,		/* 00 MF_PLT_CLK0 */
	GPIO_NC,		/* 01 PWM1 */
	GPIO_NC,		/* 02 MF_PLT_CLK1 */
	GPIO_INPUT_PD_20K,	/* 03 MF_PLT_CLK4 */
	GPIO_NC,		/* 04 MF_PLT_CLK3 */
	GPIO_NC,		/* 05 PWM0*/
	GPIO_INPUT_PD_20K,	/* 06 MF_PLT_CLK5 */
	GPIO_INPUT_PD_20K,	/* 07 MF_PLT_CLK2 */
	GPIO_NC,		/* 15 SDMMC2_D3_CD_B */
	GPIO_NC,		/* 16 SDMMC1_CLK */
	GPIO_NC,		/* 17 SDMMC1_D0 */
	GPIO_NC,		/* 18 SDMMC2_D1 */
	GPIO_NC,		/* 19 SDMMC2_CLK */
	GPIO_NC,		/* 20 SDMMC1_D2 */
	GPIO_NC,		/* 21 SDMMC2_D2 */
	GPIO_NC,		/* 22 SDMMC2_CMD  */
	GPIO_NC,		/* 23 SDMMC1_CMD */
	GPIO_NC,		/* 24 SDMMC1_D1 */
	GPIO_NC,		/* 25 SDMMC2_D0 */
	GPIO_NC,		/* 26 SDMMC1_D3_CD_B */
	GPIO_NC,		/* 30 SDMMC3_D1 */
	GPIO_NC,		/* 31 SDMMC3_CLK */
	GPIO_NC,		/* 32 SDMMC3_D3 */
	GPIO_NC,		/* 33 SDMMC3_D2 */
	GPIO_NC,		/* 34 SDMMC3_CMD */
	GPIO_NC,		/* 35 SDMMC3_D0 */
	NATIVE_PU20K(1),	/* 45 MF_LPC_AD2 */
	NATIVE_PU20K(1),	/* 46 LPC_CLKRUNB */
	NATIVE_PU20K(1),	/* 47 MF_LPC_AD0 */
	NATIVE_PU20K(1),	/* 48 LPC_FRAMEB */
	NATIVE_PD20K(1),	/* 49 MF_LPC_CLKOUT1 */
	NATIVE_PU20K(1),	/* 50 MF_LPC_AD3 */
	Native_M1,		/* 51 MF_LPC_CLKOUT0 */
	NATIVE_PU20K(1),	/* 52 MF_LPC_AD1 */
	GPIO_NC,		/* 60 SPI1_MISO */
	GPIO_NC,		/* 61 SPI1_CS0_B */
	GPIO_NC,		/* 62 SPI1_CLK */
	GPIO_NC,		/* 63 MMC1_D6 */
	GPIO_NC,		/* 64 SPI1_MOSI */
	GPIO_NC,		/* 65 MMC1_D5 */
	GPIO_NC,		/* 66 SPI1_CS1_B */
	GPIO_NC,		/* 67 MMC1_D4_SD_WE */
	GPIO_NC,		/* 68 MMC1_D7 */
	GPIO_NC,		/* 69 MMC1_RCLK */
	NATIVE_PU20K(1),	/* 75 USB_OC1_B */
	NATIVE_PU20K(1),	/* 76 PMU_RESETBUTTON_B */
	GPI(trig_level_low, L2, P_20K_H, non_maskable, en_rx_data, NA, NA),
	/* 77 GPIO_ALERT   */
	GPIO_NC,		/* 78 SDMMC3_PWR_EN_B */
	NATIVE_PU20K(1),	/* 79 ILB_SERIRQ */
	NATIVE_PU20K(1),	/* 80 USB_OC0_B */
	GPIO_NC,		/* 81 SDMMC3_CD_B */
	NATIVE_PU20K(1),	/* 82 SPKR */
	NATIVE_PD20K(1),	/* 83 SUSPWRDNACK */
	GPIO_NC,		/* 84 SDMMC1_RCLK */
	GPIO_NC,		/* 85 SDMMC3_1P8_EN */
	GPIO_END
};

/* South West Community */
static const struct soc_gpio_map  gpsw_gpio_map[] = {
	NATIVE_PU20K(1),	/* 00 FST_SPI_D2 */
	NATIVE_PU20K(1),	/* 01 FST_SPI_D0 */
	NATIVE_PU20K(1),	/* 02 FST_SPI_CLK */
	NATIVE_PU20K(1),	/* 03 FST_SPI_D3 */
	GPO_FUNC(P_20K_H, 1),	/* 04 FST_SPI_CS1_B */
	NATIVE_PU20K(1),	/* 05 FST_SPI_D1 */
	NATIVE_PU20K(1),	/* 06 FST_SPI_CS0_B */
	GPIO_OUTPUT_PD_5K,	/* 07 FST_SPI_CS2_B */
	GPIO_NC,		/* 15 UART1_RTS_B */
	GPIO_NC,		/* 16 UART1_RXD */
	GPIO_NC,		/* 17 UART2_RXD */
	GPIO_NC,		/* 18 UART1_CTS_B */
	GPIO_NC,		/* 19 UART2_RTS_B */
	GPIO_NC,		/* 20 UART1_TXD */
	GPIO_NC,		/* 21 UART2_TXD */
	GPIO_NC,		/* 22 UART2_CTS_B */
	NATIVE_PD20K(2),	/* 30 MF_HDA_CLK */
	NATIVE_PD20K(2),	/* 31 GPIO_SW31/MF_HDA_RSTB */
	NATIVE_PD20K(2),	/* 32 GPIO_SW32 /MF_HDA_SDI0 */
	NATIVE_PD20K(2),	/* 33 MF_HDA_SDO */
	GPIO_NC,		/* 34 MF_HDA_DOCKRSTB */
	NATIVE_PD20K(2),	/* 35 MF_HDA_SYNC */
	NATIVE_PD20K(2),	/* 36 GPIO_SW36 MF_HDA_SDI1 */
	GPIO_NC,		/* 37 MF_HDA_DOCKENB */
	NATIVE_PU1K_INVTX(1),		/* 45 I2C5_SDA */
	NATIVE_PU1K(1),			/* 46 I2C4_SDA */
	NATIVE_PU1K_INVTX(1),		/* 47 I2C6_SDA */
	NATIVE_PU1K_INVTX(1),		/* 48 I2C5_SCL */
	NATIVE_FUNC(1, P_20K_H, inv_tx_enable),	/* 49 I2C_NFC_SDA */
	NATIVE_PU1K(1),			/* 50 I2C4_SCL */
	NATIVE_PU1K_INVTX(1),		/* 51 I2C6_SCL */
	NATIVE_FUNC(1, P_20K_H, inv_tx_enable),	/* 52 I2C_NFC_SCL */
	NATIVE_PU1K_INVTX(1),		/* 60 I2C1_SDA */
	NATIVE_PU1K_INVTX(1),		/* 61 I2C0_SDA */
	NATIVE_PU1K_INVTX(1),		/* 62 I2C2_SDA */
	NATIVE_PU1K_INVTX(1),		/* 63 I2C1_SCL */
	NATIVE_PU1K_INVTX(1),		/* 64 I2C3_SDA */
	NATIVE_PU1K_INVTX(1),		/* 65 I2C0_SCL */
	NATIVE_PU1K_INVTX(1),		/* 66 I2C2_SCL */
	NATIVE_PU1K_INVTX(1),		/* 67 I2C3_SCL */
	GPIO_NC,			/* 75 SATA_GP0 */
	GPIO_NC,			/* 76 SATA_GP1 */
	NATIVE_PD20K(1),		/* 77 SATA_LEDN */
	NATIVE_PD20K(1),		/* 78 SATA_GP2 */
	NATIVE_PU20K(1),		/* 79 MF_SMB_ALERTB */
	NATIVE_PD20K(1),		/* 80 SATA_GP3 */
	NATIVE_PU20K(1),		/* 81 NFC_DEV_WAKE , MF_SMB_CLK */
	NATIVE_PU20K(1),		/* 82 NFC_FW_DOWNLOAD, MF_SMB_DATA */
	NATIVE_PU20K(1),	/* 90 PCIE_CLKREQ0B */
	NATIVE_PU20K(1),	/* 91 PCIE_CLKREQ1B */
	NATIVE_PD20K(1),	/* 92 GP_SSP_2_CLK */
	NATIVE_PU20K(1),	/* 93 PCIE_CLKREQ2B */
	NATIVE_PD20K(1),	/* 94 GP_SSP_2_RXD */
	NATIVE_PU20K(1),	/* 95 PCIE_CLKREQ3B */
	NATIVE_PD20K(1),	/* 96 GP_SSP_2_FS */
	NATIVE_FUNC(1, 0, inv_tx_enable),	/* 97 GP_SSP_2f_TXD */
	GPIO_END
};


/* North Community */
static const struct soc_gpio_map  gpn_gpio_map[] = {
	NATIVE_PD20K(5),	/* 00 GPIO_DFX0 */
	NATIVE_FUNC(5, P_20K_L, 0),	/* 01 GPIO_DFX3 */
	GPIO_INPUT_PU_20K,	/* 02 GPIO_DFX7 */
	NATIVE_PD20K(5),	/* 03 GPIO_DFX1 */
	GPIO_NC,		/* 04 GPIO_DFX5 */
	GPIO_NC,		/* 05 GPIO_DFX4 */
	NATIVE_PU20K(1),	/* 06 GPIO_DFX8 */
	NATIVE_PD20K(5),	/* 07 GPIO_DFX2 */
	NATIVE_PU20K(8),	/* 08 GPIO_DFX6 */
	GPI(PAD_TRIG_EDGE_LOW,L8,P_20K_L,non_maskable,en_edge_rx_data,UNMASK_WAKE,SCI),
	/* 15 GPIO_SUS0 */
	GPO_FUNC(P_20K_L, 1),	/* 16 SEC_GPIO_SUS10 */
	NATIVE_PD20K(1),	/* 17 GPIO_SUS3 */
	GPI(PAD_TRIG_EDGE_LOW,L15,P_20K_H,non_maskable,en_edge_rx_data,NA,SMI),
	/* 18 GPIO_SUS7 */
	NATIVE_PD20K(1),	/* 19 GPIO_SUS1 */
	GPIO_INPUT_PU_20K,	/* 20 GPIO_SUS5 */
	GPI(PAD_TRIG_EDGE_HIGH,L2,P_20K_L,non_maskable,en_edge_rx_data,NA,NA),
	/* 21 SEC_GPIO_SUS11 */
	NATIVE_PU20K(1),	/* 22 GPIO_SUS4 */
	GPI(PAD_TRIG_EDGE_LEVEL,L3,P_20K_H,non_maskable,en_rx_data,NA,NA),
	/* 23 SEC_GPIO_SUS8 */
	NATIVE_PU20K(1),	/* 24 GPIO_SUS2 */
	GPI(PAD_TRIG_EDGE_LOW,L14,P_20K_H,non_maskable,en_edge_rx_data,NA,SCI),
	/* 25 GPIO_SUS6 */
	NATIVE_PU5K(1),		/* 26 CX_PREQ_B */
	GPIO_NC,		/* 27 SEC_GPIO_SUS9 */
	NATIVE_PU5K(1),		/* 30 TRST_B */
	NATIVE_PD5K(1),		/* 31 TCK */
	GPIO_SKIP,		/* 32 PROCHOT_B */
	GPIO_SKIP,		/* 33 SVID0_DATA */
	NATIVE_PU5K(1),		/* 34 TMS */
	NATIVE_PU5K(1),		/* 35 CX_PRDY_B_2 */
	Native_M1,		/* 36 TDO_2 */
	GPIO_NC,		/* 37 CX_PRDY_B */
	GPIO_SKIP,		/* 38 SVID0_ALERT_B */
	Native_M1,		/* 39 TDO */
	GPIO_SKIP,		/* 40 SVID0_CLK */
	NATIVE_PU5K(1),		/* 41 TDI */
	GPIO_NC,		/* 45 GP_CAMERASB05 */
	GPIO_NC,		/* 46 GP_CAMERASB02 */
	GPIO_PD_20K,		/* 47 GP_CAMERASB08 */
	GPIO_NC,		/* 48 GP_CAMERASB00 */
	GPIO_NC,		/* 49 GP_CAMERASBO6 */
	GPIO_NC,		/* 50 GP_CAMERASB10 */
	GPIO_NC,		/* 51 GP_CAMERASB03 */
	GPIO_PD_20K,		/* 52 GP_CAMERASB09 */
	GPIO_NC,		/* 53 GP_CAMERASB01 */
	GPIO_NC,		/* 54 GP_CAMERASB07 */
	GPIO_PD_20K,		/* 55 GP_CAMERASB11 */
	GPIO_NC,		/* 56 GP_CAMERASB04 */
	GPIO_OUT_HIGH,		/* 60 PANEL0_BKLTEN */
	Native_M1,		/* 61 HV_DDI0_HPD */
	NATIVE_PU20K(1),	/* 62 HV_DDI2_DDC_SDA */
	Native_M1,		/* 63 PANEL1_BKLTCTL */
	Native_M1,		/* 64 HV_DDI1_HPD */
	GPIO_OUT_HIGH,		/* 65 PANEL0_BKLTCTL */
	NATIVE_PU20K(1),	/* 66 HV_DDI0_DDC_SDA */
	NATIVE_PU20K(1),	/* 67 HV_DDI2_DDC_SCL */
	Native_M1,		/* 68 HV_DDI2_HPD */
	Native_M1,		/* 69 PANEL1_VDDEN */
	Native_M1,		/* 70 PANEL1_BKLTEN */
	NATIVE_PU20K(1),	/* 71 HV_DDI0_DDC_SCL */
	GPIO_OUT_HIGH,		/* 72 PANEL0_VDDEN */
	GPIO_END
};


/* East Community */
static const struct soc_gpio_map  gpe_gpio_map[] = {
	NATIVE_PU20K(1),	/* 00 PMU_SLP_S3_B */
	NATIVE_PU20K(1),	/* 01 PMU_BATLOW_B */
	NATIVE_PU20K(1),	/* 02 SUS_STAT_B */
	NATIVE_PU20K(1),	/* 03 PMU_SLP_S0IX_B */
	NATIVE_PD20K(1),	/* 04 PMU_AC_PRESENT */
	NATIVE_PU20K(1),	/* 05 PMU_PLTRST_B */
	NATIVE_PD20K(1),	/* 06 PMU_SUSCLK */
	NATIVE_PU20K(1),	/* 07 PMU_SLP_LAN_B */
	NATIVE_PU20K(1),	/* 08 PMU_PWRBTN_B */
	NATIVE_PU20K(1),	/* 09 PMU_SLP_S4_B */
	NATIVE_FUNC_TX_RX(en_rx_data, 1, P_1k_H, NA), /* 10 PMU_WAKE_B */
	GPIO_NC,		/* 11 PMU_WAKE_LAN_B */
	NATIVE_PD20K(1),	/* 15 MF_GPIO_3 */
	GPO_FUNC(P_20K_L, 1),	/* 16 MF_GPIO_7 */
	NATIVE_PU20K(1),	/* 17 MF_I2C1_SCL */
	NATIVE_PD20K(1),	/* 18 MF_GPIO_1 */
	GPO_FUNC(P_20K_L, 0),	/* 19 MF_GPIO_5 */
	NATIVE_PU20K(1),	/* 20 MF_GPIO_9 */
	NATIVE_PD20K(1),	/* 21 MF_GPIO_0 */
	GPI(trig_level_low, L0, P_20K_H, NA, en_rx_data, NA, NA), /* 22 MF_GPIO_4 */
	NATIVE_PU20K(1),	/* 23 MF_GPIO_8 */
	NATIVE_PD20K(1),	/* 24 MF_GPIO_2 */
	NATIVE_PD20K(1),	/* 25 MF_GPIO_6 */
	NATIVE_PU20K(1),	/* 26 MF_I2C1_SDA */
	GPIO_END
};


static struct soc_gpio_config gpio_config = {
	/* BSW */
	.north = gpn_gpio_map,
	.southeast = gpse_gpio_map,
	.southwest  = gpsw_gpio_map,
	.east = gpe_gpio_map
};

struct soc_gpio_config *mainboard_get_gpios(void)
{

	return &gpio_config;
}
