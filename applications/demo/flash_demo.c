#include <rtthread.h>
#include <rtdevice.h>
#include "fal_cfg.h"
#include "fal_def.h"
#include "fal.h"
#include <rtconfig.h>
#include <board.h>






static int flash_sample(int argc, char *argv[])
{
    const uint8_t test_flash[] = "hello flash test";
    const struct fal_partition* partition_table = fal_partition_find(ON_CHIP_OTHER_NAME);
    uint8_t read_data[17];
    int num_char;

    num_char = fal_partition_erase(partition_table, 0x100, 16);
    num_char = fal_partition_write(partition_table, 0x100, test_flash, 16);
    if(num_char != 16){
        rt_kprintf("char have lose a little\n");
        return RT_ERROR;
    }
    rt_kprintf("write data: %s\n", test_flash);
    num_char = fal_partition_read(partition_table, 0x100, read_data, 16);
    read_data[16] = '\0';
    rt_kprintf("read data: %s\n", read_data);
    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(flash_sample, sample);

