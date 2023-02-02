#include <rtthread.h>
#include <rtdevice.h>
#include "drv_spi.h"
#include "spi_flash_sfud.h"
#include "nrf_spim.h"

struct rt_spi_device *spi_dev_w25q;     /* SPI 设备句柄 */

static uint8_t    spi_tx_buf[256];   /**< TX buffer. */
static uint8_t    spi_rx_buf[256];   /**< RX buffer. */

/******************************************************************************
** SPI_FLASH
********************************************************************************/
typedef enum
{
    RET_SUCCESS = 0,
    RET_FlashRead_ERROR,
    RET_WriteCmd_ERROR,
    RET_WaitBusy_ERROR
}SpiRetValueType;
/*****************************************************************************
**
*****************************************************************************/

#define    SPIFLASH_CMD_LENGTH        0x03
#define    SPIFLASH_WRITE_BUSYBIT     0X01
#define    SPIFlash_ReadData_CMD      0x03
#define    SPIFlash_WriteEnable_CMD   0x06
#define    SPIFlash_WriteDisable_CMD  0x04
#define    SPIFlash_PageProgram_CMD   0x02
#define    SPIFlash_WriteSR_CMD       0x01
#define    SPIFlash_ReadSR_CMD        0x05
#define    SPIFlash_SecErase_CMD      0x20
#define    SPIFlash_BlockErase_CMD    0xD8
#define    SPIFlash_PAGEBYTE_LENGTH   256
#define    SPIFlash_SECBYTE_LENGTH   (1024*4)
#define    FLASH_BLOCK_NUMBLE         7
#define    FLASH_PAGE_NUMBLE          8


/*****************************************************************************
** 描  述：读出一个字节
** 入  参：无
** 返回值：读出的数据
******************************************************************************/
static uint8_t SpiFlash_ReadOneByte(void) 
{
    uint8_t len = 1;
	
    spi_tx_buf[0] = 0xFF;
	rt_spi_transfer(spi_dev_w25q, spi_tx_buf,  spi_rx_buf, len);
	
    return (spi_rx_buf[0]);
}
/*****************************************************************************
** 描  述：写入一个字节
** 入  参：Dat：待写入的数据
** 返回值：无
******************************************************************************/
static void SpiFlash_WriteOneByte(uint8_t Dat)
{
    uint8_t len = 1;
	
    spi_tx_buf[0] = Dat;
	rt_spi_send(spi_dev_w25q, spi_tx_buf,  len);
    
}

