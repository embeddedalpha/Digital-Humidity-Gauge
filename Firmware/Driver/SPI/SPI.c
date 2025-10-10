/**
 * @file SPI.c
 * @brief Implementation of SPI driver with DMA support for STM32F407VGT6.
 *
 * This file provides functions to initialize, enable, disable, and transmit/receive data
 * using the SPI peripheral with optional DMA support.
 *
 * @author Kunal Salvi
 * @date 2024-08-24
 * @version 1.0
 */

#include "SPI.h"


volatile bool TX_Complete[3] ;
volatile bool RX_Complete[3] ;

void SPI1_TX_ISR()
{
	TX_Complete[0] = 1;
}

void SPI1_RX_ISR()
{
	RX_Complete[0] = 1;
}

void SPI2_TX_ISR()
{
	TX_Complete[1] = 1;
}

void SPI2_RX_ISR()
{
	RX_Complete[1] = 1;
}

void SPI3_TX_ISR()
{
	TX_Complete[2] = 1;
}

void SPI3_RX_ISR()
{
	RX_Complete[2] = 1;
}



uint8_t SPI_Get_Instance_Number(SPI_Config *config)
{
	if(config->Port == SPI1) {return 0;}
	else if(config->Port == SPI2) {return 1;}
	else if(config->Port == SPI3) {return 2;}
	else {return -1;}
}

DMA_Config xDMA_TX[3];
DMA_Config xDMA_RX[3];


/**
 * @brief Enables the clock for the specified SPI peripheral.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Clock_Enable(SPI_Config *config)
{
	int8_t retval = 0;
	if(config ->Port == SPI1)RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
	else if(config ->Port == SPI2)RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
	else if(config ->Port == SPI3)RCC -> APB1ENR |= RCC_APB1ENR_SPI3EN;
	else
		retval = -1;
	return retval;
}

/**
 * @brief Disables the clock for the specified SPI peripheral.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Clock_Disable(SPI_Config *config)
{
	int8_t retval = 0;
	if(config ->Port == SPI1)RCC -> APB2ENR &= ~RCC_APB2ENR_SPI1EN;
	else if(config ->Port == SPI2)RCC -> APB1ENR &= ~RCC_APB1ENR_SPI2EN;
	else if(config ->Port == SPI3)RCC -> APB1ENR &= ~RCC_APB1ENR_SPI3EN;
	else
		retval = -1;
	return retval;
}

/**
 * @brief Resets the SPI configuration to default values.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 0 on success, -1 on failure.
 */
int8_t SPI_Config_Reset(SPI_Config *config)
{
	int8_t retval = 0;
	if      (config->Port == SPI1) { RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST; RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; }
	else if (config->Port == SPI2) { RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST; RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST; }
	else if (config->Port == SPI3) { RCC->APB1RSTR |= RCC_APB1RSTR_SPI3RST; RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI3RST; }
	else { return -1; }

	config->clock_phase = SPI_Configurations.Clock_Phase.High_1;
	config->clock_polarity = SPI_Configurations.Clock_Polarity.High_1;
	config->mode = SPI_Configurations.Mode.Full_Duplex_Master;
	config->crc = SPI_Configurations.CRC_Enable.Disable;
	config->data_format = SPI_Configurations.Data_Format.Bit8;
	config->frame_format = SPI_Configurations.Frame_Format.MSB_First;
	config->dma = SPI_Configurations.DMA_Type.TX_DMA_Disable | SPI_Configurations.DMA_Type.RX_DMA_Disable;
	config->interrupt = SPI_Configurations.Interrupts.Disable;
	config->type = SPI_Configurations.Type.Master;

	return retval;
}

