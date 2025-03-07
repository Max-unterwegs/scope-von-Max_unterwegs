/*
 * @Date: 2025-02-05 18:02:21
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 19:55:28
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\App\Src\function.c
 * @Description: ??????????????
 */
#include "function.h"

/**
 * @brief ???????
 * @param isopen: 0-?? 1-??
 * @param arris: ??????
 * @return void
 * @note ???????????????pwm??????
 * @author Max_unterwegs
 */
void DC_control(char isopen, int arris)
{
    static char ispwmopen = 0;
    if(isopen == 0)
    {
        HAL_TIM_PWM_Stop( &OUT_HAL_TIM ,OUT_CHANNEL);
        HAL_TIM_Base_Stop( &OUT_HAL_TIM );
        __HAL_TIM_SET_AUTORELOAD(&OUT_HAL_TIM, arris);
        ispwmopen = 0;
    }
        
    else
    {
        if(ispwmopen == 0)
        {
            ispwmopen = 1;
            PWM_OUT_Init();
        }
    }
        
}


/**
 * @brief ?????????
 * @param dcvalue: ?????
 * @return void
 * @note ???????????
 * @attention ?????0-3.3V
 * @author Max_unterwegs
 */
void DC_vcontrol(float dcvalue)
{

    DC_OUT( OUT_TIM , OUT_CHANNEL, dcvalue, paramshow[0]);
    
}
/**
 * @brief ??????
 * @param isCHopen: 0-?? 1-??
 * @return void
 * @note ????????????????????pwm???adc??
 * @author Max_unterwegs
 */
void CH_control(char isCHopen)
{
    static char ischpwmopen = 0;
    if(isCHopen == 0)
    {
        HAL_ADC_Stop_DMA( &ADC_handle );
        HAL_TIM_Base_Stop( &CH_HAL_TIM );
        HAL_TIM_PWM_Stop( &CH1_HAL_TIM ,CH1_CHANNEL);
        HAL_TIM_PWM_Stop( &CH2_HAL_TIM ,CH2_CHANNEL);
        HAL_TIM_Base_Stop( &CH1_HAL_TIM );
        HAL_TIM_Base_Stop( &CH2_HAL_TIM );
        ischpwmopen = 0;
    }
    else
    {
        for(int i=0;i<ADC_CHANNEL_NUM;i++)
        {
            adcValues[i] = 0;
        }
        if(ischpwmopen == 0)
        {
            ischpwmopen = 1;
            HAL_TIM_Base_Start( &CH_HAL_TIM );
            PWM_CH_Init();
            VOLT_Init();
        }
    }
}
/**
 * @brief ??????
 * @param chnum: ???
 * @param chvmode: 2:2??�3.3V?? 10:10??�16.65V??
 * @return void
 * @note ???????
 * @author Max_unterwegs
 */
void CH_vcontrol(char chnum,char chvmode)
{
    switch (chnum)
    {
        case 1:
            switch (chvmode)
            {
            case 2:
                HAL_GPIO_WritePin(SW1_GPIO_Port,SW1_Pin,GPIO_PIN_RESET);
                DC_OUT( CH1_TIM ,CH1_CHANNEL,1.1,paramshow[0]);
                break;
            
            case 10:
                HAL_GPIO_WritePin(SW1_GPIO_Port,SW1_Pin,GPIO_PIN_SET);
                DC_OUT( CH1_TIM ,CH1_CHANNEL,1.50123,paramshow[0]);
                break;
            default:
                break;
            }

            break;
        case 2:
            switch (chvmode)
            {
            case 2:
                HAL_GPIO_WritePin(SW2_GPIO_Port,SW2_Pin,GPIO_PIN_RESET);
                DC_OUT( CH2_TIM ,CH2_CHANNEL,1.1,paramshow[0]);
                break;
            
            case 10:
                HAL_GPIO_WritePin(SW2_GPIO_Port,SW2_Pin,GPIO_PIN_SET);
                DC_OUT( CH2_TIM ,CH2_CHANNEL,1.50123,paramshow[0]);
                break;
            default:
                break;
            }
            break;

        default:
            break;
    }
}
/**
 * @brief ????????
 * @param freq: ??????
 * @param isCHopen: 0-?? 1-??
 * @return void
 * @note ?????????
 * @author Max_unterwegs
 */
void CH_fcontrol(float freq ,char isCHopen) {
    if(isCHopen == 1)
    {
        HAL_TIM_Base_Stop( &CH_HAL_TIM );
        HAL_ADC_Stop_DMA( &ADC_handle );
        uint32_t prescaler = 1;
        while ((float) HCLK / (float) prescaler / freq > 65535) {
            do {
                prescaler++;
            } while (HCLK % prescaler);
        }
        CH_HAL_TIM.Instance->PSC = prescaler - 1;
        CH_HAL_TIM.Instance->ARR = (uint16_t) ((float) HCLK / (float) prescaler / freq) - 1;
        
        for(int i=0;i<ADC_CHANNEL_NUM;i++)
        {
            adcValues[i] = 0;
        }

        HAL_TIM_Base_Start( &CH_HAL_TIM );
        VOLT_Init();
    }
    
}
/**
 * @brief ?????
 * @param mapbuffer: ?????
 * @return void
 * @note ??????????????
 * @author Max_unterwegs
 */
void voltage_map(float* mapbuffer)
{
    mapbuffer[0] = (1.65 - mapbuffer[0])*paramshow[1];
    mapbuffer[1] = (1.65 - mapbuffer[1])*paramshow[2];
}
/**
 * @brief ?????
 * @param vsvalue: ???
 * @param resbuffer: ?????
 * @param mapbuffer: ?????
 * @return void
 * @note ?????
 * @author Max_unterwegs
 */
void Get_Res(float vsvalue,float* resbuffer,float* mapbuffer)
{
    resbuffer[0] = vsvalue*(1000000.0/paramshow[1])/(1.65-mapbuffer[0])-1000000.0;
    resbuffer[1] = vsvalue*(1000000.0/paramshow[2])/(1.65-mapbuffer[1])-1000000.0;
    if(resbuffer[0] < 70)
    {
        functionshow[2] = 1;   
    }
    if(resbuffer[1] < 70)
    {
        functionshow[2] = 1;   
    }
    resbuffer[0] = resbuffer[0] > 1000000? 1000000 : resbuffer[0];
    resbuffer[1] = resbuffer[1] > 1000000? 1000000 : resbuffer[1];
    
}

