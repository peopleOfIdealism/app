/*
*lib_motor.c
*
*this lib give the motor function
*/

#include "lib_motor.h"

#define MOTOR "/dev/moto_dev"

#define MAXSPEED    100

int fd;

int paraChangeR;
int paraChangeL;
    
motor_ctrl glb_motor;

int checkIn(int n, int max)
{
    if(n > max)
    {
        msg_print("motor", msg_pri_error, "input overflow:input %d max %d", n, max);
        return max;
    }
    else if(n < -max)
    {
        msg_print("motor", msg_pri_error, "input overflow:input %d max %d", n, max);
        return -max;
    }
    else
    return n;
    
}

/********************************
*convert 0~100 to specified grade speed,now is 10
*********************************/
motor_speed speed(int n)
{
    //put input speed into pwm output
    motor_speed m_speed;
    int speed_t = n/10;
    if(0 == n)
    {
        m_speed.ontime = 0;
        m_speed.offtime = 0;
    }
    
    switch(speed_t)
    {
    case 0://5.0  4.8~5.011
        m_speed.ontime = 50;
        m_speed.offtime = 74950;
        break;
    case 1://5.7  5.688~5.72
        m_speed.ontime = 50;
        m_speed.offtime = 54950;
        break;
    case 2://6.4  6.0~6.2
        m_speed.ontime = 50;
        m_speed.offtime = 39950;
        break;
    case 3://7.1  6.9
        m_speed.ontime = 50;
        m_speed.offtime = 29950;
        break;
    case 4://7.8  7.8
        m_speed.ontime = 50;
        m_speed.offtime = 19950;
        break;
    case 5://8.5  8.3
        m_speed.ontime = 50;
        m_speed.offtime = 14950;
        break;
    case 6://9.2  8.9
        m_speed.ontime = 50;
        m_speed.offtime = 9950;
        break;
    case 7://9.9  9.69
        m_speed.ontime = 50;
        m_speed.offtime = 4950;
        break;
    case 8://10.6  10.64
        m_speed.ontime = 50;
        m_speed.offtime = 50;
        break;
    case 9://11.3  11.23
        m_speed.ontime = 4950;
        m_speed.offtime = 64;
        break;
    case 10://12  
        m_speed.ontime = 100000;
        m_speed.offtime = 64;
        
        break;
    default:/*do as stop*/
        msg_print("motor", msg_pri_error, "error speed %d %d", n, speed_t);
        m_speed.ontime = 0;
        m_speed.offtime = 0;
        
    }
    return m_speed;
}

/*
void motor_l_forward(int fd)
{
    ioctl(fd, MOTO_L_F);
}

void motor_l_backward(int fd)
{
    ioctl(fd, MOTO_L_B);
}

void motor_l_on(int fd)
{
    ioctl(fd, MOTO_L_ON);
}

void motor_l_off(int fd)
{
    ioctl(fd, MOTO_L_OFF);
}

void motor_r_foward(int fd)
{
    ioctl(fd, MOTO_R_F);
}
*/


/*********************************************
**this is a API function, 
*input: leftspeed: left motor speed
*          rightspeed: right motor speed
* output: set the right parameter to th global vairable
*           so that the motoRC and mtotLC can read and change as commanded
* return :the status of motor 
*
**********************************************/
int motor(int leftSpeed, int rightSpeed)
{
    int ilspeed = 0;/*leftspeed*/
    int irspeed = 0;/*rightspeed*/
    int ret     = 0;
    ilspeed = checkIn(leftSpeed, MAXSPEED);/*input check*/
    irspeed = checkIn(rightSpeed, MAXSPEED);

    motor_ctrl *motor_control;
    memset(motor_control, 0, sizeof(motor_ctrl));
    
    if(ilspeed >= 0)
    {/*forward*/
        motor_control->left_flag = MOTO_L_F;
    }
    else
    {/*backward*/
        motor_control->left_flag = MOTO_L_B;
    }

    motor_control->left_speed= speed(abs(leftSpeed));
    if(irspeed >= 0)
    {
        motor_control->right_flag = MOTO_R_F;
    }
    else
    {
        motor_control->left_flag = MOTO_R_B;
    }
    motor_control->left_speed = speed(abs(rightSpeed));

    memcpy(&glb_motor, motor_control, sizeof(motor_ctrl));
    
    return ret;
}

/************************************************
*the thread control right motor
*
*************************************************/
void motorRC(void)
{
    printf("motor thread start\n");
    while(1)
    {
        ioctl(fd, glb_motor.right_flag);
        
        while(1)
        {
            ioctl (fd,MOTO_R_ON);
            usleep(glb_motor.right_speed.ontime);
            ioctl (fd,MOTO_R_OFF);
            usleep(glb_motor.right_speed.offtime);
        }
    }
}

/************************************************
*the thread control left motor
*
*************************************************/
void motorLC(void)
{
    printf("motor thread start\n");
    while(1)
    {
        ioctl(fd, glb_motor.left_flag);
        while(1)
        {
            ioctl (fd,MOTO_R_ON);
            usleep(glb_motor.left_speed.ontime);
            ioctl (fd,MOTO_R_OFF);
            usleep(glb_motor.left_speed.offtime);
        }
    }
}

/************************************************
*
*
*************************************************/
int motor_init(){
    int ret ;
    pthread_t motorL;
    pthread_t motorR;

    
    fd = open (MOTOR ,O_RDWR);    
    if (fd < 0)
    {        
        perror("open");        
        exit(0);    
    }    
    msg_print("motor", msg_pri_comm, "motor opened, fd %d\n",fd);

    init_sem_wait();
    
    ret = pthread_create(&motorL, NULL, (void *)motorLC, NULL);
    ret = pthread_create(&motorR, NULL, (void *)motorRC, NULL);

    init_sem_unlock();
    return ret;
}