/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Deja_vu.c
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  Ѱ��
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEJA_VU_C
#define  __DEJA_VU_C

/* Includes ------------------------------------------------------------------*/
#include <DEJA_VU.H>
#include "GLOBAL.H"
#include "MOTOR.H"
#include "PWM.H"
#include "LED.h"
/* Private define ------------------------------------------------------------*/
volatile unsigned char half_speed_flag=0;                // ���ٱ�־λ
volatile unsigned char Tracing_All_White_Stop_Flag = 0;  // ȫ��ͣ����־λ
/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
volatile unsigned char Tracing_status = TRACING_STATUS_STATUS_IDLE;           // ��ǰѰ������״̬

/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Tracing_Start
* Description    :  ��ʼѰ������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Start(void)
{
    // ����Ѱ�����Ƶ�״̬Ϊ��������
    Tracing_status = TRACING_STATUS_STATUS_RUNING;

    // �������Ӷ��ȸ����ٶ�
    MotorL_setting_auto_dir(10);
    MotorR_setting_auto_dir(10);

}// End of void Tracing_Start(void)

/*******************************************************************************
*                           ������@2018-11-25
* Function Name  :  Tracing_Set_Speed_Half
* Description    :  ����Ѱ�����ٶ�Ϊ����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Set_Speed_Half(void)
{
    half_speed_flag = 1;
}// End of void Tracing_Set_Speed_Half(void)


/*******************************************************************************
*                           ������@2018-11-25
* Function Name  :  Tracing_Enable_All_White_Stop
* Description    :  ʹ��ȫ��ͣ������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Enable_All_White_Stop(void)
{
    Tracing_All_White_Stop_Flag = 1;
}// End of void Tracing_Enable_All_White_Stop(void)

/*******************************************************************************
*                           ������@2018-11-25
* Function Name  :  Tracing_Disnable_All_White_Stop
* Description    :  ʧ��ȫ��ͣ������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Disnable_All_White_Stop(void)
{
    Tracing_All_White_Stop_Flag = 0;
}// End of void Tracing_Disnable_All_White_Stop(void)

 /*******************************************************************************
 *                           ������@2018-11-25
 * Function Name  :  Tracing_Set_Speed_All
 * Description    :  ����Ѱ�����ٶ�Ϊȫ��
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void Tracing_Set_Speed_All(void)
{
    half_speed_flag = 0;
}// End of void Tracing_Set_Speed_All(void)

 /*******************************************************************************
 *                           ������@2018-11-24
 * Function Name  :  Tracing_Stop
 * Description    :  ֹͣѰ������
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void Tracing_Stop(void)
{
    // ����Ѱ�����Ƶ�״̬Ϊ���ڿ���״̬
    Tracing_status = TRACING_STATUS_STATUS_IDLE;

    // ֹͣ���
    Motors_stop();

    //PWM�趨��Ч
    pwms_enable();         
}// End of void Tracing_Stop(void)


/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Tracing_Get_Black_Spot_Number
* Description    :  ��ȡ8·Ѱ��������ѹ�кڵ�ĸ���
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
unsigned char Tracing_Get_Black_Spot_Number(void)
{
    unsigned char number_cnt=0;           // �ڵ����
    unsigned char i = 0;
    for (i = 0; i < 8; i++)
    {
        // �����ǰ��Ϊ�ڵ�
        if (situation&(0x01 << i))
        {
            // �ڵ����++
            number_cnt++;
        }
    }
    return number_cnt;
}// End of unsigned char Tracing_Get_Black_Spot_Number(void)



/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Tracing_Timer_Handle
* Description    :  Ѱ����ʱ��������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Timer_Handle(void)
{
    // �����ǰѰ�����ƴ�������״̬
    if (Tracing_status == TRACING_STATUS_STATUS_RUNING)
    {
        G_LED_ON();
        switch (situation)
        {
					
            //��
        case 255:					//1111 1111
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(50/2);
                MotorR_setting_auto_dir(50/2);
            }
            else
            {
                MotorL_setting_auto_dir(50);
                MotorR_setting_auto_dir(50);
            }
            break;
        }

        //ֹͣ

        case 0:
        {
            // ���ȫ��ͣ����־λ����λ,��PWM��0
            if (Tracing_All_White_Stop_Flag)
            {
                MotorL_setting_auto_dir(0);
                MotorR_setting_auto_dir(0);
							
            }
            else
            {
                // ����ǰ���
                if (half_speed_flag)
                {
                    MotorL_setting_auto_dir(50 / 2);
                    MotorR_setting_auto_dir(50 / 2);
                }
                else
                {
                    MotorL_setting_auto_dir(50);
                    MotorR_setting_auto_dir(50);
                }
            }
            
            break;
        }

        //ֱ���е���
        //4�����
        case 60:					//0011 1100
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(100);
            }
            break;
        }
        case 30:				  	//0001 1110
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(50/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(50);
            }
            break;
        }
        case 120:					//0111 1000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(50/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(50);
                MotorR_setting_auto_dir(100);
            }
        }

        //3�����	
        case 28:					        //0001 1100
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100 / 2);
                MotorR_setting_auto_dir(80 / 2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(80);
            }
            break;
        }
        case 56:						    //0011 1000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(80 / 2);
                MotorR_setting_auto_dir(100 / 2);
            }
            else
            {
                MotorL_setting_auto_dir(80);
                MotorR_setting_auto_dir(100);
            }
            break;
        }
        case 14:							//0000 1110
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(40/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(40);
            }
            break;
        }
        case 112:							//0111 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(40/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(40);
                MotorR_setting_auto_dir(100);
            }
            break;
        }

        //2�����
        case 18:								//0001 1000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(100);
            }
            break;
        }
        case 24:                             //0000 1100
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(60/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(60);
            }
            break;
        }
        case 48:								//0011 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(60/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(60);
                MotorR_setting_auto_dir(100);
            }
            break;
        }
        //1�����    
        case 8:										//0000 1000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(80/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(80);
            }
            break;
        }
        case 10:										//0001 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(80/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(80);
                MotorR_setting_auto_dir(100);
            }
            break;
        }

        case 4:										//0000 0100
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(60/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(60);
            }		
            break;
        }
        case 32:									    //0010 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(60/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(60);
                MotorR_setting_auto_dir(100);
            }
            break;
        }
        //��ת��

        case 240:								//1111 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(-50/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(-50);
                MotorR_setting_auto_dir(100);
            }
            break;
        }

        case 224:								//1110 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(-75 / 2);
                MotorR_setting_auto_dir(100 / 2);
            }
            else
            {
                MotorL_setting_auto_dir(-75);
                MotorR_setting_auto_dir(100);
            }
            break;
        }

        case 192:								//1100 0000
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(-100/2);
                MotorR_setting_auto_dir(100/2);
            }
            else
            {
                MotorL_setting_auto_dir(-100);
                MotorR_setting_auto_dir(100);
            }
            break;
        }
 

        case 15:								//0000 1111
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100 / 2);
                MotorR_setting_auto_dir(-50 / 2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(-50);
            }
            break;
        }

        case 7:								//0000 0111
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100 / 2);
                MotorR_setting_auto_dir(-75 / 2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(-75);
            }
            break;
        }

        case 195:								//0000 0011
        {
            // ����ǰ���
            if (half_speed_flag)
            {
                MotorL_setting_auto_dir(100/2);
                MotorR_setting_auto_dir(-100/2);
            }
            else
            {
                MotorL_setting_auto_dir(100);
                MotorR_setting_auto_dir(-100);
            }
            break;
        }

        }
        pwms_enable();         //PWM�趨��Ч
    }
    else
    {
        G_LED_OFF();
    }
    
}// End of void Tracing_Timer_Handle(void)

#endif /* __DEJA_VU_C */


