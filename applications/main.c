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

static rt_device_t serial;

int main(void)
{
    int count = 1;
    char uart_name[] = "uart0";
    char str[] = "RT_Thread\n";
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);
    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
    // LOG_I("LOG_Printf_info\n");
    // LOG_D("LOG_Printf_debug\n");
    while (count++)
    {
        rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
        rt_thread_mdelay(500);
        // LOG_D("LED_used\n");
        rt_device_write(serial, 0, str, (sizeof(str) - 1));
    }
    return RT_EOK;
}

