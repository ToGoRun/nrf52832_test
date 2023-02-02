#include <rtthread.h>
#include <rtdevice.h>

#define DK_BOARD_LED_1  17
#define DK_BOARD_LED_2  18
#define DK_BOARD_LED_3  19
#define DK_BOARD_LED_4  20

#define DK_BOARD_KEY_1  13
#define DK_BOARD_KEY_2  14
#define DK_BOARD_KEY_3  15
#define DK_BOARD_KEY_4  16

#define DK_BOARD_BEEP   12

#define PIN_TEST_KEY1   0x80
#define PIN_TEST_KEY2   0x40
#define PIN_TEST_KEY3   0x20
#define PIN_TEST_KEY4   0x10

#define test_start      0x08
#define led_on_all      0x04
#define led_on_turn     0x02
#define test_stop       0x01

static rt_thread_t PIN_TEST;
static u_char FLAG_PIN;



static void test_start_pin(void){
    for(int i = 0; i<4; i++){
        rt_pin_write(DK_BOARD_LED_1+i, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(DK_BOARD_LED_1+i, PIN_HIGH);
    }
}
static void led_on_all_pin(void){
    rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
    rt_pin_write(DK_BOARD_LED_2, PIN_LOW);
    rt_pin_write(DK_BOARD_LED_3, PIN_LOW);
    rt_pin_write(DK_BOARD_LED_4, PIN_LOW);
}
static void led_on_turn_pin(void){
    static char type = PIN_HIGH;
    if(type == PIN_LOW)
    {
        type = PIN_HIGH;
    }
    else{
        type =PIN_LOW; 
    }
    rt_pin_write(DK_BOARD_LED_1, type);
    rt_pin_write(DK_BOARD_LED_2, type);
    rt_pin_write(DK_BOARD_LED_3, type);
    rt_pin_write(DK_BOARD_LED_4, type);
    rt_thread_mdelay(1000);
}
static void test_stop_pin(void){
    rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
    rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
    rt_pin_write(DK_BOARD_LED_3, PIN_HIGH);
    rt_pin_write(DK_BOARD_LED_4, PIN_HIGH);
}

static void pin_test_entry(void *parameter)
{
    u_char *FLAG = parameter;

    while(1)
    {
        switch((*FLAG)&0x0f){
        case test_start :
            test_start_pin();
            break;
        case led_on_all :
            led_on_all_pin();
            break;
        case led_on_turn :
            led_on_turn_pin();
            break;
        case test_stop :
            test_stop_pin();
            break;
    }
    }

}

/* 中断回调函数 */
static void test_on(void *args)
{
    u_char *FLAG;
    FLAG = args;
    
    rt_kprintf("interrupt begain\n");
    u_char FLAG_KEY;
    FLAG_KEY =((!(char)rt_pin_read(DK_BOARD_KEY_1))<<7) | ((!(char)rt_pin_read(DK_BOARD_KEY_2))<<6) | ((!(char)rt_pin_read(DK_BOARD_KEY_3))<<5) |((!(char)rt_pin_read(DK_BOARD_KEY_4))<<4);
    switch(FLAG_KEY){
        case PIN_TEST_KEY1 :
            *FLAG = test_start;
            rt_kprintf("PIN_TEST_KEY1\n");
            break;
        case PIN_TEST_KEY2 :
            *FLAG = led_on_all;
            rt_kprintf("PIN_TEST_KEY2\n");
            break;
        case PIN_TEST_KEY3 :
            *FLAG = led_on_turn;
            rt_kprintf("PIN_TEST_KEY3\n");
            break;
        case PIN_TEST_KEY4 :
            *FLAG = test_stop;
            rt_kprintf("PIN_TEST_KEY4\n");
            break;
    }

}

static void pin_sample(int argc, char *argv[])
{
    const char str[] = "hello RT-Thread!\r\n";
    FLAG_PIN = 0;
    u_char *FLAG = &FLAG_PIN;
    rt_kprintf("%s", str);
    /* 蜂鸣器引脚为输出模式 */
    rt_pin_mode(DK_BOARD_BEEP, PIN_MODE_OUTPUT);

    /* LED引脚为输出模式 */
    rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
    rt_pin_mode(DK_BOARD_LED_2, PIN_MODE_OUTPUT);
    rt_pin_mode(DK_BOARD_LED_3, PIN_MODE_OUTPUT);
    rt_pin_mode(DK_BOARD_LED_4, PIN_MODE_OUTPUT);

    /* KEY引脚为上拉输入模式 */
    rt_pin_mode(DK_BOARD_KEY_1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(DK_BOARD_KEY_2, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(DK_BOARD_KEY_3, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(DK_BOARD_KEY_4, PIN_MODE_INPUT_PULLUP);
    
    /* 绑定中断，下降沿模式，回调函数名为test_on */
    *FLAG = PIN_TEST_KEY1;
    rt_pin_attach_irq(DK_BOARD_KEY_1, PIN_IRQ_MODE_FALLING, test_on, FLAG);
     /* 使能中断 */
    rt_pin_irq_enable(DK_BOARD_KEY_1, PIN_IRQ_ENABLE);
    *FLAG = PIN_TEST_KEY2;
    rt_pin_attach_irq(DK_BOARD_KEY_2, PIN_IRQ_MODE_FALLING, test_on, FLAG);
    /* 使能中断 */
    rt_pin_irq_enable(DK_BOARD_KEY_2, PIN_IRQ_ENABLE);
    *FLAG = PIN_TEST_KEY3;
    rt_pin_attach_irq(DK_BOARD_KEY_3, PIN_IRQ_MODE_FALLING, test_on, FLAG);
    /* 使能中断 */
    rt_pin_irq_enable(DK_BOARD_KEY_3, PIN_IRQ_ENABLE);
    *FLAG = PIN_TEST_KEY4;
    rt_pin_attach_irq(DK_BOARD_KEY_4, PIN_IRQ_MODE_FALLING, test_on, FLAG);
    /* 使能中断 */
    rt_pin_irq_enable(DK_BOARD_KEY_4, PIN_IRQ_ENABLE);

    /* 创建测试线程，名称是 pin_test，入口是 pin_test_entry*/
    PIN_TEST = rt_thread_create("pin_test",
                            pin_test_entry, &FLAG_PIN,
                            RT_MAIN_THREAD_STACK_SIZE,
                            RT_MAIN_THREAD_PRIORITY, 5);

    /* 如果获得线程控制块，启动这个线程 */
    if (PIN_TEST != RT_NULL)
        rt_thread_startup(PIN_TEST);
    

}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pin_sample, sample);
