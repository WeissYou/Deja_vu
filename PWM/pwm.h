#ifndef __PWM_H_
#define __PWM_H_

/***** ����PWM���ú��� *****/
void pwmL_setting(uchar duty);	//���PWM�趨
void pwmR_setting(uchar duty);	//�ұ�PWM�趨
void pwms_enable(void);			//pwm�趨��Ч

/***** �궨�� *****/
#define CYCLE   1252L   //PWMƵ��2KHz���������ͣ����ֵ32767

#endif