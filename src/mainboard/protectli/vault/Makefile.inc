##
## This file is part of the coreboot project.
##
## Copyright (C) 2013 Google Inc.
## Copyright (C) 2015 Intel Corp.
## Copyright (C) 2016 Andreas Galauner <andreas@galauner.de>
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; version 2 of the License.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##

subdirs-y += spd

romstage-y += com_init.c
romstage-y += spd.c

ramstage-y += boardid.c
ramstage-y += gpio.c
ramstage-y += irqroute.c
ramstage-y += ramstage.c
ramstage-y += hda_verb.c

smm-$(CONFIG_HAVE_SMI_HANDLER) += smihandler.c
