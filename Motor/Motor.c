#include"Global.h"
#include<Motor.h>
#include"PWM.h"
/***** 函数 *****/
void MotorL_setting(uchar speed,uchar dir)  //左侧电机控制			   
{
  pwmL_setting(speed);		 //改变speed取值（1~100）改变占空比
  if(dir == 1)				     //dir取1前进，dir取0后退
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
void MotorR_setting(uchar speed,uchar dir)  //右侧电机控制		   
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

void Motors_stop(void)  		  //非正常情况下的停车
{							 
  IN1 = 0;
  IN2 = 0;
  IN3 = 0;
  IN4 = 0;
}

void Motors_break(void)  //电机停转
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