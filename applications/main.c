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

/* 中断回调函数 */
static void test_on(void *args)
{
    rt_kprintf("interrupt begain\n");
}

int main(void)
{
    int count = 1;
    char str[] = "RT_Thread\n";
    rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
    // LOG_I("LOG_Printf_info\n");
    // LOG_D("LOG_Printf_debug\n");
    // rt_pin_mode(13, PIN_MODE_INPUT_PULLUP);
    // rt_pin_attach_irq(13, PIN_IRQ_MODE_FALLING, test_on, RT_NULL);
    while (count++)
    {
        // if(rt_pin_read(13)==PIN_LOW){
        //     rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
        //     rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
        //     rt_thread_mdelay(500);
        // }else{
        rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
        rt_thread_mdelay(500);
        // LOG_D("LED_used\n");
        // }
    }
    return RT_EOK;
}

