/*
 * GC9A01.c
 *
 *  Created on: May 6, 2025
 *      Author: kunal
 */

#include "GC9A01.h"

static const uint8_t gc9a01_init_seq[] = {
		0xEF, 0 ,                                      // Inter register enable 2
		0xEB, 1 , 0x14,
		0xFE, 0 ,
		0xEF, 0 ,
		0xEB, 1 , 0x14,
		0x84, 1 , 0x40,
		0x85, 1 , 0xFF,
		0x86, 1 , 0xFF,
		0x87, 1 , 0xFF,
		0x88, 1 , 0x0A,
		0x89, 1 , 0x21,
		0x8A, 1 , 0x00,
		0x8B, 1 , 0x80,
		0x8C, 1 , 0x01,
		0x8D, 1 , 0x01,
		0x8E, 1 , 0xFF,
		0x8F, 1 , 0xFF,
		0xB6, 2 , 0x00, 0x20,
		0x36, 1 , 0x08,          // Memory Access Control (RGB/BGR & rotation)
		0x3A, 1 , 0x05,          // Interface Pixel Format = 16‑bit
		0x90, 4 , 0x08,0x08,0x08,0x08,
		0xBD, 1 , 0x06,
		0xBC, 1 , 0x00,
		0xFF, 3 , 0x60,0x01,0x04,
		0xC3, 1 , 0x13,
		0xC4, 1 , 0x13,
		0xC9, 1 , 0x22,
		0xBE, 1 , 0x11,
		0xE1, 2 , 0x10,0x0E,
		0xDF, 3 , 0x21,0x0C,0x02,
		0xF0, 6 , 0x45,0x09,0x08,0x08,0x26,0x2A,
		0xF1, 6 , 0x43,0x70,0x72,0x36,0x37,0x6F,
		0xF2, 6 , 0x45,0x09,0x08,0x08,0x26,0x2A,
		0xF3, 6 , 0x43,0x70,0x72,0x36,0x37,0x6F,
		0xED, 2 , 0x1B,0x0B,
		0xAE, 1 , 0x77,
		0xCD, 1 , 0x63,
		0x70, 7 , 0x07,0x07,0x04,0x0E,0x0F,0x09,0x07,
		0xE8, 1 , 0x34,
		0x62,12 , 0x18,0x0D,0x71,0xED,0x70,0x70,0x18,0x0F,0x71,0xEF,0x70,0x70,
		0x63,12 , 0x18,0x11,0x71,0xF1,0x70,0x70,0x18,0x13,0x71,0xF3,0x70,0x70,
		0x64, 7 , 0x28,0x29,0xF1,0x01,0xF1,0x00,0x07,
		0x66,27 , 0x3C,0x00,0xCD,0x67,0x45,0x45,0x10,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,
		0x67,10 , 0x00,0x3C,0x00,0x00,0x00,0x01,0x54,0x10,0x32,0x98,
		0x74, 7 , 0x10,0x85,0x80,0x00,0x00,0x4E,0x00,
		0x98, 2 , 0x3E,0x07,
		0x35, 1 , 0x00,
		0x21, 0 ,                                      // Inversion ON
		0x11, 0x80,                                     // Sleep out + delay
		0x29, 0x80,                                     // Display ON + delay
		0x00                                             // End marker
};




//static  void CS_L(GC9A01_Config *config) { GPIO_Pin_Low(config->cs_port, config->cs_pin); }
//static  void CS_H(GC9A01_Config *config) { GPIO_Pin_High(config->cs_port, config->cs_pin); }




//void GC9A01_write_command(uint8_t cmd) {
//    GC9A01_set_data_command(OFF);
//    GC9A01_set_chip_select(OFF);
//    GC9A01_spi_tx(&cmd, sizeof(cmd));
//    GC9A01_set_chip_select(ON);
//}


static  void DC_C(GC9A01_Config *config) { GPIO_Pin_Low(config->dc_port, config->dc_pin); }
static  void DC_D(GC9A01_Config *config) { GPIO_Pin_High(config->dc_port, config->dc_pin); }

static  void RST_L(GC9A01_Config *config) { GPIO_Pin_Low(config->rst_port, config->rst_pin); }
static  void RST_H(GC9A01_Config *config) { GPIO_Pin_High(config->rst_port, config->rst_pin); }




static void write_command(GC9A01_Config *config, uint8_t cmd)
{
	DC_C(config);
	SPI_NSS_Low(config->SPI_Port);
	SPI_TRX_Byte(config->SPI_Port, cmd);
	SPI_NSS_High(config->SPI_Port);
}

