/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <ulog.h>
#define DK_BOARD_LED_1  17
#define DK_BOARD_LED_2  18

int main(void)
{
    int count = 1;
    rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
    LOG_I("LOG_Printf_info\n");
    LOG_D("LOG_Printf_debug\n");
    while (count++)
    {
        rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
        rt_thread_mdelay(500);
        LOG_D("LED_used\n");
    }
    return RT_EOK;
}

