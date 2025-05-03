/*
 * W25Qxx_Flash.h
 *
 *  Created on: May 1, 2025
 *      Author: kunal
 */

#ifndef W25QXX_FLASH_W25QXX_FLASH_H_
#define W25QXX_FLASH_W25QXX_FLASH_H_

#include "W25Qxx_Flash_Defs.h"
#include "main.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"

typedef struct W25Qxx_Config
{
	SPI_Config *SPI_Port;
	uint8_t Maufacturer_ID;
	uint8_t Memory_Type;
	uint8_t Capacity;
	uint64_t Unique_ID;
	uint32_t Memory_Size;
	GPIO_TypeDef *WP_Port;
	uint8_t WP_Pin;
	GPIO_TypeDef *HOLD_Reset_Port;
	uint8_t HOLD_Reset_Pin;

}W25Qxx_Config;

typedef enum{
	In_Progress,
	Completed,
	Error,

}W25Qxx_Status;




W25Qxx_Status W25Qxx_Init(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Read_ID(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Chip_Erase(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Power_Down(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Release_Power_Down(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Suspend(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Resume(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Reset_Device(W25Qxx_Config *_w25q_config_);
W25Qxx_Status W25Qxx_Page_Program(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size);
W25Qxx_Status W25Qxx_Sector_Erase(W25Qxx_Config *_w25q_config_,uint32_t address );
W25Qxx_Status W25Qxx_Block_Erase_32KB(W25Qxx_Config *_w25q_config_,uint32_t address );
W25Qxx_Status W25Qxx_Block_Erase_64KB(W25Qxx_Config *_w25q_config_,uint32_t address );
W25Qxx_Status W25Qxx_Read_Data(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size);
W25Qxx_Status W25Qxx_Fast_Read_Data(W25Qxx_Config *_w25q_config_,uint32_t address, uint8_t *buffer, size_t size);


#endif /* W25QXX_FLASH_W25QXX_FLASH_H_ */
