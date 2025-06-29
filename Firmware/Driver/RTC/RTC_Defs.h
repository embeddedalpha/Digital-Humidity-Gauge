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

typedef struct __RTC_Interrupt_Type__
{
	uint16_t Alarm_A_Interrupt;
	uint16_t Alarm_B_Interrupt;
	uint16_t Wakeup_Timer_Interrupt;
	uint16_t Timestamp_Event_Interrupt;
	uint16_t Tamper_Detection_Interrupt;
}__RTC_Interrupt_Type__;


static const struct RTC_Configurations
{
	__RTC_Time_Format__ Format;
	__RTC_Interrupt_Type__ Interrupt_Type;

}RTC_Configurations =
		{
				.Format = {
						.H24 = 1,
						.H12 = 2,
				},

				.Interrupt_Type = {
						.Alarm_A_Interrupt = 1 << 12,
						.Alarm_B_Interrupt = 1 << 13,
						.Wakeup_Timer_Interrupt = 1 << 14,
						.Timestamp_Event_Interrupt = 1 << 15,
				},
		};






#endif /* RTC_RTC_DEFS_H_ */
