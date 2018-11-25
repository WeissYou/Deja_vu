/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Task.h
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  任务处理
*******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define  __TASK_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
typedef enum
{
    TASK_STATUS_STARTING_POINT_STANDBY = 0,             // 当前小车处于起点待机状态
    TASK_STATUS_IN_LOADING_AREA,                        // 当前小车处于马上要进入上料区状态
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_1,           // 当前小车处于上料区第1个停车位
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_1_WORKING,   // 当前小车处于上料区第1个停车位上执行机械手操作
    TASK_STATUS_GOING_LOADING_AREA_PARKING_SPACE_2,     // 当前小车处于正在前往上料区第2个停车位的路上
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_2,           // 当前小车处于上料区第2个停车位
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_2_WORKING,   // 当前小车处于上料区第2个停车位上执行机械手操作
    TASK_STATUS_OUT_LOADING_AREA,                       // 当前小车处于退出上料区状态
    TASK_STATUS_IN_OBSTACLE_AREA,                       // 当前小车进入障碍区
    TASK_STATUS_OUT_OBSTACLE_AREA,                      // 当前小车退出障碍区
    TASK_STATUS_CORRECTION,                             // 当前小车正在纠偏
    TASK_STATUS_CUTTING_PARKING_SPACE_1,                // 当前小车处于下料区第1个停车位
    TASK_STATUS_CUTTING_PARKING_SPACE_2,                // 当前小车处于下料区第2个停车位
    TASK_STATUS_END_POINT_STANDBY                       // 当前小车处于终点待机状态
}TASK_STATUS;// 任务状态


/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

void Task_Timer_Handle(void);

#endif /* __TASK_H */




/******************* (C) COPYRIGHT 2018 陈苏阳 *****END OF FILE******************/