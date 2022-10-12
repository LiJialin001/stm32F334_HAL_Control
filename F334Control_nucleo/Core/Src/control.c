/*
 * control.c
 *
 *  Created on: Oct 12, 2022
 *      Author: Lijialin001
 */

#include "main.h"
#include "control.h"
#include "pid.h"

//宏定义区
#define EMERGENT    0      // 紧急停止输出pwm 标志位
#define PWM1      pwm[0]
#define PWM2      pwm[1]
#define PWM3      pwm[2]
#define PWM4      pwm[3]
#define ClearPwm  memset(pwm, 0, sizeof(int16_t) * 4)


//私有变量区
int16_t pwm[4];


/**
  * @brief Pid 稳压函数
  * @param fDt：pid dt
  * @param fDesired: 电压期望值
  * @retval None
  */
// ToDo: 加入pwm调整
void VolStaPIDControl(float fDt, float fDesired, float fMeasured, emPID_list_t pidItem)
{
	volatile static uint8_t status = WAITING_1;
	switch(status)
	{
		case WAITING_1:
			status = READY_11;
			break;
		case READY_11:
			ResetPID();    	 //批量复位PID数据，防止上次遗留的数据影响本次控制
			PIDGroup[pidItem].desired = 0;
			PIDGroup[pidItem].measured = 0;
			status = PROCESS_31;
			break;
		case PROCESS_31:
			PIDGroup[pidItem].measured = fMeasured;
			PIDGroup[pidItem].desired = fDesired;
			if (PIDGroup[pidItem].desired > 50)
				PIDGroup[pidItem].desired = 50;
			else if (PIDGroup[pidItem].desired < 0)
				PIDGroup[pidItem].desired = 0;
			UpdatePID(&PIDGroup[pidItem], fDt);
			break;
		case EXIT_255:                  //退出控制
		    ResetPID();
		    status = WAITING_1;         //返回等待运行
		    break;
		default:
			status = EXIT_255;
			break;
	}

}


/**
  * @brief Pwm 稳压函数
  * @param fDt：pid dt
  * @param fDesired: 电压期望值
  * @retval None
  */


