#include"GLOBAL.H"
#include"USART.H"
#include "stdio.h"

/*----------------------------
��ʼ������
----------------------------*/

void Usart_init(void)  //115200bps@33.1776MHz
{
	  SCON = 0x50;                        //8λ�ɱ䲨����
    AUXR |= 0x01 << AUXR_T1X12_POS;       //��ʱ��1Ϊ1Tģʽ
    AUXR &= ~(0x01 << AUXR_UART_M0X6_POS);//����1Ϊ12��Ƶ
    AUXR &= ~(0x01 << AUXR_SIST2_POS);  // ����1ʹ�ö�ʱ��1��Ϊ�����ʷ�����

    TMOD = 0x00;                //��ʱ��1Ϊģʽ0(16λ�Զ�����)
    TL1 = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    TH1 = (65536 - (FOSC/4/BAUD))>>8;
    TR1 = 1;                    //��ʱ��1��ʼ����
	
	#ifdef DEBUG
		// Ϊ��ʹ��printf,��Ҫ��������
		TI=1;
	#endif
}

/*----------------------------
���ʹ�������
----------------------------*/
void Data_sending(uchar dat)
{
    while (busy);                    //�ȴ�ǰһ�����ݷ������
	  busy = 1;
	  SBUF = dat;
}


/*----------------------------
���մ�������
----------------------------*/
void Data_receiving(void)
{
    while (busy);                    //�ȴ�ǰһ�����ݽ������
    busy = 1;                         //������ձ�־
    receive = SBUF;                     //��������
}
/*----------------------------
�����ַ���
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //����ַ���������־
    Data_sending(*s++);         //���͵�ǰ�ַ�
}
