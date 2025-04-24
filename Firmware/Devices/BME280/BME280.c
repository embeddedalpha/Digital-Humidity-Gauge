/*
 * BME280.c
 *
 *  Created on: Apr 23, 2025
 *      Author: kunal
 */


#include "BME280.h"

static bme280_calib_t calib;

uint8_t BME280_Init(I2C_Config *config)
{
	int ID = 0;
	ID = I2C_Master_Read_Register(config, BME280_ADDR, 0xD0);
	if(ID == 0x60)
	{
		// Soft Reset
		I2C_Master_Write_Register(config, BME280_ADDR, 0xE0, 0xB6);
		Delay_milli(5);
		uint8_t temp[40];
		I2C_Master_Read_Registers_Bulk(config, BME280_ADDR, 0x88, temp, 24);
		temp[24] = I2C_Master_Read_Register(config, BME280_ADDR, 0xA1);
		I2C_Master_Read_Registers_Bulk(config, BME280_ADDR, 0xE1, &temp[25], 7);

		calib.dig_T1 = (temp[1] << 8) | (temp[0] << 0);
		calib.dig_T2 = (temp[3] << 8) | (temp[2] << 0);
		calib.dig_T3 = (temp[5] << 8) | (temp[4] << 0);

		calib.dig_P1 = (temp[7] << 8) | (temp[6] << 0);
		calib.dig_P2 = (temp[9] << 8) | (temp[8] << 0);
		calib.dig_P3 = (temp[11] << 8) | (temp[10] << 0);

		calib.dig_P4 = (temp[13] << 8) | (temp[12] << 0);
		calib.dig_P5 = (temp[15] << 8) | (temp[14] << 0);
		calib.dig_P6 = (temp[17] << 8) | (temp[16] << 0);

		calib.dig_P7 = (temp[19] << 8) | (temp[18] << 0);
		calib.dig_P8 = (temp[21] << 8) | (temp[20] << 0);
		calib.dig_P9 = (temp[23] << 8) | (temp[22] << 0);

		calib.dig_H1 =  (temp[24] << 0);
		calib.dig_H2 = (temp[26] << 8) | (temp[25] << 0);
		calib.dig_H3 = (temp[27] << 0);
		calib.dig_H4 = (temp[29] << 8) | (temp[28] << 0);
		calib.dig_H5 = (temp[31] << 8) | (temp[30] << 0);
		calib.dig_H6 = (temp[32] << 0);

		return 1;
	}

	return 0;
}

void BME280_Get_Raw(I2C_Config *config, bme280_raw *raw_values)
{
	uint8_t raw[8];
	I2C_Master_Read_Registers_Bulk(config, BME280_ADDR, 0xf7, raw, 8);
	raw_values->Pressure_Raw = (raw[0]<<12)|(raw[1]<<4)|(raw[2]>>4);
	raw_values->Temperature_Raw = (raw[3]<<12)|(raw[4]<<4)|(raw[5]>>4);
	raw_values->Humidity_Raw = (raw[6]<<8) | raw[7];
}

float BME280_Compensate_T(int32_t adc_T)
{
    int32_t var1 = (((adc_T>>3) - ((int32_t)calib.dig_T1<<1)) *
                   calib.dig_T2) >> 11;
    int32_t var2 = (((((adc_T>>4) - calib.dig_T1) *
                   ((adc_T>>4) - calib.dig_T1)) >> 12) *
                   calib.dig_T3) >> 14;
    calib.t_fine = var1 + var2;
    return (calib.t_fine * 5 + 128) >> 8;   // 0.01 °C
}

float BME280_Compensate_P(int32_t adc_P)
{
    int64_t var1 = calib.t_fine - 128000;
    int64_t var2 = var1*var1*calib.dig_P6;
    var2 += ((var1*calib.dig_P5)<<17) + (((int64_t)calib.dig_P4)<<35);
    var1 = ((var1*var1*calib.dig_P3)>>8) + ((var1*calib.dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*calib.dig_P1>>33;
    if (var1==0) return 0;  /* avoid div-by-0 */
    int64_t p = 1048576 - adc_P;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (calib.dig_P9 * (p>>13) * (p>>13)) >> 25;
    var2 = (calib.dig_P8 * p) >> 19;
    return ((p + var1 + var2) >> 8) + (calib.dig_P7<<4); // Pa
}

float BME280_Compensate_H(int32_t adc_H)
{
    int32_t v_x = calib.t_fine - 76800;
    v_x = (((adc_H<<14) - (calib.dig_H4<<20) -
          (calib.dig_H5 * v_x)) + 16384)>>15;
    v_x = v_x * (((((((v_x*calib.dig_H6)>>10) *
          (((v_x*calib.dig_H3)>>11)+32768))>>10)+2097152) *
          calib.dig_H2 + 8192)>>14);
    v_x = v_x - (((((v_x>>15)*(v_x>>15))>>7)*calib.dig_H1)>>4);
    v_x = (v_x<0)?0:v_x;
    v_x = (v_x>419430400)?419430400:v_x;
    return v_x>>12; /* 1024 = 100 %RH */
}

