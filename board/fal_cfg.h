/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-06-26     chenyingchun  the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

#define ON_CHIP_FLASH_DEV_NAME  "mcu_onchip_flash"
#define ON_CHIP_PARTION_NAME    "code_data"
#define ON_CHIP_OTHER_NAME      "other_data"

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev mcu_onchip_flash;

/* flash device table */
#define FAL_FLASH_DEV_TABLE \
    {                       \
        &mcu_onchip_flash,  \
    }
/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                                  \
    {                                                                                                   \
        {FAL_PART_MAGIC_WORD, ON_CHIP_PARTION_NAME, ON_CHIP_FLASH_DEV_NAME,     0 * 1024,   100 * 1024,  0}, \
        {FAL_PART_MAGIC_WORD, ON_CHIP_OTHER_NAME,   ON_CHIP_FLASH_DEV_NAME,   100 * 1024,   512 * 1024,  0}, \
    }
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */
