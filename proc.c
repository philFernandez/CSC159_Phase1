// proc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "spede.h"
#include "kernel.h" // was using <kernel.h>

void numberToString(int, char *);
int strLen(char *);

void Clock()
{
    int i = 0;
    int j = 0;
    char str[] = "    "; // str for 4-digits, plus NUL
    unsigned short *p;
    while (1)
    {
        if (sys_tick % 100 == 0)
        {
            i += 1;
            numberToString(i, str);
            p = (unsigned short *)VIDEO_START;
            p += 75;
            while (str[j] != '\0')
            {
                *p = str[j] + VIDEO_MASK;
                j++;
            }
        }
    }
}

/*
 * Takes number and reference to str. str is populated with number
 */
// http://athena.ecs.csus.edu/~changw/159/grades/C-Test-Code/strings/itoa.c
void numberToString(int number, char *str)
{
    int j = 0;
    char tmp;

    str[0] = '0';

    while (number)
    {
        if (str[j] == '\0')
            break;
        str[j] = (number % 10) + '0';
        number /= 10;
        j++;
    }

    for (number = 0; number < j / 2; number++)
    {
        tmp = str[number];
        str[number] = str[j - number - 1];
        str[j - number - 1] = tmp;
    }
}

/*
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
