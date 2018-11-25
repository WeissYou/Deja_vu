/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Deja_vu.c
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  寻迹
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
volatile unsigned char half_speed_flag=0;                // 半速标志位
volatile unsigned char Tracing_All_White_Stop_Flag = 0;  // 全白停车标志位
/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
volatile unsigned char Tracing_status = TRACING_STATUS_STATUS_IDLE;           // 当前寻迹机制状态

/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Tracing_Start
* Description    :  开始寻迹机制
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Start(void)
{
    // 设置寻迹机制的状态为正在运行
    Tracing_status = TRACING_STATUS_STATUS_RUNING;

    // 两个轮子都先给个速度
    MotorL_setting_auto_dir(10);
    MotorR_setting_auto_dir(10);

}// End of void Tracing_Start(void)

/*******************************************************************************
*                           陈苏阳@2018-11-25
* Function Name  :  Tracing_Set_Speed_Half
* Description    :  设置寻迹的速度为半速
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Set_Speed_Half(void)
{
    half_speed_flag = 1;
}// End of void Tracing_Set_Speed_Half(void)


/*******************************************************************************
*                           陈苏阳@2018-11-25
* Function Name  :  Tracing_Enable_All_White_Stop
* Description    :  使能全白停车功能
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Enable_All_White_Stop(void)
{
    Tracing_All_White_Stop_Flag = 1;
}// End of void Tracing_Enable_All_White_Stop(void)

/*******************************************************************************
*                           陈苏阳@2018-11-25
* Function Name  :  Tracing_Disnable_All_White_Stop
* Description    :  失能全白停车功能
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Disnable_All_White_Stop(void)
{
    Tracing_All_White_Stop_Flag = 0;
}// End of void Tracing_Disnable_All_White_Stop(void)

 /*******************************************************************************
 *                           陈苏阳@2018-11-25
 * Function Name  :  Tracing_Set_Speed_All
 * Description    :  设置寻迹的速度为全速
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void Tracing_Set_Speed_All(void)
{
    half_speed_flag = 0;
}// End of void Tracing_Set_Speed_All(void)

 /*******************************************************************************
 *                           陈苏阳@2018-11-24
 * Function Name  :  Tracing_Stop
 * Description    :  停止寻迹机制
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void Tracing_Stop(void)
{
    // 设置寻迹机制的状态为处于空闲状态
    Tracing_status = TRACING_STATUS_STATUS_IDLE;

    // 停止电机
    Motors_stop();

    //PWM设定生效
    pwms_enable();         
}// End of void Tracing_Stop(void)


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Tracing_Get_Black_Spot_Number
* Description    :  获取8路寻迹传感器压中黑点的个数
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
unsigned char Tracing_Get_Black_Spot_Number(void)
{
    unsigned char number_cnt=0;           // 黑点计数
    unsigned char i = 0;
    for (i = 0; i < 8; i++)
    {
        // 如果当前点为黑点
        if (situation&(0x01 << i))
        {
            // 黑点个数++
            number_cnt++;
        }
    }
    return number_cnt;
}// End of unsigned char Tracing_Get_Black_Spot_Number(void)



/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Tracing_Timer_Handle
* Description    :  寻迹定时器处理函数
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Tracing_Timer_Handle(void)
{
    // 如果当前寻迹机制处于运行状态
    if (Tracing_status == TRACING_STATUS_STATUS_RUNING)
    {
        G_LED_ON();
        switch (situation)
        {
					
            //起动
        case 255:					//1111 1111
        {
            // 如果是半速
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

        //停止

        case 0:
        {
            // 如果全白停车标志位被置位,则PWM给0
            if (Tracing_All_White_Stop_Flag)
            {
                MotorL_setting_auto_dir(0);
                MotorR_setting_auto_dir(0);
							
            }
            else
            {
                // 如果是半速
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

        //直行中调整
        //4灯情况
        case 60:					//0011 1100
        {
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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

        //3灯情况	
        case 28:					        //0001 1100
        {
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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

        //2灯情况
        case 18:								//0001 1000
        {
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
        //1灯情况    
        case 8:										//0000 1000
        {
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
        //右转向

        case 240:								//1111 0000
        {
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
            // 如果是半速
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
        pwms_enable();         //PWM设定生效
    }
    else
    {
        G_LED_OFF();
    }
    
}// End of void Tracing_Timer_Handle(void)

#endif /* __DEJA_VU_C */


