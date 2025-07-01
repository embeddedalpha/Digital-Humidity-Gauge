/*
 * BME280_Defs.h
 *
 *  Created on: May 5, 2025
 *      Author: kunal
 */

#ifndef BME280_BME280_DEFS_H_
#define BME280_BME280_DEFS_H_

#include "main.h"


 typedef struct __BME280_Device_Address__
{
	uint8_t Ox76;
	uint8_t Ox77;

}__BME280_Device_Address__;


typedef struct __BME280_Oversampling__
{
	uint8_t Skip_T_Oversampling;
	uint8_t Oversampling_X_1;
	uint8_t Oversampling_X_2;
	uint8_t Oversampling_X_4;
	uint8_t Oversampling_X_8;
	uint8_t Oversampling_X_16;

}__BME280_Oversampling__;

typedef struct __BME280_T_Standby_MS__
{
	uint8_t t_standby_ms_0x5;  //0.5 ms
	uint8_t t_standby_ms_62x5; //62.5 ms
	uint8_t t_standby_ms_125;  //125 ms
	uint8_t t_standby_ms_250;  //125 ms
	uint8_t t_standby_ms_500;  //125 ms
	uint8_t t_standby_ms_1000;  //1000 ms
	uint8_t t_standby_ms_10;    //10 ms
	uint8_t t_standby_ms_20;    //20 ms
}__BME280_T_Standby_MS__;

typedef struct __BME280_T_Mode__
{
	uint8_t Sleep;
	uint8_t Forced;
	uint8_t Normal;

}__BME280_T_Mode__;

static const struct BME280_Configurations{

	__BME280_Device_Address__ Device_Address;
	__BME280_Oversampling__ Pressure_Oversampling;
	__BME280_Oversampling__ Temperature_Oversampling;
	__BME280_Oversampling__ Humidity_Oversampling;
	__BME280_T_Standby_MS__ T_Standby_ms;
	__BME280_T_Mode__       Mode;



}BME280_Configurations = {

		.Device_Address = {
				.Ox76 = 0x76,
				.Ox77 = 0x77,
		},

};


#endif /* BME280_BME280_DEFS_H_ */
