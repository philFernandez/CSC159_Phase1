// proc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "spede.h"
#include "kernel.h"
#include "syscall.h"

void toStr(int, char *);
int strLen(char *);
void output_message(char toDisplay[]);

// Text video memory base address
uint16 *const video_base = (uint16 *)0xB8000;

void Clock()
{
    char str[] = "    "; // str for 4-digits, plus NUL
    while (1)
    {
        if (sys_tick % 100 == 0)
        {
            toStr(sys_tick / 100, str);
            output_message(str);
        }
    }
}

/*
 * Modified version of function from lab manual p 54
 */
void output_message(char toDisplay[])
{
    uint8 *vp8 = (uint8 *)(video_base + 75);
    uint8 *p = (uint8 *)toDisplay;

    for (; *p != '\0'; p += 1, vp8 += 2)
    {
        *vp8 = *p;
    }
}

/**
 * Takes number and reference to str.
 * str is populated with number.
 * str is populated from back to front
 */
void toStr(int number, char *str)
{

    int len = strLen(str);
    int j = len - 1;

    while (number)
    {
        if (str[j] == '\0')
            break;
        str[j] = (number % 10) + '0';
        number /= 10;
        j--;
    }
}

/**
 * Return str length
 */
int strLen(char *s)
{
    int length = 0;
    char c = *(s + length);

    // '\0' marks end of char array (string)
    // count up all chars before reaching '\0'
    // to get string length
    while (c != '\0')
    {
        length++;
        c = *(s + length);
    }

    return length;
}

void Init()
{
    int cur_time;
    char *time;
    while(1)
    {
        cur_time = get_time_call();
        toStr(cur_time, time);
        write_call(time);
    }
}