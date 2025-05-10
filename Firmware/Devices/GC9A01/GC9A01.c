/*
 * GC9A01.c
 *
 *  Created on: May 6, 2025
 *      Author: kunal
 */

#include "GC9A01.h"

static  void CS_L(GC9A01_Config *config) { GPIO_Pin_Low(config->cs_port, config->cs_pin); }
static  void CS_H(GC9A01_Config *config) { GPIO_Pin_High(config->cs_port, config->cs_pin); }

static  void DC_C(GC9A01_Config *config) { GPIO_Pin_Low(config->dc_port, config->dc_pin); }
static  void DC_D(GC9A01_Config *config) { GPIO_Pin_High(config->dc_port, config->dc_pin); }

static  void RST_L(GC9A01_Config *config) { GPIO_Pin_Low(config->rst_port, config->rst_pin); }
static  void RST_H(GC9A01_Config *config) { GPIO_Pin_High(config->rst_port, config->rst_pin); }


static void write_command(GC9A01_Config *config, uint8_t cmd)
{
	DC_C(config);
	CS_L(config);
	CS_L(config);
	SPI_TRX_Byte(config->SPI_Port, cmd);
	CS_H(config);
}

static void write_data(GC9A01_Config *config, uint8_t *data, size_t len)
{
	DC_D(config);
	CS_L(config);
	for(int i = 0; i < len; i++) SPI_TRX_Byte(config->SPI_Port, *data++);
	CS_H(config);
}

static inline void GC9A01_write_byte(GC9A01_Config *config,uint8_t val) {
	write_data(config,&val, sizeof(val));
}


static void GC9A01_Write_Data(GC9A01_Config *config, uint8_t *data, uint32_t len)
{
	DC_D(config);
	CS_L(config);

	while(len--)
	{
		SPI_TRX_Byte(config->SPI_Port, *data++);
	}
	CS_H(config);
}

static void GC9A01_Drite_Data16_Repeat(GC9A01_Config *config, uint16_t color, uint32_t count)
{
	DC_D(config);
	CS_L(config);

	while(count--) {
		SPI_TRX_Byte(config->SPI_Port, color >> 8);
		SPI_TRX_Byte(config->SPI_Port, color & 0xFF);
	}
	CS_H(config);
}

static inline void GC9A01_DrawPixelSafe(GC9A01_Config *cfg,
                                        int16_t x, int16_t y,
                                        uint16_t color)
{
    if ((uint16_t)x < GC9A01_WIDTH &&     /* same as 0 ≤ x < width  */
        (uint16_t)y < GC9A01_HEIGHT)      /*      0 ≤ y < height   */
    {
        GC9A01_DrawPixel(cfg, (uint16_t)x, (uint16_t)y, color);
    }
}

