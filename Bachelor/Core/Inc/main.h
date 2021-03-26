/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC1_Throttle_Pin GPIO_PIN_0
#define ADC1_Throttle_GPIO_Port GPIOC
#define ADC1_Battery_Voltage_Pin GPIO_PIN_0
#define ADC1_Battery_Voltage_GPIO_Port GPIOA
#define ADC3_MDC_Voltage_Pin GPIO_PIN_1
#define ADC3_MDC_Voltage_GPIO_Port GPIOA
#define ADC1_H1_Pin GPIO_PIN_2
#define ADC1_H1_GPIO_Port GPIOA
#define ADC3_H3_Pin GPIO_PIN_3
#define ADC3_H3_GPIO_Port GPIOA
#define ADC2_H2_Pin GPIO_PIN_4
#define ADC2_H2_GPIO_Port GPIOC
#define ADC2_System_Current_Pin GPIO_PIN_5
#define ADC2_System_Current_GPIO_Port GPIOC
#define H1_GPIO_Pin GPIO_PIN_10
#define H1_GPIO_GPIO_Port GPIOC
#define H2_GPIO_Pin GPIO_PIN_11
#define H2_GPIO_GPIO_Port GPIOC
#define H3_GPIO_Pin GPIO_PIN_12
#define H3_GPIO_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
