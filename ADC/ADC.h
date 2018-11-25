#ifndef __ADC_H_
#define __ADC_H_

#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

void ADC_init(void);                    // ADC初始化
void Data_processing(void);             // ADC数据处理

//软件查询方式
void ADCResult_getting(void);           // 读取ADC结果
unsigned char ADC_Get_Channel_Data(uchar _channel); // 获取指定ADC通道的转换结果
void ADCResult_showing(uchar channel);  // 发送ADC结果到PC

#endif