#include<GLOBAL.H>


/***** 全局变量 *****/
uchar code gray[8] = {0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0};
uchar channel = 0;     //ADC通道号
uchar situation;		   //各种循迹情况
uchar receive;         //串口接收数据
uchar goback;          //倒车标志
uchar adc[8];		       //ADC原始数据存放数组
uchar daten;           //处理后数据
uchar p1[8];           //处理后数据存放数组
bit busy;              //串口忙碌标志    

/***** 全局函数 *****/										   
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
软件延时
----------------------------*/
void Delay(uint n)  //延时n毫秒
{
    uint x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}
