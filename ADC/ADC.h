#ifndef __ADC_H_
#define __ADC_H_

#define ADC_POWER   0x80            //ADC��Դ����λ
#define ADC_FLAG    0x10            //ADC��ɱ�־
#define ADC_START   0x08            //ADC��ʼ����λ
#define ADC_SPEEDLL 0x00            //540��ʱ��
#define ADC_SPEEDL  0x20            //360��ʱ��
#define ADC_SPEEDH  0x40            //180��ʱ��
#define ADC_SPEEDHH 0x60            //90��ʱ��

void ADC_init(void);                    // ADC��ʼ��
void Data_processing(void);             // ADC���ݴ���

//�����ѯ��ʽ
void ADCResult_getting(void);           // ��ȡADC���
unsigned char ADC_Get_Channel_Data(uchar _channel); // ��ȡָ��ADCͨ����ת�����
void ADCResult_showing(uchar channel);  // ����ADC�����PC

#endif