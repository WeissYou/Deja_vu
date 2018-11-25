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
extern bit busy;            //串口忙位 

/***** 声明全局函数 *****/
void GPIO_init(void);		 //设置所有引脚为GPIO
void Delay(uint n);          //延时n毫秒

/***** 宏定义 *****/


// 8路寻迹传感器压中多少黑点即可认为是压中全黑
#define TRACING_ALL_BLACK_SPOT_NUMBER   8       // 设置为压中7个黑点就认为是压中十字路口


// 蜂鸣器短鸣时间
#define BUZZER_SHORT_TWEET_TIME         20      // 设置蜂鸣器短鸣的时间为20个定时器中断周期


// 小车离开起跑线后单纯寻迹的时间(屏蔽十字路口识别以及其他识别,仅仅是寻迹)
#define TASK_STARTING_POINT_DELAY_TIME 200      // 设置小车在检测到全黑的起跑线并开启寻迹后,除了寻迹以外其他检测机制的延迟开启时间为200个定时器中断周期


// 小车离开一个停车位后重新开始SNR0以及SNR1变黑检测的延时时间
#define TASK_OUT_PARKING_SPACE_SNR_CHECK_DELAY_TIME 15  // 设置小车从一个停车位到下一个停车位的过程中,开始寻迹后SNR检测的延迟开始时间为15定时器中断周期


// 小车在上料区离开第二个停车位后到开启8路灰度传感器检测全黑之间的延时(增加这个延时是为了防止在下坡过程中导致8路灰度传感器误识别十字路口)
#define TASK_OUT_LOADING_AREA_CROSS_ROADS_CHECK_DELAY_TIME  20  // 设置小车上料区第二个停车点的SNR检测为白色后到开启十字路口识别之间的延时为20个定时器中断周期




// 白灯
#define W_LED_PIN P42

// 绿灯
#define G_LED_PIN P40

// 红灯
#define R_LED_PIN P52

// 蓝灯
#define B_LED_PIN P51

// 黄灯
#define Y_LED_PIN P50


// 8颗LED
#define LED_LINE_0 P21
#define LED_LINE_1 P34
#define LED_LINE_2 P35
#define LED_LINE_3 P36
#define LED_LINE_4 P37
#define LED_LINE_5 P55
#define LED_LINE_6 P54
#define LED_LINE_7 P53


// 两颗LED
#define SIDE_LED_0 P26
#define SIDE_LED_1 P27


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


// 蜂鸣器IO口
#define BUZZER_PIN P00

#endif