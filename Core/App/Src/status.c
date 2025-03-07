/*
 * @Date: 2025-02-05 18:01:42
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-07 19:56:43
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\App\Src\status.c
 * @Description: 根据状态调节执行功能模式
 */
#include "status.h"

int status = 1;//0:SCOPE 1:MESSER 2:MU

/**
 * @brief 状态初始化
 * @param void
 * @return void
 * @note 根据状态初始化相应功能
 * @attention 无
 * @Author Max_unterwegs
 */
void init_status()
{
    switch (status)
    {
    case SCOPE_STATUS:
        scope_init();
        break;
    case MESSER_STATUS:
        messer_init();
        break;
    case MU_STATUS:
        mu_init();
        break;
    default:
        break;
    }
}
/**
 * @brief 状态主函数
 * @param void
 * @return void
 * @note 根据状态执行相应功能
 * @attention 无
 * @Author Max_unterwegs
 */
void main_status()
{
    switch (status)
    {
    case SCOPE_STATUS:
        scope_main();
        break;
    case MESSER_STATUS:
        messer_main();
        break;
    case MU_STATUS:
        mu_main();
        break;
    default:
        break;
    }
   
}
