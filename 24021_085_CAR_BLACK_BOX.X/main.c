/*
 * File:   main.c
 * Author: emertxe
 *
 * Created on 14 February, 2024, 5:40 PM
 */


#include "black_box.h"
#include "clcd.h"
#include "mkp.h"
#include "adc.h"
#include "timer0.h"
#include "ds1307.h"
#include "I2C.h"
#include "uart.h"

State_t state;

void init_config()
{
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_i2c();
    init_ds1307();
    init_uart();
    
    state = e_dashboard;
}

unsigned char gears[9][3] = {"ON","GN","G1","G2","G3","G4","G5","GR","CC"};
unsigned short gear_index = 0;
unsigned char write_addr = 0x00;
int speed = 0;

void main(void) 
{
    init_config();

    while(1)
    {
        // Detect key press
        
        //display_rtc_time();
        get_rtc_time(time); // to get real time clock with i2c
        
        switch (state)
        {   
            case e_dashboard:
                // Display dashboard
                view_dashboard();
                break;
            
            case e_main_menu:
                // Display dashboard
                display_main_menu();
                break;
            
            case e_view_log:
                // Display dashboard
                view_log();
                break;
                 
            case e_download_log:
                download_log();
                break;
                
            case e_clear_log:
                clear_log();
                break;
                
                      
            case e_set_time:
                set_time();
                break;
                
        }
        
    }
    
}