static void write_data(GC9A01_Config *config, uint8_t *data, size_t len)
{
	DC_D(config);
	SPI_NSS_Low(config->SPI_Port);
	for(int i = 0; i < len; i++) SPI_TRX_Byte(config->SPI_Port, *data++);
	SPI_NSS_High(config->SPI_Port);
}

static inline void GC9A01_write_byte(GC9A01_Config *config,uint8_t val) {
	write_data(config,&val, sizeof(val));
}
//
//
//static void GC9A01_Write_CMD(GC9A01_Config *config, uint8_t cmd)
//{
//	DC_C(config);
//	SPI_NSS_Low(config->SPI_Port);
//	SPI_TRX_Byte(config->SPI_Port, cmd);
//	SPI_NSS_High(config->SPI_Port);
//}

static void GC9A01_Write_Data(GC9A01_Config *config, uint8_t *data, uint32_t len)
{
	DC_D(config);
	SPI_NSS_Low(config->SPI_Port);

	while(len--)
	{
		SPI_TRX_Byte(config->SPI_Port, *data++);
	}
	SPI_NSS_High(config->SPI_Port);
}

static void GC9A01_Drite_Data16_Repeat(GC9A01_Config *config, uint16_t color, uint32_t count)
{
	DC_D(config);
	SPI_NSS_Low(config->SPI_Port);

	while(count--) {
		SPI_TRX_Byte(config->SPI_Port, color >> 8);
		SPI_TRX_Byte(config->SPI_Port, color & 0xFF);
	}
	SPI_NSS_High(config->SPI_Port);
}

