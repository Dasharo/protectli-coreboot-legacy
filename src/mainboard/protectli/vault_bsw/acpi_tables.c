/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <arch/ioapic.h>
#include <soc/acpi.h>
#include <string.h>

void acpi_create_gnvs(global_nvs_t *gnvs)
{
	memset(gnvs, 0, sizeof(*gnvs));

	acpi_init_gnvs(gnvs);

	/* Enable USB ports in S3 */
	gnvs->s3u0 = 1;
	gnvs->s3u1 = 1;

	gnvs->dev.lpss_en[LPSS_NVS_I2C2] = 0;
	
}

unsigned long acpi_fill_madt(unsigned long current)
{
	/* Local APICs */
	current = acpi_create_madt_lapics(current);

	/* IOAPIC */
	current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current, 1, IO_APIC_ADDR, 0);

	current = acpi_madt_irq_overrides(current);

	current +=
		acpi_create_madt_lapic_nmi((acpi_madt_lapic_nmi_t *) current, 0xff, 0x05, 1);

	return current;
}

void mainboard_fill_fadt(acpi_fadt_t *fadt)
{
	fadt->preferred_pm_profile = PM_MOBILE;
	fadt->iapc_boot_arch = ACPI_FADT_LEGACY_DEVICES;
}
