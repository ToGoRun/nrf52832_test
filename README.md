# nRF52832-青风开发板 BSP说明

## 简介

该文件夹主要存放所有主芯片为nRF52832的板级支持包。目前默认支持的开发板是青风nrf52832开发板(https://item.taobao.com/item.htm?spm=a230r.1.14.30.68f61ddfGZCen7&id=547996319690&ns=1&abbucket=16#detail)
主要内容如下：

- 开发板资源介绍


## 开发板介绍

青风nrf52832开发板，搭载nRF52832 芯片，基于ARM Cortex-M4内核，最高主频64 MHz，具有丰富的资源。


开发板常用 **板载资源** 如下：

- MCU：NRF52832，主频 64MHz，512kB FLASH ，64kB RAM
- MCU 外设: GPIO, UART, SPI, I2C(TWI), RTC,TIMER,NFC,PWM,ADC
- 板载外设
  - LED：4个 。
  - 按键：5个，4个USER and 1个RESET 。
- 调试接口：J-LINK 调试器。




## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** |   **备注**    |
| :----------- | :----------: | :-----------: |
| GPIO         |     支持     |     GPION     |
| UART         |     支持     |     UART0     |
| PWM          |     支持     |     支持      |
| SPI          |     支持     |     支持      |
| RTC          |     支持     |               |
| ADC          |     支持     |               |
| TIMER        |     支持     | TIMER0~TIMER4 |
|              |              |               |
|              |              |               |



### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 0 的功能，更多高级功能需要利用 env 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。




维护人: ToGoRun

-  