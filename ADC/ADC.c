#include"GLOBAL.H"
#include"USART.H"
#include<ADC.H>

/*----------------------------
初始化ADC
----------------------------*/
void ADC_init(void)
{
    P1ASF = 0xff;                   //设置P1为ADC引脚
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | channel;
    Delay(2);                       //ADC上电并延时
	
}

//软件查询方式
/*----------------------------
发送ADC结果到PC
----------------------------*/
void ADCResult_showing(uchar channel)
{
    Data_sending(adc[channel]);     //显示ADC高8位结果
}

/*----------------------------
读取ADC结果
----------------------------*/
void ADCResult_getting(void)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | channel | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
	
	  adc[channel] = ADC_RES;	   //将ADC结果存入数组相应位
    //Data_sending(ADC_RES);  //读取高8位结果并发送到串口
	
	  if(++channel > 7)
    channel = 0;  //切换到下一个通道
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | channel; 	
}
 
/*----------------------------
ADC数据处理
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
	if(adc[channel] >= gray[channel])	       //若采样值大于一临界值
    daten = 1;				               //判定为1
  else					                   //否则
    daten = 0;				               //判定为0
  
	for(i = 0; i <= 7; i++)
		p1[i] = daten;
  switch(channel)			               //将处理结果存入数组相应位
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
	       + p1[5]*32 + p1[6]*64 + 	p1[7]*128;       //进制转换	  
*/				 
}

