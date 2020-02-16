// proc.c, 159
// Team Name: ChaOS (Members: Aditya Tuladhar, Marcus Huston, Phil Fernandez)

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

#include "spede.h"
#include "kernel.h"
#include "syscall.h"
#define ANS_STR_SZ 96

void toStr(int, char *);
int strLen(char *);

void Clock()
{
    int i;
    char str[] = "    ";
    unsigned short *p;

    while (1)
    {
        if (sys_tick % TIME_SIZE == NUL)
        {
            cur_second = sys_tick / 100;
            toStr(cur_second, str);
            p = VIDEO_START;
            p += 75;

            for (i = 0; str[i] != NUL; i++)
            {
                *p = str[i] + VIDEO_MASK;
                // shift p over to make room for more digits
                p++;
            }
        }
    }
}

void toStr(int number, char *str)
{

    int len = strLen(str);
    int j = len - 1;

    while (number && j >= 0)
    {
        str[j] = (number % 10) + '0';
        number /= 10;
        j--;
    }
}

int strLen(char *s)
{
    int length = 0;
    char c = *(s + length);

    while (c != NUL)
    {
        length++;
        c = *(s + length);
    }

    return length;
}

void Init()
{
    int cur_time;
    char time_str[] = "    ";
    char answer_str[ANS_STR_SZ];
    while (1)
    {
        cur_time = get_time_call();
        toStr(cur_time, time_str);
        write_call("The time is ");
        write_call(time_str); // pass "The time is "
        write_call(".\n");
        write_call("What do you say to a cup of coffee? ");
        read_call(answer_str);
        write_call("The answer is ");
        write_call(answer_str);
        write_call(".\n");
    }
}
