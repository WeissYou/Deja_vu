#ifndef __MOTOR_H_
#define __MOTOR_H_

/***** 电机设置函数 *****/
void Motors_stop(void);		            //非正常情况下的停车	
void Motors_break(void);                     //停车			
void MotorL_setting(uchar speed,uchar dir);	 //电机0控制
void MotorR_setting(uchar speed,uchar dir);	 //电机1控制


#endif