/*****************************************************************************
** 描  述：写入命令
** 入  参：*CMD：指向待写入的命令
** 返回值：RET_SUCCESS
******************************************************************************/
static uint8_t SpiFlash_Write_CMD(uint8_t *CMD)
{
    uint8_t len = 3;

    spi_tx_buf[0] = *CMD;
    spi_tx_buf[1] = *(CMD+1);
    spi_tx_buf[2] = *(CMD+2);
    rt_spi_send(spi_dev_w25q, spi_tx_buf,  len);
    
    return RET_SUCCESS;
}
/*****************************************************************************
** 描  述：写使能
** 入  参：无
** 返回值：无
******************************************************************************/
static void SpiFlash_Write_Enable(void)
{
	  SpiFlash_WriteOneByte(SPIFlash_WriteEnable_CMD);
}
/*****************************************************************************
** 描  述：擦除扇区，W25Q128FVSIG最小的擦除单位是扇区
** 入  参：Block_Num：块号
**         Sector_Number：扇区号
** 返回值：
******************************************************************************/
static void SPIFlash_Erase_Sector(uint8_t Block_Num,uint8_t Sector_Number)
{
    SpiFlash_Write_Enable();
		
    spi_tx_buf[0] = SPIFlash_SecErase_CMD;
    spi_tx_buf[1] = Block_Num;
    spi_tx_buf[2] = Sector_Number<<4;
    spi_tx_buf[3] = 0x00;
	rt_spi_send(spi_dev_w25q, spi_tx_buf, 4);

}
/*****************************************************************************
** 描  述：向指定的地址写入数据
**         *pBuffer:指向待写入的数据
**         WriteAddr:写入的起始地址
**         WriteBytesNum:读出的字节数
** 返回值：RET_SUCCESS
******************************************************************************/
static uint8_t SpiFlash_Write_Page(uint8_t *pBuffer, uint32_t WriteAddr, uint32_t WriteBytesNum)
{
    uint8_t len;
	
    SpiFlash_Write_Enable();
		
    spi_tx_buf[0] = SPIFlash_PageProgram_CMD;
    spi_tx_buf[1] = (uint8_t)((WriteAddr&0x00ff0000)>>16);
    spi_tx_buf[2] = (uint8_t)((WriteAddr&0x0000ff00)>>8);
    spi_tx_buf[3] = (uint8_t)WriteAddr;

    memcpy(&spi_tx_buf[4],pBuffer,WriteBytesNum);

    len = WriteBytesNum + 4;
    rt_spi_transfer(spi_dev_w25q, spi_tx_buf,  spi_rx_buf, len);

    return RET_SUCCESS;
}
/*****************************************************************************
** 描  述：从指定的地址读出指定长度的数据
** 入  参：pBuffer：指向存放读出数据的首地址       
**         ReadAddr：待读出数据的起始地址
**         ReadBytesNum：读出的字节数
** 返回值：
******************************************************************************/
static uint8_t SpiFlash_Read(uint8_t *pBuffer,uint32_t ReadAddr,uint32_t ReadBytesNum)
{
    uint8_t len;
		
    spi_tx_buf[0] = SPIFlash_ReadData_CMD;
    spi_tx_buf[1] = (uint8_t)((ReadAddr&0x00ff0000)>>16);
    spi_tx_buf[2] = (uint8_t)((ReadAddr&0x0000ff00)>>8);
    spi_tx_buf[3] = (uint8_t)ReadAddr;
    
    len = ReadBytesNum + 4;
    rt_spi_transfer(spi_dev_w25q, spi_tx_buf,  spi_rx_buf, len);
    memcpy(pBuffer,&spi_rx_buf[4],ReadBytesNum);
    
    return RET_SUCCESS;
}
/********************************************END FILE*******************************************/




uint8_t Tx_Buffer[10] = {"hello spi"};
uint8_t Rx_Buffer[10] = {0};

static int spi_flash_sample(int argc, char *argv[])
{
    struct rt_spi_device *spi_device;
    char spi_name[] = "spi0";
    char spi_device_name[] = "spi00";
    /* get physical spi bus */
    spi_device = (struct rt_spi_device *)rt_device_find(spi_name);
    if (spi_device == RT_NULL)
    {
        rt_kprintf("spi device %s not found!\r\n", spi_device_name);
        return -RT_ENOSYS;
    }
    rt_err_t ret;
    ret = rt_hw_spi_device_attach(spi_name, spi_device_name, BSP_SPI0_SS_PIN);
    if(ret != RT_EOK){
        return RT_ERROR;
    }

    if (RT_NULL == rt_sfud_flash_probe("W25Q16", "spi00"))
    {
        return -RT_ERROR;
    };

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible Modes 0 */
        cfg.max_hz = 4 * 1000 * 1000; /* SPI Interface with Clock Speeds Up to 20 MHz */
        rt_spi_configure(spi_device, &cfg);
    } /* config spi */

    /* 查找 spi 设备获取设备句柄 */
    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(spi_device_name);

    SPIFlash_Erase_Sector(0,0);	 //写之前必须先擦除
    rt_thread_mdelay(100);
    SpiFlash_Write_Page(Tx_Buffer,0x00,5);//写入5个字节数据
    rt_kprintf("write char data: %s\n", Tx_Buffer);
    for(int i=0;i<10;i++)
        Rx_Buffer[i] = 0;
    SpiFlash_Read(Rx_Buffer,0x00,5);      //读出5个字节数据
    rt_kprintf("read char data: %s\n", Rx_Buffer);

}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_flash_sample, sample);
