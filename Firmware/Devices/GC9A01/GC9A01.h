/*
 * GC9A01.h
 *
 *  Created on: May 6, 2025
 *      Author: kunal
 */

#ifndef GC9A01_GC9A01_H_
#define GC9A01_GC9A01_H_

#include "main.h"
#include "SPI/SPI.h"
#include "GPIO/GPIO.h"

#define GC9A01_WIDTH   240U
#define GC9A01_HEIGHT  240U

/** Handle describing the physical connections */
typedef struct GC9A01_Config{
    SPI_Config   *SPI_Port;                 /*!< SPI peripheral (already clock‑enabled)        */
    GPIO_TypeDef  *cs_port; uint16_t  cs_pin;   /*!< Chip‑select  (active‑low)                    */
    GPIO_TypeDef  *dc_port; uint16_t  dc_pin;   /*!< Data/Command select – 0:Cmd  1:Data          */
    GPIO_TypeDef  *rst_port;uint16_t  rst_pin;  /*!< Hardware reset (active‑low). Optional (NULL) */
    void (*delay_ms)(uint32_t ms);              /*!< Millisecond delay callback                   */
} GC9A01_Config;

#ifdef __cplusplus
extern "C" {
#endif

/** Initialise GPIO, reset display, execute vendor init sequence */
void GC9A01_Init(GC9A01_Config *config);

/** Set an address window (inclusive X0..X1, Y0..Y1) ready for RAM write */
void GC9A01_SetAddressWindow(GC9A01_Config *config,
                             uint16_t x0, uint16_t y0,
                             uint16_t x1, uint16_t y1);

/** Push one RGB565 pixel.  _Must_ be preceded by SetAddressWindow */
void GC9A01_PushColor(GC9A01_Config *config, uint16_t rgb565);

/** Convenience helpers */
void GC9A01_DrawPixel  (GC9A01_Config *config, uint16_t x, uint16_t y, uint16_t rgb);
void GC9A01_Fill       (GC9A01_Config *config, uint16_t rgb);
void GC9A01_DrawImage  (GC9A01_Config *config, uint16_t x, uint16_t y,
                        uint16_t w, uint16_t h, const uint16_t *img);

void GC9A01_EraseChar(GC9A01_Config *lcd,
                      uint16_t x, uint16_t y,
                      uint16_t bg);
void GC9A01_DrawChar(GC9A01_Config *lcd,
                     uint16_t x, uint16_t y,
                     char c,
                     uint16_t fg, uint16_t bg);
void GC9A01_PrintNumber(GC9A01_Config *lcd,
                              uint16_t x, uint16_t y,
                              int value,
                              uint16_t fg, uint16_t bg);

void GC9A01_DrawCircle(GC9A01_Config *cfg,
                       int16_t xc, int16_t yc,
                       int16_t r,  uint16_t color);

void GC9A01_DrawCircleStroke(GC9A01_Config *cfg,
                             int16_t xc, int16_t yc,
                             int16_t r, int16_t thickness,
                             uint16_t color);

void GC9A01_Draw_Checks(GC9A01_Config *config, uint16_t color1, uint16_t color2);

void GC9A01_DrawLine(GC9A01_Config *config,uint16_t x0,
                     uint16_t y0,
                     uint16_t x1,
                     uint16_t y1,
                     uint16_t colour);

void GC9A01_DrawArcStroke(GC9A01_Config *cfg,
                          int16_t  xc, int16_t  yc,
                          int16_t  r,
                          uint16_t start_deg, uint16_t end_deg,
                          int16_t  thickness,
                          uint16_t color);
void GC9A01_DrawArc(GC9A01_Config *cfg,
                                   int16_t xc, int16_t yc, int16_t r,
                                   uint16_t start_deg, uint16_t end_deg,
                                   uint16_t color);
#ifdef __cplusplus
}
#endif

#endif /* GC9A01_GC9A01_H_ */
