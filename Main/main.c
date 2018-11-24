#include"INTERRUPT.H"
#include"GLOBAL.H"
#include"USART.H"
#include"TIMER.H"
#include"MOTOR.H"
#include"ADC.H"
#include"PWM.H"

#include "stdio.h"

/***** ������ *****/
void main()
{						
	GPIO_init();					  //��ʼ������ 
  Usart_init();					//��ʼ������
	Interrupt_init();			//��ʼ���ж�	
	
  Timers_init();					//��ʱ����ʼ��
  ADC_init();					  //��ʼ��ADC
  //MotorL_setting(80,1);
	//MotorR_setting(80,1);
	//pwms_enable();
	while(1)
  {
		  ADCResult_getting();  //ADC�����ȡ
	}
	 
}	
 
