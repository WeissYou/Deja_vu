#include"Global.h"
#include<Motor.h>
#include"PWM.h"
/***** ���� *****/
void MotorL_setting(uchar speed,uchar dir)  //���������			   
{
  pwmL_setting(speed);		 //�ı�speedȡֵ��1~100���ı�ռ�ձ�
  if(dir == 1)				     //dirȡ1ǰ����dirȡ0����
  {
    IN1 = 1;
	IN2 = 0;
  }
  if(dir == 0) 
  {
    IN1 = 0;
	IN2 = 1;
  }
}
void MotorR_setting(uchar speed,uchar dir)  //�Ҳ�������		   
{
  pwmR_setting(speed);
  if(dir == 1)
  {
    IN3 = 1;
	IN4 = 0;
  }
  if(dir == 0) 
  {
    IN3 = 0;
	IN4 = 1;
  }
}

void Motors_stop(void)  		  //����������µ�ͣ��
{							 
  IN1 = 0;
  IN2 = 0;
  IN3 = 0;
  IN4 = 0;
}

void Motors_break(void)  //���ͣת
{ 
	IN1 = 0;
  IN2 = 0;
  IN3 = 0;
  IN4 = 0;
	
	Delay(20);
	
  while(SNR0 == 0 || SNR1 == 0)
	{
    MotorL_setting(40,0);
		MotorR_setting(40,0);
	}
	
	IN1 = 0;
  IN2 = 0;
  IN3 = 0;
  IN4 = 0;
}