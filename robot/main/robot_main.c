#include "robot_lib.h"
//#include <stdio.h>

int main()
{
    int ret;
    
    pthread_t timer_100ms_thread;
    pthread_t timer_1s_thread;
    pthread_t timer_10s_thread;

    init_sem();
    
    ret = motor_init();
    msg_print("main", msg_pri_comm, "motor init %s", result(ret));
    if(0 != ret)
    {
        //handle;
    }
    ret = timer();
    msg_print("main", msg_pri_comm, "timer init %s", result(ret));
    if(0 != ret)
    {
        //handle;
    }
    
    ret = pthread_create(&timer_100ms_thread, NULL, (void *)timer_100ms_func, NULL);
    msg_print("main", msg_pri_comm, "100ms thread create %s", result(ret));
    
    msg_print("motor", msg_pri_comm, "motor ssssssssssss");
    motor(0,100);
    msg_print("motor", msg_pri_comm, "motor end----------------");

    
    ret = pthread_create(&timer_1s_thread, NULL, (void *)timer_1s_func, NULL);
    msg_print("main", msg_pri_comm, "1s thread create %s", result(ret));
    
    ret = pthread_create(&timer_10s_thread, NULL, (void *)timer_10s_func, NULL);
    msg_print("main", msg_pri_comm, "10s thread create %s", result(ret));
    
    pthread_join(timer_100ms_thread, NULL);
    pthread_join(timer_1s_thread, NULL);
    pthread_join(timer_10s_thread, NULL);

    return 0;
}
