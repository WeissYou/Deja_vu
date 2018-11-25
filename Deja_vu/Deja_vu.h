/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Deja_vu.h
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  Ѱ��
*******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEJA_VU_H
#define  __DEJA_VU_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
    TRACING_STATUS_STATUS_IDLE = 0,         // ��ǰС��Ѱ�����ƴ��ڿ���״̬
    TRACING_STATUS_STATUS_RUNING,           // ��ǰѰ�����ƴ�������״̬
}TRACING_STATUS;// Ѱ�����Ƶ�����״̬


/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/

void Tracing_Start(void);               // ��ʼѰ������
void Tracing_Set_Speed_Half(void);      // ����Ѱ���ٶ�Ϊ����
void Tracing_Enable_All_White_Stop(void); // ʹ��ȫ��ͣ������
void Tracing_Disnable_All_White_Stop(void); // ʧ��ȫ��ͣ������
void Tracing_Set_Speed_All(void);       // ����Ѱ���ٶ�Ϊ����
void Tracing_Stop(void);                // ֹͣѰ������
unsigned char Tracing_Get_Black_Spot_Number(void);      // ��ȡ��ǰѰ��������ѹ���ĺڵ����
void Tracing_Timer_Handle(void);        //ѭ����ʱ��������

#endif /* __DEJA_VU_H */





/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/