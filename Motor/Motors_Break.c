/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Motors_Break.c
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  小车后退修正
*******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#include "Motors_Break.h"
#include "Global.h"

/* Private variables ---------------------------------------------------------*/
unsigned char Motors_Break_Status = MOTORS_BREAK_STATUS_IDLE;      // 当前小车倒退修正机制状态
unsigned char Motors_Break_Delay_Time_Cnt = 0;                // 小车倒退修正机制等待时间计数 
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Motors_Break_Start
* Description    :  开始运行小车倒退修正机制
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Motors_Break_Start(void)
{

    // 电机停止
    Motors_stop();

    // 给delay时间计数设置一个初值
    Motors_Break_Delay_Time_Cnt = MOTORS_BREAK_MOTOR_STOP_FIRST_DELAY_TIME;

    // 将当前状态设置为第一次停止等待
    Motors_Break_Status = MOTORS_BREAK_STATUS_FIRST_STOP_DELAY;

}// End of void Motors_Break_Start(void)


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Motors_Break_Is_Ok
* Description    :  查询小车倒退修正机制是否已经完成
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
unsigned char Motors_Break_Is_Ok(void)
{
    if (Motors_Break_Status == MOTORS_BREAK_STATUS_IDLE)return 1;
    return 0;
}// End of unsigned char Motors_Break_Is_Ok(void)


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Motors_Break_Timer_Handle
* Description    :  电机后退_定时器处理函数(在定时器中断中调用)
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Motors_Break_Timer_Handle(void)
{
    switch (Motors_Break_Status)
    {
        // 如果当前处于第一次停车等待状态
        case MOTORS_BREAK_STATUS_FIRST_STOP_DELAY:
        {
            // 如果等待时间还没结束,时间计数--
            if (Motors_Break_Delay_Time_Cnt > 0)
            {
                Motors_Break_Delay_Time_Cnt--;
            }
            else
            {
                // 如果等待时间已经结束

                MotorL_setting_auto_dir(-40);
                MotorR_setting_auto_dir(-40);

                // 将当前状态设置为正在等待黑线的出现
                Motors_Break_Status = MOTORS_BREAK_STATUS_WAIT_BLACK_LINE;
            }
            break;
        }

        // 如果当前处于等待黑线出现状态
        case MOTORS_BREAK_STATUS_WAIT_BLACK_LINE:
        {
            // 如果黑线出现了
            if (SNR0 == 0 || SNR1 == 0)
            {
                // 电机停止
                Motors_stop();

                // 设置倒车修正机制为空闲状态
                Motors_Break_Status = MOTORS_BREAK_STATUS_IDLE;
            }
            else
            {
                // 如果黑线还没出现则直接退出这次循环,等待下次检测
            }
            break;
        }
    }
}// End of void Motors_Break_Timer_Handle(void)




/******************* (C) COPYRIGHT 2018 陈苏阳 *****END OF FILE******************/

