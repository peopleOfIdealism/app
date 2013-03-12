#include "robot_lib.h"


static sem_t    g_init_sem;

void init_sem()
{
    sem_init(&g_init_sem, 0, 0);
}

void init_sem_unlock()
{
    sem_post(&g_init_sem);
}

void init_sem_wait()
{
    sem_wait(&g_init_sem);
}


char *result(int n)
{
	if(0 == n)
		{
			return "SUCCESS";
		}
	else
		{
			return "failed";
		}
}

unsigned short chksum16(unsigned short *data, unsigned int data_len)
{
    int sum = 0;

    while ( data_len > 1 )
    {
        sum += *data;
        data++;
        data_len -= 2;
    }

    if ( data_len > 0 )
    {
        sum += *(unsigned char *)data;
    }

    sum = ( sum >> 16 ) + ( sum & 0xffff );
    sum += ( sum >> 16 );
    sum = ~sum;

    return (unsigned short)sum;
}


