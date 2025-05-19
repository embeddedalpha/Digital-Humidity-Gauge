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


#define COMPILE_DATE	__DATE__
#define COMPILE_TIME	__TIME__

typedef struct RTC_Config
{

	uint8_t Format;

	uint8_t Interrupt_Type;

	__RTC_Alarm_Config__ Alarm_A;
	__RTC_Alarm_Config__ Alarm_B;

	struct __RTC_Interrupt__
	{
		void (*Alarm_A_ISR)(void);
		void (*Alarm_B_ISR)(void);
		void (*Timestamp_ISR)(void);
		void (*Wakeup_Time_ISR)(void);

	}Interrupt_ISR;

}RTC_Config;



void RTC_Init(RTC_Config *config);
void RTC_Set_Alarm_A(RTC_Config *config, void (*attach_Alarm_ISR));



#endif /* RTC_RTC_H_ */
