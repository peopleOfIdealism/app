/*
*lib_print.c
*
*this lib print output message
*/

#ifndef __LOG_H__
#define __LOG_H__


#include "robot_lib.h"



#define MAX_MESSAGE_LENGTH      1500


extern int  print_message(const char* modules, const unsigned int privilege,
                    const char *file, const int line, const char *format, ...);


#define msg_print(modules, privilege, format, args...)                              \
    do                                                                              \
    {                                                                               \
        print_message(modules, privilege, __FILE__, __LINE__, format, ##args);      \
    }while(0)

#endif
