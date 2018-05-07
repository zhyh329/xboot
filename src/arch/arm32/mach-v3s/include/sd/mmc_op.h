/*
 * (C) Copyright 2007-2012
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 * Description: MMC driver for general mmc operations
 * Author: Aaron <leafy.myeh@allwinnertech.com>
 * Date: 2012-2-3 14:18:18
 */

#ifndef _MMC_OP_H_
#define _MMC_OP_H_

#include "mmc_def.h"
#include "mmc.h"

extern s32_t SDMMC_PhyInit(u32_t card_no, u32_t bus_width);
extern s32_t SDMMC_PhyExit(u32_t card_no);

extern s32_t SDMMC_PhyRead     (u32_t start_sector, u32_t nsector, void *buf, u32_t card_no);
extern s32_t SDMMC_PhyWrite    (u32_t start_sector, u32_t nsector, void *buf, u32_t card_no);

extern s32_t SDMMC_LogicalInit(u32_t card_no, u32_t card_offset, u32_t bus_width);
extern s32_t SDMMC_LogicalExit(u32_t card_no);

extern s32_t SDMMC_LogicalRead (u32_t start_sector, u32_t nsector, void *buf, u32_t card_no);
extern s32_t SDMMC_LogicalWrite(u32_t start_sector, u32_t nsector, void *buf, u32_t card_no);

#endif /* _MMC_H_ */
