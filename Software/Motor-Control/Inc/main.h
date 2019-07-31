/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Focus_Pin GPIO_PIN_0
#define Focus_GPIO_Port GPIOC
#define Shutter_Pin GPIO_PIN_1
#define Shutter_GPIO_Port GPIOC
#define S_dir1_Pin GPIO_PIN_2
#define S_dir1_GPIO_Port GPIOC
#define S_dir2_Pin GPIO_PIN_3
#define S_dir2_GPIO_Port GPIOC
#define VBat1_Pin GPIO_PIN_0
#define VBat1_GPIO_Port GPIOA
#define VBat2_Pin GPIO_PIN_1
#define VBat2_GPIO_Port GPIOA
#define Axis1_Pin GPIO_PIN_2
#define Axis1_GPIO_Port GPIOA
#define Axis2_Pin GPIO_PIN_3
#define Axis2_GPIO_Port GPIOA
#define M_EN_Pin GPIO_PIN_4
#define M_EN_GPIO_Port GPIOA
#define Dir5_Pin GPIO_PIN_5
#define Dir5_GPIO_Port GPIOA
#define Step5_Pin GPIO_PIN_4
#define Step5_GPIO_Port GPIOC
#define CS_MD5_Pin GPIO_PIN_5
#define CS_MD5_GPIO_Port GPIOC
#define Dir4_Pin GPIO_PIN_2
#define Dir4_GPIO_Port GPIOB
#define Step4_Pin GPIO_PIN_12
#define Step4_GPIO_Port GPIOB
#define CS_MD4_Pin GPIO_PIN_13
#define CS_MD4_GPIO_Port GPIOB
#define Dir3_Pin GPIO_PIN_14
#define Dir3_GPIO_Port GPIOB
#define Step3_Pin GPIO_PIN_15
#define Step3_GPIO_Port GPIOB
#define CS_MD3_Pin GPIO_PIN_6
#define CS_MD3_GPIO_Port GPIOC
#define Dir2_Pin GPIO_PIN_7
#define Dir2_GPIO_Port GPIOC
#define Step2_Pin GPIO_PIN_8
#define Step2_GPIO_Port GPIOC
#define CS_MD2_Pin GPIO_PIN_9
#define CS_MD2_GPIO_Port GPIOC
#define Dir1_Pin GPIO_PIN_8
#define Dir1_GPIO_Port GPIOA
#define Step1_Pin GPIO_PIN_11
#define Step1_GPIO_Port GPIOA
#define CS_MD1_Pin GPIO_PIN_12
#define CS_MD1_GPIO_Port GPIOA
#define CSN_Pin GPIO_PIN_15
#define CSN_GPIO_Port GPIOA
#define DR_Pin GPIO_PIN_2
#define DR_GPIO_Port GPIOD
#define PWRUP_Pin GPIO_PIN_3
#define PWRUP_GPIO_Port GPIOB
#define TRX_CE_Pin GPIO_PIN_4
#define TRX_CE_GPIO_Port GPIOB
#define TX_EN_Pin GPIO_PIN_5
#define TX_EN_GPIO_Port GPIOB
#define RF_AM_Pin GPIO_PIN_8
#define RF_AM_GPIO_Port GPIOB
#define RF_CD_Pin GPIO_PIN_9
#define RF_CD_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