/**
 * @brief Initializes the GPIO pins used for SPI communication.
 *
 * This function configures the necessary GPIO pins for the specified SPI port.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
static void SPI_Pin_Init(SPI_Config *config)
{
	if(config -> Port == SPI1)
	{
		if((config->mode == SPI_Configurations.Mode.Full_Duplex_Master) || (config->mode == SPI_Configurations.Mode.Full_Duplex_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI1_.CLK1.PA5) GPIO_Pin_Init(GPIOA, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI1_.CLK1.PB3) GPIO_Pin_Init(GPIOB, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			if(config->miso_pin == SPI_Configurations.Pin._SPI1_.MISO1.PA6) GPIO_Pin_Init(GPIOA, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->miso_pin == SPI_Configurations.Pin._SPI1_.MISO1.PB4) GPIO_Pin_Init(GPIOB, 4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			if(config->mosi_pin == SPI_Configurations.Pin._SPI1_.MOSI1.PA7) GPIO_Pin_Init(GPIOA, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->mosi_pin == SPI_Configurations.Pin._SPI1_.MOSI1.PB5) GPIO_Pin_Init(GPIOB, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			config->Port -> CR1 &= ~SPI_CR1_BIDIMODE;
		}
		else if((config->mode == SPI_Configurations.Mode.Half_Duplex_Master) || (config->mode == SPI_Configurations.Mode.TX_Only_Master) || (config->mode == SPI_Configurations.Mode.RX_Only_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI1_.CLK1.PA5) GPIO_Pin_Init(GPIOA, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI1_.CLK1.PB3) GPIO_Pin_Init(GPIOB, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			if(config->mosi_pin == SPI_Configurations.Pin._SPI1_.MOSI1.PA7) GPIO_Pin_Init(GPIOA, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->mosi_pin == SPI_Configurations.Pin._SPI1_.MOSI1.PB5) GPIO_Pin_Init(GPIOB, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 |= SPI_CR1_BIDIOE;
		}
		else if((config->mode == SPI_Configurations.Mode.Half_Duplex_Slave) || (config->mode == SPI_Configurations.Mode.RX_Only_Master) || (config->mode == SPI_Configurations.Mode.TX_Only_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI1_.CLK1.PA5) GPIO_Pin_Init(GPIOA, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI1_.CLK1.PB3) GPIO_Pin_Init(GPIOB, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			if(config->miso_pin == SPI_Configurations.Pin._SPI1_.MISO1.PA6) GPIO_Pin_Init(GPIOA, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);
			else if(config->miso_pin == SPI_Configurations.Pin._SPI1_.MISO1.PB4) GPIO_Pin_Init(GPIOB, 4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_1);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 &= ~SPI_CR1_BIDIOE;
		}
	}
	/***************************************************************************************************************************************************************************************************************/
	else if(config -> Port == SPI2)
	{
		if((config->mode == SPI_Configurations.Mode.Full_Duplex_Master) || (config->mode == SPI_Configurations.Mode.Full_Duplex_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI2_.CLK2.PB10) GPIO_Pin_Init(GPIOB, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI2_.CLK2.PB13) GPIO_Pin_Init(GPIOB, 13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);

			if(config->miso_pin == SPI_Configurations.Pin._SPI2_.MISO2.PB14) GPIO_Pin_Init(GPIOB, 14, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);
			else if(config->miso_pin == SPI_Configurations.Pin._SPI2_.MISO2.PC2) GPIO_Pin_Init(GPIOC, 2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);

			if(config->mosi_pin == SPI_Configurations.Pin._SPI2_.MOSI2.PB15) GPIO_Pin_Init(GPIOB, 15, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);
			else if(config->mosi_pin == SPI_Configurations.Pin._SPI2_.MOSI2.PC3) GPIO_Pin_Init(GPIOC, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);

			config->Port -> CR1 &= ~SPI_CR1_BIDIMODE;
		}
		else if((config->mode == SPI_Configurations.Mode.Half_Duplex_Master) || (config->mode == SPI_Configurations.Mode.TX_Only_Master) || (config->mode == SPI_Configurations.Mode.RX_Only_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI2_.CLK2.PB10) GPIO_Pin_Init(GPIOB, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI2_.CLK2.PB13) GPIO_Pin_Init(GPIOB, 13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 |= SPI_CR1_BIDIOE;
		}
		else if((config->mode == SPI_Configurations.Mode.Half_Duplex_Slave) || (config->mode == SPI_Configurations.Mode.RX_Only_Master) || (config->mode == SPI_Configurations.Mode.TX_Only_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI2_.CLK2.PB10) GPIO_Pin_Init(GPIOB, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI2_.CLK2.PB13) GPIO_Pin_Init(GPIOB, 13, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);

			if(config->miso_pin == SPI_Configurations.Pin._SPI2_.MISO2.PB14) GPIO_Pin_Init(GPIOB, 14, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);
			else if(config->miso_pin == SPI_Configurations.Pin._SPI2_.MISO2.PC2) GPIO_Pin_Init(GPIOC, 2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_2);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 &= ~SPI_CR1_BIDIOE;
		}
	}
	/***************************************************************************************************************************************************************************************************************/
	else if(config -> Port == SPI3)
	{

		if((config->mode == SPI_Configurations.Mode.Full_Duplex_Master) || (config->mode == SPI_Configurations.Mode.Full_Duplex_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI3_.CLK3.PB3) GPIO_Pin_Init(GPIOB, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI3_.CLK3.PC10) GPIO_Pin_Init(GPIOC, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			if(config->miso_pin == SPI_Configurations.Pin._SPI3_.MISO3.PB4) GPIO_Pin_Init(GPIOB, 4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->miso_pin == SPI_Configurations.Pin._SPI3_.MISO3.PC11) GPIO_Pin_Init(GPIOC,11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			if(config->mosi_pin == SPI_Configurations.Pin._SPI3_.MOSI3.PB5) GPIO_Pin_Init(GPIOB, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->mosi_pin == SPI_Configurations.Pin._SPI3_.MOSI3.PC12) GPIO_Pin_Init(GPIOC, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			config->Port -> CR1 &= ~SPI_CR1_BIDIMODE;
		}
		else if((config->mode == SPI_Configurations.Mode.Half_Duplex_Master) || (config->mode == SPI_Configurations.Mode.TX_Only_Master) || (config->mode == SPI_Configurations.Mode.RX_Only_Slave))
		{


			if(config->clock_pin == SPI_Configurations.Pin._SPI3_.CLK3.PB3) GPIO_Pin_Init(GPIOB, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI3_.CLK3.PC10) GPIO_Pin_Init(GPIOC, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			if(config->miso_pin == SPI_Configurations.Pin._SPI3_.MISO3.PB4) GPIO_Pin_Init(GPIOB, 4, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->miso_pin == SPI_Configurations.Pin._SPI3_.MISO3.PC11) GPIO_Pin_Init(GPIOC,11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 |= SPI_CR1_BIDIOE;
		}
		else if((config->mode == SPI_Configurations.Mode.Half_Duplex_Slave) || (config->mode == SPI_Configurations.Mode.RX_Only_Master) || (config->mode == SPI_Configurations.Mode.TX_Only_Slave))
		{
			if(config->clock_pin == SPI_Configurations.Pin._SPI3_.CLK3.PB3) GPIO_Pin_Init(GPIOB, 3, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->clock_pin == SPI_Configurations.Pin._SPI3_.CLK3.PC10) GPIO_Pin_Init(GPIOC, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			if(config->mosi_pin == SPI_Configurations.Pin._SPI3_.MOSI3.PB5) GPIO_Pin_Init(GPIOB, 5, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);
			else if(config->mosi_pin == SPI_Configurations.Pin._SPI3_.MOSI3.PC12) GPIO_Pin_Init(GPIOC, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.SPI_3);

			config->Port -> CR1 |= SPI_CR1_BIDIMODE;
			config->Port -> CR1 &= ~SPI_CR1_BIDIOE;
		}
	}
}

/**
 * @brief Initializes the SPI peripheral with the specified configuration.
 *
 * This function sets up the SPI peripheral based on the settings in the SPI_Config structure.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @return int8_t Returns 1 on success, -1 on failure.
 */
int8_t SPI_Init(SPI_Config *config)
{
	//	if(config->type == SPI_Configurations.Type.Master){
	//		GPIO_Pin_Init(config->NSS_Port, config->NSS_Pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);
	//	}
	//	else if(config->type == SPI_Configurations.Type.Slave){
	//		GPIO_Pin_Init(config->NSS_Port, config->NSS_Pin, GPIO_Configuration.Mode.Input, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);
	//	}

	uint8_t spi_dma_instance = SPI_Get_Instance_Number(config);

	SPI_Clock_Enable(config);
	SPI_Pin_Init(config);

	//	SPI_NSS_High(config);

	config -> Port -> CR1 &= ~SPI_CR1_SPE;



	if((config -> Port == SPI1) || (config -> Port == SPI2) || (config -> Port == SPI3))
	{

		config -> Port ->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;


		if(config -> clock_phase == SPI_Configurations.Clock_Phase.Low_0) config-> Port -> CR1 &= ~SPI_CR1_CPHA;
		else if(config -> clock_phase == SPI_Configurations.Clock_Phase.High_1) config-> Port -> CR1 |= SPI_CR1_CPHA;
		else {return -1;}

		if(config -> clock_polarity == SPI_Configurations.Clock_Polarity.Low_0) config-> Port -> CR1 &= ~SPI_CR1_CPOL;
		else if(config -> clock_polarity == SPI_Configurations.Clock_Polarity.High_1) config-> Port -> CR1 |= SPI_CR1_CPOL;
		else {return -1;}

		if(config -> crc == SPI_Configurations.CRC_Enable.Disable) config -> Port -> CR1 &= ~SPI_CR1_CRCEN;
		else if(config -> crc == SPI_Configurations.CRC_Enable.Enable) config -> Port -> CR1 |=  SPI_CR1_CRCEN;
		else {return -1;}

		if(config -> data_format == SPI_Configurations.Data_Format.Bit8) config -> Port -> CR1 &= ~SPI_CR1_DFF;
		else if(config -> data_format == SPI_Configurations.Data_Format.Bit16) config -> Port -> CR1 |=  SPI_CR1_DFF;
		else {return -1;}

		if(config -> frame_format == SPI_Configurations.Frame_Format.LSB_First) config -> Port -> CR1 |= SPI_CR1_LSBFIRST;
		else if(config -> frame_format == SPI_Configurations.Frame_Format.MSB_First) config -> Port -> CR1 &= ~SPI_CR1_LSBFIRST;
		else {return -1;}

		if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_2) config -> Port -> CR1 &=   ~SPI_CR1_BR;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_4) config -> Port -> CR1 |=    SPI_CR1_BR_0;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_8) config -> Port -> CR1 |=    SPI_CR1_BR_1;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_16) config -> Port -> CR1 |=   SPI_CR1_BR_0 | SPI_CR1_BR_1;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_32) config -> Port -> CR1 |=   SPI_CR1_BR_2;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_64) config -> Port -> CR1 |=   SPI_CR1_BR_2 | SPI_CR1_BR_0;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_128) config -> Port -> CR1 |=  SPI_CR1_BR_2 | SPI_CR1_BR_1;
		else if(config->prescaler == SPI_Configurations.Prescaler.CLK_div_256) config -> Port -> CR1 |=  SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
		else {return -1;}

		if(config->type == SPI_Configurations.Type.Master) config -> Port -> CR1 |= SPI_CR1_MSTR;
		else if(config->type == SPI_Configurations.Type.Slave) config -> Port -> CR1 &= ~SPI_CR1_MSTR;
		else {return -1;}

		if(config->interrupt == SPI_Configurations.Interrupts.Disable) config -> Port ->  CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE);
		else if(config->interrupt == SPI_Configurations.Interrupts.Tx_Buffer_Empty) config -> Port ->  CR2 |= SPI_CR2_TXEIE;
		else if(config->interrupt == SPI_Configurations.Interrupts.RX_Buffer_not_Empty) config -> Port ->  CR2 |= SPI_CR2_RXNEIE ;
		else if(config->interrupt == SPI_Configurations.Interrupts.Error) config -> Port ->  CR2 |=  SPI_CR2_ERRIE;
		else { return -1;}


		if((config -> dma & SPI_Configurations.DMA_Type.RX_DMA_Enable) == SPI_Configurations.DMA_Type.RX_DMA_Enable)
		{
			if(config->Port == SPI1){
				xDMA_RX[0].Request = DMA_Configuration.Request.SPI1_RX;
				xDMA_RX[0].ISR_Routines.Full_Transfer_Commplete_ISR = SPI1_RX_ISR;
			}
			else if(config->Port == SPI2){
				xDMA_RX[1].Request = DMA_Configuration.Request.SPI2_RX;
				xDMA_RX[1].ISR_Routines.Full_Transfer_Commplete_ISR = SPI2_RX_ISR;
			}
			else if(config->Port == SPI3){
				xDMA_RX[2].Request = DMA_Configuration.Request.SPI3_RX;
				xDMA_RX[2].ISR_Routines.Full_Transfer_Commplete_ISR = SPI3_RX_ISR;
			}

			xDMA_RX[spi_dma_instance].transfer_direction = DMA_Configuration.Transfer_Direction.Peripheral_to_memory;
			xDMA_RX[spi_dma_instance].circular_mode = DMA_Configuration.Circular_Mode.Disable;
			xDMA_RX[spi_dma_instance].flow_control = DMA_Configuration.Flow_Control.DMA_Control;
			xDMA_RX[spi_dma_instance].interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete;
			xDMA_RX[spi_dma_instance].peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
			xDMA_RX[spi_dma_instance].memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
			xDMA_RX[spi_dma_instance].priority_level = DMA_Configuration.Priority_Level.Very_high;

			DMA_Init(&xDMA_RX[spi_dma_instance]);
		}

		if((config -> dma & SPI_Configurations.DMA_Type.TX_DMA_Enable) == SPI_Configurations.DMA_Type.TX_DMA_Enable)
		{
			if(config->Port == SPI1){
				xDMA_TX[0].Request = DMA_Configuration.Request.SPI1_TX;
				xDMA_TX[0].ISR_Routines.Full_Transfer_Commplete_ISR = SPI1_TX_ISR;
			}
			else if(config->Port == SPI2){
				xDMA_TX[1].Request = DMA_Configuration.Request.SPI2_TX;
				xDMA_TX[1].ISR_Routines.Full_Transfer_Commplete_ISR = SPI2_TX_ISR;
			}
			else if(config->Port == SPI3){
				xDMA_TX[2].Request = DMA_Configuration.Request.SPI3_TX;
				xDMA_TX[2].ISR_Routines.Full_Transfer_Commplete_ISR = SPI3_TX_ISR;
			}

			xDMA_TX[spi_dma_instance].transfer_direction = DMA_Configuration.Transfer_Direction.Memory_to_peripheral;
			xDMA_TX[spi_dma_instance].circular_mode = DMA_Configuration.Circular_Mode.Disable;
			xDMA_TX[spi_dma_instance].flow_control = DMA_Configuration.Flow_Control.DMA_Control;
			xDMA_TX[spi_dma_instance].interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete;
			xDMA_TX[spi_dma_instance].peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
			xDMA_TX[spi_dma_instance].memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
			xDMA_TX[spi_dma_instance].priority_level = DMA_Configuration.Priority_Level.Very_high;

			DMA_Init(&xDMA_TX[spi_dma_instance]);
		}








	}
	else
	{
		return -1;
	}

	return 1;
}

