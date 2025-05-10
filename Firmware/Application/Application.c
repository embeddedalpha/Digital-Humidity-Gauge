/*
 * Application.c
 *
 *  Created on: May 6, 2025
 *      Author: kunal
 */

#include "Application.h"



void Flash_Init()
{

	Flash.clock_pin      = SPI_Configurations.Pin._SPI1_.CLK1.PA5;
	Flash.miso_pin       = SPI_Configurations.Pin._SPI1_.MISO1.PA6;
	Flash.mosi_pin       = SPI_Configurations.Pin._SPI1_.MOSI1.PA7;
	Flash.Port           = SPI1;
	Flash.clock_phase    = SPI_Configurations.Clock_Phase.Low_0;
	Flash.clock_polarity = SPI_Configurations.Clock_Polarity.Low_0;
	Flash.type           = SPI_Configurations.Type.Master;
	Flash.prescaler      = SPI_Configurations.Prescaler.CLK_div_8;
	Flash.mode           = SPI_Configurations.Mode.Full_Duplex_Master;
	Flash.frame_format   = SPI_Configurations.Frame_Format.MSB_First;
	Flash.dma            = SPI_Configurations.DMA_Type.TX_DMA_Enable | SPI_Configurations.DMA_Type.RX_DMA_Enable;
	Flash.data_format    = SPI_Configurations.Data_Format.Bit8;
	Flash.crc            = SPI_Configurations.CRC_Enable.Disable;
	Flash.interrupt      = SPI_Configurations.Interrupts.Disable;


	Chip1.SPI_Port = &Flash;


	W25Qxx_Init(&Chip1);

}
