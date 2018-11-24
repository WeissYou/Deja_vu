/******************** (C) COPYRIGHT 2018 ³ÂËÕÑô **********************************
* File Name          :  motor.h
* Author             :  ³ÂËÕÑô
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTOR_H
#define  __MOTOR_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Motors_stop(void);
void MotorL_setting_auto_dir(char speed);
void MotorR_setting_auto_dir(char speed);

#endif /* __MOTOR_H */



/******************* (C) COPYRIGHT 2018 ³ÂËÕÑô *****END OF FILE******************/

