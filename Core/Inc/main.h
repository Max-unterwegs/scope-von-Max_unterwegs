/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_14
#define LED_GPIO_Port GPIOC
#define buzzer_Pin GPIO_PIN_15
#define buzzer_GPIO_Port GPIOC
#define key1_Pin GPIO_PIN_4
#define key1_GPIO_Port GPIOA
#define key2_Pin GPIO_PIN_5
#define key2_GPIO_Port GPIOA
#define DC1_Pin GPIO_PIN_6
#define DC1_GPIO_Port GPIOA
#define DC2_Pin GPIO_PIN_1
#define DC2_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_8
#define SW1_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_6
#define SW2_GPIO_Port GPIOC
#define key3_Pin GPIO_PIN_15
#define key3_GPIO_Port GPIOA
#define key3_EXTI_IRQn EXTI4_15_IRQn
#define key4_Pin GPIO_PIN_3
#define key4_GPIO_Port GPIOB
#define key5_Pin GPIO_PIN_4
#define key5_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_5
#define OLED_DC_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_6
#define OLED_RES_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
