/*
 * BME280.h
 *
 *  Created on: May 5, 2025
 *      Author: kunal
 */

#ifndef BME280_BME280_H_
#define BME280_BME280_H_

#include "main.h"
#include "I2C/I2C.h"
#include "BME280_Defs.h"



typedef struct BME280_Typedef{

	I2C_Config *I2C_Port;

	uint8_t device_Address;

	GPIO_TypeDef *CSS_Port;
	uint8_t CSS_Pin;

	struct __BME280_Settings__{
		uint8_t Pressure_Oversampling;
		uint8_t Temperature_Oversampling;
		uint8_t Humidity_Oversampling;
		uint8_t Filter_Coefficients;
		uint8_t Standby_Time;
	}Settings;


	uint32_t Temperature;
	uint32_t Relative_Humidity;
	uint32_t Pressure;


}BME280_Typedef;


uint8_t BME280_Init(BME280_Typedef *_bme280_config_);

uint8_t BME280_Soft_Reset(BME280_Typedef *_bme280_config_);

void BME280_Get_Data(BME280_Typedef *_bme280_config_);


#endif /* BME280_BME280_H_ */
