/*
 * @Date: 2025-02-05 17:58:21
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-25 23:05:14
 * @FilePath: \MDK-ARMd:\Mein_Werk\meine code\stm32projekt\scope\Core\App\Src\show.c
 */
#include "show.h"

char statuschar[4][10] = {"test123", "SCOPE", "MESSER", "MU"};
char functionshowchar[5][10] = {"DC", "CH", "BUZZER", "OLED", "SHOW"};
char paramshowchar[5][10] = {"DCarr", "CH1mv", "CH2mv", "DCv", "CHf"};
int showparamlist[5] = {3, 1, 2, 0, 4};


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
        // 显示功能
        for (int i = 0; i < 5; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%s:%d", functionshowchar[i], functionshow[i]);
            if (select.forp == 0 && select.index == i) {
                OLED_PrintASCIIString(0, (i + 1) * 8, buffer, &afont8x6, OLED_COLOR_REVERSED);
            } else {
                OLED_PrintASCIIString(0, (i + 1) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
            }
        }

        // 显示参数
        for (int i = 0; i < 5; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%s:%.2f", paramshowchar[showparamlist[i]], paramshow[showparamlist[i]]);
            if (select.forp == 1 && select.index == i) {
                OLED_PrintASCIIString(0, (i + 6) * 8, buffer, &afont8x6, OLED_COLOR_REVERSED);
            } else {
                OLED_PrintASCIIString(0, (i + 6) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
            }
        }

        // 显示电压
        for (int i = 0; i < 3; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "Voltage %d: %.2fV", i + 1, voltages[i]);
            OLED_PrintASCIIString(0, (i + 11) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
        }

        // 显示电阻
        for (int i = 0; i < 2; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "Resistor %d: %.2fΩ", i + 1, res[i]);
            OLED_PrintASCIIString(0, (i + 14) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
        }

        // 显示状态
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Status: %s", statuschar[status]);
        OLED_PrintASCIIString(0, 0, buffer, &afont8x6, OLED_COLOR_NORMAL);
        OLED_PrintASCIIString(27, 8, "Max-unterwegs^_^", &afont8x6, OLED_COLOR_REVERSED);
        OLED_DrawImage(125-50, 17, &likeImg, OLED_COLOR_NORMAL);
        OLED_ShowFrame();
    

    
}
