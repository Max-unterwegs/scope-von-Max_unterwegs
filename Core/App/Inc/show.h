/*
 * @Date: 2025-02-05 17:58:30
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 19:36:04
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Inc\show.h
 */
#ifndef SHOW_H
#define SHOW_H

#include "oled.h"
#include "font.h"
#include "status.h"
#include "key.h"

extern int status;
extern float res[];
extern float voltages[];
extern int functionshow[];
extern float paramshow[];
extern select_Typedef select;
void showinit(void);
void showshow(void);

#endif
