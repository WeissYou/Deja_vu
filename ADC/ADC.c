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


/*******************************************************************************
*                           ������@2018-11-25
* Function Name  :  ADC_Get_Channel_Data
* Description    :  ��ȡָ��ADCͨ����ת�����
* Input          :  uchar _channel
* Output         :  unsigned char
* Return         :  None
*******************************************************************************/
unsigned char ADC_Get_Channel_Data(uchar _channel)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDH | _channel | ADC_START;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return ADC_RES;
}// End of unsigned char ADC_Get_Channel_Data(uchar _channel)
 
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
}

