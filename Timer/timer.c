#include"GLOBAL.H"
#include<TIMER.H>

/***** ��ʱ������ *****/

void Timers_init(void)
{
 AUXR &= ~(0x01 << AUXR_T0x12_POS);  //��ʱ��0Ϊ12Tģʽ
 //AUXR &= ~(0x01 << AUXR_T2x12_POS);  //��ʱ��2Ϊ12Tģʽ

 //23����@33.1776MHz
 TH0 = 0x07;		//���ö�ʱ��ֵ
 TL0 = 0x9a;		//���ö�ʱ��ֵ
 TF0 = 0;		    //���TF0��־
	
 //1����@33.1776MHz
 //T2H = 0x94;
 //T2L = 0x00;
	
 TR0 = 1;		                    //��ʱ��0��ʼ��ʱ
 //AUXR |= 0x01 << AUXR_T2R_POS;  //��ʱ��2��ʼ��ʱ
}	