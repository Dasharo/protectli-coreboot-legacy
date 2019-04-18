/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2016-2018 Intel Corporation.
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

#include <cbfs.h>
#include <console/console.h>
#include <fsp/api.h>
#include <soc/romstage.h>
#include <soc/gpio.h>
#include <spd_bin.h>
#include <soc/pei_data.h>
#include <soc/pei_wrapper.h>

static void mainboard_fill_dq_map_data(void *dq_map_ptr)
{
	/* DQ byte map */
	const u8 dq_map[2][12] = {
		  { 0x0F, 0xF0, 0x00, 0xF0, 0x0F, 0xF0,
		    0x0F, 0x00, 0xFF, 0x00, 0xFF, 0x00 },
		  { 0x33, 0xCC, 0x00, 0xCC, 0x33, 0xCC,
		    0x33, 0x00, 0xFF, 0x00, 0xFF, 0x00 } };
	memcpy(dq_map_ptr, dq_map, sizeof(dq_map));
}

static void mainboard_fill_dqs_map_data(void *dqs_map_ptr)
{
	/* DQS CPU<>DRAM map */
	const u8 dqs_map[2][8] = {
		{ 0, 1, 2, 3, 4, 5, 6, 7 },
		{ 1, 0, 2, 3, 4, 5, 6, 7 } };
	memcpy(dqs_map_ptr, dqs_map, sizeof(dqs_map));
}

static void mainboard_fill_rcomp_res_data(void *rcomp_ptr)
{
	/* Rcomp resistor */
	const u16 RcompResistor[3] = { 121, 81, 100 };
	memcpy(rcomp_ptr, RcompResistor,
		 sizeof(RcompResistor));
}

static void mainboard_fill_rcomp_strength_data(void *rcomp_strength_ptr)
{
	/* Rcomp target */
	static const u16 RcompTarget[5] = {
		100, 40, 20, 20, 26 };

	memcpy(rcomp_strength_ptr, RcompTarget, sizeof(RcompTarget));
}


void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	FSP_M_CONFIG *mem_cfg;
	mem_cfg = &mupd->FspmConfig;

	mainboard_fill_dq_map_data(&mem_cfg->DqByteMapCh0);
	mainboard_fill_dqs_map_data(&mem_cfg->DqsMapCpu2DramCh0);
	mainboard_fill_rcomp_res_data(&mem_cfg->RcompResistor);
	mainboard_fill_rcomp_strength_data(&mem_cfg->RcompTarget);


	struct spd_block blk = {
		.addr_map = { 0x50, 0x52, },
	};

	mem_cfg->DqPinsInterleaved = 1;
	mem_cfg->CaVrefConfig = 2;
	get_spd_smbus(&blk);
	dump_spd_info(&blk);

	mem_cfg->MemorySpdDataLen = blk.len;
	mem_cfg->MemorySpdPtr00 = (uintptr_t)blk.spd_array[0];
	mem_cfg->MemorySpdPtr10 = (uintptr_t)blk.spd_array[1];

	mem_cfg->EnableSgx = 1;
}
