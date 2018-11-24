#ifndef __USART_H_
#define __USART_H_

#define FOSC    33177600L
#define BAUD    115200

#define URMD    1            //0:使用定时器2作为波特率发生器
                             //1:使用定时器1的模式0(16位自动重载模式)作为波特率发生器
                             //2:使用定时器1的模式2(8位自动重载模式)作为波特率发生器

// AUXR寄存器定时器1、串口1相关bit位置
#define AUXR_T1X12_POS                  6
#define AUXR_UART_M0X6_POS              5
#define AUXR_SIST2_POS                  0

void Usart_init(void);          //串口初始化
void Data_sending(uchar dat);  //发送数据
void Data_receiving(void);	   //接收数据
void SendString(char *s);



#endif