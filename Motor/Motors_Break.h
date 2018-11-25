/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Motors_Break.h
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  小车后退修正
*******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTORS_BREAK_H
#define  __MOTORS_BREAK_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define MOTORS_BREAK_MOTOR_STOP_FIRST_DELAY_TIME                                10           //小车倒车修正机制开始后的停车时间(单位为倒车修正机制Time_Handle函数的执行周期)


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    MOTORS_BREAK_STATUS_IDLE = 0,         // 当前小车倒退修正机制处于空闲状态
    MOTORS_BREAK_STATUS_FIRST_STOP_DELAY, // 当前小车倒退修正机制处于第一次等待中(刚刚开始倒车修正,先停转电机后等待若干时间)
    MOTORS_BREAK_STATUS_WAIT_BLACK_LINE,  // 当前小车倒退机制正在等待黑线(小车倒退中)
}MOTORS_BREAK_STATUS;// 小车倒退修正机制的运行状态

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Motors_Break_Start(void);
unsigned char Motors_Break_Is_Ok(void);
void Motors_Break_Timer_Handle(void);
#endif /* __MOTORS_BREAK_H */




/******************* (C) COPYRIGHT 2018 陈苏阳 *****END OF FILE******************/