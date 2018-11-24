/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Motor.c
* Author             :  ������
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
*                           ������@2018-11-24
* Function Name  :  MotorL_setting_auto_dir
* Description    :  ���������(�Զ��жϷ���)
* Input          :  char speed          // ���ռ�ձ�,����Ϊǰ��,����Ϊ����
* Output         :  None
* Return         :  None
*******************************************************************************/
void MotorL_setting_auto_dir(char speed)		   
{
  uchar _speed;               // �ٶ���ʱ����
  if (speed < 0)
  {
    // ����
    IN1 = 0;
    IN2 = 1;
    
    // �ڴ���һ��-100������
    if (speed < -100)
    {
        _speed = 100;
    }
    else
    {
        // �Ӹ�����Ϊ����
        _speed = -speed;
    }
  }
  else
  {
    // �ڴ���һ��100������
    if (speed > 100)
    {
          _speed = 100;
    }
    else
    {
        // ������ֱ�Ӹ�ֵ
        _speed = speed;
    }

    // ǰ��
    IN1 = 1;
    IN2 = 0;
  }

  // �ı�speedȡֵ��1~100���ı�ռ�ձ�
  pwmL_setting(_speed);		 
  
}// End of void MotorL_setting_auto_dir(char speed)		   



 /*******************************************************************************
 *                           ������@2018-11-24
 * Function Name  :  MotorR_setting_auto_dir
 * Description    :  ���������(�Զ��жϷ���)
 * Input          :  char speed          // ���ռ�ձ�,����Ϊǰ��,����Ϊ����
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void MotorR_setting_auto_dir(char speed)		   
{
    uchar _speed;               // �ٶ���ʱ����
    if (speed < 0)
    {
        // ����
        IN3 = 0;
        IN4 = 1;

        // �ڴ���һ��-100������
        if (speed < -100)
        {
            _speed = 100;
        }
        else
        {
            // �Ӹ�����Ϊ����
            _speed = -speed;
        }
    }
    else
    {
        // �ڴ���һ��100������
        if (speed > 100)
        {
            _speed = 100;
        }
        else
        {
            // ������ֱ�Ӹ�ֵ
            _speed = speed;
        }

        // ǰ��
        IN3 = 1;
        IN4 = 0;
    }
    // �ı�speedȡֵ��1~100���ı�ռ�ձ�
    pwmR_setting(_speed);

}// End of void MotorR_setting_auto_dir(char speed)	


/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Motors_stop
* Description    :  ͣ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Motors_stop(void)
{		
    // ����ռ�ձ�Ϊ0
    pwmR_setting(0);
    pwmL_setting(0);
    IN1 = 0;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
}// End of void Motors_stop(void)

