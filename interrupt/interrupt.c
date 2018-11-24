#include"DEJA_VU.H"
#include"GLOBAL.H"
#include"USART.H"
#include"MOTOR.H"
#include"PWM.H"
#include"ADC.H"

void Interrupt_init(void)
{
 	ET0 = 1;			 //定时器0中断允许
	
	EX0 = 1;       //外部中断0允许
	IT0 = 0;			 //外部中断0任意沿触发
   
	ES = 1;        //使能串口中断
    
	EA = 1;			   //总中断打开
}

/*----------------------------
定时器0中断函数
----------------------------*/
void Timer0_routine(void) interrupt 1 using 0
{   
  //定时器0中断测试
	//SendString("Timer0 all right!");
	TR0 = 0;
	if(flag == 1)
	  {
		  flag = 0;
	    Motors_break();
	    Delay(1000);
	    MotorL_setting(50,1);
	    MotorR_setting(50,1);
	    pwms_enable();
		  Delay(20);
	  }
	else
		{
			Data_processing();  //数据处理 	
	    Deja_vu();          //循迹函数   
		}
	/*
  Data_sending(0x00);  //发送0x00作为机械臂开始动作的标志
	while(1)
	{
    if(SBUF = 0xff)  //接收0xff作为机械臂完成动作的标志
	   break;
  }
	*/

	TR0 = 1;
}

/*----------------------------
外部中断函数
----------------------------*/
void Exint0_routine(void) interrupt 0 using 1  	 
{ 
	if(SNR0 == 1 && SNR1 == 1)
	{
	  flag = 1;
	}

}

/*----------------------------
UART 中断服务程序
-----------------------------*/
void Usart(void) interrupt 4 using 2
{
    if (RI)
    {
        RI = 0;                 //清除RI位
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy = 0;               //清忙标志
    }
}