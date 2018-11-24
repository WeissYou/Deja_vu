/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Motor.c
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  
*******************************************************************************/




/* Includes ------------------------------------------------------------------*/
#include"Global.h"
#include<Motor.h>
#include"PWM.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  MotorL_setting_auto_dir
* Description    :  设置左侧电机(自动判断方向)
* Input          :  char speed          // 电机占空比,正数为前进,负数为后退
* Output         :  None
* Return         :  None
*******************************************************************************/
void MotorL_setting_auto_dir(char speed)		   
{
  uchar _speed;               // 速度临时变量
  if (speed < 0)
  {
    // 后退
    IN1 = 0;
    IN2 = 1;
    
    // 在此做一个-100的限制
    if (speed < -100)
    {
        _speed = 100;
    }
    else
    {
        // 从负数变为正数
        _speed = -speed;
    }
  }
  else
  {
    // 在此做一个100的限制
    if (speed > 100)
    {
          _speed = 100;
    }
    else
    {
        // 正数就直接赋值
        _speed = speed;
    }

    // 前进
    IN1 = 1;
    IN2 = 0;
  }

  // 改变speed取值（1~100）改变占空比
  pwmL_setting(_speed);		 
  
}// End of void MotorL_setting_auto_dir(char speed)		   



 /*******************************************************************************
 *                           陈苏阳@2018-11-24
 * Function Name  :  MotorR_setting_auto_dir
 * Description    :  设置左侧电机(自动判断方向)
 * Input          :  char speed          // 电机占空比,正数为前进,负数为后退
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void MotorR_setting_auto_dir(char speed)		   
{
    uchar _speed;               // 速度临时变量
    if (speed < 0)
    {
        // 后退
        IN3 = 0;
        IN4 = 1;

        // 在此做一个-100的限制
        if (speed < -100)
        {
            _speed = 100;
        }
        else
        {
            // 从负数变为正数
            _speed = -speed;
        }
    }
    else
    {
        // 在此做一个100的限制
        if (speed > 100)
        {
            _speed = 100;
        }
        else
        {
            // 正数就直接赋值
            _speed = speed;
        }

        // 前进
        IN3 = 1;
        IN4 = 0;
    }
    // 改变speed取值（1~100）改变占空比
    pwmR_setting(_speed);

}// End of void MotorR_setting_auto_dir(char speed)	


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Motors_stop
* Description    :  停车
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Motors_stop(void)
{		
    // 设置占空比为0
    pwmR_setting(0);
    pwmL_setting(0);
    IN1 = 0;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
}// End of void Motors_stop(void)

