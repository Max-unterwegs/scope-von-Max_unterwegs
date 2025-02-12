/*
 * @Date: 2025-02-04 10:30:55
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-12 21:09:29
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\Lib\Src\key.c
 */
#include "key.h"

select_Typedef select = {1,0};
volatile uint8_t EC11_A_Last = 0; // 上一次A相状态
volatile uint8_t EC11_B_Last = 0; // 上一次B相状态
int8_t B_level = 0, encoder_value = 0;
uint8_t paramlist[5] = {3, 1, 2, 0, 4};

/**
 * @brief  按键扫描函数
 * @param  GPIOx：x 可以是 A，B，C，D或者 E
 * @param  GPIO_Pin：待读取的端口位
 * @retval KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    KEY_TypeDef *KeyTemp; // 定义一个按键类型的指针变量
    uint8_t ReturnTemp; // 定义一个返回值变量

    // 检查按下的是哪一个按钮
    switch ((uint32_t)GPIOx)
    {
        case ((uint32_t)key1_GPIO_Port): // 如果按下的是KEYA
            switch (GPIO_Pin)
            {
            case key1_Pin: // 如果按下的是KEY1的引脚
                KeyTemp = &Key[0]; // 将KeyTemp指向Key数组的第一个元素
                break;
            case key2_Pin: // 如果按下的是KEY2的引脚
                KeyTemp = &Key[1]; // 将KeyTemp指向Key数组的第二个元素
                break;
            case key3_Pin: // 如果按下的是KEY3的引脚
                KeyTemp = &Key[2]; // 将KeyTemp指向Key数组的第三个元素
                break;
            // port和pin不匹配
            default:
                //printf("error: GPIO port pin not match\r\n"); // 打印错误信息
                return KEY_IDLE; // 返回空闲状态
            }
            break;
       
        case ((uint32_t)key4_GPIO_Port): // 如果按下的是KEY4
            switch (GPIO_Pin)
            {
            case key4_Pin: // 如果按下的是KEY4的引脚
                KeyTemp = &Key[3]; // 将KeyTemp指向Key数组的第四个元素
                break;
            case key5_Pin: // 如果按下的是KEY5的引脚
                KeyTemp = &Key[4]; // 将KeyTemp指向Key数组的第五个元素
                break;
            // port和pin不匹配
            default:
                //printf("error: GPIO port pin not match\r\n"); // 打印错误信息
                return KEY_IDLE; // 返回空闲状态
            }
            break;
        default:
            //printf("error: key do not exist\r\n"); // 打印错误信息
            return KEY_IDLE; // 返回空闲状态
        }

    KeyTemp->KeyPhysic = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin); // 读取按键的物理状态

    /* 检测按下、松开、长按 */
    switch (KeyTemp->KeyLogic)
    {
    case KEY_ON:
        switch (KeyTemp->KeyPhysic)
        {
        //（1，1）中将关闭计数清零，并对开启计数累加直到切换至逻辑长按状态
        case KEY_ON:
            KeyTemp->KeyOFFCounts = 0; // 关闭计数清零
            KeyTemp->KeyONCounts++; // 开启计数累加
            KeyTemp->MulClickCounts = 0; // 多击计数清零
            
            if(KeyTemp->MulClickFlag == KEY_2ClICK){ // 如果预备双击状态，但仍然只有一次点击
                if (KeyTemp->KeyONCounts >= HOLD_COUNTS){ // 如果开启计数达到长按计数
                    KeyTemp->KeyONCounts = 0; // 开启计数清零
                    KeyTemp->KeyLogic = KEY_HOLD; // 切换至逻辑长按状态
                    return KEY_HOLD; // 返回长按状态
                }
            }
            return KEY_IDLE; // 返回空闲状态

        //（1，0）中对关闭计数累加直到切换至逻辑关闭状态
        case KEY_OFF:
            KeyTemp->KeyOFFCounts++; // 关闭计数累加
            
            if (KeyTemp->KeyOFFCounts >= SHAKES_COUNTS) // 如果关闭计数达到抖动计数
            {
                KeyTemp->KeyLogic = KEY_OFF; // 切换至逻辑关闭状态
                KeyTemp->KeyOFFCounts = 0; // 关闭计数清零
                
                return KEY_OFF; // 返回关闭状态
            }
            return KEY_IDLE; // 返回空闲状态

        default:
            break;
        }

    case KEY_OFF:
        switch (KeyTemp->KeyPhysic)
        {
        //（0，1）中对开启计数累加直到切换至逻辑开启状态
        case KEY_ON:
            (KeyTemp->KeyONCounts)++; // 开启计数累加
            if (KeyTemp->KeyONCounts >= SHAKES_COUNTS) // 如果开启计数达到抖动计数
            {
                KeyTemp->KeyLogic = KEY_ON; // 切换至逻辑开启状态
                KeyTemp->KeyONCounts = 0; // 开启计数清零

                if(KeyTemp->MulClickFlag == KEY_1ClICK) // 如果是单击状态
                {
                    KeyTemp->MulClickFlag = KEY_2ClICK; // 切换至预备双击状态
                    return KEY_ON; // 返回开启状态
                }
                else
                {
                    if(KeyTemp->MulClickFlag != (KEY_MAX_MULCLICK + 1)) // 如果多击状态未达到最大值
                    {
                        KeyTemp->MulClickFlag++; // 多击状态累加
                        KeyTemp->MulClickCounts = 0; // 多击计数清零
                    }					
                }		
                // return KEY_ON; // 返回开启状态		
            }
            return KEY_IDLE; // 返回空闲状态

        //（0，0）中将开启计数清零，对多击计数
        case KEY_OFF:
            (KeyTemp->KeyONCounts) = 0; // 开启计数清零
            if(KeyTemp->MulClickFlag != KEY_1ClICK) // 如果不是单击状态
            {
                if(KeyTemp->MulClickCounts++ > MULTIPLE_CLICK_COUNTS) // 如果多击计数超过最大间隔时间
                {
                    ReturnTemp = KeyTemp->MulClickFlag - 1; // 返回多击状态减一
                    KeyTemp->MulClickCounts = 0; // 多击计数清零
                    KeyTemp->MulClickFlag = KEY_1ClICK; // 切换至单击状态
                    return ReturnTemp; // 返回多击状态
                }
            }
            
            return KEY_IDLE; // 返回空闲状态
        default:
            break;
        }

    case KEY_HOLD:
        switch (KeyTemp->KeyPhysic)
        {
        //（2，1）对关闭计数清零
        case KEY_ON:
            KeyTemp->KeyOFFCounts = 0; // 关闭计数清零
            KeyTemp->MulClickFlag = 0; // 多击状态清零
            KeyTemp->MulClickCounts = 0; // 多击计数清零
            return KEY_HOLD; // 返回长按状态
        //（2，0）对关闭计数累加直到切换至逻辑关闭状态
        case KEY_OFF:
            (KeyTemp->KeyOFFCounts)++; // 关闭计数累加
            if (KeyTemp->KeyOFFCounts >= SHAKES_COUNTS) // 如果关闭计数达到抖动计数
            {
                KeyTemp->KeyLogic = KEY_OFF; // 切换至逻辑关闭状态
                KeyTemp->KeyOFFCounts = 0; // 关闭计数清零
                return KEY_OFF; // 返回关闭状态
            }
            return KEY_IDLE; // 返回空闲状态

        default:
            break;
        }

    
    default:
        break;
    }
    return KEY_ERROR; // 返回错误状态
}


