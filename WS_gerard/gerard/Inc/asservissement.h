/**
  ******************************************************************************
  * @file    asservissement.h
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F0xx_ASSERV_H
#define __STM32F0xx_ASSERV_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "mxconstants.h"

void motor_SetDuty(TIM_HandleTypeDef *htim, uint8_t duty); // duty 0 to 100


#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_ASSERV_H */
