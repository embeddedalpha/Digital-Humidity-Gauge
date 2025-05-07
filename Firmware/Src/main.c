#include "main.h"
#include "Console/Console.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"
#include "../Devices/BME280/BME280.h"
#include "../Devices/W25Qxx_Flash/W25Qxx_Flash.h"
#include "../Middleware/Filesystem/Filesystem.h"
#include "../Devices/GC9A01/GC9A01.h"


FileSystem_Typedef nn;

#include "BME280.h"

I2C_Config BME280_I2C;
SPI_Config Global_SPI;

BME280_Typedef Sensor1;
W25Qxx_Config Chip;
GC9A01_Config Display;

int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	Delay_ms(1);


	Global_SPI.clock_pin      = SPI_Configurations.Pin._SPI1_.CLK1.PA5;
	Global_SPI.miso_pin       = SPI_Configurations.Pin._SPI1_.MISO1.PA6;
	Global_SPI.mosi_pin       = SPI_Configurations.Pin._SPI1_.MOSI1.PA7;
	Global_SPI.Port           = SPI1;
	Global_SPI.clock_phase    = SPI_Configurations.Clock_Phase.Low_0;
	Global_SPI.clock_polarity = SPI_Configurations.Clock_Polarity.Low_0;
	Global_SPI.type           = SPI_Configurations.Type.Master;
	Global_SPI.prescaler      = SPI_Configurations.Prescaler.CLK_div_8;
	Global_SPI.mode           = SPI_Configurations.Mode.Full_Duplex_Master;
	Global_SPI.frame_format   = SPI_Configurations.Frame_Format.MSB_First;
	Global_SPI.dma            = SPI_Configurations.DMA_Type.TX_DMA_Enable | SPI_Configurations.DMA_Type.RX_DMA_Enable;
	Global_SPI.data_format    = SPI_Configurations.Data_Format.Bit8;
	Global_SPI.crc            = SPI_Configurations.CRC_Enable.Disable;
	Global_SPI.interrupt      = SPI_Configurations.Interrupts.Disable;



	Display.SPI_Port = &Global_SPI;
	Display.dc_pin = 1;
	Display.dc_port = GPIOA;
	Display.rst_pin = 0;
	Display.rst_port = GPIOA;
	Display.SPI_Port->NSS_Pin = 2;
	Display.SPI_Port->NSS_Port = GPIOA;


	GC9A01_Init(&Display);

	GC9A01_Fill(&Display, 0x0000);        // clear to black
	GC9A01_DrawPixel(&Display,120,120,0xFFFF);  // centre white pixel












	for(;;)
	{




	}
}


