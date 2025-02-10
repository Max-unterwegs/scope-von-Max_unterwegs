/*
 * @Author: Max-unterwegs 14068827+max_unterwegs@user.noreply.gitee.com
 * @Date: 2025-02-04 10:27:54
 * @LastEditors: Max-unterwegs 14068827+max_unterwegs@user.noreply.gitee.com
 * @LastEditTime: 2025-02-04 11:17:50
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Inc\oled.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __OLED_H__
#define __OLED_H__

#include "font.h"
#include "main.h"
#include "string.h"

typedef enum {
  OLED_COLOR_NORMAL = 0, // 正常模式 黑底白字
  OLED_COLOR_REVERSED    // 反色模式 白底黑字
} OLED_ColorMode;

#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin, GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin, GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin, GPIO_PIN_SET)

void OLED_Init(void);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);

void OLED_NewFrame(void);
void OLED_ShowFrame(void);
void OLED_SetPixel(uint8_t x, uint8_t y, OLED_ColorMode color);

void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, OLED_ColorMode color);
void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, OLED_ColorMode color);
void OLED_DrawFilledRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, OLED_ColorMode color);
void OLED_DrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, OLED_ColorMode color);
void OLED_DrawFilledTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, OLED_ColorMode color);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
void OLED_DrawFilledCircle(uint8_t x, uint8_t y, uint8_t r, OLED_ColorMode color);
void OLED_DrawEllipse(uint8_t x, uint8_t y, uint8_t a, uint8_t b, OLED_ColorMode color);
void OLED_DrawImage(uint8_t x, uint8_t y, const Image *img, OLED_ColorMode color);

void OLED_PrintASCIIChar(uint8_t x, uint8_t y, char ch, const ASCIIFont *font, OLED_ColorMode color);
void OLED_PrintASCIIString(uint8_t x, uint8_t y, char *str, const ASCIIFont *font, OLED_ColorMode color);
void OLED_PrintString(uint8_t x, uint8_t y, char *str, const Font *font, OLED_ColorMode color);

#endif // __OLED_H__
