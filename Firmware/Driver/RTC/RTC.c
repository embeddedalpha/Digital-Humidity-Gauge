/*
 * RTC.c
 *
 *  Created on: May 17, 2025
 *      Author: kunal
 */

#include "RTC.h"

#define RTC_TIMEOUT  (uint32_t)0x0001FFFF

RTC_Config *__RTC_CONFIG__;

/*
 * \	if(DMA_LISR & DMA_LISR_DMEIF0)
	{
		if(__DMA1_Stream0_Config__->interrupts & DMA_Configuration.DMA_Interrupts.Direct_Mode_Error)
		{
			if (__DMA1_Stream0_Config__ -> ISR_Routines.Direct_Mode_Error_ISR)
			{
				__DMA1_Stream0_Config__ ->ISR_Routines.Direct_Mode_Error_ISR();
				DMA1 -> LIFCR |= DMA_LIFCR_CDMEIF0;
			}
		}
	}
 */

void RTC_Alarm_IRQHandler(void)
{
  if(RTC->ISR & RTC_ISR_ALRAF) {
    RTC->ISR &= ~RTC_ISR_ALRAF;         // clear flag
    if(__RTC_CONFIG__->Interrupt_ISR.Alarm_A_ISR)
    {
    	EXTI->PR = EXTI_PR_PR17;            // clear pending
    	__RTC_CONFIG__->Interrupt_ISR.Alarm_A_ISR();
    }
  }

  if(RTC->ISR & RTC_ISR_ALRBF) {
    RTC->ISR &= ~RTC_ISR_ALRBF;         // clear flag
    if(__RTC_CONFIG__->Interrupt_ISR.Alarm_A_ISR)
    {
    	EXTI->PR = EXTI_PR_PR17;            // clear pending
    	__RTC_CONFIG__->Interrupt_ISR.Alarm_A_ISR();
    }
  }
}


//void RTC_IRQHandler(void)
//{
//
//	if(RTC -> ISR & RTC_ISR_TSF){
//
//	}
//
////    if (RTC->ISR & RTC_ISR_SECIF) // Check second interrupt flag
////    {
//        RTC->ISR &= ~RTC_ISR_SECIF; // Clear it
//
//        // Read time & date (in BCD)
//        uint32_t tr = RTC->TR;
//        uint32_t dr = RTC->DR;
//
//        RTC_DateTime local;
//
//        local.sec = ((tr >> 4) & 0x70) + (tr & 0x0F);
//        local.mins = ((tr >> 12) & 0x70) + ((tr >> 8) & 0x0F);
//        local.hour   = ((tr >> 20) & 0x30) + ((tr >> 16) & 0x0F);
//
//        local.day     = ((dr >> 4) & 0x30) + (dr & 0x0F);
//        local.month   = ((dr >> 12) & 0x10) + ((dr >> 8) & 0x0F);
//        local.year    = ((dr >> 20) & 0xF0) + ((dr >> 16) & 0x0F);
//        local.weekday = (dr >> 13) & 0x07;
//
//        SystemTime = local;  // Atomic write (no pointer used)
////    }
//}

static uint8_t Calculate_Weekday(uint16_t y, uint8_t m, uint8_t d)
{
    if (m < 3) {
        m += 12;
        y--;
    }
    uint8_t h = (d + 2 * m + (3 * (m + 1)) / 5 + y + y/4 - y/100 + y/400 + 1) % 7;
    return h == 0 ? 7 : h; // Convert 0=Sunday to 7=Sunday
}

void RTC_Init(RTC_Config *config)
{
	  uint32_t timeout = RTC_TIMEOUT;
	// Parse compile time
	int hh, mm, ss;
	sscanf(__TIME__, "%2d:%2d:%2d", &hh, &mm, &ss);

	// Parse compile date
	char month_str[4];
	int day, year;
	sscanf(__DATE__, "%3s %2d %4d", month_str, &day, &year);

	int month = 1;
	const char *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
	for (int i = 0; i < 12; i++) {
		if (strncmp(month_str, months + i * 3, 3) == 0) {
			month = i + 1;
			break;
		}
	}




	RCC->APB1ENR |= RCC_APB1ENR_PWREN;     // Enable power interface clock
	PWR->CR |= PWR_CR_DBP;                 // Enable access to RTC and backup registers

	RCC->BDCR |= RCC_BDCR_LSEON;           // Enable LSE
    while (!(RCC->BDCR & RCC_BDCR_LSERDY) && --timeout) {
        __NOP();  // small delay
    }

	RCC->CSR |= RCC_CSR_LSION;
	while (!(RCC->CSR & RCC_CSR_LSIRDY)&& --timeout){
		__NOP();  // small delay
	}

	RCC->BDCR &= ~RCC_BDCR_RTCSEL;         // Clear RTC clock source
	RCC->BDCR |= RCC_BDCR_RTCSEL_0;        // 01: LSE selected
	RCC->BDCR |= RCC_BDCR_RTCEN;           // Enable RTC clock

	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	RTC->ISR |= RTC_ISR_INIT;
	while (!(RTC->ISR & RTC_ISR_INITF)); // Wait until allowed to change settings

	RTC->PRER = (127 << 16) | 255;  // Async = 127, Sync = 255

    RTC->TR = ((hh / 10) << 20) | ((hh % 10) << 16) |
              ((mm / 10) << 12) | ((mm % 10) << 8) |
              ((ss / 10) << 4)  | (ss % 10);

    uint8_t weekday = Calculate_Weekday(2025, 5, 17);  // e.g., Saturday → 6
    RTC->DR |= (weekday << 13);

    RTC->DR = (((year - 2000) / 10) << 20) | (((year - 2000) % 10) << 16) |
              ((month / 10) << 12) | ((month % 10) << 8) |
              ((day / 10) << 4)    | (day % 10);


	RTC->ISR &= ~RTC_ISR_INIT;
	while (!(RTC->ISR & RTC_ISR_RSF));  // Wait for register sync flag
	RTC->WPR = 0xFF;

//	RTC->CR |= RTC_CR_SECIE;         // Enable second interrupt
	NVIC_EnableIRQ(RTC_Alarm_IRQn);        // Enable in NVIC


	if(config->Interrupt_Type & RTC_Configurations.Interrupt_Type.Alarm_A_Interrupt)
	{
		__RTC_CONFIG__->Interrupt_ISR.Alarm_A_ISR = config->Interrupt_ISR.Alarm_A_ISR;
		NVIC_EnableIRQ(RTC_Alarm_IRQn);
	}


	config->Time_n_Date.sec = ss;
	config->Time_n_Date.mins = mm;
	config->Time_n_Date.hour = hh;

	config->Time_n_Date.weekday = weekday;
	config->Time_n_Date.year = year;
	config->Time_n_Date.month = month;
	config->Time_n_Date.AM_PM = 0;
	config->Time_n_Date.day = day;

}
void RTC_Set_Alarm_A(RTC_Config *config, void (*attach_Alarm_ISR));

