// proc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "spede.h"
#include "kernel.h" // was using <kernel.h>
void toStr(int, char *);
int strLen(char *);
uint16 *const video_base = (uint16 *)0xB8000;

void output_message(char toDisplay[])
{
    uint8 *vp8 = (uint8 *)(video_base + 75);
    uint8 *p = (uint8 *)toDisplay;

    for (; *p != '\0'; p += 1, vp8 += 2)
    {
        *vp8 = *p;
    }
}

void Clock()
{
    int j;
    int len;
    char str[] = "    "; // str for 4-digits, plus NUL
    while (1)
    {
        if (sys_tick % 100 == 0)
        {
            toStr(sys_tick / 100, str);
            printf("STR: %s\n", str);
            output_message(str);
        }
    }
}

/*
 * Takes number and reference to str. str is populated with number
 */
// http://athena.ecs.csus.edu/~changw/159/grades/C-Test-Code/strings/itoa.c
void toStr(int number, char *str)
{
    /**
     * PROFESOR'S CODE
    int len = strLen(str);
    str[len - 1] = number % 10 + '0';
    number /= 10;
    */

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

    // for (number = 0; number < strLen(str) / 2; number++)
    //{
    // tmp = str[number];
    // str[number] = str[j - number - 1];
    // str[j - number - 1] = tmp;
    //}
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
