// proc.c, 159
// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "kernel.h" // was using <kernel.h>
#include <spede.h>
#include <stdio.h>
#include <string.h>

void numberToString(int, char *);
int strLen(char *);

void Clock()
{
    int i;
    char str[] = "    "; // str for 4-digits, plus NUL
    unsigned short *p;
    while (1)
    {
    }
}

/*program a void - return function Clock that takes no argument*/
/*{*/

/*an infinite loop*/
/*: if sys_tick is now at a new second convert the current second count*/
/*number to str set p to VIDEO_START(1st row, 1st column)*/
/*advance p by 75 columns(to the right, on the same row)*/

/*loop thru each char in str*/
/*: *p = the character + VIDEO_MASK*/
/*}*/

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
