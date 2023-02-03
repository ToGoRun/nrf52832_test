#include <rtthread.h>
#include "utest.h"
#include <fal.h>

#define FLASH_TEST_NAME     "other_data"
#define READ_WRITE_NUMBER   16

static void test_flash(void)
{
    const uint8_t test_flash[] = "hello flash test";
    const struct fal_partition* partition_table = fal_partition_find(FLASH_TEST_NAME);
    uint8_t read_data[17];

    uassert_int_equal(fal_partition_erase(partition_table, 0x100, READ_WRITE_NUMBER), READ_WRITE_NUMBER);
    uassert_int_equal(fal_partition_write(partition_table, 0x100, test_flash, READ_WRITE_NUMBER), READ_WRITE_NUMBER);
    uassert_int_equal(fal_partition_read(partition_table, 0x100, read_data, READ_WRITE_NUMBER), READ_WRITE_NUMBER);
    read_data[16] = '\0';
    uassert_str_equal((char*)test_flash, (char*)read_data);

    uassert_true(1);
}

static rt_err_t utest_tc_init(void)
{
    fal_init();
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_flash);
}
UTEST_TC_EXPORT(testcase, "flash_utest", utest_tc_init, utest_tc_cleanup, 1);


