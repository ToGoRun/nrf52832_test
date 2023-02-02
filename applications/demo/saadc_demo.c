#include <rtthread.h>
#include <rtdevice.h>
#include "drv_adc.h"


#define SAMPLE_ADC_MODE_SINGLE_ENDED    0   //single-ended mode
#define SAMPLE_ADC_MODE_DIFFERENTIAL    1   //differential mode

#define SAMPLE_ADC_CHANNEL_0   0

#define ADC_DEV_NAME        "adc"      /* ADC 设备名称 */
#define SAMPLE_ADC_AIN2     2
#define SAMPLE_ADC_AIN_NC   0   //disable input of AINx

#define REFER_VOLTAGE       330         /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 12)   /* 转换位数为12位 */

static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;
    drv_nrfx_saadc_channel_t channel_config;

    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }
    adc_dev->parent.user_data = &channel_config;

    channel_config = (drv_nrfx_saadc_channel_t){.mode = SAMPLE_ADC_MODE_SINGLE_ENDED,
                                                .pin_p = SAMPLE_ADC_AIN2,
                                                .pin_n = SAMPLE_ADC_AIN_NC,
                                                .channel_num = SAMPLE_ADC_CHANNEL_0};
    rt_adc_enable(adc_dev, channel_config.channel_num);

    /* 读取采样值 */
    value = rt_adc_read(adc_dev, SAMPLE_ADC_CHANNEL_0);
    rt_kprintf("the value is :%d \n", value);

    /* 转换为对应电压值 */
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

    /* 关闭通道 */
    ret = rt_adc_disable(adc_dev, SAMPLE_ADC_CHANNEL_0);

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);