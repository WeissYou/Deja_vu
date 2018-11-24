#include"GLOBAL.H"
#include"USART.H"
#include<ADC.H>

/*----------------------------
��ʼ��ADC
----------------------------*/
void ADC_init(void)
{
    P1ASF = 0xff;                   //����P1ΪADC����
    ADC_RES = 0;                    //�������Ĵ���
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | channel;
    Delay(2);                       //ADC�ϵ粢��ʱ
	
}

//�����ѯ��ʽ
/*----------------------------
����ADC�����PC
----------------------------*/
void ADCResult_showing(uchar channel)
{
    Data_sending(adc[channel]);     //��ʾADC��8λ���
}

/*----------------------------
��ȡADC���
----------------------------*/
void ADCResult_getting(void)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | channel | ADC_START;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
	
	  adc[channel] = ADC_RES;	   //��ADC�������������Ӧλ
    //Data_sending(ADC_RES);  //��ȡ��8λ��������͵�����
	
	  if(++channel > 7)
    channel = 0;  //�л�����һ��ͨ��
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | channel; 	
}
 
/*----------------------------
ADC���ݴ���
----------------------------*/
void Data_processing(void) 
{   
	uchar i = 0;
	situation=0x00;
	for(i = 0; i <8 ; i++)
	{
		if(adc[i]>=gray[i])
		{
			situation|=(0x01<<i);
		}
		else
		{
			situation&=(~(0x01<<i));
		}
	}
	/*
	if(adc[channel] >= gray[channel])	       //������ֵ����һ�ٽ�ֵ
    daten = 1;				               //�ж�Ϊ1
  else					                   //����
    daten = 0;				               //�ж�Ϊ0
  
	for(i = 0; i <= 7; i++)
		p1[i] = daten;
  switch(channel)			               //������������������Ӧλ
  {
    case 0:
	  p1[channel] = daten;
	  break;
	case 1:
	  p1[channel] = daten;
	  break;
	case 2:
	  p1[channel] = daten;
	  break;
   	case 3:
	  p1[channel] = daten;
	  break;
	case 4:
	  p1[channel] = daten;
	  break;
	case 5:
	  p1[channel] = daten;
	  break;
	case 6:
	  p1[channel] = daten;
	  break;
	case 7:
	  p1[channel] = daten;
	  break;
  }
	 
	 situation = p1[0]*1 + p1[1]*2 + p1[2]*4 + p1[3]*8 + p1[4]*16
	       + p1[5]*32 + p1[6]*64 + 	p1[7]*128;       //����ת��	  
*/				 
}

