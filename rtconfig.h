#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512

/* kservice optimization */

#define RT_DEBUG

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart0"
#define RT_VER_NUM 0x40101

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define RT_USING_FAL
#define FAL_DEBUG_CONFIG
#define FAL_DEBUG 1
#define FAL_PART_HAS_TABLE_CFG

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_HWTIMER
#define RT_USING_PIN
#define RT_USING_ADC
#define RT_USING_PWM
#define RT_USING_RTC
#define RT_USING_SPI
#define RT_USING_SFUD
#define RT_SFUD_SPI_MAX_HZ 40000000
#define RT_USING_WDT

/* Using USB */


/* C/C++ and POSIX layer */

#define RT_LIBC_DEFAULT_TIMEZONE 8

/* POSIX (Portable Operating System Interface) layer */


/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */


/* Network */


/* Utilities */

#define RT_USING_ULOG
#define ULOG_OUTPUT_LVL_D
#define ULOG_OUTPUT_LVL 7
#define ULOG_USING_ISR_LOG
#define ULOG_ASSERT_ENABLE
#define ULOG_LINE_BUF_SIZE 128

/* log format */

#define ULOG_USING_COLOR
#define ULOG_OUTPUT_TIME
#define ULOG_TIME_USING_TIMESTAMP
#define ULOG_OUTPUT_LEVEL
#define ULOG_OUTPUT_TAG
#define ULOG_BACKEND_USING_CONSOLE

/* RT-Thread Utestcases */


/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* IoT Cloud */


/* security packages */


/* language packages */

/* JSON: JavaScript Object Notation, a lightweight data-interchange format */


/* XML: Extensible Markup Language */


/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */


/* u8g2: a monochrome graphic library */


/* PainterEngine: A cross-platform graphics application framework written in C language */


/* tools packages */


/* system packages */

/* enhanced kernel services */


/* acceleration: Assembly language or algorithmic acceleration packages */


/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */


/* Micrium: Micrium software products porting for RT-Thread */


/* peripheral libraries and drivers */

/* sensors drivers */


/* touch drivers */

#define NRFX_RTC_ENABLED 1
#define NRFX_RTC1_ENABLED 1
#define PKG_USING_NRFX
#define PKG_USING_NRFX_LATEST_VERSION

/* Kendryte SDK */


/* AI packages */


/* Signal Processing and Control Algorithm Packages */


/* miscellaneous packages */

/* project laboratory */

/* samples: kernel and components samples */


/* entertainment: terminal games and other interesting software packages */


/* Arduino libraries */


/* Projects */


/* Sensors */


/* Display */


/* Timing */


/* Data Processing */


/* Data Storage */

/* Communication */


/* Device Control */


/* Other */

/* Signal IO */


/* Uncategorized */

/* Hardware Drivers Config */

#define SOC_NRF52832
#define NRFX_CLOCK_ENABLED 1
#define NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY 7
#define NRFX_CLOCK_CONFIG_LF_SRC 1
#define SOC_NORDIC

/* Onboard Peripheral Drivers */


/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define NRFX_GPIOTE_ENABLED 1
#define BSP_USING_SAADC
#define NRFX_SAADC_ENABLED 1
#define BSP_USING_PWM
#define NRFX_PWM_ENABLED 1
#define BSP_USING_PWM0
#define NRFX_PWM0_ENABLED 1
#define BSP_USING_PWM0_CH0 17
#define BSP_USING_PWM0_CH1 18
#define BSP_USING_PWM0_CH2 19
#define BSP_USING_PWM0_CH3 20
#define BSP_USING_UART
#define NRFX_USING_UART
#define NRFX_UART_ENABLED 1
#define BSP_USING_UART0
#define NRFX_UART0_ENABLED 1
#define BSP_UART0_RX_PIN 8
#define BSP_UART0_TX_PIN 6
#define BSP_USING_SPI
#define NRFX_SPI_ENABLED 1
#define BSP_USING_SPI0
#define BSP_SPI0_SCK_PIN 3
#define BSP_SPI0_MOSI_PIN 2
#define BSP_SPI0_MISO_PIN 28
#define BSP_SPI0_SS_PIN 29
#define BSP_USING_ON_CHIP_FLASH

/* On-chip flash config */

#define MCU_FLASH_START_ADDRESS 0x00000000
#define MCU_FLASH_SIZE_KB 512
#define MCU_SRAM_START_ADDRESS 0x20000000
#define MCU_SRAM_SIZE_KB 64
#define MCU_FLASH_PAGE_SIZE 0x1000
#define BSP_USING_WDT
#define NRFX_WDT_ENABLED 1
#define NRFX_WDT0_ENABLED 1
#define NRFX_WDT_CONFIG_NO_IRQ 1
#define BSP_USING_ONCHIP_RTC
#define NRFX_RTC0_ENABLED 1
#define NRFX_RTC2_ENABLED 1
#define RTC_INSTANCE_ID 2
#define BSP_USING_RNG
#define NRFX_RNG_ENABLED 1
#define BSP_USING_TIM
#define NRFX_TIMER_ENABLED 1
#define BSP_USING_TIM0
#define NRFX_TIMER0_ENABLED 1
#define BSP_USING_TIM1
#define NRFX_TIMER1_ENABLED 1
#define BSP_USING_TIM2
#define NRFX_TIMER2_ENABLED 1
#define BSP_USING_TIM3
#define NRFX_TIMER3_ENABLED 1
#define BSP_USING_TIM4
#define NRFX_TIMER4_ENABLED 1
#define BLE_STACK_USING_NULL

#endif
