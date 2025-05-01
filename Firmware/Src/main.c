#include "main.h"
#include "Console/Console.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"


SPI_Config flash;




int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();


	flash.NSS_Pin = 4;
	flash.NSS_Port = GPIOA;
	flash.clock_pin = SPI_Configurations.Pin._SPI1_.CLK1.PA5;
	flash.miso_pin = SPI_Configurations.Pin._SPI1_.MISO1.PA6;
	flash.mosi_pin = SPI_Configurations.Pin._SPI1_.MOSI1.PA7;


	flash.Port = SPI1;
	flash.clock_phase = SPI_Configurations.Clock_Phase.High_1;
	flash.clock_polarity = SPI_Configurations.Clock_Polarity.High_1;
	flash.type = SPI_Configurations.Type.Master;
	flash.prescaler = SPI_Configurations.Prescaler.CLK_div_16;
	flash.mode = SPI_Configurations.Mode.Full_Duplex_Master;
	flash.frame_format = SPI_Configurations.Frame_Format.MSB_First;
	flash.dma = SPI_Configurations.DMA_Type.TX_DMA_Enable;
	flash.data_format = SPI_Configurations.Data_Format.Bit8;
	flash.crc = SPI_Configurations.CRC_Enable.Disable;
	flash.interrupt = SPI_Configurations.Interrupts.Disable;


	SPI_Init(&flash);
	SPI_Enable(&flash);



	uint8_t buffer[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

	for(;;)
	{

		SPI_NSS_Low(&flash);
		SPI_TRX_Buffer(&flash, buffer, buffer, 13, 13);

		SPI_NSS_High(&flash);
		Delay_milli(1000);


	}
}


