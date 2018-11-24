#include<DEJA_VU.H>
#include"GLOBAL.H"
#include"MOTOR.H"
#include"PWM.H"
#include "stdio.h"

char history_dir_data[HISTORY_DIR_DATA_SIZE] = { 0x00 };        // 历史方向数据

// 方向PID参数
const char dir_pid_p = 17;
const char dir_pid_i = 4;
const char dir_pid_d = 5;

/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Calculate_Motor_Parameters
* Description    :  计算电机参数
* Input          :  None
* Output         :  None
* Return         :  char                返回最终计算出的方向
*******************************************************************************/
char Calculate_Motor_Parameters(void)
{
    int dir_pid_p_tmp = 0;      // pid比例计算临时存储变量
    int dir_pid_i_tmp=0;        // pid积分计算临时存储变量
    int dir_pid_d_tmp = 0;      // pid微分计算临时存储变量
    char calculate_dir = 0;      // 计算出的最终结果
    unsigned char i = 0;

    /****************方向PID*****************/
    for (i = 0; i < HISTORY_DIR_DATA_SIZE; i++)
    {
        // 对历史位置数据积分累加
        dir_pid_i_tmp += history_dir_data[i];
    }
    // 乘以积分系数
    dir_pid_i_tmp *= dir_pid_i;
		
    // 比例结果为当前位置*比例系数
    dir_pid_p_tmp = history_dir_data[0] * dir_pid_p;

    // 微分结果为(本次位置-上上次位置(跳过一个,以拉大时间差))*微分系数
    dir_pid_d_tmp = (history_dir_data[0] - history_dir_data[2]);//*dir_pid_i;
		
    // 计算最终结果
    calculate_dir = dir_pid_p_tmp + dir_pid_i_tmp + dir_pid_d_tmp;
  
    // 限位
    if (calculate_dir > 100)calculate_dir = 100;
    if (calculate_dir < -100)calculate_dir = -100;


    /*****************方向对应的电机方向&PWM映射*******************/
    if (calculate_dir > 0)
    {
		
			if(calculate_dir>50)
			{
				// 如果偏的过多,需要使用反转
				MotorR_setting_auto_dir(100);
        MotorL_setting_auto_dir(-calculate_dir);
			}
			else
			{
				// 如果偏的不多,直接减速就可以处理
        MotorR_setting_auto_dir(100);
        MotorL_setting_auto_dir(100 - calculate_dir);
			}
    }
    else if (calculate_dir < 0)
    {
			
			if(calculate_dir<-50)
			{
				// 如果偏的过多,需要使用反转
        MotorR_setting_auto_dir(calculate_dir);
        MotorL_setting_auto_dir(100);
			}
			else
			{
				// 如果偏的不多,直接减速就可以处理
        MotorR_setting_auto_dir(100 - (-calculate_dir));
        MotorL_setting_auto_dir(100);
			}
    }
    else
    {
        MotorL_setting_auto_dir(100);
        MotorR_setting_auto_dir(100);
    }

    return calculate_dir;
}// End of char Calculate_Motor_Parameters(void)



/*******************************************************************************
*                           陈苏阳@2018-11-24
* Function Name  :  Calculate_Dir
* Description    :  计算方向数据
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
char Calculate_Dir(unsigned char sensor_data)
{
    char Weights[8] = { -3,-2,-1,0,0,1,2,3 };               // 8路寻迹灰度传感器每一位的权重
    char dir = 0;                                             // 根据权重以及灰度传感器数据计算出的方向
    unsigned char i = 0;
    // 计算方向值
    for (i = 0; i < 8; i++)
    {
        // 如果灰度传感器的第i位为1
        if (sensor_data&(0x01 << i))
        {
            // 方向数值上加上对应位的权重
            dir = dir + Weights[i];
        }
    }
    return dir;
}// End of char Calculate_Dir(unsigned char sensor_data)



void Deja_vu(void)
{  
    char Weights[8] = { -3,-2,-1,0,0,1,2,3 };               // 8路寻迹灰度传感器每一位的权重
    char dir=0;                                             // 根据权重以及灰度传感器数据计算出的方向
    unsigned char i=0;

    // 计算方向
    dir=Calculate_Dir(situation);

    // 更新历史方向数据
    for (i = HISTORY_DIR_DATA_SIZE - 1; i > 0; i--)
    {
        history_dir_data[i] = history_dir_data[i-1];
    }
    history_dir_data[0] = dir;

    // 小车跑飞(所有传感器全压白线)
    if (situation == 0x00)
    {
        Motors_stop();
    }
    // 小车处于起跑线(所有传感器全压黑线)
    else if(situation ==0xFF)
    {
        MotorL_setting_auto_dir(100);
        MotorR_setting_auto_dir(100);
    }
    else
    {
        // 计算电机参数并驱动电机
        Calculate_Motor_Parameters();
    }


		// PWM设定生效
		pwms_enable();         
}