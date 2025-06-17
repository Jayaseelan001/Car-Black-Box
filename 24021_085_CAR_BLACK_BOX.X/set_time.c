#include "main.h"

extern unsigned char time[9];
unsigned char hour, min, sec;
unsigned char flag = 0;
unsigned char field = 0;
unsigned long delay;

void set_time(void)
{
    if (flag == 0)
    {
        hour = time[0] - '0';
        hour = hour * 10 + time[1] - '0';
        min = time[3] - '0';
        min = min * 10 + time[4] - '0';
        sec = time[6] - '0';
        sec = sec * 10 + time[7] - '0';
        flag = 1;
    }
    
    unsigned char key = read_matrix_keypad(STATE_CHANGE);
    
    if (key == 1)
    {
        if (field == 0)
        {
            if (hour++ == 23)
            {
                hour = 0;
            }
        }
        if (field == 1)
        {
            if (min++ == 59)
            {
                min = 0;
            }
        }
        if (field == 2)
        {
            if (sec++ == 59)
            {
                sec = 0;
            }
        }
    }
    if (key == 2)
    {
        if (field++ == 2)
        {
            field = 0;
        }
    }
    if (key == 11)
    {
        hour = ((hour / 10) << 4) | (hour % 10);
        write_ds1307(HOUR_ADDR, hour);
        min = ((min / 10) << 4) | (min % 10);
        write_ds1307(MIN_ADDR, min);
        sec = ((sec / 10) << 4) | (sec % 10);
        write_ds1307(SEC_ADDR, sec);
        state = e_main_menu;
        flag = 0;
        CLEAR_DISP_SCREEN;
        return;
    }

    if (key == 12)
    {
        state = e_main_menu;
        flag = 0;
        return;
    }

    clcd_print(" HH:MM:SS ", LINE1(0));
    if (delay++ < 500)
    {
        clcd_putch(' ', LINE2(0));
        clcd_putch('0' + hour / 10, LINE2(1));
        clcd_putch('0' + hour % 10, LINE2(2));
        clcd_putch(':', LINE2(3));
        clcd_putch('0' + min / 10, LINE2(4));
        clcd_putch('0' + min % 10, LINE2(5));
        clcd_putch(':', LINE2(6));
        clcd_putch('0' + sec / 10, LINE2(7));
        clcd_putch('0' + sec % 10, LINE2(8));
    }
    else
    {
        if (field == 0)
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch(' ', LINE2(1));
            clcd_putch(' ', LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch('0' + min / 10, LINE2(4));
            clcd_putch('0' + min % 10, LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch('0' + sec / 10, LINE2(7));
            clcd_putch('0' + sec % 10, LINE2(8));
        }
        else if (field == 1)
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch('0' + hour / 10, LINE2(1));
            clcd_putch('0' + hour % 10, LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch('0' + sec / 10, LINE2(7));
            clcd_putch('0' + sec % 10, LINE2(8));
        }
        else if (field == 2)
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch('0' + hour / 10, LINE2(1));
            clcd_putch('0' + hour % 10, LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch('0' + min / 10, LINE2(4));
            clcd_putch('0' + min % 10, LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        }
    }
    if (delay == 1000)
    {
        delay = 0;
    }
}

