/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define delay(x) HAL_Delay(x)
#define led(x) ((x)? HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET): HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET))
#define out(x) ((x)? HAL_GPIO_WritePin(OUT_GPIO_Port,OUT_Pin,GPIO_PIN_SET): HAL_GPIO_WritePin(OUT_GPIO_Port,OUT_Pin,GPIO_PIN_RESET))
#define ToggleLed HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin)
	

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
#define OUT_Pin GPIO_PIN_0
#define OUT_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_1
#define LCD_RS_GPIO_Port GPIOA
#define LCD_RW_Pin GPIO_PIN_2
#define LCD_RW_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_3
#define LCD_EN_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D4_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_7
#define LCD_D7_GPIO_Port GPIOA
#define INT_Pin GPIO_PIN_10
#define INT_GPIO_Port GPIOA
#define INT_EXTI_IRQn EXTI4_15_IRQn
#define LCD_BLK_Pin GPIO_PIN_12
#define LCD_BLK_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_15
#define KEY1_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_3
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_4
#define KEY3_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
