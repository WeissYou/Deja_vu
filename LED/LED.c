/******************** (C) COPYRIGHT 2018 ������ **********************************
* File Name          :  LED.c
* Author             :  ������
* CPU Type           :  STC15
* IDE                :  IAR 8.22.1
* Version            :  V1.0
* Date               :  25/11/2018
* Description        :  LED
*******************************************************************************/




/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "LED.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           ������@2018-11-25
* Function Name  :  LED_Init
* Description    :  LED��ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LED_Init(void)
{
    W_LED_PIN = 0;
    G_LED_PIN = 0;
    R_LED_PIN = 0;
    B_LED_PIN = 0;
    Y_LED_PIN = 0;
}// End of void LED_Init(void)

/*******************************************************************************
*                           ������@2018-11-25
* Function Name  :  W_LED_ON
* Description    :  �����׵�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void W_LED_ON(void)
{
    W_LED_PIN = 1;
}// End of void W_LED_ON(void)


 /*******************************************************************************
 *                           ������@2018-11-25
 * Function Name  :  W_LED_OFF
 * Description    :  Ϩ��׵�
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void W_LED_OFF(void)
{
    W_LED_PIN = 0;
}// End of void W_LED_OFF(void)



 /*******************************************************************************
 *                           ������@2018-11-25
 * Function Name  :  G_LED_ON
 * Description    :  �����̵�
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void G_LED_ON(void)
{
    G_LED_PIN = 1;
}// End of void G_LED_ON(void)


 /*******************************************************************************
 *                           ������@2018-11-25
 * Function Name  :  G_LED_OFF
 * Description    :  Ϩ���̵�
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void G_LED_OFF(void)
{
    G_LED_PIN = 0;
}// End of void G_LED_OFF(void)


/******************* (C) COPYRIGHT 2018 ������ *****END OF FILE******************/