/** Initialise GPIO, reset display, execute vendor init sequence */
void GC9A01_Init(GC9A01_Config *config)
{
	GPIO_Pin_Init(config->cs_port, config->cs_pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(config->rst_port, config->rst_pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);

	GPIO_Pin_Init(config->dc_port, config->dc_pin, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.None);

	CS_H(config);


	SPI_Init(config->SPI_Port);
	SPI_Enable(config->SPI_Port);


	CS_H(config);
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

	CS_L(config);
	DC_D(config);
	for(uint32_t i = 0, size = (uint32_t)w * h; i < size; ++i) {
		uint16_t c = img[i];
		SPI_TRX_Byte(config->SPI_Port, c >> 8);
		SPI_TRX_Byte(config->SPI_Port, c & 0xFF);
	}
	CS_H(config);
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

 void GC9A01_Draw_Checks(GC9A01_Config *config, uint16_t color1, uint16_t color2)
 {
 	uint16_t color = 0;
 	for (int x = 0; x < 240; x++)
 	{
 		for (int y = 0; y < 240; y++) {
 			if ((x / 10) % 2 ==  (y / 10) % 2) {
 				color = color1;
 			} else {
 				color = color2;
 			}
 			GC9A01_DrawPixel(config,x,  y, color);;
 		}
 	}
 }

 void GC9A01_DrawCircle(GC9A01_Config *cfg,
                        int16_t xc, int16_t yc,
                        int16_t r,  uint16_t color)
 {
     if (r <= 0) return;

     int32_t d = 1 - r;          /* error term                 */
     int16_t x = 0;
     int16_t y = r;

     while (x <= y)
     {
         /* 8‑way symmetry points */
         GC9A01_DrawPixelSafe(cfg, xc + x, yc + y, color);
         GC9A01_DrawPixelSafe(cfg, xc - x, yc + y, color);
         GC9A01_DrawPixelSafe(cfg, xc + x, yc - y, color);
         GC9A01_DrawPixelSafe(cfg, xc - x, yc - y, color);
         GC9A01_DrawPixelSafe(cfg, xc + y, yc + x, color);
         GC9A01_DrawPixelSafe(cfg, xc - y, yc + x, color);
         GC9A01_DrawPixelSafe(cfg, xc + y, yc - x, color);
         GC9A01_DrawPixelSafe(cfg, xc - y, yc - x, color);

         /* update error term */
         if (d < 0) {
             d += (x << 1) + 3;           /* choose E            */
         } else {
             d += ((x - y) << 1) + 5;     /* choose SE, y‑‑      */
             --y;
         }
         ++x;
     }
 }

 void GC9A01_DrawCircleStroke(GC9A01_Config *cfg,
                              int16_t xc, int16_t yc,
                              int16_t r, int16_t thickness,
                              uint16_t color)
 {
     if (thickness <= 0 || r <= 0) return;
     if (thickness > r) thickness = r;

     for (int16_t t = 0; t < thickness; ++t)
         GC9A01_DrawCircle(cfg, xc, yc, r - t, color);
 }

 void GC9A01_DrawLine(GC9A01_Config *config,uint16_t x0,
                      uint16_t y0,
                      uint16_t x1,
                      uint16_t y1,
                      uint16_t colour)
 {
     /*-------------  Clip against display bounds (optional)  ----------*/
     if (x0 >= 240 || y0 >= 240 || x1 >= 240 || y1 >= 240) return;

     /*-------------  Classic integer Bresenham                         */
     int16_t dx  = (int16_t)abs((int16_t)x1 - (int16_t)x0);
     int16_t sx  = (x0 < x1) ? 1 : -1;
     int16_t dy  = -(int16_t)abs((int16_t)y1 - (int16_t)y0);
     int16_t sy  = (y0 < y1) ? 1 : -1;
     int16_t err = dx + dy;               /* error value         */

     while (1)
     {
         GC9A01_DrawPixel(config,x0, y0, colour);/* single‑pixel write  */
         if (x0 == x1 && y0 == y1) break; /* reached the end     */

         int16_t e2 = (err << 1);         /* 2×err for speed     */
         if (e2 >= dy) { err += dy; x0 += sx; }  /* step in x dir  */
         if (e2 <= dx) { err += dx; y0 += sy; }  /* step in y dir  */
     }
 }

 static const int16_t sin_q15_025deg[361] = {
       0,   143,   286,   429,   572,   715,   858,  1001,  1144,  1287,
    1430,  1573,  1716,  1859,  2002,  2145, /* … keep full list … */
 };

 /* Quarter‑wave symmetry helpers (angle in "deg×4", i.e. 0.25° units) */
 static inline int16_t sin_deg_q15(uint16_t deg_q4)
 {
     deg_q4 &= 0x3FF;                       /* 0‑1023 => 0‑359.75° */
     if (deg_q4 <= 256)      return  sin_q15_025deg[deg_q4];
     else if (deg_q4 <= 512) return  sin_q15_025deg[512 - deg_q4];
     else if (deg_q4 <= 768) return -sin_q15_025deg[deg_q4 - 512];
     else                    return -sin_q15_025deg[1024 - deg_q4];
 }
 static inline int16_t cos_deg_q15(uint16_t deg_q4)
 {
     return sin_deg_q15((deg_q4 + 256) & 0x3FF);   /* cos θ = sin(θ+90°) */
 }


 void GC9A01_DrawArcStroke(GC9A01_Config *cfg,
	                          int16_t xc, int16_t yc, int16_t r,
	                          uint16_t start_deg, uint16_t end_deg,
	                          int16_t thickness, uint16_t color)
	 {
	     if (r <= 0 || thickness <= 0) return;
	     if (thickness > r) thickness = r;

	     float step = 0.5f;                               /* 0.5° resolution */
	     for (float a = start_deg; ; a += step)
	     {
	         if (a >= 360.0f) a -= 360.0f;
	         if (((int)(a*2+0.5f)) == (int)(end_deg*2+0.5f)) break; /* stop at end */

	         float rad = a * (float)M_PI / 180.0f;
	         float s = sinf(rad), c = cosf(rad);

	         for (int16_t t = 0; t < thickness; ++t)
	             GC9A01_DrawPixelSafe(cfg,
	                 xc + (int16_t)((r - t) * c + 0.5f),
	                 yc + (int16_t)((r - t) * s + 0.5f),
	                 color);
	     }
	 }


 /* Optional 1‑pixel wrapper */
void GC9A01_DrawArc(GC9A01_Config *cfg,
                                   int16_t xc, int16_t yc, int16_t r,
                                   uint16_t start_deg, uint16_t end_deg,
                                   uint16_t color)
 {
     GC9A01_DrawArcStroke(cfg, xc, yc, r, start_deg, end_deg, 1, color);
 }
