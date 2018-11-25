/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Task.c
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  任务处理
*******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "Task.h"
#include "motor.h"
#include "Motors_Break.h"
#include "Deja_vu.h"
#include "Buzzer.h"
#include "stdio.h"

/* Private variables ---------------------------------------------------------*/
volatile unsigned char Task_Status = TASK_STATUS_STARTING_POINT_STANDBY;        // 任务状态
volatile unsigned int Task_Delay_Time_Cnt = 0;                                  // 任务中的无阻塞延时时间计数
    
volatile unsigned char tmp_flag=0;																							// 临时flag
volatile unsigned char tmp_flag2 = 0;																						// 临时flag2
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Task_Delay_Start
* Description    :  任务延时开始
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Task_Delay_Start(unsigned int time)
{
    // 设置延时时间
    Task_Delay_Time_Cnt = time;
}// End of void Task_Delay_Start(unsigned int time)


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Task_Delay_Is_Delay
* Description    :  任务延时是否处于延时中
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
unsigned char Task_Delay_Is_Delay(void)
{
    if (Task_Delay_Time_Cnt>0)return 1;
    return 0;
}// End of unsigned char Task_Delay_Is_Delay(void)


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Task_Timer_Handle
* Description    :  任务定时器处理函数
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Task_Timer_Handle(void)
{

    // 如果任务延时时间计数还有值,则任务延时时间计数--
    if (Task_Delay_Time_Cnt>0)Task_Delay_Time_Cnt--;

	switch (Task_Status)
	{
    // 当前处于起点待机状态
    case TASK_STATUS_STARTING_POINT_STANDBY:
    {
        // 如果寻迹传感器遇到全黑
        if (Tracing_Get_Black_Spot_Number() >= TRACING_ALL_BLACK_SPOT_NUMBER)
        {
            // 开始寻迹机制
            Tracing_Start();
					
            // 蜂鸣器短鸣
            Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

            // 延时开启其他检测机制
            Task_Delay_Start(TASK_STARTING_POINT_DELAY_TIME);
			
#ifdef DEBUG
            printf("正进入上料区\n");
#endif		
            // 切换状态为正在进入上料区
            Task_Status=TASK_STATUS_IN_LOADING_AREA;
        }
        else
        {
            // 如果当期寻迹传感器不是全黑
            // 停止寻迹机制
            Tracing_Stop();
        }
        break;
    }

    // 当前小车正在进入上料区
    case TASK_STATUS_IN_LOADING_AREA:
    {
        // 如果现在不在Task Delay中,说明延时开启其他检测的这个延时已经过去
        if (Task_Delay_Is_Delay() == 0)
        {
            // 如果检测到全黑的十字路口(因为十字路口比较小,所以放宽检测条件需要的黑点数),说明遇上了上料区上坡前的那个小十字路口且临时标志位没有置位(第一次检测到十字路口)
            if (tmp_flag ==0 && (Tracing_Get_Black_Spot_Number() >= TRACING_ALL_BLACK_SPOT_NUMBER-3))
            {
                // 设置临时标志位置位
                tmp_flag = 1;
                // 蜂鸣器短鸣
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // 失能寻迹机制的全白停车功能
                Tracing_Disnable_All_White_Stop();

                // 清空临时标志位2
                tmp_flag2 = 0;
            }

            // 如果遇到了上料区第一个停车位,且是第一次遇到
            if (tmp_flag2==0 && SNR0 == 1 && SNR1 == 1)
            {
                // 临时标志位置位
                tmp_flag2 = 1;

                // 从现在起表明小车已经在上料区平台上了,小车运动速度减半
                Tracing_Set_Speed_Half();

                // 蜂鸣器短鸣
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);
							
			    // 停止寻迹机制
				Tracing_Stop();
							
                // 开始运行小车倒退修正机制
                Motors_Break_Start();
							
                // 切换状态为当前小车处于上料区第1个停车位
                Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_1;

            }
        }
		else
		{
			// 如果还在Task delay中,说明上一状态<<起点待机>>中最后设置的delay时间还没到
			// 在这里顺便初始化一下临时标志位
			tmp_flag=0;
		}
		break;
    }
    // 当前小车处于上料区第1个停车位
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_1:
    {
        // 如果小车倒退修正机制已经把小车位置修正完成
        if (Motors_Break_Is_Ok())
        {
#ifdef DEBUG
            printf("在上料区1车位\n");
#endif
            // 切换状态为当前小车处于上料区第1个停车位上执行机械手操作
            Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_1_WORKING;

            // 确保临时标志位已经被清空
            tmp_flag=0;
        }

        break;
    }

    // 当前小车处于上料区第1个停车位上执行机械手操作
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_1_WORKING:
    {

        // 如果是第一次运行本状态,临时标志位还没被置位
        if (tmp_flag == 0)
        {
            // 设置一个长时间的delay来模拟抓取操作
            Task_Delay_Start(200);

            // 蜂鸣器短鸣
            Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

            // 临时标志位置位
            tmp_flag = 1;
        }
        // 在这里做机械臂的抓取操作
        


        if(Task_Delay_Is_Delay()==0)//if (机械臂操作完毕)
        {
            // 确认操作完毕后开启寻迹机制
            Tracing_Start();

            // 判断现在SNR0以及SNR1已经离开黑色(不可靠,需要下面加delay)
            if (SNR0 == 0 && SNR1 == 0)
            {

                // 延时一定时间,确保下次检测SNR0以及SNR1的时候车子已经离开第1个停车位的两个特征小半十字路口
                Task_Delay_Start(TASK_OUT_PARKING_SPACE_SNR_CHECK_DELAY_TIME);
#ifdef DEBUG
                printf("往上料区2车位\n");
#endif
                // 切换状态为当前小车处于正在前往上料区第2个停车位的路上
                Task_Status = TASK_STATUS_GOING_LOADING_AREA_PARKING_SPACE_2;

                // 确保临时标志位已经被清空
                tmp_flag = 0;
            }
        }
        break;
    }
    //当前小车处于正在前往上料区第2个停车位的路上
    case TASK_STATUS_GOING_LOADING_AREA_PARKING_SPACE_2:
    {
        // 如果现在SNR延时检测的Delay时间已经过了
        if (Task_Delay_Is_Delay()==0)
        {
            // 如果遇上上料区的第二个停车位,且是第一次遇上
            if (tmp_flag ==0 && SNR0 == 1 && SNR1 == 1)
            {
                // 临时标志位置位
                tmp_flag = 1;

                // 蜂鸣器短鸣
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // 停止寻迹机制
	            Tracing_Stop();
								
                // 开始运行小车倒退修正机制
                Motors_Break_Start();
#ifdef DEBUG
                printf("处于上料区2车位\n");
#endif
                // 切换状态为当前小车处于上料区第2个停车位
                Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_2;

                // 确保临时标志位已经被清空
                tmp_flag = 0;
            }
        }
        else
        {
            // 趁SNR延时检测delay时间还未结束,清空两个临时标志位
            tmp_flag = 0;
            tmp_flag2 = 0;
        }
        break;
    }

    // 当前小车处于上料区第2个停车位
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_2:
    {
        // 如果小车倒退修正机制已经把小车位置修正完成
        if (Motors_Break_Is_Ok())
        {

            // 切换状态为当前小车处于上料区第2个停车位上执行机械手操作
            Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_2_WORKING;

            // 确保临时标志位已经被清空
            tmp_flag = 0;
        }

        break;
    }

    // 当前小车处于上料区第2个停车位上执行机械手操作
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_2_WORKING:
    {

        // 如果是第一次运行本状态,临时标志位还没被置位
        if (tmp_flag == 0)
        {
            // 设置一个长时间的delay来模拟抓取操作
            Task_Delay_Start(200);

            // 蜂鸣器短鸣
            Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

            // 临时标志位置位
            tmp_flag = 1;
        }



        if (Task_Delay_Is_Delay() == 0)//if (机械臂操作完毕)
        {
            // 确认操作完毕后开启寻迹机制
            Tracing_Start();
            
            // 恢复寻迹的速度满速
            Tracing_Set_Speed_All();

            // 判断现在SNR0以及SNR1已经离开黑色(不可靠,需要下面加delay)
            if (SNR0 == 0 && SNR1 == 0)
            {
                // 蜂鸣器短鸣
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // 延时一定时间,确保下次检测十字路口的时候不会因为下坡时车体姿态不正而导致误识别
                Task_Delay_Start(TASK_OUT_LOADING_AREA_CROSS_ROADS_CHECK_DELAY_TIME);
#ifdef DEBUG
                printf("退出上料区\n");
#endif
                // 切换状态为当前小车处于退出上料区状态
                Task_Status = TASK_STATUS_OUT_LOADING_AREA;

                // 确保临时标志位已经被清空
                tmp_flag = 0;
            }
        }
        break;
    }

    // 当前小车处于退出上料区状态
    case TASK_STATUS_OUT_LOADING_AREA:
    {
     
        // 如果现在十字路口延时检测的Delay时间已经过了
        if (Task_Delay_Is_Delay() == 0)
        {
            // 如果检测到全黑的十字路口,而且是第一次检测到,说明遇上了避障区前面的那个大十字路口
            if (tmp_flag == 0 && Tracing_Get_Black_Spot_Number() >= TRACING_ALL_BLACK_SPOT_NUMBER-2)
            {
                tmp_flag = 1;

            }
            
            // 如果之前检测到过十字路口,而现在8路灰度传感器压到的黑点数量很少
            if (tmp_flag == 1 && Tracing_Get_Black_Spot_Number() <= TRACING_ALL_BLACK_SPOT_NUMBER-3)
            {
#ifdef DEBUG
                printf("进障碍区\n");
#endif
                // 切换状态为当前小车进入障碍区
                Task_Status = TASK_STATUS_IN_OBSTACLE_AREA;

                // 清空临时标志位
                tmp_flag = 0;

                // 蜂鸣器短鸣
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // 停止寻迹
                Tracing_Stop();
            }
        }
        else
        {
            // 如果十字路口延时检测delay时间还没结束

            // 把两个临时标志位先清掉
            tmp_flag = 0;
            tmp_flag2 = 0;

        }
        
        
        break;
    }

    // 小车进入障碍区
    case TASK_STATUS_IN_OBSTACLE_AREA:
    {

        break;
    }

	}
}// End of void Task_Timer_Handle(void)


/******************* (C) COPYRIGHT 2018 陈苏阳 *****END OF FILE******************/


