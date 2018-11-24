#include"Global.h"
#include<PWM.h>
#include "stdio.h"

/***** 函数 *****/
void pwmL_setting(uchar duty)	  	
{
    P_SW2 |= 0x80;                //使能访问XSFR
    PWM6T1 = 0x0000;                //设置PWM6第1次反转的PWM计数
    PWM6T2 = CYCLE * duty / 100;    //设置PWM6第2次反转的PWM计数
                                    //占空比为(PWM6T2-PWM6T1)/PWMC
    PWM6CR = 0x08;                  //选择PWM6输出到P0.7,不使能PWM2中断
    P_SW2 &= ~0x80;
}

void pwmR_setting(uchar duty)
{
    P_SW2 |= 0x80;                //使能访问XSFR
    PWM7T1 = 0x0000;                //设置PWM7第1次反转的PWM计数
    PWM7T2 = CYCLE * duty / 100;    //设置PWM7第2次反转的PWM计数
                                    //占空比为(PWM7T2-PWM7T1)/PWMC
    PWM7CR = 0x08;                  //选择PWM7输出到P0.6,不使能PWM3中断
    P_SW2 &= ~0x80;
}

void pwms_enable(void)			    //每处pwm设定均需调用该函数，且须置于所有pwmn_setting之后
{
  	P_SW2 |= 0x80; 
	PWMCFG = 0x00;                  //配置PWM的输出初始电平为低电平
    PWMCKS = 0x0c;                  //选择PWM的时钟为Fosc/(0+12)
	PWMC = CYCLE;                   //设置PWM周期
    PWMCR = 0xB0;                   //使能PWM模块	 
	P_SW2 &= ~0x80;   
}



