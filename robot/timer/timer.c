/*
*timer.h
*
*
*/

#include "timer.h"


#define TIMER_INTERVAL_US       100000


static sem_t        timer_sem_100ms;
static sem_t        timer_sem_1s;
static sem_t        timer_sem_10s;

static unsigned int timer_100ms_intr    = (unsigned int)(-1);
static unsigned int timer_1s_intr       = (unsigned int)(-1);
static unsigned int timer_10s_intr      = (unsigned int)(-1);

static unsigned int s_runTime = 0;

static void send_signal(int signo)
{
    switch(signo)
    {
        /* call once every TIMER_INTERVAL_US(us) */
        case SIGALRM:
            timer_100ms_intr++;
            if ( timer_100ms_intr >= 1 )
            {
                sem_post(&timer_sem_100ms);
                timer_100ms_intr = 0;
            }

            timer_1s_intr++;
            if ( timer_1s_intr >= 9 ) /*因为时间偏慢，大约在900ms的时候，就够了*/
            {
                sem_post(&timer_sem_1s);
                timer_1s_intr = 0;
            }

            timer_10s_intr++;
            if ( timer_10s_intr >= 100 )
            {
                sem_post(&timer_sem_10s);
                timer_10s_intr = 0;
            }

            break;
        default:
            break;
    }
}

int timer()
{
    int                 ret;
    struct itimerval    timer;

    timer.it_value.tv_sec   = 0;
    timer.it_value.tv_usec  = TIMER_INTERVAL_US;
    timer.it_interval       = timer.it_value;

    ret = sem_init(&timer_sem_100ms, 0, 0);
    msg_print("timer", msg_pri_comm, "init 100ms semaphore %s", result(ret));
    if(ret < 0 )
    {
        return ERR_SEM;
    }

    ret = sem_init(&timer_sem_1s, 0, 0);
    msg_print("timer", msg_pri_comm, "init 1s semaphore %s", result(ret));
    if(ret < 0 )
    {
        return ERR_SEM;
    }

    signal(SIGALRM, send_signal);

    setitimer(ITIMER_REAL, &timer, NULL);

    return ROBOT_OK;
}

void timer_100ms_func(void)
{
    while (1)
    {
        sem_wait(&timer_sem_100ms);
    }
}

void timer_1s_func(void)
{
    //set_wtdg_timeout(10);

    //wtdg_enable();

    while (1)
    {
        sem_wait(&timer_sem_1s);

        s_runTime++;

        //check_isReboot();

        //update_timer();

       // wtdg_keelalive();
        
    }
}

void timer_10s_func(void)
{
    while (1)
    {
        sem_wait(&timer_sem_10s);

    }
}

unsigned int get_run_time(void)
{
    return s_runTime;
}
