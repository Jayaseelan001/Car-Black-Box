#include "main.h"
extern unsigned char main_menu;
extern unsigned short menu_no;
extern unsigned short star;
void view_log(void)
{
    //clcd_print("ENTERED ",LINE1(0));
    //clcd_print(main_menu[menu_no + star],LINE2(3));
    if(star == 0)
    {
        clcd_print("ENTERED ",LINE1(0));
        clcd_print(main_menu[menu_no],LINE2(3));
    }
    else
    {
        clcd_print("ENTERED ",LINE1(0));
        clcd_print(main_menu[menu_no + 1],LINE2(3));
    }
}