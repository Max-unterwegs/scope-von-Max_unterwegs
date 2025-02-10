/*
 * @Date: 2025-02-04 10:54:15
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 18:31:40
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Inc\send.h
 */
#ifndef __SEND_H
#define __SEND_H

#include "valuepack.h"
#include "printf.h"

void sendinit(void);
void sendvolt(float *sendbuffer);
void sendres(float *sendbuffer);

#endif
