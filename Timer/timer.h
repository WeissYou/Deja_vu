#ifndef __TIMER_H_
#define __TIMER_H_

//AUXR寄存器定时器0相关
#define AUXR_T0x12_POS 7

//AUXR寄存器定时器2相关
#define AUXR_T2R_POS   4
#define AUXR_T2x12_POS 2

//TMOD寄存器定时器0相关
#define TMOD_T0M0_POS  0
#define TMOD_T0M1_POS  1
#define TMOD_T0CT_POS  2
#define TMOD_T0GT_POS  3

void Timers_init(void);					//定时器初始化

#endif