#include"DEJA_VU.H"
#include"GLOBAL.H"
#include"USART.H"
#include"MOTOR.H"
#include"PWM.H"
#include"ADC.H"

void Interrupt_init(void)
{
 	ET0 = 1;			 //��ʱ��0�ж�����
	
	EX0 = 1;       //�ⲿ�ж�0����
	IT0 = 0;			 //�ⲿ�ж�0�����ش���
   
	ES = 1;        //ʹ�ܴ����ж�
    
	EA = 1;			   //���жϴ�
}

/*----------------------------
��ʱ��0�жϺ���
----------------------------*/
void Timer0_routine(void) interrupt 1 using 0
{   
  //��ʱ��0�жϲ���
	//SendString("Timer0 all right!");
	TR0 = 0;
	if(flag == 1)
	  {
		  flag = 0;
	    Motors_break();
	    Delay(1000);
	    MotorL_setting(50,1);
	    MotorR_setting(50,1);
	    pwms_enable();
		  Delay(20);
	  }
	else
		{
			Data_processing();  //���ݴ��� 	
	    Deja_vu();          //ѭ������   
		}
	/*
  Data_sending(0x00);  //����0x00��Ϊ��е�ۿ�ʼ�����ı�־
	while(1)
	{
    if(SBUF = 0xff)  //����0xff��Ϊ��е����ɶ����ı�־
	   break;
  }
	*/

	TR0 = 1;
}

/*----------------------------
�ⲿ�жϺ���
----------------------------*/
void Exint0_routine(void) interrupt 0 using 1  	 
{ 
	if(SNR0 == 1 && SNR1 == 1)
	{
	  flag = 1;
	}

}

/*----------------------------
UART �жϷ������
-----------------------------*/
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