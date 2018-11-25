/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  Buzzer.c
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  ������
*******************************************************************************/





/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "Buzzer.h"
/* Private variables ---------------------------------------------------------*/
unsigned int buzzer_tweet_time_cnt=0;              // ʣ������е�ʱ��

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/



/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Buzzer_Init
* Description    :  ��������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Buzzer_Init(void)
{
    // ����P00��Ϊ��©
    P0M1 |= 0x01;
    P0M0 |= 0x01;
}// End of void Buzzer_Init(void)

/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  _Buzzer_ON 
* Description    :  ����������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void _Buzzer_ON(void)
{
    BUZZER_PIN = 0;
}// End of void _Buzzer_ON(void)



/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  _Buzzer_OFF
* Description    :  �������ر�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void _Buzzer_OFF(void)
{
    BUZZER_PIN = 1;
}// End of void _Buzzer_OFF(void)



/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Buzzer_Tweet
* Description    :  ����������
* Input          :  unsigned char tweet_time            // ���г�����ʱ��
* Output         :  None
* Return         :  None
*******************************************************************************/
void Buzzer_Tweet(unsigned char tweet_time)
{
    // ����ʣ������ʱ��
    buzzer_tweet_time_cnt = tweet_time;

    // ����������
    _Buzzer_ON();

}// End of void Buzzer_Tweet(unsigned char tweet_time)


/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Buzzer_Timer_Handle
* Description    :  ��������ʱ������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Buzzer_Timer_Handle(void)
{
    // ��黹��û��ʣ������ʱ��
    if (buzzer_tweet_time_cnt)
    {
        // ����������
        _Buzzer_ON();
        buzzer_tweet_time_cnt--;
    }
    else
    {
        // �رշ�����
        _Buzzer_OFF();
    }
}// End of void Buzzer_Timer_Handle(void)

/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/

