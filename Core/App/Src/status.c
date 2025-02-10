/*
 * @Date: 2025-02-05 18:01:42
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-10 19:38:00
 * @FilePath: \MDK-ARMd:\Mein Werk\meine code\stm32projekt\scope\Core\App\Src\status.c
 */
#include "status.h"

int status = SCOPE_STATUS;

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
