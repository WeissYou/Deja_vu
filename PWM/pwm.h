#ifndef __PWM_H_
#define __PWM_H_

/***** 声明PWM设置函数 *****/
void pwmL_setting(uchar duty);	//左边PWM设定
void pwmR_setting(uchar duty);	//右边PWM设定
void pwms_enable(void);			//pwm设定生效

/***** 宏定义 *****/
#define CYCLE   1252L   //PWM频率2KHz，长整数型，最大值32767

#endif