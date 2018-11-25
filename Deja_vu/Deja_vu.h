/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Deja_vu.h
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  寻迹
*******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEJA_VU_H
#define  __DEJA_VU_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    TRACING_STATUS_STATUS_IDLE = 0,         // 当前小车寻迹机制处于空闲状态
    TRACING_STATUS_STATUS_RUNING,           // 当前寻迹机制处于运行状态
}TRACING_STATUS;// 寻迹机制的运行状态


/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/

void Tracing_Start(void);               // 开始寻迹机制
void Tracing_Set_Speed_Half(void);      // 设置寻迹速度为半速
void Tracing_Enable_All_White_Stop(void); // 使能全白停车功能
void Tracing_Disnable_All_White_Stop(void); // 失能全白停车功能
void Tracing_Set_Speed_All(void);       // 设置寻迹速度为半速
void Tracing_Stop(void);                // 停止寻迹机制
unsigned char Tracing_Get_Black_Spot_Number(void);      // 获取当前寻迹传感器压到的黑点个数
void Tracing_Timer_Handle(void);        //循迹定时器处理函数

#endif /* __DEJA_VU_H */





/******************* (C) COPYRIGHT 2018 陈苏阳 *****END OF FILE******************/