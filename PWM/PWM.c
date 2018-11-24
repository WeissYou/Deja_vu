#include"Global.h"
#include<PWM.h>
#include "stdio.h"

/***** ���� *****/
void pwmL_setting(uchar duty)	  	
{
    P_SW2 |= 0x80;                //ʹ�ܷ���XSFR
    PWM6T1 = 0x0000;                //����PWM6��1�η�ת��PWM����
    PWM6T2 = CYCLE * duty / 100;    //����PWM6��2�η�ת��PWM����
                                    //ռ�ձ�Ϊ(PWM6T2-PWM6T1)/PWMC
    PWM6CR = 0x08;                  //ѡ��PWM6�����P0.7,��ʹ��PWM2�ж�
    P_SW2 &= ~0x80;
}

void pwmR_setting(uchar duty)
{
    P_SW2 |= 0x80;                //ʹ�ܷ���XSFR
    PWM7T1 = 0x0000;                //����PWM7��1�η�ת��PWM����
    PWM7T2 = CYCLE * duty / 100;    //����PWM7��2�η�ת��PWM����
                                    //ռ�ձ�Ϊ(PWM7T2-PWM7T1)/PWMC
    PWM7CR = 0x08;                  //ѡ��PWM7�����P0.6,��ʹ��PWM3�ж�
    P_SW2 &= ~0x80;
}

void pwms_enable(void)			    //ÿ��pwm�趨������øú�����������������pwmn_setting֮��
{
  	P_SW2 |= 0x80; 
	PWMCFG = 0x00;                  //����PWM�������ʼ��ƽΪ�͵�ƽ
    PWMCKS = 0x0c;                  //ѡ��PWM��ʱ��ΪFosc/(0+12)
	PWMC = CYCLE;                   //����PWM����
    PWMCR = 0xB0;                   //ʹ��PWMģ��	 
	P_SW2 &= ~0x80;   
}



