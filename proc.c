// proc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "kernel.h" // was using <kernel.h>
#include "spede.h"
//#include <stdio.h>
//#include <string.h>

void numberToString(int, char *);
int strLen(char *);

void Clock()
{
    // int i = 0;
    // char str[] = "    "; // str for 4-digits, plus NUL
    // unsigned short *p;
    // while (1)
    //{
    // if (sys_tick % 60 == 0)
    //{
    // i += 1;
    // numberToString(i, str);
    //*p = VIDEO_START;
    //*p += 75;
    // int j = 0;
    // while (str[j] != '\0')
    //{
    //*p = str[j] + VIDEO_MASK;
    // j++;
    //}
    //}
    //}
}

/*
 * Takes number and reference to str. str is populated with number
 */
void numberToString(int number, char *str)
{
    sprintf(str, "%d", number);
}

/*
 * Return str length
 */
int strLen(char *str)
{
    return strlen(str);
}
