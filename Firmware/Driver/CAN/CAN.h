/*
 * CAN.h
 *
 *  Created on: Feb 19, 2025
 *      Author: kunal
 */

#ifndef CAN_CAN_H_
#define CAN_CAN_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "Timer/Timer.h"
#include "CAN_Defs.h"

typedef struct {
	  uint32_t id;       // 11-bit (STD) in bits[10:0] or 29-bit (EXT) in bits[28:0]
	  uint8_t  dlc;
	  uint8_t  ide;      // 0=STD, 1=EXT
	  uint8_t  rtr;      // 0=Data, 1=Remote
	  uint8_t  data[8];
	  uint32_t timestamp;  // ticks from DWT/TIM (optional)
	} can_frame_t;

typedef struct CAN_Config
{
	CAN_TypeDef *Port;

	struct __CAN_Pins__{
		uint8_t RX_Pin;
		uint8_t TX_Pin;
	}Pins;
	uint32_t Baudrate;
	int timestamp_enable;
	int interrupt;

	struct __CAN_Interrupts__{
		void (* Sleep_ISR)(void);
		void (*Wake_UP_ISR)(void);
		void (*Error_ISR)(void);
		void (*Last_Error_Code_ISR)(void);
		void (*Bus_off_ISR)(void);
		void (*Error_Passive_ISR)(void);
		void (*Error_Warning_ISR)(void);
		void (*FIFO_Overrun_ISR)(void);
		void (*FIFO_Full_ISR)(void);
		void (*FIFO_Message_Pending_ISR)(void);
		void (*Transmit_Mailbox_Empty_ISR)(void);

	}ISR_Routines;

}CAN_Config;


CAN_Status_T CAN_Init(CAN_Config *config);
CAN_Status_T CAN_Reset(CAN_Config *config);
CAN_Status_T CAN_Set_Filter(CAN_Config *config);




#endif /* CAN_CAN_H_ */
