#include<GLOBAL.H>


/***** ȫ�ֱ��� *****/
uchar code gray[8] = {0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0};
uchar channel = 0;     //ADCͨ����
uchar situation;		   //����ѭ�����
uchar receive;         //���ڽ�������
uchar goback;          //������־
uchar adc[8];		       //ADCԭʼ���ݴ������
uchar daten;           //���������
uchar p1[8];           //��������ݴ������
bit busy;              //����æµ��־    

/***** ȫ�ֺ��� *****/										   
void GPIO_init(void)		  
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;			  
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
}

/*----------------------------
�����ʱ
----------------------------*/
void Delay(uint n)  //��ʱn����
{
    uint x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}
