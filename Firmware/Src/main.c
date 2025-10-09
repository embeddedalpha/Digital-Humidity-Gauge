#include "main.h"
#include "Console/Console.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"
#include "../Devices/BME280/BME280.h"
#include "../Devices/W25Qxx_Flash/W25Qxx_Flash.h"
#include "../Middleware/Filesystem/Filesystem.h"
#include "../Devices/GC9A01/GC9A01.h"
#include "../GC9A01/GC9A01_Image.h"
#include "RTC/RTC.h"

#define frame_delay 1000
FileSystem_Typedef nn;

#include "BME280.h"

I2C_Config BME280_I2C;
SPI_Config Global_SPI;

BME280_Typedef Sensor1;
W25Qxx_Config Chip;
GC9A01_Config Display;


RTC_Config rtc;

void Display_Init(void);



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	Delay_s(1);

	//	BME280_I2C.Port = I2C1;
	//	BME280_I2C.Speed_Mode = I2C_Configuration.Speed_Mode.FM_Mode;
	//	BME280_I2C.SDA_Pin = I2C_Configuration.Pin.__I2C1__.SDA.PB7;
	//	BME280_I2C.SCL_Pin = I2C_Configuration.Pin.__I2C1__.SCL.PB6;
	//	BME280_I2C.Mode = I2C_Configuration.Mode.Master;
	//	BME280_I2C.DMA_Control = I2C_Configuration.DMA_Control.RX_DMA_Enable | I2C_Configuration.DMA_Control.TX_DMA_Enable;
	//
	//
	//	Sensor1.I2C_Port = &BME280_I2C;
	//	Sensor1.device_Address = BME280_Configurations.Device_Address.Ox76;
	//	Sensor1.Settings.Temperature_Oversampling = BME280_Configurations.Temperature_Oversampling.Oversampling_X_1;
	//	Sensor1.Settings.Filter_Coefficients = BME280_Configurations.Filter_Coeff.Off;
	//	Sensor1.Settings.Humidity_Oversampling = BME280_Configurations.Humidity_Oversampling.Oversampling_X_1;
	//	Sensor1.Settings.Pressure_Oversampling = BME280_Configurations.Pressure_Oversampling.Oversampling_X_1;
	//	Sensor1.Settings.Standby_Time = BME280_Configurations.T_Standby_ms.t_standby_ms_0x5;
	//
	//	BME280_Init(&Sensor1);
	//
	//
	//	rtc.Format = RTC_Configurations.Format.H12;

	Display_Init();


	uint16_t color1 = 0x77c0;
	uint16_t color2 = 0x77bc;
	uint16_t color3 = 0xe904;

	GC9A01_DrawArcStroke(&Display, 120, 120, 120, 0, 120,10, color1);

	GC9A01_DrawArcStroke(&Display, 120, 120, 110, 120, 240, 10, color2);

	GC9A01_DrawArcStroke(&Display, 120, 120, 100, 240, 360-1,10, color3);

	GC9A01_DrawArcStroke(&Display, 120, 120, 90, 40, 160-1,10, color1);

	GC9A01_DrawArcStroke(&Display, 120, 120, 80, 80, 280,10, color2);

	GC9A01_DrawArcStroke(&Display, 120, 120, 70, 120, 340,10, color3);
//
//	GC9A01_DrawArcStroke(&Display, 120, 120, 80, 120+40, 240+40, 10, color2);

//	GC9A01_DrawArcStroke(&Display, 120, 120, 70, 240+40, 360+40,10, color3);

	for(;;)
	{


//		for(int i = 1; i <= 360; i++)
//		{
//			GC9A01_DrawArcStroke(&Display, 120, 120, 100, 0, i,10, color2);
//			Delay_milli(1);
//		}




//		GC9A01_Fill(&Display, 0xF8F8);        // clear to black
//		GC9A01_DrawCircleStroke(&Display,120, 120, 120, 15, color);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 100, 15, color);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 80, 15, color);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 60, 15, color);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 40, 15, color);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 20, 15, color);
//
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 20, 15, 0xffff);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 40, 15, 0xffff);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 60, 15, 0xffff);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 80, 15, 0xffff);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 100, 15, 0xffff);
//
//		Delay_milli(frame_delay);
//
//		GC9A01_DrawCircleStroke(&Display,120, 120, 120, 15, 0xffff);
//
//		Delay_milli(frame_delay);


	}
}



void Display_Init(void)
{
	Global_SPI.clock_pin      = SPI_Configurations.Pin._SPI1_.CLK1.PA5;
	Global_SPI.miso_pin       = SPI_Configurations.Pin._SPI1_.MISO1.PA6;
	Global_SPI.mosi_pin       = SPI_Configurations.Pin._SPI1_.MOSI1.PA7;
	Global_SPI.Port           = SPI1;
	Global_SPI.clock_phase    = SPI_Configurations.Clock_Phase.High_1;
	Global_SPI.clock_polarity = SPI_Configurations.Clock_Polarity.High_1;
	Global_SPI.type           = SPI_Configurations.Type.Master;
	Global_SPI.prescaler      = SPI_Configurations.Prescaler.CLK_div_2;
	Global_SPI.mode           = SPI_Configurations.Mode.Full_Duplex_Master;
	Global_SPI.frame_format   = SPI_Configurations.Frame_Format.MSB_First;
	Global_SPI.dma            = SPI_Configurations.DMA_Type.TX_DMA_Enable | SPI_Configurations.DMA_Type.RX_DMA_Enable;
	Global_SPI.data_format    = SPI_Configurations.Data_Format.Bit8;
	Global_SPI.crc            = SPI_Configurations.CRC_Enable.Disable;
	Global_SPI.interrupt      = SPI_Configurations.Interrupts.Disable;
	Display.SPI_Port = &Global_SPI;
	Display.rst_pin = 0;
	Display.rst_port = GPIOA;
	Display.cs_pin = 1;
	Display.cs_port = GPIOA;
	Display.dc_pin = 2;
	Display.dc_port = GPIOA;

	GC9A01_Init(&Display);

	GC9A01_Fill(&Display, 0x0000);
}
