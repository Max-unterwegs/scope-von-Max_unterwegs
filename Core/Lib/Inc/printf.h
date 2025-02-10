#ifndef __PRINTF_H
#define __PRINTF_H

#include <stdio.h>

int fputc(int ch, FILE *f);

int fgetc(FILE *f);

#define UART_HANDLE huart2
extern UART_HandleTypeDef UART_HANDLE;   //ÉùÃ÷´®¿Ú

#endif
