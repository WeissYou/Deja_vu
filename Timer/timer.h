#ifndef __TIMER_H_
#define __TIMER_H_

//AUXR�Ĵ�����ʱ��0���
#define AUXR_T0x12_POS 7

//AUXR�Ĵ�����ʱ��2���
#define AUXR_T2R_POS   4
#define AUXR_T2x12_POS 2

//TMOD�Ĵ�����ʱ��0���
#define TMOD_T0M0_POS  0
#define TMOD_T0M1_POS  1
#define TMOD_T0CT_POS  2
#define TMOD_T0GT_POS  3

void Timers_init(void);					//��ʱ����ʼ��

#endif