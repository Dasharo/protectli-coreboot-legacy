/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corp.
 * Copyright (C) 2018 Eltan B.V.
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

#include <console/console.h>
#include <device/device.h>
#include <device/azalia_device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include <arch/io.h>
#include <delay.h>
#include <soc/intel/common/hda_verb.h>
#include <soc/ramstage.h>

static void codecs_init(u8 *base, u32 codec_mask)
{
	int i;

	/* Can support up to 4 codecs */
	for (i = 3; i >= 0; i--) {
		if (!(codec_mask & (1 << i)))
			continue;

		hda_codec_init(base, i,
			cim_verb_data_size,
			cim_verb_data);
	}

	if (pc_beep_verbs_size)
		hda_codec_write(base, pc_beep_verbs_size, pc_beep_verbs);
}

static void hda_init(struct device *dev)
{
	u8 *base;
	struct resource *res;
	u32 codec_mask;
	u32 reg32;

	/* Find base address */
	res = find_resource(dev, PCI_BASE_ADDRESS_0);
	if (!res)
		return;

	base = res2mmio(res, 0, 0);
	printk(BIOS_DEBUG, "HDA: base = %p\n", base);

	/* Set Bus Master */
	reg32 = pci_read_config32(dev, PCI_COMMAND);
	pci_write_config32(dev, PCI_COMMAND, reg32 | PCI_COMMAND_MASTER);

	codec_mask = hda_codec_detect(base);

	if (codec_mask) {
		printk(BIOS_DEBUG, "HDA: codec_mask = %02x\n", codec_mask);
		codecs_init(base, codec_mask);
	}
}

static void hda_enable(struct device *dev)
{
	u32 reg32;

	if (!dev->enabled) {
		/* Ensure memory, io, and bus master are all disabled */
		reg32 = pci_read_config32(dev, PCI_COMMAND);
		reg32 &= ~(PCI_COMMAND_MASTER |
			   PCI_COMMAND_MEMORY | PCI_COMMAND_IO);
		pci_write_config32(dev, PCI_COMMAND, reg32);

		/* Disable this device */
		sc_disable_devfn(dev);
	}
}

static const struct device_operations device_ops = {
	.read_resources		= pci_dev_read_resources,
	.set_resources		= pci_dev_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.init		= hda_init,
	.enable		= hda_enable,
	.scan_bus	= NULL,
	.ops_pci	= &soc_pci_ops,
};

static const struct pci_driver southcluster __pci_driver = {
	.ops		= &device_ops,
	.vendor		= PCI_VENDOR_ID_INTEL,
	.device		= HDA_DEVID,
};
