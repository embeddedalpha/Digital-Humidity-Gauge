/*
 * BME280.h
 *
 *  Created on: Apr 23, 2025
 *      Author: kunal
 */

#ifndef BME280_BME280_H_
#define BME280_BME280_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "I2C/I2C.h"




#define BME280_ADDR (0x76)

typedef struct {
    uint16_t dig_T1; int16_t dig_T2, dig_T3;
    uint16_t dig_P1; int16_t dig_P2, dig_P3, dig_P4,
                     dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    uint8_t  dig_H1;
    int16_t  dig_H2; uint8_t dig_H3;
    int16_t  dig_H4, dig_H5; int8_t dig_H6;
    int32_t  t_fine;
} bme280_calib_t;

typedef struct {
	int32_t Pressure_Raw;
	int32_t Temperature_Raw;
	int32_t Humidity_Raw;
}bme280_raw;



uint8_t BME280_Init(I2C_Config *config);
void BME280_Get_Raw(I2C_Config *config, bme280_raw *raw_values);
float BME280_Compensate_T(int32_t adc_T);
float BME280_Compensate_P(int32_t adc_P);
float BME280_Compensate_H(int32_t adc_H);

#endif /* BME280_BME280_H_ */
