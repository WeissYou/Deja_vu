#include"DEJA_VU.H"
#include"GLOBAL.H"
#include"USART.H"
#include"MOTOR.H"
#include"PWM.H"
#include"ADC.H"
#include "Motors_Break.h"
#include "Buzzer.h"
#include "Task.h"
#include "LED.h"
void Interrupt_init(void)
{
 	ET0 = 1;			 //定时器0中断允许
	
   
	#ifndef DEBUG
	ES = 1;        //使能串口中断
	#endif
    
	EA = 1;			   //总中断打开
}

/*----------------------------
定时器0中断函数
----------------------------*/
void Timer0_routine(void) interrupt 1 using 0
{   

    unsigned char i = 0;

    // 读取八路灰度传感器的ADC数据
    for (i = 0; i < 8; i++)adc[i] = ADC_Get_Channel_Data(i);

    //数据处理 
	Data_processing();              	

    // 任务处理函数
    Task_Timer_Handle();

    // 运行小车倒退修正机制处理函数
    Motors_Break_Timer_Handle();        

    // 如果倒退修正机制不在运行
    if(Motors_Break_Is_Ok())
    {
        W_LED_OFF();
        //循迹机制处理函数 
        Tracing_Timer_Handle();        
    }
    else
    {
        W_LED_ON();
    }

    // 蜂鸣器处理函数
    Buzzer_Timer_Handle();              
	

}


/*----------------------------
UART 中断服务程序
-----------------------------*/

#ifndef DEBUG
void Usart(void) interrupt 4 using 2
{
    if (RI)
    {
        RI = 0;                 //清除RI位
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy = 0;               //清忙标志
    }
}

#endif
