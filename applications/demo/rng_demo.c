#include "nrfx_rng.h"
#include <rtthread.h>
#include <rtdevice.h>

#define NRFX_RNG_DEFAULT_CONFIG_IRQ_PRIORITY 7

void nrfx_rng_value_handle(uint8_t rng_data)
{
    nrfx_rng_stop();
    rt_kprintf("rng_data: %d\n", (int)rng_data);
}


static void rng_sample(int argc, char *argv[])
{
    const char str[] = "hello RT-Thread!\r\n";
    rt_kprintf("%s", str);
    nrfx_rng_config_t p_config = NRFX_RNG_DEFAULT_CONFIG;
    nrfx_rng_init(&p_config, nrfx_rng_value_handle);
    nrfx_rng_start();
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(rng_sample, sample);
