#include"INTERRUPT.H"
#include"GLOBAL.H"
#include"USART.H"
#include"TIMER.H"
#include"MOTOR.H"
#include"ADC.H"
#include"PWM.H"
#include "Buzzer.h"
#include  "stdio.h"
/***** ������ *****/
void main()
{						
  GPIO_init();					        // ��ʼ������ 
  Buzzer_Init();                        // ��ʼ��������
  Usart_init();					        // ��ʼ������
  Interrupt_init();			            // ��ʼ���ж�	
	
  // ����������
  Buzzer_Tweet(BUZZER_SHORT_TWEET_TIME);
	
	Timers_init();					    // ��ʱ����ʼ��
  ADC_init();					        // ��ʼ��ADC
	
  while(1)
  {
    // ADC�����ȡ
    //ADCResult_getting();  
  }
	 
}	
 
