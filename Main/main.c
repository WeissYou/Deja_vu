#include"INTERRUPT.H"
#include"GLOBAL.H"
#include"USART.H"
#include"TIMER.H"
#include"MOTOR.H"
#include"ADC.H"
#include"PWM.H"
#include "Buzzer.h"
#include  "stdio.h"
/***** 主函数 *****/
void main()
{						
  GPIO_init();					        // 初始化引脚 
  Buzzer_Init();                        // 初始化蜂鸣器
  Usart_init();					        // 初始化串口
  Interrupt_init();			            // 初始化中断	
	
  // 蜂鸣器短鸣
  Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);
	
	Timers_init();					    // 定时器初始化
  ADC_init();					        // 初始化ADC
	
  while(1)
  {
    // ADC结果读取
    //ADCResult_getting();  
  }
	 
}	
 
