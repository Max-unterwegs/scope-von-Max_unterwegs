/*
 * @Date: 2025-02-05 18:00:12
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 18:27:49
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Inc\status.h
 */
#ifndef STATUS_H
#define STATUS_H

#include "mode.h"

enum statuslist { SCOPE_STATUS, MESSER_STATUS, MU_STATUS };



//status外联调节
void init_status(void);
void main_status(void);

#endif 
