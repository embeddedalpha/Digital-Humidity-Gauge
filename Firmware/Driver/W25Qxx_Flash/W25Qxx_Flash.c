/*
 * W25Qxx_Flash.c
 *
 *  Created on: May 1, 2025
 *      Author: kunal
 */

#include <W25Qxx_Flash/W25Qxx_Flash.h>


static uint32_t Read_Status_Registers(W25Qxx_Config *_w25q_config_)
{
	uint8_t status[3];

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x05);
	status[0] = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x35);
	status[1] = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x15);
	status[2] = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_NSS_High(_w25q_config_->SPI_Port);


	return (status[0] << 16) || (status[1] << 8) || (status[2] << 0);
}

W25Qxx_Status W25Qxx_Release_Power_Down(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAB);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	return Completed;
}

W25Qxx_Status W25Qxx_Init(W25Qxx_Config *_w25q_config_)
{
	uint32_t dummy = 0;
	SPI_Init(_w25q_config_->SPI_Port);
	SPI_Enable(_w25q_config_->SPI_Port);


	W25Qxx_Release_Power_Down(_w25q_config_);

	W25Qxx_Read_ID(_w25q_config_);

	dummy = Read_Status_Registers(_w25q_config_);

	return Completed;

}


W25Qxx_Status W25Qxx_Read_ID(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x9F);
	_w25q_config_->Maufacturer_ID = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAA);
	_w25q_config_->Memory_Type = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAA);
	_w25q_config_->Capacity = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAA);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x4B);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	_w25q_config_->Unique_ID = ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 56) |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 48) |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 40) |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 32) |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 24) |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 16) |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 8)  |
							   ((uint64_t)SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00) << 0);

	SPI_NSS_High(_w25q_config_->SPI_Port);

	return Completed;
}


W25Qxx_Status W25Qxx_Chip_Erase(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x9F);
	_w25q_config_->Maufacturer_ID = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAA);
	_w25q_config_->Memory_Type = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAA);
	_w25q_config_->Capacity = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xAA);
	SPI_NSS_High(_w25q_config_->SPI_Port);
}
W25Qxx_Status W25Qxx_Power_Down(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Suspend(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Resume(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Reset_Device(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Page_Program(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size);
W25Qxx_Status W25Qxx_Sector_Erase(W25Qxx_Config *_w25q_config_,uint32_t address );
W25Qxx_Status W25Qxx_Block_Erase_32KB(W25Qxx_Config *_w25q_config_,uint32_t address );
W25Qxx_Status W25Qxx_Block_Erase_64KB(W25Qxx_Config *_w25q_config_,uint32_t address );
W25Qxx_Status W25Qxx_Read_Data(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size);
W25Qxx_Status W25Qxx_Fast_Read_Data(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size);
