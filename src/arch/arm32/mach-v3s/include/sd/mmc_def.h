/*
 * (C) Copyright 2007-2012
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 * Description: MMC driver for general mmc operations
 * Author: Aaron <leafy.myeh@allwinnertech.com>
 * Date: 2012-2-3 14:18:18
 */

#ifndef _MMC_DEF_H_
#define _MMC_DEF_H_

#include <xboot.h>
#include <string.h>


#define MAX_MMC_NUM			4
//#define MMC_TRANS_BY_DMA

#define MMC_REG_BASE		0x01c0f000
#define MMC_REG_FIFO_OS		(0x200)
#define CCMU_HCLKGATE0_BASE 	0x01c20060

#define CCMU_MMC0_CLK_BASE 	0x01c20088
#define CCMU_MMC1_CLK_BASE 	0x01c2008C
#define CCMU_MMC2_CLK_BASE 	0x01c20090
#define __be32_to_cpu(x)	((0x000000ff&((x)>>24)) | (0x0000ff00&((x)>>8)) | 			\
							 (0x00ff0000&((x)<< 8)) | (0xff000000&((x)<<24)))

#define mmcinfo(fmt...)	printf("[mmc]: "fmt)
#define mmcdbg(fmt...)	printf("[mmc]: "fmt)

#define readb(addr)		(*((volatile unsigned char  *)(addr)))
#define readw(addr)		(*((volatile unsigned short *)(addr)))
#define readl(addr)		(*((volatile unsigned long  *)(addr)))
#define writeb(v, addr)	(*((volatile unsigned char  *)(addr)) = (unsigned char)(v))
#define writew(v, addr)	(*((volatile unsigned short *)(addr)) = (unsigned short)(v))
#define writel(v, addr)	(*((volatile unsigned long  *)(addr)) = (unsigned long)(v))

extern void OSAL_CacheRangeFlush(void*Address, u32_t Length, u32_t Flags);

#endif /* _MMC_H_ */
