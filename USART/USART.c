#include"GLOBAL.H"
#include"USART.H"
#include "stdio.h"

/*----------------------------
初始化串口
----------------------------*/

void Usart_init(void)  //115200bps@33.1776MHz
{
	  SCON = 0x50;                        //8位可变波特率
    AUXR |= 0x01 << AUXR_T1X12_POS;       //定时器1为1T模式
    AUXR &= ~(0x01 << AUXR_UART_M0X6_POS);//串口1为12分频
    AUXR &= ~(0x01 << AUXR_SIST2_POS);  // 串口1使用定时器1作为波特率发生器

    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    TH1 = (65536 - (FOSC/4/BAUD))>>8;
    TR1 = 1;                    //定时器1开始启动
	
	#ifdef DEBUG
		// 为了使用printf,需要下列设置
		TI=1;
	#endif
}

/*----------------------------
发送串口数据
----------------------------*/
void Data_sending(uchar dat)
{
    while (busy);                    //等待前一个数据发送完成
	  busy = 1;
	  SBUF = dat;
}


/*----------------------------
接收串口数据
----------------------------*/
void Data_receiving(void)
{
    while (busy);                    //等待前一个数据接收完成
    busy = 1;                         //清除接收标志
    receive = SBUF;                     //接收数据
}
/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    Data_sending(*s++);         //发送当前字符
}
