#include"INTERRUPT.H"
#include"GLOBAL.H"
#include"USART.H"
#include"TIMER.H"
#include"MOTOR.H"
#include"ADC.H"
#include"PWM.H"

#include "stdio.h"

/***** 主函数 *****/
void main()
{						
	GPIO_init();					  //初始化引脚 
  Usart_init();					//初始化串口
	Interrupt_init();			//初始化中断	
	
  Timers_init();					//定时器初始化
  ADC_init();					  //初始化ADC
  //MotorL_setting(80,1);
	//MotorR_setting(80,1);
	//pwms_enable();
	while(1)
  {
		  ADCResult_getting();  //ADC结果读取
	}
	 
}	
 
