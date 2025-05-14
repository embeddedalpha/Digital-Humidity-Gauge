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

static const struct BME280_Configurations{

	__BME280_Device_Address__ Device_Address;


}BME280_Configurations = {

		.Device_Address = {
				.Ox76 = 0x76,
				.Ox77 = 0x77,
		},

};


#endif /* BME280_BME280_DEFS_H_ */
