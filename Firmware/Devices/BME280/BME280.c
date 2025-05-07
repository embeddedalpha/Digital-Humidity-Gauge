/*
 * BME280.c
 *
 *  Created on: May 5, 2025
 *      Author: kunal
 */


#include "BME280.h"


static const struct Memory_Map{
	uint8_t hum_lsb;
	uint8_t hum_msb;
	uint8_t temp_xlsb;
	uint8_t temp_lsb;
	uint8_t temp_msb;
	uint8_t press_xlsb;
	uint8_t press_lsb;
	uint8_t press_msb;
	uint8_t config;
	uint8_t ctrl_meas;
	uint8_t status;
	uint8_t ctrl_hum;
	uint8_t calib26;
	uint8_t calib_mem_15;
	uint8_t reset;
	uint8_t id;
	uint8_t calib00;
	uint8_t calib_mem_25;
}Memory_Map = {
		.hum_lsb = 0xFE,
		.hum_msb = 0xFD,
		.temp_xlsb = 0xFc,
		.temp_lsb = 0xFB,
		.temp_msb = 0xFA,
		.press_xlsb = 0xF9,
		.press_lsb = 0xF8,
		.press_msb = 0xF7,
		.config = 0xF5,
		.ctrl_meas = 0xF4,
		.status = 0xF3,
		.ctrl_hum = 0xF2,
		.calib26 = 0xE1,
		.calib_mem_15 = 15,
		.reset = 0xE0,
		.id = 0xD0,
		.calib00 = 0x88,
		.calib_mem_25 = 26,
};

uint8_t BME280_Init(BME280_Typedef *_bme280_config_)
{
	if(_bme280_config_->SPI_Port)
	{
		SPI_Init(_bme280_config_->SPI_Port);
		SPI_Enable(_bme280_config_->SPI_Port);





		return 1;

	}

	if(_bme280_config_->I2C_Port)
	{
		I2C_Init(_bme280_config_->I2C_Port);


		return 1;

	}

	return 0;
}



void BME280_Get_Data(BME280_Typedef *_bme280_config_)
{

}