void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    B_level = HAL_GPIO_ReadPin(key5_GPIO_Port, key5_Pin);
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{

        if(B_level==1 && HAL_GPIO_ReadPin(key5_GPIO_Port,key5_Pin) == 0) 
		{
			encoder_value = 1;//正转
		}
		else if(B_level==0 && HAL_GPIO_ReadPin(key5_GPIO_Port,key5_Pin) == 1)
		{
			encoder_value = -1;//反转
        }
        else
        {
            encoder_value = 0;//无效
		}	 
    
    switch (encoder_value)
        {
        case 1:
        {
            switch (select.forp)
            {
            case 0:
                functionshow[select.index] = !functionshow[select.index];
                break;
            case 1:
            {
                switch (paramlist[select.index])
                {
                case 0:
                    paramshow[0] = paramshow[0] + 100;
                    break;
                case 1:
                    paramshow[1] = (paramshow[1] == (float)10.1) ? 2 : 10.1;
                    break;
                case 2:
                    paramshow[2] = (paramshow[2] == (float)10.1) ? 2 : 10.1;
                    break;
                case 3:
                    paramshow[3] = (float)(((int)(paramshow[3] * 10 + 1)) % 33) / 10.0;
                    break;
                case 4:
                    paramshow[4] = paramshow[4] + 100000;
                    break;

                default:
                    break;
                }
            }
            break;
            default:
                break;
            }
        }
        break;

        case -1:
        {
            switch (select.forp)
            {
            case 0:
                functionshow[select.index] = !functionshow[select.index];
                break;
            case 1:
            {
                switch (paramlist[select.index])
                {
                case 0:
                    paramshow[0] = paramshow[0] - 100;
                    break;
                case 1:
                    paramshow[1] = (paramshow[1] == (float)2) ? 10.1 : 2;
                    break;
                case 2:
                    paramshow[2] = (paramshow[2] == (float)2) ? 10.1 : 2;
                    break;
                case 3:
                    paramshow[3] = (float)(((int)(paramshow[3] * 10 - 1 + 33)) % 33) / 10.0;
                    break;
                case 4:
                    paramshow[4] = paramshow[4] - 100000;
                    break;

                default:
                    break;
                }
            }
            break;
            default:
                break;
            }
        }
        break;

        default:
            break;
        }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim17)
    {
        
        // //扫描并通过串口显示各按键状态
        //     uint8_t keyvalue = Key_Scan(key1_GPIO_Port, key1_Pin);
        //     printf("key1: %d\r\n", keyvalue);
        //     keyvalue = Key_Scan(key2_GPIO_Port, key2_Pin);
        //     printf("key2: %d\r\n", keyvalue);
        //     keyvalue = Key_Scan(key3_GPIO_Port, key3_Pin);
        //     printf("key3: %d\r\n", keyvalue);
        //     keyvalue = Key_Scan(key4_GPIO_Port, key4_Pin);
        //     printf("key4: %d\r\n", keyvalue);
        //     keyvalue = Key_Scan(key5_GPIO_Port, key5_Pin);
        //     printf("key5: %d\r\n", keyvalue);
        //     //扫描编码器状态
        //     uint8_t encoder_value = Encoder_Scan(Key_Scan(key3_GPIO_Port, key3_Pin), Key_Scan(key5_GPIO_Port, key5_Pin));
        //     switch (encoder_value)
        //     {
        //     case 1:
        //         printf("encoder: 1\r\n");
        //         break;
        //     case -1:
        //         printf("encoder: -1\r\n");
        //         break;
        //     default:
        //         break;
        //     }
            
        if (Key_Scan(key2_GPIO_Port, key2_Pin) == KEY_ON)
        {
            allstop();
            status = (status + 1) % 3;
            printf("statusvalue: %d\r\n", status);
            init_status();
        }
        if (Key_Scan(key1_GPIO_Port, key1_Pin) == KEY_ON)
        {
            select.forp = !select.forp;
            printf("selectvalue: %d\r\n", select.forp);
        }
        if (Key_Scan(key4_GPIO_Port, key4_Pin) == KEY_ON)
        {
            select.index = (select.index + 1) % 5;
            printf("selectindex: %d\r\n", select.index);
        }
        
        
    }
}



