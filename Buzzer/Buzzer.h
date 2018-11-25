/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Buzzer.h
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  ������
*******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUZZER_H
#define  __BUZZER_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

void Buzzer_Init(void);
void Buzzer_Tweet(unsigned char tweet_time);
void Buzzer_Timer_Handle(void);

#endif /* __BUZZER_H */





/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/


