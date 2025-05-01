#include "main.h"
#include "Console/Console.h"
#include "GPIO/GPIO.h"
#include "SPI/SPI.h"


SPI_Config flash;

static void SPI1_GPIO_Init(void)
{
    /* 1. Enable GPIOA clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* 2. Configure PA5, PA6, PA7 to Alternate-Function 5 */
    /*    MODER: 10 = AF, OSPEEDR: 10 = High (50 MHz),
          OTYPER: 0 = Push-Pull, PUPDR: 00 = No Pull */
    GPIOA->MODER   &= ~(0x3FU << (5*2));        // clear bits
    GPIOA->MODER   |=  (0x2AU << (5*2));        // AF on 5,6,7
    GPIOA->OSPEEDR |=  (0x3FU << (5*2));        // High speed
    GPIOA->OTYPER  &= ~(0x7  << 5);             // Push-pull
    GPIOA->PUPDR   &= ~(0x3FU << (5*2));        // No pull

    /* 3. Set AFR[0] for pins 5-7 to AF5 (0b0101) */
    GPIOA->AFR[0] &= ~(0xFFFU << (5*4));
    GPIOA->AFR[0] |=  (0x555U << (5*4));
}

void SPI1_Init(void)
{
    SPI1_GPIO_Init();

    /* 4. Enable SPI1 peripheral clock on APB2 */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /* 5. Reset then configure CR1 */
    SPI1->CR1 = 0;                  // Disable & clear

    /*  Master, clk = PCLK2/8  (84 MHz/8 ≈ 10.5 MHz)   */
    SPI1->CR1 |= SPI_CR1_MSTR                     |
                 SPI_CR1_BR_1 | SPI_CR1_BR_0;     // fPCLK/8

    /*  CPOL = 0, CPHA = 0  (mode-0).  Flip these bits
        if your slave needs a different mode.          */

    /*  Software-managed NSS so we can bit-bang CS lines */
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    /*  8-bit data, MSB first (default).  For 16-bit set DFF */
    /*  Enable the peripheral                                */
    SPI1->CR1 |= SPI_CR1_SPE;
}

/*========== Helper:  blocking byte transfer ==========*/
uint8_t SPI1_Transfer(uint8_t tx)
{
    while(!(SPI1->SR & SPI_SR_TXE));   // wait TX buffer empty
    *(__IO uint8_t *)&SPI1->DR = tx;   // half-word access avoids DFF issues
    while(!(SPI1->SR & SPI_SR_RXNE));  // wait RX complete
    return *(__IO uint8_t *)&SPI1->DR;
}

static inline void CS_LOW (void)  { GPIOA->BSRR = GPIO_BSRR_BR4; }
static inline void CS_HIGH(void)  { GPIOA->BSRR = GPIO_BSRR_BS4; }

static void CS_GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* PA4 as push-pull output, high-speed, no pull */
    GPIOA->MODER   &= ~(3u << (4*2));
    GPIOA->MODER   |=  (1u << (4*2));      /* 01 = GPIO Out */
    GPIOA->OTYPER  &= ~(1u << 4);          /* Push-pull    */
    GPIOA->OSPEEDR |=  (2u << (4*2));      /* 10 = High    */
    GPIOA->PUPDR   &= ~(3u << (4*2));      /* No pull      */

    CS_HIGH();                             /* idle-high    */
}



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

//	CS_GPIO_Init();
//	    SPI1_Init();            /* from our earlier snippet */
//
//	    /* Example frame: send 0x9F (JEDEC-ID read for SPI flash) and
//	       capture the three reply bytes. */
//	    uint8_t rx_id[3];

	flash.NSS_Pin = 4;
	flash.NSS_Port = GPIOA;
	flash.clock_pin = SPI_Configurations.Pin._SPI1_.CLK1.PA5;
	flash.miso_pin = SPI_Configurations.Pin._SPI1_.MISO1.PA6;
	flash.mosi_pin = SPI_Configurations.Pin._SPI1_.MOSI1.PA7;


	flash.Port = SPI1;
	flash.clock_phase = SPI_Configurations.Clock_Phase.High_1;
	flash.clock_polarity = SPI_Configurations.Clock_Polarity.High_1;
	flash.type = SPI_Configurations.Type.Master;
	flash.prescaler = SPI_Configurations.Prescaler.CLK_div_16;
	flash.mode = SPI_Configurations.Mode.Full_Duplex_Master;
	flash.frame_format = SPI_Configurations.Frame_Format.MSB_First;
	flash.dma = SPI_Configurations.DMA_Type.TX_DMA_Disable;
	flash.data_format = SPI_Configurations.Data_Format.Bit8;
	flash.crc = SPI_Configurations.CRC_Enable.Disable;


	SPI_Init(&flash);
	SPI_Enable(&flash);



	uint8_t buffer[] = {0,1,2,3,4,5,6,7,8,9};

	for(;;)
	{

		SPI_NSS_Low(&flash);
//		SPI_TRX_Buffer(&flash, buffer, buffer, 10, 10);
		SPI_TRX_Byte(&flash, 0xAA);
		SPI_TRX_Byte(&flash, 0xBB);
		SPI_TRX_Byte(&flash, 0xCC);
		SPI_NSS_High(&flash);
//        CS_LOW();
//        SPI1_Transfer(0x9F);          /* opcode */
//        rx_id[0] = SPI1_Transfer(0x00);
//        rx_id[1] = SPI1_Transfer(0x00);
//        rx_id[2] = SPI1_Transfer(0x00);
//        CS_HIGH();
		Delay_milli(200);


	}
}


