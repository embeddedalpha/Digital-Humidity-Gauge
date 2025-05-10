/*
 * BME280.c
 *
 *  Created on: May 5, 2025
 *      Author: kunal
 */


#include "BME280.h"


static  void CS_L(BME280_Typedef *_bme280_config_) { GPIO_Pin_Low(_bme280_config_->CSS_Port, _bme280_config_->CSS_Pin); }
static  void CS_H(BME280_Typedef *_bme280_config_) { GPIO_Pin_High(_bme280_config_->CSS_Port, _bme280_config_->CSS_Pin); }


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
		GPIO_Pin_Init(_bme280_config_->CSS_Port, _bme280_config_->CSS_Pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull,
				                                                           GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);

		CS_H(_bme280_config_);
		SPI_Init(_bme280_config_->SPI_Port);
		SPI_Enable(_bme280_config_->SPI_Port);





		return 1;

	}

	if(_bme280_config_->I2C_Port)
	{
		I2C_Init(_bme280_config_->I2C_Port);

		Delay_ms(1);

		uint8_t temp = 0;
		temp = I2C_Read_Register(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.id);
		if(temp != 0x60) return 0;





		return 1;

	}

	return 0;
}



void BME280_Get_Data(BME280_Typedef *_bme280_config_)
{
	uint8_t byte_array[8];
	uint8_t temp = 0;

	 uint32_t adc_T = 0;
	 uint32_t adc_H = 0;
	 uint32_t adc_P = 0;

	if(_bme280_config_->SPI_Port)
	{

	}
	if(_bme280_config_->I2C_Port)
	{
		do {
			temp = I2C_Read_Register(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.id);
		} while (!(temp & 0b00001000));


		I2C_Master_Read_Registers_Bulk(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.press_msb, byte_array, 8);

		adc_P = ((uint32_t)byte_array[0] << 12) | ((uint32_t)byte_array[1] << 4) | ((byte_array[2] & 0x0F) << 0);
		adc_T = ((uint32_t)byte_array[3] << 12) | ((uint32_t)byte_array[4] << 4) | ((byte_array[5] & 0x0F) << 0);
		adc_H = ((uint32_t)byte_array[0] << 8) | ((byte_array[0]) << 0);



	}







}
