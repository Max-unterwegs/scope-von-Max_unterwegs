/*
 * @Date: 2025-02-05 17:58:21
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 19:41:21
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Src\show.c
 */
#include "show.h"

char statuschar[3][10] = {"SCOPE", "MESSER", "M-U"};
char functionshowchar[5][10] = {"DC", "CH", "BUZZER", "LED", "OLED"};
char paramshowchar[5][10] = {"DCarr", "CH1mv", "CH2mv", "DCv", "CHf"};

void showinit(){
    HAL_Delay(20);
    OLED_Init();
}

/**
 * @brief 显示电压、电阻、状态、模式、参数等信息
 */
void showshow()
{
    OLED_NewFrame();

    // 显示状态
    OLED_PrintASCIIString(0, 0, statuschar[status], &afont12x6, OLED_COLOR_NORMAL);

    // 显示功能
    for (int i = 0; i < 5; i++) {
        if (select.forp == 0 && select.index == i) {
            OLED_PrintASCIIString(0, (i + 3) * 12, functionshowchar[i], &afont12x6, OLED_COLOR_REVERSED);
        } else {
            OLED_PrintASCIIString(0, (i + 3) * 12, functionshowchar[i], &afont12x6, OLED_COLOR_NORMAL);
        }
    }

    // 显示参数
    for (int i = 0; i < 5; i++) {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%s: %.2f", paramshowchar[i], paramshow[i]);
        if (select.forp == 1 && select.index == i) {
            OLED_PrintASCIIString(64, i * 12, buffer, &afont12x6, OLED_COLOR_REVERSED);
        } else {
            OLED_PrintASCIIString(64, i * 12, buffer, &afont12x6, OLED_COLOR_NORMAL);
        }
    }

    // 显示电压
    for (int i = 0; i < 3; i++) {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Voltage %d: %.2fV", i + 1, voltages[i]);
        OLED_PrintASCIIString(0, (i + 8) * 12, buffer, &afont12x6, OLED_COLOR_REVERSED);
    }

    // 显示电阻
    for (int i = 0; i < 2; i++) {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Resistor %d: %.2fΩ", i + 1, res[i]);
        OLED_PrintASCIIString(64, (i + 8) * 12, buffer, &afont12x6, OLED_COLOR_REVERSED);
    }



    OLED_ShowFrame();
}
