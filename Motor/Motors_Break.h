/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Motors_Break.h
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  С����������
*******************************************************************************/




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTORS_BREAK_H
#define  __MOTORS_BREAK_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define MOTORS_BREAK_MOTOR_STOP_FIRST_DELAY_TIME                                10           //С�������������ƿ�ʼ���ͣ��ʱ��(��λΪ������������Time_Handle������ִ������)


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    MOTORS_BREAK_STATUS_IDLE = 0,         // ��ǰС�������������ƴ��ڿ���״̬
    MOTORS_BREAK_STATUS_FIRST_STOP_DELAY, // ��ǰС�������������ƴ��ڵ�һ�εȴ���(�ոտ�ʼ��������,��ͣת�����ȴ�����ʱ��)
    MOTORS_BREAK_STATUS_WAIT_BLACK_LINE,  // ��ǰС�����˻������ڵȴ�����(С��������)
}MOTORS_BREAK_STATUS;// С�������������Ƶ�����״̬

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Motors_Break_Start(void);
unsigned char Motors_Break_Is_Ok(void);
void Motors_Break_Timer_Handle(void);
#endif /* __MOTORS_BREAK_H */




/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/