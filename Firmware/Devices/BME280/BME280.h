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
#include "SPI/SPI.h"

#define Device_Address_1 0x76
#define Device_Address_2 0x77

typedef struct BME280_Typedef{

	I2C_Config *I2C_Port;
	SPI_Config *SPI_Port;

	uint8_t device_Address;

	GPIO_TypeDef *CSS_Port;
	uint8_t CSS_Pin;


	uint32_t Temperature;
	uint32_t Relative_Humidity;
	uint32_t Pressure;


}BME280_Typedef;


uint8_t BME280_Init(BME280_Typedef *_bme280_config_);
void BME280_Get_Data(BME280_Typedef *_bme280_config_);


#endif /* BME280_BME280_H_ */
