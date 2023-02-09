#include "board.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <nrf_power.h>


#ifdef BSP_USING_PM


#define SLEEP_HWTIMER   "timer0"     /* 低功耗休眠定时器 */
static rt_device_t hw_dev;

__STATIC_INLINE void pm_sleep_idle(void)
{
    
    nrf_power_task_trigger(NRF_POWER, NRF_POWER_TASK_CONSTLAT);
    

}

__STATIC_INLINE void pm_sleep_light(void)
{
    
    nrf_power_task_trigger(NRF_POWER, NRF_POWER_TASK_LOWPWR);
    
}

__STATIC_INLINE void pm_sleep_deep(void)
{
    NRF_POWER->SYSTEMOFF = POWER_SYSTEMOFF_SYSTEMOFF_Enter;
    // nrf_power_system_off();
}

static void drv_set_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE :
        pm_sleep_idle();
        break;
    case PM_SLEEP_MODE_IDLE :
        pm_sleep_idle();
        break;
    case PM_SLEEP_MODE_LIGHT :
        pm_sleep_light();
        break; 
    case PM_SLEEP_MODE_DEEP :
        pm_sleep_deep();
        break;
    default:
        pm_sleep_idle();
        break;
    }

}

#include "nrfx_clock.h"
__STATIC_INLINE void run_normal_speed(void)
{
    rt_spin_lock(lock);
    nrfx_clock_hfclk_start();
    rt_spin_unlock(lock);
}

__STATIC_INLINE void run_low_speed(void)
{
    rt_spin_lock(lock);
    nrfx_clock_lfclk_start();
    rt_spin_unlock(lock);
}

__STATIC_INLINE void run_clock_stop(rt_uint8_t mode)
{
    rt_spin_lock(lock);
    if (mode == PM_RUN_MODE_NORMAL_SPEED)
        nrfx_clock_stop(NRF_CLOCK_DOMAIN_HFCLK);
    else
        nrfx_clock_stop(NRF_CLOCK_DOMAIN_LFCLK);
    rt_spin_unlock(lock);
}

static void drv_set_run(struct rt_pm *pm, rt_uint8_t mode)
{
    run_clock_stop(pm->run_mode);
    switch (mode)
    {
    case PM_RUN_MODE_NORMAL_SPEED :
        run_normal_speed();
        break;
    case PM_RUN_MODE_LOW_SPEED :
        run_low_speed();
        break;
    default:
        ;
        break;
    }
}


/* 定时器超时回调函数 */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static void drv_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    int ret;
    rt_uint32_t freq = 1000000;
    rt_hwtimer_mode_t mode = HWTIMER_MODE_PERIOD;
    rt_hwtimerval_t timeout_s;

    hw_dev = rt_device_find(SLEEP_HWTIMER);
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    RT_ASSERT(ret == RT_EOK);
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    RT_ASSERT(ret == RT_EOK);
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    RT_ASSERT(ret == RT_EOK);
    timeout_s.sec = timeout/1000;
    timeout_s.usec = (timeout%1000)*1000;
    ret = rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    RT_ASSERT(ret != 0);
    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
}

static void drv_timer_stop(struct rt_pm *pm)
{
    int ret;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_STOP, RT_NULL);
    RT_ASSERT(ret == RT_EOK);
    ret = rt_device_close(hw_dev);
    RT_ASSERT(ret == RT_EOK);
}

static rt_tick_t drv_timer_get_tick(struct rt_pm *pm)
{
    int ret;
    rt_tick_t ticks;
    rt_hwtimerval_t timeout_s;
    ret = rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    RT_ASSERT(ret != 0);
    // rt_kprintf("timeout.sec = %d s, timeout.usec = %d us\n", timeout_s.sec, timeout_s.usec);
    ticks = timeout_s.sec * RT_TICK_PER_SECOND + timeout_s.usec*RT_TICK_PER_SECOND/1000000;
    return ticks;
}

struct rt_pm_ops ops = {
    drv_set_sleep,
    drv_set_run,
    drv_timer_start,
    drv_timer_stop,
    drv_timer_get_tick
};

static void pm_init_test(void)
{
    int ret;
    rt_system_pm_init(&ops, PM_SLEEP_MODE_DEEP, RT_NULL);
    ret = rt_pm_run_enter(PM_RUN_MODE_NORMAL_SPEED);
    RT_ASSERT(ret == RT_EOK);
}
MSH_CMD_EXPORT(pm_init_test, sample);

/***********************************************************************
 * 函数测试命令
************************************************************************/

static int drv_pm_run_sleep_test(int argc, char *argv[])
{
    struct rt_pm pm;
    pm.run_mode = NRF_CLOCK_DOMAIN_LFCLK;
    drv_set_run(&pm, PM_RUN_MODE_NORMAL_SPEED);
    return RT_EOK;
}
MSH_CMD_EXPORT(drv_pm_run_sleep_test, sample);

extern int count;

static int drv_pm_lowpower(int argc, char *argv[])
{
    drv_timer_start(RT_NULL, 5000);
    count  =0;
    return RT_EOK;
}
MSH_CMD_EXPORT(drv_pm_lowpower, sample);


static int drv_pm_timer_test(int argc, char *argv[])
{
    rt_kprintf("drv_pm_function test degain...\n");
    rt_tick_t ticks;
    drv_timer_start(RT_NULL, 5000);
    ticks = drv_timer_get_tick(RT_NULL);
    rt_kprintf("first ticks: %d\n", ticks);
    rt_kprintf("first ticks: %d\n", rt_tick_get());
    rt_thread_mdelay(3000);
    ticks = drv_timer_get_tick(RT_NULL);
    rt_kprintf("second ticks: %d\n", ticks);
    rt_kprintf("second ticks: %d\n", rt_tick_get());
    rt_thread_mdelay(9000);
    drv_timer_stop(RT_NULL);
    return RT_EOK;
}

MSH_CMD_EXPORT(drv_pm_timer_test, sample);
#endif

