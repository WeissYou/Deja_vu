/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Task.c
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  ������
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
volatile unsigned char Task_Status = TASK_STATUS_STARTING_POINT_STANDBY;        // ����״̬
volatile unsigned int Task_Delay_Time_Cnt = 0;                                  // �����е���������ʱʱ�����
    
volatile unsigned char tmp_flag=0;																							// ��ʱflag
volatile unsigned char tmp_flag2 = 0;																						// ��ʱflag2
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Task_Delay_Start
* Description    :  ������ʱ��ʼ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Task_Delay_Start(unsigned int time)
{
    // ������ʱʱ��
    Task_Delay_Time_Cnt = time;
}// End of void Task_Delay_Start(unsigned int time)


/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Task_Delay_Is_Delay
* Description    :  ������ʱ�Ƿ�����ʱ��
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
*                           ������@2018-11-24
* Function Name  :  Task_Timer_Handle
* Description    :  ����ʱ��������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Task_Timer_Handle(void)
{

    // ���������ʱʱ���������ֵ,��������ʱʱ�����--
    if (Task_Delay_Time_Cnt>0)Task_Delay_Time_Cnt--;

	switch (Task_Status)
	{
    // ��ǰ����������״̬
    case TASK_STATUS_STARTING_POINT_STANDBY:
    {
        // ���Ѱ������������ȫ��
        if (Tracing_Get_Black_Spot_Number() >= TRACING_ALL_BLACK_SPOT_NUMBER)
        {
            // ��ʼѰ������
            Tracing_Start();
					
            // ����������
            Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

            // ��ʱ��������������
            Task_Delay_Start(TASK_STARTING_POINT_DELAY_TIME);
			
#ifdef DEBUG
            printf("������������\n");
#endif		
            // �л�״̬Ϊ���ڽ���������
            Task_Status=TASK_STATUS_IN_LOADING_AREA;
        }
        else
        {
            // �������Ѱ������������ȫ��
            // ֹͣѰ������
            Tracing_Stop();
        }
        break;
    }

    // ��ǰС�����ڽ���������
    case TASK_STATUS_IN_LOADING_AREA:
    {
        // ������ڲ���Task Delay��,˵����ʱ�����������������ʱ�Ѿ���ȥ
        if (Task_Delay_Is_Delay() == 0)
        {
            // �����⵽ȫ�ڵ�ʮ��·��(��Ϊʮ��·�ڱȽ�С,���Էſ���������Ҫ�ĺڵ���),˵������������������ǰ���Ǹ�Сʮ��·������ʱ��־λû����λ(��һ�μ�⵽ʮ��·��)
            if (tmp_flag ==0 && (Tracing_Get_Black_Spot_Number() >= TRACING_ALL_BLACK_SPOT_NUMBER-3))
            {
                // ������ʱ��־λ��λ
                tmp_flag = 1;
                // ����������
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // ʧ��Ѱ�����Ƶ�ȫ��ͣ������
                Tracing_Disnable_All_White_Stop();

                // �����ʱ��־λ2
                tmp_flag2 = 0;
            }

            // �����������������һ��ͣ��λ,���ǵ�һ������
            if (tmp_flag2==0 && SNR0 == 1 && SNR1 == 1)
            {
                // ��ʱ��־λ��λ
                tmp_flag2 = 1;

                // �����������С���Ѿ���������ƽ̨����,С���˶��ٶȼ���
                Tracing_Set_Speed_Half();

                // ����������
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);
							
			    // ֹͣѰ������
				Tracing_Stop();
							
                // ��ʼ����С��������������
                Motors_Break_Start();
							
                // �л�״̬Ϊ��ǰС��������������1��ͣ��λ
                Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_1;

            }
        }
		else
		{
			// �������Task delay��,˵����һ״̬<<������>>��������õ�delayʱ�仹û��
			// ������˳���ʼ��һ����ʱ��־λ
			tmp_flag=0;
		}
		break;
    }
    // ��ǰС��������������1��ͣ��λ
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_1:
    {
        // ���С���������������Ѿ���С��λ���������
        if (Motors_Break_Is_Ok())
        {
#ifdef DEBUG
            printf("��������1��λ\n");
#endif
            // �л�״̬Ϊ��ǰС��������������1��ͣ��λ��ִ�л�е�ֲ���
            Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_1_WORKING;

            // ȷ����ʱ��־λ�Ѿ������
            tmp_flag=0;
        }

        break;
    }

    // ��ǰС��������������1��ͣ��λ��ִ�л�е�ֲ���
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_1_WORKING:
    {

        // ����ǵ�һ�����б�״̬,��ʱ��־λ��û����λ
        if (tmp_flag == 0)
        {
            // ����һ����ʱ���delay��ģ��ץȡ����
            Task_Delay_Start(200);

            // ����������
            Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

            // ��ʱ��־λ��λ
            tmp_flag = 1;
        }
        // ����������е�۵�ץȡ����
        


        if(Task_Delay_Is_Delay()==0)//if (��е�۲������)
        {
            // ȷ�ϲ�����Ϻ���Ѱ������
            Tracing_Start();

            // �ж�����SNR0�Լ�SNR1�Ѿ��뿪��ɫ(���ɿ�,��Ҫ�����delay)
            if (SNR0 == 0 && SNR1 == 0)
            {

                // ��ʱһ��ʱ��,ȷ���´μ��SNR0�Լ�SNR1��ʱ�����Ѿ��뿪��1��ͣ��λ����������С��ʮ��·��
                Task_Delay_Start(TASK_OUT_PARKING_SPACE_SNR_CHECK_DELAY_TIME);
#ifdef DEBUG
                printf("��������2��λ\n");
#endif
                // �л�״̬Ϊ��ǰС����������ǰ����������2��ͣ��λ��·��
                Task_Status = TASK_STATUS_GOING_LOADING_AREA_PARKING_SPACE_2;

                // ȷ����ʱ��־λ�Ѿ������
                tmp_flag = 0;
            }
        }
        break;
    }
    //��ǰС����������ǰ����������2��ͣ��λ��·��
    case TASK_STATUS_GOING_LOADING_AREA_PARKING_SPACE_2:
    {
        // �������SNR��ʱ����Delayʱ���Ѿ�����
        if (Task_Delay_Is_Delay()==0)
        {
            // ��������������ĵڶ���ͣ��λ,���ǵ�һ������
            if (tmp_flag ==0 && SNR0 == 1 && SNR1 == 1)
            {
                // ��ʱ��־λ��λ
                tmp_flag = 1;

                // ����������
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // ֹͣѰ������
	            Tracing_Stop();
								
                // ��ʼ����С��������������
                Motors_Break_Start();
#ifdef DEBUG
                printf("����������2��λ\n");
#endif
                // �л�״̬Ϊ��ǰС��������������2��ͣ��λ
                Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_2;

                // ȷ����ʱ��־λ�Ѿ������
                tmp_flag = 0;
            }
        }
        else
        {
            // ��SNR��ʱ���delayʱ�仹δ����,���������ʱ��־λ
            tmp_flag = 0;
            tmp_flag2 = 0;
        }
        break;
    }

    // ��ǰС��������������2��ͣ��λ
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_2:
    {
        // ���С���������������Ѿ���С��λ���������
        if (Motors_Break_Is_Ok())
        {

            // �л�״̬Ϊ��ǰС��������������2��ͣ��λ��ִ�л�е�ֲ���
            Task_Status = TASK_STATUS_LOADING_AREA_PARKING_SPACE_2_WORKING;

            // ȷ����ʱ��־λ�Ѿ������
            tmp_flag = 0;
        }

        break;
    }

    // ��ǰС��������������2��ͣ��λ��ִ�л�е�ֲ���
    case TASK_STATUS_LOADING_AREA_PARKING_SPACE_2_WORKING:
    {

        // ����ǵ�һ�����б�״̬,��ʱ��־λ��û����λ
        if (tmp_flag == 0)
        {
            // ����һ����ʱ���delay��ģ��ץȡ����
            Task_Delay_Start(200);

            // ����������
            Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

            // ��ʱ��־λ��λ
            tmp_flag = 1;
        }



        if (Task_Delay_Is_Delay() == 0)//if (��е�۲������)
        {
            // ȷ�ϲ�����Ϻ���Ѱ������
            Tracing_Start();
            
            // �ָ�Ѱ�����ٶ�����
            Tracing_Set_Speed_All();

            // �ж�����SNR0�Լ�SNR1�Ѿ��뿪��ɫ(���ɿ�,��Ҫ�����delay)
            if (SNR0 == 0 && SNR1 == 0)
            {
                // ����������
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // ��ʱһ��ʱ��,ȷ���´μ��ʮ��·�ڵ�ʱ�򲻻���Ϊ����ʱ������̬������������ʶ��
                Task_Delay_Start(TASK_OUT_LOADING_AREA_CROSS_ROADS_CHECK_DELAY_TIME);
#ifdef DEBUG
                printf("�˳�������\n");
#endif
                // �л�״̬Ϊ��ǰС�������˳�������״̬
                Task_Status = TASK_STATUS_OUT_LOADING_AREA;

                // ȷ����ʱ��־λ�Ѿ������
                tmp_flag = 0;
            }
        }
        break;
    }

    // ��ǰС�������˳�������״̬
    case TASK_STATUS_OUT_LOADING_AREA:
    {
     
        // �������ʮ��·����ʱ����Delayʱ���Ѿ�����
        if (Task_Delay_Is_Delay() == 0)
        {
            // �����⵽ȫ�ڵ�ʮ��·��,�����ǵ�һ�μ�⵽,˵�������˱�����ǰ����Ǹ���ʮ��·��
            if (tmp_flag == 0 && Tracing_Get_Black_Spot_Number() >= TRACING_ALL_BLACK_SPOT_NUMBER-2)
            {
                tmp_flag = 1;

            }
            
            // ���֮ǰ��⵽��ʮ��·��,������8·�Ҷȴ�����ѹ���ĺڵ���������
            if (tmp_flag == 1 && Tracing_Get_Black_Spot_Number() <= TRACING_ALL_BLACK_SPOT_NUMBER-3)
            {
#ifdef DEBUG
                printf("���ϰ���\n");
#endif
                // �л�״̬Ϊ��ǰС�������ϰ���
                Task_Status = TASK_STATUS_IN_OBSTACLE_AREA;

                // �����ʱ��־λ
                tmp_flag = 0;

                // ����������
                Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);

                // ֹͣѰ��
                Tracing_Stop();
            }
        }
        else
        {
            // ���ʮ��·����ʱ���delayʱ�仹û����

            // ��������ʱ��־λ�����
            tmp_flag = 0;
            tmp_flag2 = 0;

        }
        
        
        break;
    }

    // С�������ϰ���
    case TASK_STATUS_IN_OBSTACLE_AREA:
    {

        break;
    }

	}
}// End of void Task_Timer_Handle(void)


/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/


