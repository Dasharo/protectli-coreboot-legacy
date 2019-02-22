/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2006 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2017 Gergely Kiss <mail.gery@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef SUPERIO_ITE_IT8613E_H
#define SUPERIO_ITE_IT8613E_H

#define IT8613E_SP1  0x01 /* Com1 */
#define IT8613E_EC   0x04 /* Environment controller */
#define IT8613E_KBCK 0x05 /* PS/2 keyboard */
#define IT8613E_KBCM 0x06 /* PS/2 mouse */
#define IT8613E_GPIO 0x07 /* GPIO */
#define IT8613E_CIR  0x0a /* Consumer Infrared */

#endif /* SUPERIO_ITE_IT8613E_H */
