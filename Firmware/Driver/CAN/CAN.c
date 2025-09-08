/*
 * CAN.c
 *
 *  Created on: Feb 19, 2025
 *      Author: kunal
 */


#include "CAN.h"

static CAN_Status_T CAN_Pin_Init(CAN_Config *config)
{
	if(config->Port == CAN1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_CAN1EN;

		if(config->Pins.TX_Pin == CAN_Configuration.Pin._CAN1.TX.PA12)
			GPIO_Pin_Init(GPIOA,12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_1);
		else if(config->Pins.TX_Pin == CAN_Configuration.Pin._CAN1.TX.PB9)
			GPIO_Pin_Init(GPIOB,9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_1);
		else if(config->Pins.TX_Pin == CAN_Configuration.Pin._CAN1.TX.PD1)
			GPIO_Pin_Init(GPIOD,1, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_1);
		else return CAN_Pin_Error;


		if(config->Pins.RX_Pin == CAN_Configuration.Pin._CAN1.RX.PA11)
			GPIO_Pin_Init(GPIOA,11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_1);
		else if(config->Pins.RX_Pin == CAN_Configuration.Pin._CAN1.RX.PB8)
			GPIO_Pin_Init(GPIOB,8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_1);
		else if(config->Pins.RX_Pin == CAN_Configuration.Pin._CAN1.RX.PD0)
			GPIO_Pin_Init(GPIOD,0, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_1);
		else return CAN_Pin_Error;


		return CAN_OK;
	}
	else if(config->Port == CAN2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_CAN2EN;

		if(config->Pins.TX_Pin == CAN_Configuration.Pin._CAN2.TX.PB13)
			GPIO_Pin_Init(GPIOB,13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_2);
		else if(config->Pins.TX_Pin == CAN_Configuration.Pin._CAN2.TX.PB6)
			GPIO_Pin_Init(GPIOB,6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_2);
		else return CAN_Pin_Error;

		if(config->Pins.RX_Pin == CAN_Configuration.Pin._CAN2.RX.PB12)
			GPIO_Pin_Init(GPIOB,12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_2);
		else if(config->Pins.RX_Pin == CAN_Configuration.Pin._CAN2.RX.PB5)
			GPIO_Pin_Init(GPIOB,5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.CAN_2);
		else return CAN_Pin_Error;

		return CAN_OK;
	}

	return CAN_Port_Error;
}

CAN_Status_T CAN_Init(CAN_Config *config)
{
	CAN_Status_T retval = CAN_OK;

	retval = CAN_Pin_Init(config);
	if(retval != CAN_OK)return retval;

	if(config -> timestamp_enable == ENABLE) config -> Port -> MCR |= CAN_MCR_TTCM;
	else config -> Port -> MCR &= ~CAN_MCR_TTCM;

	return retval;
}

CAN_Status_T CAN_Reset(CAN_Config *config)
{
	CAN_Status_T retval = CAN_OK;

	config -> Port -> MCR |= CAN_MCR_RESET;

	if(!((config -> Port -> MCR & CAN_MCR_RESET_Msk) >> CAN_MCR_RESET_Pos))
	{
		retval = CAN_OK;
	}
	else
	{
		retval = CAN_Reset_Error;
	}

	return retval;
}
