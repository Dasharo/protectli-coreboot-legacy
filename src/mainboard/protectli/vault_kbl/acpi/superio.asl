/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Google Inc.
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

#undef SIO_ENABLE_FDC0
#undef SIO_ENABLE_INFR
#undef SIO_ENABLE_GPIO
#undef SIO_ENABLE_PS2K
#undef SIO_ENABLE_PS2M

#define SIO_ENABLE_COM1
#define SIO_ENABLE_ENVC
#define SIO_ENVC_IO0		0xa40
#define SIO_ENVC_IO1		0xa30

#include <superio/ite/it8772f/acpi/superio.asl>
