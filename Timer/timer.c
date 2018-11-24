#include"GLOBAL.H"
#include<TIMER.H>

/***** 定时器函数 *****/

void Timers_init(void)
{
 AUXR &= ~(0x01 << AUXR_T0x12_POS);  //定时器0为12T模式
 //AUXR &= ~(0x01 << AUXR_T2x12_POS);  //定时器2为12T模式

 //23毫秒@33.1776MHz
 TH0 = 0x07;		//设置定时初值
 TL0 = 0x9a;		//设置定时初值
 TF0 = 0;		    //清除TF0标志
	
 //1毫秒@33.1776MHz
 //T2H = 0x94;
 //T2L = 0x00;
	
 TR0 = 1;		                    //定时器0开始计时
 //AUXR |= 0x01 << AUXR_T2R_POS;  //定时器2开始计时
}	