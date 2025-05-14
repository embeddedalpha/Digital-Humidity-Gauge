/*
 * BME280.c
 *
 *  Created on: May 5, 2025
 *      Author: kunal
 */


#include "BME280.h"




struct Calibration_Data{

	uint16_t dig_t1;
	uint16_t dig_t2;
	uint16_t dig_t3;
	uint16_t dig_p1;
	uint16_t dig_p2;
	uint16_t dig_p3;
	uint16_t dig_p4;
	uint16_t dig_p5;
	uint16_t dig_p6;
	uint16_t dig_p7;
	uint16_t dig_p8;
	uint16_t dig_p9;
	uint16_t dig_h1;
	uint16_t dig_h2;
	uint16_t dig_h3;
	uint16_t dig_h4;
	uint16_t dig_h5;
	uint16_t dig_h6;
	uint16_t t_fine;



}Calibration_Data;



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
	if(_bme280_config_->I2C_Port)
	{
		I2C_Init(_bme280_config_->I2C_Port);

		Delay_ms(1);

		uint8_t temp = 0;
		temp = I2C_Read_Register(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.id);
		if(temp != 0x60) return 0;

		uint8_t byte_array[50] = {0};
		I2C_Master_Read_Registers_Bulk(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.calib00, byte_array, 8);


		Calibration_Data.dig_t1 = ((uint32_t)byte_array[1] << 7) |  byte_array[0];
		Calibration_Data.dig_t2 = ((uint32_t)byte_array[3] << 7) |  byte_array[2];
		Calibration_Data.dig_t3 = ((uint32_t)byte_array[5] << 7) |  byte_array[4];

		Calibration_Data.dig_p1 = ((uint32_t)byte_array[7] << 7) |  byte_array[6];
		Calibration_Data.dig_p2 = ((uint32_t)byte_array[9] << 7) |  byte_array[8];
		Calibration_Data.dig_p3 = ((uint32_t)byte_array[11] << 7) |  byte_array[10];
		Calibration_Data.dig_p4 = ((uint32_t)byte_array[13] << 7) |  byte_array[12];
		Calibration_Data.dig_p5 = ((uint32_t)byte_array[15] << 7) |  byte_array[14];
		Calibration_Data.dig_p6 = ((uint32_t)byte_array[17] << 7) |  byte_array[16];
		Calibration_Data.dig_p7 = ((uint32_t)byte_array[19] << 7) |  byte_array[18];
		Calibration_Data.dig_p8 = ((uint32_t)byte_array[21] << 7) |  byte_array[20];
		Calibration_Data.dig_p9 = ((uint32_t)byte_array[23] << 7) |  byte_array[22];

		Calibration_Data.dig_h1 = ((uint32_t)byte_array[25] << 7) |  byte_array[24];
		Calibration_Data.dig_h2 = ((uint32_t)byte_array[27] << 7) |  byte_array[26];
		Calibration_Data.dig_h3 = ((uint32_t)byte_array[29] << 7) |  byte_array[28];
		Calibration_Data.dig_h4 = ((uint32_t)byte_array[31] << 7) |  byte_array[30];
		Calibration_Data.dig_h5 = ((uint32_t)byte_array[33] << 7) |  byte_array[32];
		Calibration_Data.dig_h6 = ((uint32_t)byte_array[35] << 7) |  byte_array[34];




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

	double var1;
	double var2;

	double temperature_min = -40;
	double temperature_max = 85;

	if(_bme280_config_->I2C_Port)
	{
		do {
			temp = I2C_Read_Register(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.id);
		} while (!(temp & 0b00001000));


		I2C_Master_Read_Registers_Bulk(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.press_msb, byte_array, 8);

		adc_P = ((uint32_t)byte_array[0] << 12) | ((uint32_t)byte_array[1] << 4) | ((byte_array[2] & 0x0F) << 0);
		adc_T = ((uint32_t)byte_array[3] << 12) | ((uint32_t)byte_array[4] << 4) | ((byte_array[5] & 0x0F) << 0);
		adc_H = ((uint32_t)byte_array[0] << 8) | ((byte_array[0]) << 0);




		var1 = (((double)adc_T) / 16384.0 - ((double)Calibration_Data.dig_t1) / 1024.0);
		var1 = var1 * ((double)Calibration_Data.dig_t2);
		var2 = (((double)adc_T) / 131072.0 - ((double)Calibration_Data.dig_t1) / 8192.0);
		var2 = (var2 * var2) * ((double)Calibration_Data.dig_t3);
		Calibration_Data.t_fine = (int32_t)(var1 + var2);
		_bme280_config_->Temperature = (var1 + var2) / 5120.0;

		if (_bme280_config_->Temperature  < temperature_min)
		{
			_bme280_config_->Temperature  = temperature_min;
		}
		else if (_bme280_config_->Temperature  > temperature_max)
		{
			_bme280_config_->Temperature  = temperature_max;
		}




	}


}


uint8_t BME280_Soft_Reset(BME280_Typedef *_bme280_config_)
{
	uint8_t result;

	I2C_Master_Write_Register(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.reset, 0xB6);

	do {

		result = I2C_Read_Register(_bme280_config_->I2C_Port, _bme280_config_->device_Address, Memory_Map.status);
		Delay_us(1);

	} while (result & 0x01);
}