/**
 * @brief Enables the SPI peripheral.
 *
 * This function enables the SPI peripheral, allowing data transmission and reception.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_Enable(SPI_Config *config)
{
	config->Port -> CR1 |= SPI_CR1_SPE;
}

/**
 * @brief Disables the SPI peripheral.
 *
 * This function disables the SPI peripheral, preventing data transmission and reception.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_Disable(SPI_Config *config)
{
	config->Port -> CR1 &= ~SPI_CR1_SPE;
}

/**
 * @brief Deinitializes the SPI peripheral.
 *
 * This function resets the SPI peripheral and releases the associated resources.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_DeInit(SPI_Config *config)
{
	if      (config->Port == SPI1) { RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST; RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; }
	else if (config->Port == SPI2) { RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST; RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST; }
	else if (config->Port == SPI3) { RCC->APB1RSTR |= RCC_APB1RSTR_SPI3RST; RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI3RST; }
}

/**
 * @brief Transmits and receives a single byte over SPI.
 *
 * This function transmits a single byte of data over SPI and returns the received byte.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 * @param[in] tx_data Data to transmit.
 * @return uint16_t Received data.
 */
uint16_t SPI_TRX_Byte(SPI_Config *config,uint16_t tx_data)
{
	volatile uint16_t temp = 0;
	while (!(config->Port->SR & SPI_SR_TXE));
	config->Port -> DR = tx_data;
	while (!(config->Port->SR & SPI_SR_RXNE));
	temp = config->Port -> DR;
	while (!(config->Port->SR & SPI_SR_TXE));
	while (config->Port->SR & SPI_SR_BSY);
	return temp;
}

