#include "main.h"

unsigned char main_menu[4][16] = {"View_log      ","Clear_log     ","Download_log  ","Set_time      "};
unsigned short menu_no = 0;
unsigned short star = 0;

void display_main_menu(void)
{
    
    clcd_print(main_menu[menu_no],LINE1(2));
    clcd_print(main_menu[menu_no+1],LINE2(2));
    
    unsigned char key = read_matrix_keypad(STATE_CHANGE);
    
    if(star == 0)
    {
        clcd_putch('*',LINE1(0));
        clcd_putch(' ',LINE2(0));
    }
    else
    {
        clcd_putch('*',LINE2(0));
        clcd_putch(' ',LINE1(0));
    }
    
    if(key == 1)
    {
        if(star == 1)
        {
            star = 0;
        }
        else
        {
            if(menu_no > 0)
            {
                menu_no--;
            }
        }
    }
    else if(key == 2)
    {
        if(star == 0)
        {
            star = 1;
        }
        else
        {
            if(menu_no < 2)
            {
                menu_no++;
            }
        }
    }
    else if(key == 12)
    {
        state = e_dashboard;
        CLEAR_DISP_SCREEN;
    }
    
    else if(key == 11)
    {
        int select_menu = menu_no + star;
        switch(select_menu)
        {
            case 0:
                state = e_view_log;
                CLEAR_DISP_SCREEN;
                break;
            case 1:
                state = e_clear_log;
                CLEAR_DISP_SCREEN;
                break;
            case 2:
                state = e_download_log;
                CLEAR_DISP_SCREEN;
                break;
            case 3:
                state = e_set_time;
                CLEAR_DISP_SCREEN;
                break;
        }
    }
}


