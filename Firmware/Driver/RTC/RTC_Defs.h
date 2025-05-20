/*
 * RTC_Defs.h
 *
 *  Created on: May 17, 2025
 *      Author: kunal
 */

#ifndef RTC_RTC_DEFS_H_
#define RTC_RTC_DEFS_H_

#include "main.h"


typedef struct RTC_DateTime
{
	uint8_t weekday;
	uint8_t day;
	uint8_t month;
	uint16_t year;
	uint8_t hour;
	uint8_t mins;
	uint8_t sec;
	uint8_t AM_PM;

}RTC_DateTime;

typedef struct __RTC_Time_Format__
{
	uint8_t H24;
	uint8_t H12;
}__RTC_Time_Format__;


static const struct RTC_Configurations
{
	__RTC_Time_Format__ Format;

}RTC_Configurations =
		{
				.Format = {
						.H24 = 1,
						.H12 = 2,
				},
		};






#endif /* RTC_RTC_DEFS_H_ */
