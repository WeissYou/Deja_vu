#ifndef __USART_H_
#define __USART_H_

#define FOSC    33177600L
#define BAUD    115200

#define URMD    1            //0:ʹ�ö�ʱ��2��Ϊ�����ʷ�����
                             //1:ʹ�ö�ʱ��1��ģʽ0(16λ�Զ�����ģʽ)��Ϊ�����ʷ�����
                             //2:ʹ�ö�ʱ��1��ģʽ2(8λ�Զ�����ģʽ)��Ϊ�����ʷ�����

// AUXR�Ĵ�����ʱ��1������1���bitλ��
#define AUXR_T1X12_POS                  6
#define AUXR_UART_M0X6_POS              5
#define AUXR_SIST2_POS                  0

void Usart_init(void);          //���ڳ�ʼ��
void Data_sending(uchar dat);  //��������
void Data_receiving(void);	   //��������
void SendString(char *s);



#endif