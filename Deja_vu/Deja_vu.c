#include<DEJA_VU.H>
#include"GLOBAL.H"
#include"MOTOR.H"
#include"PWM.H"
#include "stdio.h"

char history_dir_data[HISTORY_DIR_DATA_SIZE] = { 0x00 };        // ��ʷ��������

// ����PID����
const char dir_pid_p = 17;
const char dir_pid_i = 4;
const char dir_pid_d = 5;

/*******************************************************************************
*                           ������@2018-11-24
* Function Name  :  Calculate_Motor_Parameters
* Description    :  ����������
* Input          :  None
* Output         :  None
* Return         :  char                �������ռ�����ķ���
*******************************************************************************/
char Calculate_Motor_Parameters(void)
{
    int dir_pid_p_tmp = 0;      // pid����������ʱ�洢����
    int dir_pid_i_tmp=0;        // pid���ּ�����ʱ�洢����
    int dir_pid_d_tmp = 0;      // pid΢�ּ�����ʱ�洢����
    char calculate_dir = 0;      // ����������ս��
    unsigned char i = 0;

    /****************����PID*****************/
    for (i = 0; i < HISTORY_DIR_DATA_SIZE; i++)
    {
        // ����ʷλ�����ݻ����ۼ�
        dir_pid_i_tmp += history_dir_data[i];
    }
    // ���Ի���ϵ��
    dir_pid_i_tmp *= dir_pid_i;
		
    // �������Ϊ��ǰλ��*����ϵ��
    dir_pid_p_tmp = history_dir_data[0] * dir_pid_p;

    // ΢�ֽ��Ϊ(����λ��-���ϴ�λ��(����һ��,������ʱ���))*΢��ϵ��
    dir_pid_d_tmp = (history_dir_data[0] - history_dir_data[2]);//*dir_pid_i;
		
    // �������ս��
    calculate_dir = dir_pid_p_tmp + dir_pid_i_tmp + dir_pid_d_tmp;
  
    // ��λ
    if (calculate_dir > 100)calculate_dir = 100;
    if (calculate_dir < -100)calculate_dir = -100;


    /*****************�����Ӧ�ĵ������&PWMӳ��*******************/
    if (calculate_dir > 0)
    {
		
			if(calculate_dir>50)
			{
				// ���ƫ�Ĺ���,��Ҫʹ�÷�ת
				MotorR_setting_auto_dir(100);
        MotorL_setting_auto_dir(-calculate_dir);
			}
			else
			{
				// ���ƫ�Ĳ���,ֱ�Ӽ��پͿ��Դ���
        MotorR_setting_auto_dir(100);
        MotorL_setting_auto_dir(100 - calculate_dir);
			}
    }
    else if (calculate_dir < 0)
    {
			
			if(calculate_dir<-50)
			{
				// ���ƫ�Ĺ���,��Ҫʹ�÷�ת
        MotorR_setting_auto_dir(calculate_dir);
        MotorL_setting_auto_dir(100);
			}
			else
			{
				// ���ƫ�Ĳ���,ֱ�Ӽ��پͿ��Դ���
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
*                           ������@2018-11-24
* Function Name  :  Calculate_Dir
* Description    :  ���㷽������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
char Calculate_Dir(unsigned char sensor_data)
{
    char Weights[8] = { -3,-2,-1,0,0,1,2,3 };               // 8·Ѱ���Ҷȴ�����ÿһλ��Ȩ��
    char dir = 0;                                             // ����Ȩ���Լ��Ҷȴ��������ݼ�����ķ���
    unsigned char i = 0;
    // ���㷽��ֵ
    for (i = 0; i < 8; i++)
    {
        // ����Ҷȴ������ĵ�iλΪ1
        if (sensor_data&(0x01 << i))
        {
            // ������ֵ�ϼ��϶�Ӧλ��Ȩ��
            dir = dir + Weights[i];
        }
    }
    return dir;
}// End of char Calculate_Dir(unsigned char sensor_data)



void Deja_vu(void)
{  
    char Weights[8] = { -3,-2,-1,0,0,1,2,3 };               // 8·Ѱ���Ҷȴ�����ÿһλ��Ȩ��
    char dir=0;                                             // ����Ȩ���Լ��Ҷȴ��������ݼ�����ķ���
    unsigned char i=0;

    // ���㷽��
    dir=Calculate_Dir(situation);

    // ������ʷ��������
    for (i = HISTORY_DIR_DATA_SIZE - 1; i > 0; i--)
    {
        history_dir_data[i] = history_dir_data[i-1];
    }
    history_dir_data[0] = dir;

    // С���ܷ�(���д�����ȫѹ����)
    if (situation == 0x00)
    {
        Motors_stop();
    }
    // С������������(���д�����ȫѹ����)
    else if(situation ==0xFF)
    {
        MotorL_setting_auto_dir(100);
        MotorR_setting_auto_dir(100);
    }
    else
    {
        // �������������������
        Calculate_Motor_Parameters();
    }


		// PWM�趨��Ч
		pwms_enable();         
}