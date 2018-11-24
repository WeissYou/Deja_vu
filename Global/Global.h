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
extern uchar flag;          //ĳ��־λ
extern bit busy;            //����æλ 

/***** ����ȫ�ֺ��� *****/
void GPIO_init(void);		 //������������ΪGPIO
void Delay(uint n);          //��ʱn����

/***** �궨�� *****/

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

#endif