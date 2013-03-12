/*
*
*
*
***/

#ifndef __LIB_MOTOR_H__
#define __LIB_MOTOR_H__

#include "robot_lib.h"

#define MOTOR_MAGIC 'm'

#define MOTO_L_ON _IO (MOTOR_MAGIC,1)
#define MOTO_L_OFF _IO (MOTOR_MAGIC,2)
#define MOTO_L_F _IO (MOTOR_MAGIC,3)
#define MOTO_L_B _IO (MOTOR_MAGIC,4)
#define MOTO_R_ON _IO (MOTOR_MAGIC,5)
#define MOTO_R_OFF _IO (MOTOR_MAGIC,6)
#define MOTO_R_F _IO (MOTOR_MAGIC,7)
#define MOTO_R_B _IO (MOTOR_MAGIC,8)

typedef struct
{
    int ontime;
    int offtime;
}motor_speed;

typedef struct
{
    int left_flag;
    int right_flag;
    motor_speed left_speed;
    motor_speed right_speed;
}motor_ctrl;

extern int motor_init();

#endif
