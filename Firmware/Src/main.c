#include "main.h"
#include "Console/Console.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"
#include "../Devices/BME280/BME280.h"
#include "../Devices/W25Qxx_Flash/W25Qxx_Flash.h"
#include "../Middleware/Filesystem/Filesystem.h"
#include "../Devices/GC9A01/GC9A01.h"
#include "../GC9A01/GC9A01_Image.h"

#define frame_delay 5
FileSystem_Typedef nn;

#include "BME280.h"

I2C_Config BME280_I2C;
SPI_Config Global_SPI;

BME280_Typedef Sensor1;
W25Qxx_Config Chip;
GC9A01_Config Display;

void DrawCircle(GC9A01_Config *config,uint16_t xc, uint16_t yc,
		uint16_t r,  uint16_t color);

void DrawCircleStroke(GC9A01_Config *config,uint16_t xc, uint16_t yc,
		uint16_t r,
		uint16_t thickness,
		uint16_t color);

void CountDemo(GC9A01_Config *lcd);

int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	Delay_s(1);


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
	Display.dc_pin = 2;
	Display.dc_port = GPIOA;
	Display.rst_pin = 0;
	Display.rst_port = GPIOA;
	Display.SPI_Port->NSS_Pin = 1;
	Display.SPI_Port->NSS_Port = GPIOA;


	GC9A01_Init(&Display);

//	uint16_t color = 0;
//	for (int x = 0; x < 240; x++)
//	{
//		for (int y = 0; y < 240; y++) {
//			if ((x / 10) % 2 ==  (y / 10) % 2) {
//				color = 0x9be9;
//			} else {
//				color = 0x41a6;
//			}
//			GC9A01_DrawPixel(&Display,x,  y, color);;
//		}
//	}
//
//
//
//
//	DrawCircleStroke(&Display,120, 120, 50, 10, 0x0000);


//	GC9A01_DrawImage(&Display, 0, 0, 240, 240, moon);


	for(;;)
	{

		GC9A01_DrawImage(&Display, 0, 0, 240, 240, sky);
		Delay_s(1);



	}
}



void DrawCircle(GC9A01_Config *config,uint16_t xc, uint16_t yc,
		uint16_t r,  uint16_t color)
{
	/* Decision variable (d) starts at 1‑r */
			int16_t  d   = 1 - (int16_t)r;
	uint16_t x   = 0;
	uint16_t y   = r;

	while (x <= y)
	{
		/* 1st octant -> replicate to all 8 symmetric points */
		GC9A01_DrawPixel(config,xc + x, yc + y, color);

		GC9A01_DrawPixel(config,xc - x, yc + y, color);   // ( -x, +y)
		GC9A01_DrawPixel(config,xc + x, yc - y, color);   // ( +x, -y)
		GC9A01_DrawPixel(config,xc - x, yc - y, color);   // ( -x, -y)
		GC9A01_DrawPixel(config,xc + y, yc + x, color);   // ( +y, +x)
		GC9A01_DrawPixel(config,xc - y, yc + x, color);   // ( -y, +x)
		GC9A01_DrawPixel(config,xc + y, yc - x, color);   // ( +y, -x)
		GC9A01_DrawPixel(config,xc - y, yc - x, color);   // ( -y, -x)

		/* Update decision variable & step */
		if (d < 0)
		{
			/* Mid‑point is inside the circle – choose E pixel */
			d += (x << 1) + 3;   // d += 2x + 3
		}
		else
		{
			/* Mid‑point is outside/on circle – choose SE pixel */
			d += ((x - y) << 1) + 5; // d += 2(x‑y) + 5
			y--;
		}
		x++;
	}
}

void DrawCircleStroke(GC9A01_Config *config,uint16_t xc, uint16_t yc,
		uint16_t r,
		uint16_t thickness,
		uint16_t color)
{
	if (thickness == 0 || r == 0) return;
	if (thickness > r) thickness = r;

	/* The simplest, portable way on small MCUs:
       draw concentric circles moving inward.   */
	for (uint16_t t = 0; t < thickness; t++)
	{
		DrawCircle(config, xc, yc, r - t, color);
	}
}

void CountDemo(GC9A01_Config *lcd)
{
	const uint16_t FG = 0xFFFF;   /* white */
	const uint16_t BG = 0x8000;   /* black */
	GC9A01_Fill(lcd, BG);

	for(int i = 0; i <= 100; ++i) {
		GC9A01_PrintNumber(lcd, 120, 120, i, FG, BG);  /* centre of 240×240 */
		Delay_ms(200);
	}
}
