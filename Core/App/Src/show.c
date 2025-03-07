/*
 * @Date: 2025-02-05 17:58:21
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 20:23:52
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\App\Src\show.c
 * @Description: ��ʾ���Ӧ�ú�����
 */
#include "show.h"

char statuschar[4][10] = {"test123", "SCOPE", "MESSER", "MU"};//״̬��ʾ��
char functionshowchar[5][10] = {"DC", "CH", "Hz", "Wave", "SHOW"};//������ʾ��
char paramshowchar[5][10] = {"DCarr", "CH1mv", "CH2mv", "DCv", "CHf"};//������ʾ��
char waveshowchar[4][10] = {"SIN","TRI","SAW","SQU"};//������ʾ��
int showparamlist[6] = {3, 1, 2, 0, 4,0};//��ʾ����˳���б�,�������һ��Ϊ��ʾ��Ƶ

/**
 * @brief ��ʾ��ʼ������
 * @param void
 * @return void
 * @note OLED��ʼ��
 * @author Max_unterwegs
 */
void showinit(){
    HAL_Delay(20);
    OLED_Init();
}

/**
 * @brief ��ʾӦ�ú���
 * @param void
 * @return void
 * @note ��ʾ��ѹ�����衢״̬��ģʽ����������Ϣ
 * @author Max_unterwegs
 */
void showshow()
{
        OLED_NewFrame();
        // ��ʾ����
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

        // ��ʾ����
        for (int i = 0; i < 5; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "%s:%.2f", paramshowchar[showparamlist[i]], paramshow[showparamlist[i]]);
            if (select.forp == 1 && select.index == i) {
                OLED_PrintASCIIString(0, (i + 6) * 8, buffer, &afont8x6, OLED_COLOR_REVERSED);
            } else {
                OLED_PrintASCIIString(0, (i + 6) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
            }
        }

        // ��ʾ��ѹ
        for (int i = 0; i < 3; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "Voltage %d: %.2fV", i + 1, voltages[i]);
            OLED_PrintASCIIString(0, (i + 11) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
        }

        // ��ʾ����
        for (int i = 0; i < 2; i++) {
            char buffer[20];
            snprintf(buffer, sizeof(buffer), "Resistor %d: %.2f��", i + 1, res[i]);
            OLED_PrintASCIIString(0, (i + 14) * 8, buffer, &afont8x6, OLED_COLOR_NORMAL);
        }

        // ��ʾ״̬
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
