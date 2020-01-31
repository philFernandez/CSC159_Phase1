// proc.c, 159
// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

include spede.h and kernel.h

prototype any subroutines of Clock() here

program a void-return function Clock that takes no argument {
   int i;
   char str[] = "    ";  // str for 4-digits, plus NUL
   unsigned short *p;

   an infinite loop:
      if sys_tick is now at a new second
         convert the current second count number to str
         set p to VIDEO_START (1st row, 1st column)
         advance p by 75 columns (to the right, on the same row)

         loop thru each char in str:
            *p = the character + VIDEO_MASK
}

Program a void-return function:
given a number and an address of a string, it converts the number
to the string.

Program an integer-return function:
given a string, the function counts up the length of the string
and returns it.

