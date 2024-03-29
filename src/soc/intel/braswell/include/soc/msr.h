/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _SOC_MSR_H_
#define _SOC_MSR_H_

#define MSR_EBL_CR_POWERON		0x2a
#define MSR_PIC_MSG_CONTROL		0x2e
#define MSR_BSEL_CR_OVERCLOCK_CONTROL	0xcd
#define MSR_PLATFORM_INFO		0xce
#define MSR_PKG_CST_CONFIG_CONTROL	0xe2
#define		SINGLE_PCTL			(1 << 11)
#define MSR_POWER_MISC			0x120
#define		ENABLE_ULFM_AUTOCM_MASK		(1 << 2)
#define		ENABLE_INDP_AUTOCM_MASK		(1 << 3)
#define IA32_MCG_CAP			0x179
#define  IA32_MCG_CAP_COUNT_MASK	0xff
#define  IA32_MCG_CAP_CTL_P_BIT		8
#define  IA32_MCG_CAP_CTL_P_MASK	(1 << IA32_MCG_CAP_CTL_P_BIT)
#define IA32_MCG_CTL			0x17b
#define MSR_POWER_CTL			0x1fc
#define MSR_PKG_POWER_SKU_UNIT		0x606
#define MSR_PKG_POWER_LIMIT		0x610
#define MSR_PP1_POWER_LIMIT		0x638
#define MSR_IACORE_RATIOS		0x66a
#define MSR_IACORE_TURBO_RATIOS		0x66c
#define MSR_IACORE_VIDS			0x66b
#define MSR_IACORE_TURBO_VIDS		0x66d
#define MSR_PKG_TURBO_CFG1		0x670
#define MSR_CPU_TURBO_WKLD_CFG1		0x671
#define MSR_CPU_TURBO_WKLD_CFG2		0x672
#define MSR_CPU_THERM_CFG1		0x673
#define MSR_CPU_THERM_CFG2		0x674
#define MSR_CPU_THERM_SENS_CFG		0x675

/* Read BCLK from MSR */
unsigned int cpu_bus_freq_khz(void);
void set_max_freq(void);

#endif /* _SOC_MSR_H_ */
