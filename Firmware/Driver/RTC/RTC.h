/*
 * RTC.h
 *
 *  Created on: May 17, 2025
 *      Author: kunal
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_

#include "main.h"
#include "RTC_Defs.h"


typedef struct RTC_Config
{
	uint8_t day;
	uint8_t month;
	uint8_t year;
	uint8_t weekday;

}RTC_Config;


void RTC_Init(RTC_Config *config);



#endif /* RTC_RTC_H_ */