int8_t SPI_TRX_Buffer_16Bit(SPI_Config *config, uint16_t *tx_buffer,uint16_t *rx_buffer, uint16_t tx_length, uint16_t rx_length)
{

	if((config->dma & SPI_Configurations.DMA_Type.RX_DMA_Enable) || (config->dma & SPI_Configurations.DMA_Type.TX_DMA_Enable))
	{
		uint8_t spi_dma_instance = SPI_Get_Instance_Number(config);

		config -> Port -> CR2 &= ~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN);
		DMA_Reset_Trigger(&xDMA_TX[spi_dma_instance]);
		DMA_Reset_Trigger(&xDMA_RX[spi_dma_instance]);

		while (config -> Port -> SR & SPI_SR_RXNE) { (void)*(__IO uint16_t *)config -> Port->DR; }
		if (config -> Port ->SR & SPI_SR_OVR) {
			(void)*(__IO uint16_t *)config -> Port ->DR;
			(void)config -> Port ->SR;
		}

		if(rx_buffer != NULL)
		{
			xDMA_RX[spi_dma_instance].memory_address = (uint32_t)&rx_buffer[0];
			xDMA_RX[spi_dma_instance].memory_data_size = DMA_Configuration.Memory_Data_Size.half_word;
			xDMA_RX[spi_dma_instance].peripheral_address = (uint32_t)&config->Port->DR;
			xDMA_RX[spi_dma_instance].peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.half_word;
			xDMA_RX[spi_dma_instance].buffer_length = rx_length;
			xDMA_RX[spi_dma_instance].memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
			DMA_Set_Target(&xDMA_RX[spi_dma_instance]);
			DMA_Set_Trigger(&xDMA_RX[spi_dma_instance]);
		}

		xDMA_TX[spi_dma_instance].memory_address = (uint32_t)&tx_buffer[0];
		xDMA_TX[spi_dma_instance].memory_data_size = DMA_Configuration.Memory_Data_Size.half_word;
		xDMA_TX[spi_dma_instance].peripheral_address = (uint32_t)&config->Port->DR;
		xDMA_TX[spi_dma_instance].peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.half_word;
		xDMA_TX[spi_dma_instance].buffer_length = tx_length;
		xDMA_TX[spi_dma_instance].memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
		DMA_Set_Target(&xDMA_TX[spi_dma_instance]);
		DMA_Set_Trigger(&xDMA_TX[spi_dma_instance]);

		if(rx_buffer)
		{
			config -> Port -> CR2 |=  SPI_CR2_RXDMAEN;
		}
		config -> Port -> CR2 |=  SPI_CR2_TXDMAEN;


		while(!TX_Complete[spi_dma_instance]){}
		if(rx_buffer)
		{
			while(!RX_Complete[spi_dma_instance]){}
			__DSB();
		}
		TX_Complete[spi_dma_instance] = 0;
		RX_Complete[spi_dma_instance] = 0;


		config -> Port -> CR2 &= ~(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN);
		DMA_Reset_Trigger(&xDMA_RX[spi_dma_instance]);
		DMA_Reset_Trigger(&xDMA_TX[spi_dma_instance]);

		while (config -> Port -> SR & SPI_SR_RXNE) { (void)*(__IO uint16_t *)config -> Port->DR; }
		if (config -> Port ->SR & SPI_SR_OVR) {
			(void)*(__IO uint16_t *)config -> Port ->DR;
			(void)config -> Port ->SR;
		}

	}
	else
	{
		for(uint16_t i = 0; i < tx_length; i++)
		{
			rx_buffer[i] = SPI_TRX_Byte(config,tx_buffer[i]);
		}
	}

	return 1;

}






/**
 * @brief Updates the SPI data format.
 *
 * This function updates the data format (8-bit, 16-bit) of the SPI peripheral.
 *
 * @param[in] config Pointer to the SPI configuration structure.
 */
void SPI_Data_Format_Update(SPI_Config *config)
{
	SPI_Disable(config);
	if(config -> data_format == SPI_Configurations.Data_Format.Bit8) config -> Port -> CR1 &= ~SPI_CR1_DFF;
	else if(config -> data_format == SPI_Configurations.Data_Format.Bit16) config -> Port -> CR1 |=  SPI_CR1_DFF;
	SPI_Enable(config);
}