/** Initialise GPIO, reset display, execute vendor init sequence */
void GC9A01_Init(GC9A01_Config *config)
{

	GPIO_Pin_Init(config->rst_port, config->rst_pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(config->dc_port, config->dc_pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);



	SPI_Init(config->SPI_Port);
	SPI_Enable(config->SPI_Port);


	SPI_NSS_High(config->SPI_Port);
	Delay_milli(150);
	RST_L(config);
	Delay_milli(150);
	RST_H(config);
	Delay_milli(150);

	write_command(config,0xEF);

	write_command(config,0xEB);
	GC9A01_write_byte(config,0x14);

	write_command(config,0xFE);
	write_command(config,0xEF);

	write_command(config,0xEB);
	GC9A01_write_byte(config,0x14);

	write_command(config,0x84);
	GC9A01_write_byte(config,0x40);

	write_command(config,0x85);
	GC9A01_write_byte(config,0xFF);

	write_command(config,0x86);
	GC9A01_write_byte(config,0xFF);

	write_command(config,0x87);
	GC9A01_write_byte(config,0xFF);

	write_command(config,0x88);
	GC9A01_write_byte(config,0x0A);

	write_command(config,0x89);
	GC9A01_write_byte(config,0x21);

	write_command(config,0x8A);
	GC9A01_write_byte(config,0x00);

	write_command(config,0x8B);
	GC9A01_write_byte(config,0x80);

	write_command(config,0x8C);
	GC9A01_write_byte(config,0x01);

	write_command(config,0x8D);
	GC9A01_write_byte(config,0x01);

	write_command(config,0x8E);
	GC9A01_write_byte(config,0xFF);

	write_command(config,0x8F);
	GC9A01_write_byte(config,0xFF);


	write_command(config,0xB6);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x00);

	write_command(config,0x36);

	GC9A01_write_byte(config,0x18);

	write_command(config,0x3A);
	GC9A01_write_byte(config,0x05);

	write_command(config,0x90);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x08);

	write_command(config,0xBD);
	GC9A01_write_byte(config,0x06);

	write_command(config,0xBC);
	GC9A01_write_byte(config,0x00);

	write_command(config,0xFF);
	GC9A01_write_byte(config,0x60);
	GC9A01_write_byte(config,0x01);
	GC9A01_write_byte(config,0x04);

	write_command(config,0xC3);
	GC9A01_write_byte(config,0x13);
	write_command(config,0xC4);
	GC9A01_write_byte(config,0x13);

	write_command(config,0xC9);
	GC9A01_write_byte(config,0x22);

	write_command(config,0xBE);
	GC9A01_write_byte(config,0x11);

	write_command(config,0xE1);
	GC9A01_write_byte(config,0x10);
	GC9A01_write_byte(config,0x0E);

	write_command(config,0xDF);
	GC9A01_write_byte(config,0x21);
	GC9A01_write_byte(config,0x0c);
	GC9A01_write_byte(config,0x02);

	write_command(config,0xF0);
	GC9A01_write_byte(config,0x45);
	GC9A01_write_byte(config,0x09);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x26);
	GC9A01_write_byte(config,0x2A);

	write_command(config,0xF1);
	GC9A01_write_byte(config,0x43);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x72);
	GC9A01_write_byte(config,0x36);
	GC9A01_write_byte(config,0x37);
	GC9A01_write_byte(config,0x6F);

	write_command(config,0xF2);
	GC9A01_write_byte(config,0x45);
	GC9A01_write_byte(config,0x09);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x26);
	GC9A01_write_byte(config,0x2A);

	write_command(config,0xF3);
	GC9A01_write_byte(config,0x43);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x72);
	GC9A01_write_byte(config,0x36);
	GC9A01_write_byte(config,0x37);
	GC9A01_write_byte(config,0x6F);

	write_command(config,0xED);
	GC9A01_write_byte(config,0x1B);
	GC9A01_write_byte(config,0x0B);

	write_command(config,0xAE);
	GC9A01_write_byte(config,0x77);

	write_command(config,0xCD);
	GC9A01_write_byte(config,0x63);

	write_command(config,0x70);
	GC9A01_write_byte(config,0x07);
	GC9A01_write_byte(config,0x07);
	GC9A01_write_byte(config,0x04);
	GC9A01_write_byte(config,0x0E);
	GC9A01_write_byte(config,0x0F);
	GC9A01_write_byte(config,0x09);
	GC9A01_write_byte(config,0x07);
	GC9A01_write_byte(config,0x08);
	GC9A01_write_byte(config,0x03);

	write_command(config,0xE8);
	GC9A01_write_byte(config,0x34);

	write_command(config,0x62);
	GC9A01_write_byte(config,0x18);
	GC9A01_write_byte(config,0x0D);
	GC9A01_write_byte(config,0x71);
	GC9A01_write_byte(config,0xED);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x18);
	GC9A01_write_byte(config,0x0F);
	GC9A01_write_byte(config,0x71);
	GC9A01_write_byte(config,0xEF);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x70);

	write_command(config,0x63);
	GC9A01_write_byte(config,0x18);
	GC9A01_write_byte(config,0x11);
	GC9A01_write_byte(config,0x71);
	GC9A01_write_byte(config,0xF1);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x18);
	GC9A01_write_byte(config,0x13);
	GC9A01_write_byte(config,0x71);
	GC9A01_write_byte(config,0xF3);
	GC9A01_write_byte(config,0x70);
	GC9A01_write_byte(config,0x70);

	write_command(config,0x64);
	GC9A01_write_byte(config,0x28);
	GC9A01_write_byte(config,0x29);
	GC9A01_write_byte(config,0xF1);
	GC9A01_write_byte(config,0x01);
	GC9A01_write_byte(config,0xF1);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x07);

	write_command(config,0x66);
	GC9A01_write_byte(config,0x3C);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0xCD);
	GC9A01_write_byte(config,0x67);
	GC9A01_write_byte(config,0x45);
	GC9A01_write_byte(config,0x45);
	GC9A01_write_byte(config,0x10);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x00);

	write_command(config,0x67);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x3C);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x01);
	GC9A01_write_byte(config,0x54);
	GC9A01_write_byte(config,0x10);
	GC9A01_write_byte(config,0x32);
	GC9A01_write_byte(config,0x98);

	write_command(config,0x74);
	GC9A01_write_byte(config,0x10);
	GC9A01_write_byte(config,0x85);
	GC9A01_write_byte(config,0x80);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x00);
	GC9A01_write_byte(config,0x4E);
	GC9A01_write_byte(config,0x00);

	write_command(config,0x98);
	GC9A01_write_byte(config,0x3e);
	GC9A01_write_byte(config,0x07);

	write_command(config,0x35);
	write_command(config,0x21);

	write_command(config,0x11);
    Delay_milli(120);
    write_command(config,0x29);
    Delay_milli(20);




}

/** Set an address window (inclusive X0..X1, Y0..Y1) ready for RAM write */
void GC9A01_SetAddressWindow(GC9A01_Config *config,
		uint16_t x0, uint16_t y0,
		uint16_t x1, uint16_t y1)
{
	uint8_t buf[4];
	write_command(config, 0x2A);           // CASET
	buf[0] = x0 >> 8; buf[1] = x0 & 0xFF;
	buf[2] = x1 >> 8; buf[3] = x1 & 0xFF;
	GC9A01_Write_Data(config, buf, 4);

	write_command(config, 0x2B);           // RASET
	buf[0] = y0 >> 8; buf[1] = y0 & 0xFF;
	buf[2] = y1 >> 8; buf[3] = y1 & 0xFF;
	GC9A01_Write_Data(config, buf, 4);

	write_command(config, 0x2C);           // RAMWR
}

