/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _SOC_PCI_DEVS_H_
#define _SOC_PCI_DEVS_H_

#include <device/pci_def.h>

#define _SA_DEVFN(slot)         PCI_DEVFN(SA_DEV_SLOT_ ## slot, 0)
#define _PCH_DEVFN(slot, func)  PCI_DEVFN(PCH_DEV_SLOT_ ## slot, func)

#if !defined(__SIMPLE_DEVICE__)
#include <device/device.h>
#define _SA_DEV(slot)           pcidev_path_on_root_debug(_SA_DEVFN(slot), __func__)
#define _PCH_DEV(slot, func)    pcidev_path_on_root_debug(_PCH_DEVFN(slot, func), __func__)
#else
#include <arch/io.h>
#define _SA_DEV(slot)           PCI_DEV(0, SA_DEV_SLOT_ ## slot, 0)
#define _PCH_DEV(slot, func)    PCI_DEV(0, PCH_DEV_SLOT_ ## slot, func)
#endif

#define SAD_ALL_DEV			29
#define SAD_ALL_FUNC			0
#define SAD_ALL_PAM0123_CSR		0x40
#define SAD_ALL_PAM456_CSR		0x44

#define UBOX_DECS_BUS			0
#define UBOX_DECS_DEV			8
#define UBOX_DECS_FUNC			2
#define UBOX_DECS_CPUBUSNO_CSR		0xcc

#define VTD_TOLM_CSR			0xd0
#define VTD_TSEG_BASE_CSR		0xa8
#define VTD_TSEG_LIMIT_CSR		0xac
#define VTD_EXT_CAP_LOW			0x10
#define VTD_MMCFG_BASE_CSR		0x90
#define VTD_MMCFG_LIMIT_CSR		0x98
#define VTD_TOHM_CSR			0xd4
#define VTD_MMIOL_CSR			0xdc
#define VTD_ME_BASE_CSR			0xf0
#define VTD_ME_LIMIT_CSR		0xf8
#define VTD_VERSION			0x00
#define VTD_CAP				0x08
#define VTD_CAP_LOW			0x08
#define VTD_CAP_HIGH			0x0C
#define VTD_EXT_CAP_HIGH		0x14

#define MMAP_VTD_CFG_REG_DEVID	0x2024
#define VTD_DEV			5
#define VTD_FUNC		0

#define VMD_DEV_NUM             0x05
#define VMD_FUNC_NUM            0x05

#define APIC_DEV_NUM            0x05
#define APIC_FUNC_NUM           0x04

#define CBDMA_DEV_NUM           0x04
#define IIO_CBDMA_MMIO_SIZE     0x10000 //64kB for one CBDMA function

#define PCH_IOAPIC_BUS_NUMBER   0x00
#define PCH_IOAPIC_DEV_NUM      0x1F
#define PCH_IOAPIC_FUNC_NUM     0x00

/* PCH Device info */

#define  XHCI_BUS_NUMBER        0x0
#define  PCH_DEV_SLOT_XHCI      0x14
#define  XHCI_FUNC_NUM          0x0

#define HPET_BUS_NUM            0x0
#define HPET_DEV_NUM            PCH_DEV_SLOT_LPC
#define HPET0_FUNC_NUM          0x00

#define MMAP_VTD_CFG_REG_DEVID		0x2024
#define VTD_DEV				5
#define VTD_FUNC			0

#define PCH_DEV_SLOT_LPC        0x1f
#define  PCH_DEVFN_LPC          _PCH_DEVFN(LPC, 0)
#define  PCH_DEVFN_P2SB         _PCH_DEVFN(LPC, 1)
#define  PCH_DEVFN_PMC          _PCH_DEVFN(LPC, 2)
#define  PCH_DEVFN_SPI          _PCH_DEVFN(LPC, 5)
#define  PCH_DEV_LPC            _PCH_DEV(LPC, 0)
#define  PCH_DEV_P2SB           _PCH_DEV(LPC, 1)
#define  PCH_DEV_PMC            _PCH_DEV(LPC, 2)
#define  PCH_DEV_SPI            _PCH_DEV(LPC, 5)


#define CBDMA_DEV_NUM           0x04
#define IIO_CBDMA_MMIO_SIZE     0x10000 //64kB for one CBDMA function

#define VMD_DEV_NUM             0x05
#define VMD_FUNC_NUM            0x05

#define APIC_DEV_NUM            0x05
#define APIC_FUNC_NUM           0x04

#define PCH_IOAPIC_BUS_NUMBER   0x00
#define PCH_IOAPIC_DEV_NUM      0x1F
#define PCH_IOAPIC_FUNC_NUM     0x00

// ========== IOAPIC Definitions for DMAR/ACPI ========
#define PCH_IOAPIC_ID                   0x08
#define PC00_IOAPIC_ID                  0x09
#define PC01_IOAPIC_ID                  0x0A
#define PC02_IOAPIC_ID                  0x0B
#define PC03_IOAPIC_ID                  0x0C
#define PC04_IOAPIC_ID                  0x0D
#define PC05_IOAPIC_ID                  0x0E
#define PC06_IOAPIC_ID                  0x0F
#define PC07_IOAPIC_ID                  0x10
#define PC08_IOAPIC_ID                  0x11
#define PC09_IOAPIC_ID                  0x12
#define PC10_IOAPIC_ID                  0x13
#define PC11_IOAPIC_ID                  0x14

#endif /* _SOC_PCI_DEVS_H_ */
