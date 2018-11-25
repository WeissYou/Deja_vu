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
 	ET0 = 1;			 //��ʱ��0�ж�����
	
   
	#ifndef DEBUG
	ES = 1;        //ʹ�ܴ����ж�
	#endif
    
	EA = 1;			   //���жϴ�
}

/*----------------------------
��ʱ��0�жϺ���
----------------------------*/
void Timer0_routine(void) interrupt 1 using 0
{   

    unsigned char i = 0;

    // ��ȡ��·�Ҷȴ�������ADC����
    for (i = 0; i < 8; i++)adc[i] = ADC_Get_Channel_Data(i);

    //���ݴ��� 
	Data_processing();              	

    // ��������
    Task_Timer_Handle();

    // ����С�������������ƴ�����
    Motors_Break_Timer_Handle();        

    // ��������������Ʋ�������
    if(Motors_Break_Is_Ok())
    {
        W_LED_OFF();
        //ѭ�����ƴ����� 
        Tracing_Timer_Handle();        
    }
    else
    {
        W_LED_ON();
    }

    // ������������
    Buzzer_Timer_Handle();              
	

}


/*----------------------------
UART �жϷ������
-----------------------------*/

#ifndef DEBUG
void Usart(void) interrupt 4 using 2
{
    if (RI)
    {
        RI = 0;                 //���RIλ
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
        busy = 0;               //��æ��־
    }
}

#endif