/** Push one RGB565 pixel.  _Must_ be preceded by SetAddressWindow */
void GC9A01_PushColor(GC9A01_Config *config, uint16_t rgb565)
{

	uint8_t hi = rgb565 >> 8, lo = rgb565 & 0xFF;
	uint8_t buf[2] = {hi, lo};
	GC9A01_Write_Data(config, buf, 2);
}

/** Convenience helpers */
void GC9A01_DrawPixel(GC9A01_Config *config, uint16_t x, uint16_t y, uint16_t rgb)
{
	if(x >= GC9A01_WIDTH || y >= GC9A01_HEIGHT) return;
	GC9A01_SetAddressWindow(config, x, y, x, y);
	GC9A01_PushColor(config, rgb);
}

void GC9A01_Fill(GC9A01_Config *config, uint16_t rgb)
{
	GC9A01_SetAddressWindow(config, 0, 0, GC9A01_WIDTH-1, GC9A01_HEIGHT-1);
	GC9A01_Drite_Data16_Repeat(config, rgb, (uint32_t)GC9A01_WIDTH * GC9A01_HEIGHT);
}

void GC9A01_DrawImage  (GC9A01_Config *config, uint16_t x, uint16_t y,
		uint16_t w, uint16_t h, const uint16_t *img)
{
	if((x >= GC9A01_WIDTH) || (y >= GC9A01_HEIGHT)) return;
	if((x + w - 1) >= GC9A01_WIDTH)  w = GC9A01_WIDTH  - x;
	if((y + h - 1) >= GC9A01_HEIGHT) h = GC9A01_HEIGHT - y;

	GC9A01_SetAddressWindow(config, x, y, x + w - 1, y + h - 1);

	SPI_NSS_Low(config->SPI_Port);
	DC_D(config);
	for(uint32_t i = 0, size = (uint32_t)w * h; i < size; ++i) {
		uint16_t c = img[i];
		SPI_TRX_Byte(config->SPI_Port, c >> 8);
		SPI_TRX_Byte(config->SPI_Port, c & 0xFF);
	}
	SPI_NSS_High(config->SPI_Port);
}

static const uint8_t gc9a01_font5x7[95][5] = {
    /* 0x20 ‘ ’ */ {0,0,0,0,0},           /* 0x21 ‘!’ */ {0x00,0x00,0x5F,0x00,0x00},
    /* 0x22 ‘\"*/ {0x00,0x07,0x00,0x07,0x00}, /* … (snip, include all glyphs through 0x7E) */
    /* 0x7E ‘~’ */ {0x08,0x04,0x08,0x10,0x08}
};


void GC9A01_DrawChar(GC9A01_Config *lcd,
                     uint16_t x, uint16_t y,
                     char c,
                     uint16_t fg, uint16_t bg)
{
    if(c < 0x20 || c > 0x7E) c = '?';
    const uint8_t *glyph = gc9a01_font5x7[c - 0x20];

    for(uint8_t col = 0; col < 5; ++col) {
        uint8_t bits = glyph[col];
        for(uint8_t row = 0; row < 8; ++row) {
            uint16_t color = (bits & 0x01) ? fg : bg;
            GC9A01_DrawPixel(lcd, x + col, y + row, color);
            bits >>= 1;
        }
    }
    /* 1‑pixel column of background colour as spacing */
    for(uint8_t row = 0; row < 8; ++row)
        GC9A01_DrawPixel(lcd, x + 5, y + row, bg);
}

void GC9A01_EraseChar(GC9A01_Config *lcd,
                      uint16_t x, uint16_t y,
                      uint16_t bg)
{
    GC9A01_SetAddressWindow(lcd, x, y, x + 5, y + 7);
    GC9A01_Drite_Data16_Repeat(lcd, bg, 6 * 8);
}

 void GC9A01_PrintNumber(GC9A01_Config *lcd,
                               uint16_t x, uint16_t y,
                               int value,
                               uint16_t fg, uint16_t bg)
{
    char buf[5];
    int n = 0;
    if(value == 0) buf[n++] = '0';
    else {
        int v = value;
        char rev[5];
        while(v && n < 5) { rev[n++] = (v % 10) + '0'; v /= 10; }
        for(int i = 0; i < n; ++i) buf[i] = rev[n-1-i];
    }
    for(int i = 0; i < n; ++i) {
        GC9A01_DrawChar(lcd, x + i*6, y, buf[i], fg, bg);
        /* erase any trailing old digits */
        Delay_s(1);
        GC9A01_EraseChar(lcd, x + (i+1)*6, y, bg);
    }
}
