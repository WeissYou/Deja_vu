/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Task.h
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  ������
*******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define  __TASK_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
typedef enum
{
    TASK_STATUS_STARTING_POINT_STANDBY = 0,             // ��ǰС������������״̬
    TASK_STATUS_IN_LOADING_AREA,                        // ��ǰС����������Ҫ����������״̬
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_1,           // ��ǰС��������������1��ͣ��λ
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_1_WORKING,   // ��ǰС��������������1��ͣ��λ��ִ�л�е�ֲ���
    TASK_STATUS_GOING_LOADING_AREA_PARKING_SPACE_2,     // ��ǰС����������ǰ����������2��ͣ��λ��·��
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_2,           // ��ǰС��������������2��ͣ��λ
    TASK_STATUS_LOADING_AREA_PARKING_SPACE_2_WORKING,   // ��ǰС��������������2��ͣ��λ��ִ�л�е�ֲ���
    TASK_STATUS_OUT_LOADING_AREA,                       // ��ǰС�������˳�������״̬
    TASK_STATUS_IN_OBSTACLE_AREA,                       // ��ǰС�������ϰ���
    TASK_STATUS_OUT_OBSTACLE_AREA,                      // ��ǰС���˳��ϰ���
    TASK_STATUS_CORRECTION,                             // ��ǰС�����ھ�ƫ
    TASK_STATUS_CUTTING_PARKING_SPACE_1,                // ��ǰС��������������1��ͣ��λ
    TASK_STATUS_CUTTING_PARKING_SPACE_2,                // ��ǰС��������������2��ͣ��λ
    TASK_STATUS_END_POINT_STANDBY                       // ��ǰС�������յ����״̬
}TASK_STATUS;// ����״̬


/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

void Task_Timer_Handle(void);

#endif /* __TASK_H */




/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/