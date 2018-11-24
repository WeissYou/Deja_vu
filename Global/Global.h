#ifndef __GLOBAL_H_
#define __GLOBAL_H_

/***** 头文件 *****/
#include <STC15F2K60S2.H>
#include"intrins.h"	         //调用延时函数时包含该文件
//#include"stdio.h"            //printf头文件

/***** 声明类型 *****/
typedef unsigned char uchar;
typedef unsigned int uint;

/***** 外部声明全局变量 *****/
extern uchar code gray[8];  //ADC基准数据
extern uchar situation;			//各种循迹情况
extern uchar receive;			  //串口接收数据
extern uchar channel;       //ADC通道号
extern uchar goback;        //倒车标志
extern uchar adc[8];		    //ADC原始数据
extern uchar daten;         //处理后数据
extern uchar p1[8];         //处理后数据
extern uchar flag;          //某标志位
extern bit busy;            //串口忙位 

/***** 声明全局函数 *****/
void GPIO_init(void);		 //设置所有引脚为GPIO
void Delay(uint n);          //延时n毫秒

/***** 宏定义 *****/

//L298相关引脚
#define IN1	P24
#define IN2 P25
#define IN3 P22
#define IN4 P23
#define ENA1 P07
#define ENA2 P06

//标志线检测传感器引脚

#define SNR0 P32
#define SNR1 P33

#endif