/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Motors_Break.c
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  С����������
*******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#include "Motors_Break.h"
#include "Global.h"

/* Private variables ---------------------------------------------------------*/
unsigned char Motors_Break_Status = MOTORS_BREAK_STATUS_IDLE;      // ��ǰС��������������״̬
unsigned char Motors_Break_Delay_Time_Cnt = 0;                // С�������������Ƶȴ�ʱ����� 
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Motors_Break_Start
* Description    :  ��ʼ����С��������������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Motors_Break_Start(void)
{

    // ���ֹͣ
    Motors_stop();

    // ��delayʱ���������һ����ֵ
    Motors_Break_Delay_Time_Cnt = MOTORS_BREAK_MOTOR_STOP_FIRST_DELAY_TIME;

    // ����ǰ״̬����Ϊ��һ��ֹͣ�ȴ�
    Motors_Break_Status = MOTORS_BREAK_STATUS_FIRST_STOP_DELAY;

}// End of void Motors_Break_Start(void)


/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Motors_Break_Is_Ok
* Description    :  ��ѯС���������������Ƿ��Ѿ����
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
*                           ������@2018-11-24
* Function Name  :  Motors_Break_Timer_Handle
* Description    :  �������_��ʱ��������(�ڶ�ʱ���ж��е���)
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Motors_Break_Timer_Handle(void)
{
    switch (Motors_Break_Status)
    {
        // �����ǰ���ڵ�һ��ͣ���ȴ�״̬
        case MOTORS_BREAK_STATUS_FIRST_STOP_DELAY:
        {
            // ����ȴ�ʱ�仹û����,ʱ�����--
            if (Motors_Break_Delay_Time_Cnt > 0)
            {
                Motors_Break_Delay_Time_Cnt--;
            }
            else
            {
                // ����ȴ�ʱ���Ѿ�����

                MotorL_setting_auto_dir(-40);
                MotorR_setting_auto_dir(-40);

                // ����ǰ״̬����Ϊ���ڵȴ����ߵĳ���
                Motors_Break_Status = MOTORS_BREAK_STATUS_WAIT_BLACK_LINE;
            }
            break;
        }

        // �����ǰ���ڵȴ����߳���״̬
        case MOTORS_BREAK_STATUS_WAIT_BLACK_LINE:
        {
            // ������߳�����
            if (SNR0 == 0 || SNR1 == 0)
            {
                // ���ֹͣ
                Motors_stop();

                // ���õ�����������Ϊ����״̬
                Motors_Break_Status = MOTORS_BREAK_STATUS_IDLE;
            }
            else
            {
                // ������߻�û������ֱ���˳����ѭ��,�ȴ��´μ��
            }
            break;
        }
    }
}// End of void Motors_Break_Timer_Handle(void)




/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/

