#include "main.h"

extern unsigned char gears[9][3];
extern unsigned short gear_index;
extern unsigned char write_addr;
extern int speed;

unsigned char time[9];  // Array to store the time string

void event_store(unsigned char time[])  // Keep it as it only takes 'time'
{
    char buffer[10];  

    // EEPROM Shift if Address >= 90
    if (write_addr > 90)
    {
        for (write_addr = 0; write_addr < 90; write_addr++)
        {
            write_external_eeprom(write_addr, read_external_eeprom(write_addr + 10));
        }
    }

    // Store time values correctly
    buffer[0] = time[0]; // HH
    buffer[1] = time[1];
    buffer[2] = time[3]; // MM
    buffer[3] = time[4];
    buffer[4] = time[6]; // SS
    buffer[5] = time[7];

    // Store gear data
    buffer[6] = gears[gear_index][0];
    buffer[7] = gears[gear_index][1];

    // Convert speed to ASCII and store
    int store_speed = (speed < 0) ? 0 : speed; // Ensure speed is non-negative
    buffer[8] = (store_speed / 10) + '0';
    buffer[9] = (store_speed % 10) + '0';

    // Write buffer values to EEPROM
    for (int i = 0; i < 10; i++)
    {
        write_external_eeprom(write_addr + i, buffer[i]);
    }

    // Update write address
    write_addr += 10;
}

unsigned char clock_reg[3];

void get_rtc_time(unsigned char time[])
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40)
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    else
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';  // End of string
}

void view_dashboard(void)
{
    get_rtc_time(time);  // Populate the time array from the RTC

    // For speed of the car
    speed = read_adc(CHANNEL4) / 10;  // Use potentiometer as channel 4
    if (speed > 99)
    {
        speed = 99;
    }

    clcd_print("TIME", LINE1(2));
    clcd_print(time, LINE2(0));

    clcd_print("GER", LINE1(10));
    clcd_print(gears[gear_index], LINE2(10));

    clcd_print("SP", LINE1(14));
    clcd_putch((speed / 10) + '0', LINE2(14));
    clcd_putch((speed % 10) + '0', LINE2(15));

    unsigned char key = read_matrix_keypad(STATE_CHANGE);
    if (key == 1)
    {
        if (gear_index < 8)  // Change limit for gear_index
        {
            gear_index++;
            event_store(time);  // Store time with the updated gear
        }
    }
    else if (key == 2)
    {
        if (gear_index == 8)
        {
            gear_index = 1;
        }
        else if (gear_index > 1)
        {
            gear_index--;
            event_store(time);  // Store time with the updated gear
        }
    }
    else if (key == 3)
    {
        gear_index = 8;  // Set gear to 8 when key 3 is pressed
        event_store(time);  // Store time with the updated gear
    }
    else if (key == 11)
    {
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }
    else if (key == 12)
    {
        state = e_dashboard;
    }
}
