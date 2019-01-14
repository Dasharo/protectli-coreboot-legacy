/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2005 Yinghai Lu <yinghailu@gmail.com>
 * Copyright (C) 2009 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015-2018 Intel Corporation.
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

#ifndef _SOC_SMBUS_H_
#define _SOC_SMBUS_H_

/* PCI Configuration Space (D31:F3): SMBus */
#define SMB_RCV_SLVA		0x09

/* SMBus I/O bits. */
#define SMBUS_SLAVE_ADDR	0x24

#endif