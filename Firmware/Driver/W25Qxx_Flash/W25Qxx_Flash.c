/*
 * W25Qxx_Flash.c
 *
 *  Created on: May 1, 2025
 *      Author: kunal
 */

#include <W25Qxx_Flash/W25Qxx_Flash.h>

 enum Status_bits{
	Status_Register_Protect_0 = 1 << 7,
	Sector_Protector_Bit = 1 << 6,
	Top_Bottom_Protect_Bit = 1 << 5,
	Block_Protect_Bit_2 = 1 << 4,
	Block_Protect_Bit_1 = 1 << 3,
	Block_Protect_Bit_0 = 1 << 2,
	Write_Enable_Latch = 1 << 1,
	Erase_Write_In_Progress = 1 << 0,

	Suspend_Status = 1 << 15,
	Complement_Protect = 1 << 14,
	Security_Register_Lock_Bit_3 = 1 << 13,
	Security_Register_Lock_Bit_2 = 1 << 12,
	Security_Register_Lock_Bit_1 = 1 << 11,
	Quad_Enable = 1 << 9,
	Status_Register_Protect_1 = 1 << 8,

	Hold_Reset_Function = 1 << 23,
	Output_Driver_Strength_1 = 1 << 22,
	Output_Driver_Strength_0 = 1 << 21,
	Write_Protect_Selection = 1 << 18,

}Status_bits;



static uint32_t Read_Status_Registers(W25Qxx_Config *_w25q_config_)
{
	uint32_t status[3];
	status[0] = 0;
	status[1] = 0;
	status[2] = 0;

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	 SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x05);
	status[0] = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x00);
	SPI_NSS_High(_w25q_config_->SPI_Port);

//	SPI_NSS_Low(_w25q_config_->SPI_Port);
//	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x35);
//	status[1] = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xff);
//	SPI_NSS_High(_w25q_config_->SPI_Port);
//
//	SPI_NSS_Low(_w25q_config_->SPI_Port);
//	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x15);
//	status[2] = SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xff);
//	SPI_NSS_High(_w25q_config_->SPI_Port);

	return ((status[2] << 16) | (status[1] << 8) | (status[0] << 0));
}

static uint32_t Write_Enable(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x06);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	return Read_Status_Registers(_w25q_config_) & Write_Enable_Latch;
}

static uint32_t Write_Disable(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x04);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	return Read_Status_Registers(_w25q_config_) & Write_Enable_Latch;
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

	SPI_Init(_w25q_config_->SPI_Port);
	SPI_Enable(_w25q_config_->SPI_Port);

	W25Qxx_Reset_Device(_w25q_config_);

	W25Qxx_Release_Power_Down(_w25q_config_);
	Delay_milli(20);
	W25Qxx_Read_ID(_w25q_config_);



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





W25Qxx_Status W25Qxx_Power_Down(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xB9);
	SPI_NSS_High(_w25q_config_->SPI_Port);
	return Completed;
}



W25Qxx_Status W25Qxx_Page_Program(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size)
{
	uint32_t temp = Write_Enable(_w25q_config_);
	if(temp == Write_Enable_Latch)
	{
		SPI_NSS_Low(_w25q_config_->SPI_Port);
		SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x02);
		SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 16);
		SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 8);
		SPI_TRX_Byte(_w25q_config_->SPI_Port, address & 0x0000FF);
		SPI_TRX_Buffer_8Bit(_w25q_config_->SPI_Port, buffer, 0, size, 0);
		SPI_NSS_High(_w25q_config_->SPI_Port);
		Delay_us(10);
		Write_Disable(_w25q_config_);
		return Completed;

	}
	else
	{
		return Error;
	}



return Completed;

}

W25Qxx_Status W25Qxx_Read_Data(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size)
{
	uint8_t txbuffer[256];

	for(int i = 0; i < 256; i++)
	{
		txbuffer[i] = 0;
	}

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x03);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 16);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 8);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address & 0x0000FF);
	SPI_TRX_Buffer_8Bit(_w25q_config_->SPI_Port, txbuffer, buffer, size, size);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	return Completed;

}



W25Qxx_Status W25Qxx_Fast_Read_Data(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size)
{
	uint8_t txbuffer[256];

	for(int i = 0; i < 256; i++)
	{
		txbuffer[i] = 0;
	}

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x0B);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 16);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 8);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address & 0x0000FF);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xFF);
	SPI_TRX_Buffer_8Bit(_w25q_config_->SPI_Port, txbuffer, buffer, size, size);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	return Completed;
}


W25Qxx_Status W25Qxx_Reset_Device(W25Qxx_Config *_w25q_config_)
{
	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x66);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x99);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	Delay_ms(1);
	return Completed;
}

W25Qxx_Status W25Qxx_Chip_Erase(W25Qxx_Config *_w25q_config_)
{
	Write_Enable(_w25q_config_);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x60);
	SPI_NSS_High(_w25q_config_->SPI_Port);

//	Write_Disable(_w25q_config_);

	uint32_t temp = 0;
	do {
		temp = 0;
		temp = Read_Status_Registers(_w25q_config_);
	} while (temp != 0);

	return Completed;
}

W25Qxx_Status W25Qxx_Sector_Erase(W25Qxx_Config *_w25q_config_,uint32_t address )
{
	Write_Enable(_w25q_config_);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x20);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 16);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 8);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address & 0x0000FF);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	uint32_t temp = 0;
	do {
		temp = 0;
		temp = Read_Status_Registers(_w25q_config_);
	} while (temp != 0);




	Write_Disable(_w25q_config_);

	return Completed;
}

W25Qxx_Status W25Qxx_Block_Erase_32KB(W25Qxx_Config *_w25q_config_,uint32_t address )
{
	Write_Enable(_w25q_config_);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0x52);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 16);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 8);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address & 0x0000FF);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	uint32_t temp = 0;
	do {
		temp = 0;
		temp = Read_Status_Registers(_w25q_config_);
	} while (temp != 0);




	Write_Disable(_w25q_config_);

	return Completed;
}


W25Qxx_Status W25Qxx_Block_Erase_64KB(W25Qxx_Config *_w25q_config_,uint32_t address )
{
	Write_Enable(_w25q_config_);

	SPI_NSS_Low(_w25q_config_->SPI_Port);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, 0xd8);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 16);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address >> 8);
	SPI_TRX_Byte(_w25q_config_->SPI_Port, address & 0x0000FF);
	SPI_NSS_High(_w25q_config_->SPI_Port);

	uint32_t temp = 0;
	do {
		temp = 0;
		temp = Read_Status_Registers(_w25q_config_);
	} while (temp != 0);

	return Completed;


	Write_Disable(_w25q_config_);

	return Completed;
}


W25Qxx_Status W25Qxx_Suspend_Operation(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Resume_Operation(W25Qxx_Config *_w25q_config_);
