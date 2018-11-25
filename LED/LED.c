/******************** (C) COPYRIGHT 2018 ³ÂËÕÑô **********************************
* File Name          :  LED.c
* Author             :  ³ÂËÕÑô
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
*                           ³ÂËÕÑô@2018-11-25
* Function Name  :  LED_Init
* Description    :  LED³õÊ¼»¯
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
*                           ³ÂËÕÑô@2018-11-25
* Function Name  :  W_LED_ON
* Description    :  µãÁÁ°×µÆ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void W_LED_ON(void)
{
    W_LED_PIN = 1;
}// End of void W_LED_ON(void)


 /*******************************************************************************
 *                           ³ÂËÕÑô@2018-11-25
 * Function Name  :  W_LED_OFF
 * Description    :  Ï¨Ãð°×µÆ
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void W_LED_OFF(void)
{
    W_LED_PIN = 0;
}// End of void W_LED_OFF(void)



 /*******************************************************************************
 *                           ³ÂËÕÑô@2018-11-25
 * Function Name  :  G_LED_ON
 * Description    :  µãÁÁÂÌµÆ
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void G_LED_ON(void)
{
    G_LED_PIN = 1;
}// End of void G_LED_ON(void)


 /*******************************************************************************
 *                           ³ÂËÕÑô@2018-11-25
 * Function Name  :  G_LED_OFF
 * Description    :  Ï¨ÃðÂÌµÆ
 * Input          :  None
 * Output         :  None
 * Return         :  None
 *******************************************************************************/
void G_LED_OFF(void)
{
    G_LED_PIN = 0;
}// End of void G_LED_OFF(void)


/*******************************************************************************
*                           ³ÂËÕÑô@2018-11-25
* Function Name  :  LED_Line_Show
* Description    :  ÏÔÊ¾LEDµÆÌõ
* Input          :  unsigned char led_data
* Output         :  None
* Return         :  None
*******************************************************************************/
void LED_Line_Show(unsigned char led_data)
{
    if (led_data&(0x01 << 0))
    {
        LED_LINE_0 = 1;
    }
    else
    {
        LED_LINE_0 = 0;
    }

    if (led_data&(0x01 << 1))
    {
        LED_LINE_1 = 1;
    }
    else
    {
        LED_LINE_1 = 0;
    }

    if (led_data&(0x01 << 2))
    {
        LED_LINE_2 = 1;
    }
    else
    {
        LED_LINE_2 = 0;
    }

    if (led_data&(0x01 << 3))
    {
        LED_LINE_3 = 1;
    }
    else
    {
        LED_LINE_3 = 0;
    }

    if (led_data&(0x01 << 4))
    {
        LED_LINE_4 = 1;
    }
    else
    {
        LED_LINE_4 = 0;
    }

    if (led_data&(0x01 << 5))
    {
        LED_LINE_5 = 1;
    }
    else
    {
        LED_LINE_5 = 0;
    }

    if (led_data&(0x01 << 6))
    {
        LED_LINE_6 = 1;
    }
    else
    {
        LED_LINE_6 = 0;
    }

    if (led_data&(0x01 << 7))
    {
        LED_LINE_7 = 1;
    }
    else
    {
        LED_LINE_7 = 0;
    }

}// End of void LED_Line_Show(unsigned char led_data)



/******************* (C) COPYRIGHT 2018 ³ÂËÕÑô *****END OF FILE******************/