/*
 * @Date: 2025-02-05 17:58:21
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:23:52
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\App\Src\show.c
 * @Description: 显示相关应用函数集
 */
#include "show.h"

char statuschar[4][10] = {"test123", "SCOPE", "MESSER", "MU"};//状态显示用
char functionshowchar[5][10] = {"DC", "CH", "Hz", "Wave", "SHOW"};//功能显示用
char paramshowchar[5][10] = {"DCarr", "CH1mv", "CH2mv", "DCv", "CHf"};//参数显示用
char waveshowchar[4][10] = {"SIN","TRI","SAW","SQU"};//波形显示用
int showparamlist[6] = {3, 1, 2, 0, 4,0};//显示参数顺序列表,其中最后一个为显示分频

/**
 * @brief 显示初始化函数
 * @param void
 * @return void
 * @note OLED初始化
 * @author Max_unterwegs
 */
void showinit(){
    HAL_Delay(20);
    OLED_Init();
}

/**
 * @brief 显示应用函数
 * @param void
 * @return void
 * @note 显示电压、电阻、状态、模式、参数等信息
 * @author Max_unterwegs
 */
void showshow()
{
        OLED_NewFrame();
        // 显示功能
        for (int i = 0; i < 5; i++) {
            char buffer[20];
            switch(i)
            {
                case 0:
                    snprintf(buffer, sizeof(buffer), "%s:%d", functionshowchar[i], functionshow[i]);
                    break;
                case 1:
                    snprintf(buffer, sizeof(buffer), "%s:%d", functionshowchar[i], functionshow[i]);
                    break;
                case 2:
                    snprintf(buffer, sizeof(buffer), "%s:%.1f", functionshowchar[i], ((float)functionshow[i])/10.0);
                    break;
                case 3:
                    snprintf(buffer, sizeof(buffer), "%s:%s", functionshowchar[i], waveshowchar[functionshow[i]]);
                    break;
                case 4:
                    snprintf(buffer, sizeof(buffer), "%s:%d", functionshowchar[i], functionshow[i]);
                    break;
            }
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
        showparamlist[5] = (showparamlist[5] + 1) % functionshow[4];
        snprintf(buffer, sizeof(buffer), "Status: %s", statuschar[status]);
        OLED_PrintASCIIString(0, 0, buffer, &afont8x6, OLED_COLOR_NORMAL);
        OLED_PrintASCIIString(27, 8, "Max-unterwegs^_^", &afont8x6, OLED_COLOR_REVERSED);
        OLED_DrawImage(125-50, 17, &likeImg, OLED_COLOR_NORMAL);
        if(showparamlist[5] == 0)
        {
            OLED_ShowFrame();
        }
}
