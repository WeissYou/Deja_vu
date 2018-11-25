#ifndef __GLOBAL_H_
#define __GLOBAL_H_

/***** ͷ�ļ� *****/
#include <STC15F2K60S2.H>
#include"intrins.h"	         //������ʱ����ʱ�������ļ�
//#include"stdio.h"            //printfͷ�ļ�

/***** �������� *****/
typedef unsigned char uchar;
typedef unsigned int uint;

/***** �ⲿ����ȫ�ֱ��� *****/
extern uchar code gray[8];  //ADC��׼����
extern uchar situation;			//����ѭ�����
extern uchar receive;			  //���ڽ�������
extern uchar channel;       //ADCͨ����
extern uchar goback;        //������־
extern uchar adc[8];		    //ADCԭʼ����
extern uchar daten;         //���������
extern uchar p1[8];         //���������
extern bit busy;            //����æλ 

/***** ����ȫ�ֺ��� *****/
void GPIO_init(void);		 //������������ΪGPIO
void Delay(uint n);          //��ʱn����

/***** �궨�� *****/


// 8·Ѱ��������ѹ�ж��ٺڵ㼴����Ϊ��ѹ��ȫ��
#define TRACING_ALL_BLACK_SPOT_NUMBER   7       // ����Ϊѹ��7���ڵ����Ϊ��ѹ��ʮ��·��


// ����������ʱ��
#define BUZZER_SHORT_TWEET_TIME         20      // ���÷�����������ʱ��Ϊ20����ʱ���ж�����


// С���뿪�����ߺ󵥴�Ѱ����ʱ��(����ʮ��·��ʶ���Լ�����ʶ��,������Ѱ��)
#define TASK_STARTING_POINT_DELAY_TIME 200      // ����С���ڼ�⵽ȫ�ڵ������߲�����Ѱ����,����Ѱ���������������Ƶ��ӳٿ���ʱ��Ϊ200����ʱ���ж�����


// С���뿪һ��ͣ��λ�����¿�ʼSNR0�Լ�SNR1��ڼ�����ʱʱ��
#define TASK_OUT_PARKING_SPACE_SNR_CHECK_DELAY_TIME 10  // ����С����һ��ͣ��λ����һ��ͣ��λ�Ĺ�����,��ʼѰ����SNR�����ӳٿ�ʼʱ��Ϊ10��ʱ���ж�����


// С�����������뿪�ڶ���ͣ��λ�󵽿���8·�Ҷȴ��������ȫ��֮�����ʱ(���������ʱ��Ϊ�˷�ֹ�����¹����е���8·�Ҷȴ�������ʶ��ʮ��·��)
#define TASK_OUT_LOADING_AREA_CROSS_ROADS_CHECK_DELAY_TIME  60  // ����С���������ڶ���ͣ�����SNR���Ϊ��ɫ�󵽿���ʮ��·��ʶ��֮�����ʱΪ60����ʱ���ж�����




// �׵�
#define W_LED_PIN P42

// �̵�
#define G_LED_PIN P40

// ���
#define R_LED_PIN P52

// ����
#define B_LED_PIN P51

// �Ƶ�
#define Y_LED_PIN P50

//L298�������
#define IN1	P24
#define IN2 P25
#define IN3 P22
#define IN4 P23
#define ENA1 P07
#define ENA2 P06

//��־�߼�⴫��������

#define SNR0 P32
#define SNR1 P33


// ������IO��
#define BUZZER_PIN P00

#endif