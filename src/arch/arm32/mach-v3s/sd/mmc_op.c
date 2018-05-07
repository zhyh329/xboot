/*
 * (C) Copyright 2007-2012
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 * Description: MMC driver for general mmc operations
 * Author: Aaron <leafy.myeh@allwinnertech.com>
 * Date: 2012-2-3 14:18:18
 */
#include "mmc_def.h"
#include "mmc.h"

static unsigned bootcard_offset;

extern int sunxi_mmc_init(int sdc_no, unsigned bus_width);
extern int sunxi_mmc_exit(int sdc_no);

s32_t SDMMC_PhyInit(u32_t card_no, u32_t bus_width)
{
	int ret = 0;
	ret = sunxi_mmc_init(card_no, bus_width);
	if ( ret <= 0) {
		mmcdbg("Init SD/MMC card failed !\n");
		return -1;
	}

	return ret;
}

s32_t SDMMC_PhyExit(u32_t card_no)
{
	sunxi_mmc_exit(card_no);
    return 0;
}

s32_t SDMMC_PhyRead(u32_t start_sector, u32_t nsector, void *buf, u32_t card_no)
{
	return mmc_bread(card_no, start_sector, nsector, buf);
}

s32_t SDMMC_PhyWrite(u32_t start_sector, u32_t nsector, void *buf, u32_t card_no)
{
	return mmc_bwrite(card_no, start_sector, nsector, buf);
}

s32_t SDMMC_PhyDiskSize(u32_t card_no)
{
	struct mmc *mmc = find_mmc_device(card_no);
	return mmc->lba;
}

s32_t SDMMC_PhyErase(u32_t block, u32_t nblock, u32_t card_no)
{
	return mmc_berase(card_no, block, nblock);
}

s32_t SDMMC_LogicalInit(u32_t card_no, u32_t card_offset, u32_t bus_width)
{
	bootcard_offset = card_offset;
    return SDMMC_PhyInit(card_no, bus_width);
}

s32_t SDMMC_LogicalExit(u32_t card_no)
{
	bootcard_offset = 0;
    return SDMMC_PhyExit(card_no);
}

s32_t SDMMC_LogicalRead(u32_t start_sector, u32_t nsector, void *buf, u32_t card_no)
{
	return mmc_bread(card_no, start_sector + bootcard_offset, nsector, buf);
}

s32_t SDMMC_LogicalWrite(u32_t start_sector, u32_t nsector, void *buf, u32_t card_no)
{
	return mmc_bwrite(card_no, start_sector + bootcard_offset, nsector, buf);
}

s32_t SDMMC_LogicalDiskSize(u32_t card_no)
{
	return SDMMC_PhyDiskSize(card_no) - bootcard_offset;
}

s32_t SDMMC_LogicaErase(u32_t block, u32_t nblock, u32_t card_no)
{
	return mmc_berase(card_no, block + bootcard_offset, nblock);
}

void OSAL_CacheRangeFlush(void*Address, u32_t Length, u32_t Flags)
{
	;
}

