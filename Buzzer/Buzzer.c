/******************** (C) COPYRIGHT 2018 陈苏阳 **********************************
* File Name          :  Buzzer.c
* Author             :  陈苏阳
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  24/11/2018
* Description        :  蜂鸣器
*******************************************************************************/





/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "Buzzer.h"
/* Private variables ---------------------------------------------------------*/
unsigned int buzzer_tweet_time_cnt=0;              // 剩余的鸣叫的时间

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/



/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Buzzer_Init
* Description    :  蜂鸣器初始化
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Buzzer_Init(void)
{
    // 设置P00口为开漏
    P0M1 |= 0x01;
    P0M0 |= 0x01;
}// End of void Buzzer_Init(void)

/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  _Buzzer_ON 
* Description    :  蜂鸣器鸣叫
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void _Buzzer_ON(void)
{
    BUZZER_PIN = 0;
}// End of void _Buzzer_ON(void)



/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  _Buzzer_OFF
* Description    :  蜂鸣器关闭
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void _Buzzer_OFF(void)
{
    BUZZER_PIN = 1;
}// End of void _Buzzer_OFF(void)



/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Buzzer_Tweet
* Description    :  蜂鸣器鸣叫
* Input          :  unsigned char tweet_time            // 鸣叫持续的时间
* Output         :  None
* Return         :  None
*******************************************************************************/
void Buzzer_Tweet(unsigned char tweet_time)
{
    // 设置剩余鸣叫时间
    buzzer_tweet_time_cnt = tweet_time;

    // 开启蜂鸣器
    _Buzzer_ON();

}// End of void Buzzer_Tweet(unsigned char tweet_time)


/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Buzzer_Timer_Handle
* Description    :  蜂鸣器定时处理函数
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Buzzer_Timer_Handle(void)
{
    // 检查还有没有剩余鸣叫时间
    if (buzzer_tweet_time_cnt)
    {
        // 开启蜂鸣器
        _Buzzer_ON();
        buzzer_tweet_time_cnt--;
    }
    else
    {
        // 关闭蜂鸣器
        _Buzzer_OFF();
    }
}// End of void Buzzer_Timer_Handle(void)

/******************* (C) COPYRIGHT 2018 陈苏阳 *****END OF FILE******************/

