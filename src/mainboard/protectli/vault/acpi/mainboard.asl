/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Google Inc.
 * Copyright (C) 2015 Intel Corp.
 * Copyright (C) 2018 3mdeb Embedded Systems Consulting
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "onboard.h"

Scope (\_SB)
{
	Device (PWRB)
	{
		Name (_HID, EisaId ("PNP0C0C"))
		Name (_UID, 1)
	}
}

Scope (\_SB.PCI0.I2C2)
{
	/* Realtek Audio Codec */
	Device (RTEK)
	{
		Name (_ADR, 0)  // _ADR: Address
		Name (_HID, AUDIO_CODEC_HID)  // _HID: Hardware ID
		Name (_CID, AUDIO_CODEC_CID)  // _CID: Compatible ID
		Name (_DDN, AUDIO_CODEC_DDN)  // _DDN: DOS Device Name
		Name (_UID, 1)  // _UID: Unique ID

		Name (_CRS, ResourceTemplate ()
		{
			I2CSerialBus(
				AUDIO_CODEC_I2C_ADDR,
				ControllerInitiated,
				400000,
				AddressingMode7Bit,
				"\\_SB.PCI0.I2C2",
			)
			GpioInt (Edge, ActiveHigh, ExclusiveAndWake,
				PullNone, , "\\_SB.GPSE")
				{ JACK_DETECT_GPIO_INDEX }
		})

		Name (_STA, 0xF)
	}
}

Scope (\_SB.PCI0.LPEA)
{
	Name (GBUF, ResourceTemplate ()
	{
		/* Jack Detect (index 0) */
		GpioInt (Edge, ActiveHigh, ExclusiveAndWake, PullNone,,
			"\\_SB.GPSE") { JACK_DETECT_GPIO_INDEX }
	})
}

Scope (\_SB.GPNC)
{
	Name (_AEI, ResourceTemplate ()  // _AEI: ACPI Event Interrupts
	{
		GpioInt (Edge, ActiveLow, ExclusiveAndWake, PullNone,,
			"\\_SB.GPNC") { BOARD_SCI_GPIO_INDEX }
	})

	Method (_E0F, 0, NotSerialized)  // _Exx: Edge-Triggered GPE
	{
	}
}
