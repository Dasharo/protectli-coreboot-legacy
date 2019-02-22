/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google Inc.
 * Copyright (C) 2015 Intel Corp.
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

#include <soc/irq.h>
#include <soc/pci_devs.h>
#include <soc/pm.h>

#define PCI_DEV_PIRQ_ROUTES \
	PCI_DEV_PIRQ_ROUTE(GFX_DEV,    A, A, A, A), \
	PCI_DEV_PIRQ_ROUTE(MMC_DEV,    D, E, F, G), \
	PCI_DEV_PIRQ_ROUTE(SD_DEV,     C, A, A, A), \
	PCI_DEV_PIRQ_ROUTE(SATA_DEV,   D, A, A, A), \
	PCI_DEV_PIRQ_ROUTE(XHCI_DEV,   E, A, A, A), \
	PCI_DEV_PIRQ_ROUTE(SIO1_DEV,   B, A, D, C), \
	PCI_DEV_PIRQ_ROUTE(TXE_DEV,    F, A, A, A), \
	PCI_DEV_PIRQ_ROUTE(HDA_DEV,    G, A, A, A), \
	PCI_DEV_PIRQ_ROUTE(PCIE_DEV,   A, B, C, D), \
	PCI_DEV_PIRQ_ROUTE(SIO2_DEV,   B, D, E, F), \
	PCI_DEV_PIRQ_ROUTE(PCU_DEV,    H, E, B, C)

#define PIRQ_PIC_ROUTES \
	PIRQ_PIC(A, 11), \
	PIRQ_PIC(B, 10), \
	PIRQ_PIC(C, 5), \
	PIRQ_PIC(D, 10), \
	PIRQ_PIC(E, 5), \
	PIRQ_PIC(F, 3), \
	PIRQ_PIC(G, 11), \
	PIRQ_PIC(H, DISABLE)
