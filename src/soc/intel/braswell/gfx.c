/* SPDX-License-Identifier: GPL-2.0-only */

#include "chip.h"
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <drivers/intel/gma/opregion.h>
#include <drivers/intel/gma/i915.h>
#include <fsp/util.h>
#include <reg_script.h>
#include <soc/gfx.h>
#include <soc/pci_devs.h>
#include <soc/ramstage.h>

static int is_graphics_disabled(struct device *dev)
{
	/* Check if Graphics PCI device is disabled */
	if (!dev || !dev->enabled)
		return 1;

	return 0;
}

static uintptr_t graphics_get_bar(struct device *dev, unsigned long index)
{
	struct resource *gm_res;

	gm_res = find_resource(dev, index);
	if (!gm_res)
		return 0;

	return gm_res->base;
}

uintptr_t fsp_soc_get_igd_bar(void)
{
	uintptr_t memory_base;
	struct device *dev = pcidev_path_on_root(PCI_DEVFN(2, 0));

	if (is_graphics_disabled(dev))
		return 0;
	/*
	 * GFX PCI config space offset 0x18 know as Graphics
	 * Memory Range Address (GMADR)
	 */
	memory_base = graphics_get_bar(dev, PCI_BASE_ADDRESS_2);
	if (!memory_base)
		printk(BIOS_ERR, "GMADR is not programmed!\n");

	return memory_base;
}

static const struct reg_script gpu_pre_vbios_script[] = {
	/* Make sure GFX is bus master with MMIO access */
	REG_PCI_OR32(PCI_COMMAND, PCI_COMMAND_MASTER|PCI_COMMAND_MEMORY),
	REG_SCRIPT_END
};

static const struct reg_script gfx_post_vbios_script[] = {
	/* Set Lock bits */
	REG_PCI_RMW32(GGC,      0xffffffff, GGC_GGCLCK),
	REG_PCI_RMW32(GSM_BASE, 0xffffffff, GSM_BDSM_LOCK),
	REG_PCI_RMW32(GTT_BASE, 0xffffffff, GTT_BGSM_LOCK),
	REG_SCRIPT_END
};

static inline void gfx_run_script(struct device *dev, const struct reg_script *ops)
{
	reg_script_run_on_dev(dev, ops);
}

static void gfx_pre_vbios_init(struct device *dev)
{
	printk(BIOS_SPEW, "%s/%s (%s)\n", __FILE__, __func__, dev_name(dev));
	printk(BIOS_INFO, "GFX: Pre VBIOS Init\n");
	gfx_run_script(dev, gpu_pre_vbios_script);
}

static void gfx_post_vbios_init(struct device *dev)
{
	printk(BIOS_SPEW, "%s/%s (%s)\n", __FILE__, __func__, dev_name(dev));
	printk(BIOS_INFO, "GFX: Post VBIOS Init\n");
	gfx_run_script(dev, gfx_post_vbios_script);
}

static void gfx_init(struct device *dev)
{
	printk(BIOS_SPEW, "%s/%s (%s)\n", __FILE__, __func__, dev_name(dev));

	intel_gma_init_igd_opregion();

	if (!CONFIG(RUN_FSP_GOP)) {
		/* Pre VBIOS Init */
		gfx_pre_vbios_init(dev);

		/* Run VBIOS */
		pci_dev_init(dev);

		/* Post VBIOS Init */
		gfx_post_vbios_init(dev);
	}
}

static void gma_generate_ssdt(const struct device *dev)
{
	const struct soc_intel_braswell_config *chip = dev->chip_info;

	drivers_intel_gma_displays_ssdt_generate(&chip->gfx);
}

static struct device_operations gfx_device_ops = {
	.read_resources		= pci_dev_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.init			= gfx_init,
	.ops_pci		= &soc_pci_ops,
	.acpi_fill_ssdt		= gma_generate_ssdt,
};

static const struct pci_driver gfx_driver __pci_driver = {
	.ops	= &gfx_device_ops,
	.vendor	= PCI_VENDOR_ID_INTEL,
	.device	= GFX_DEVID,
};
