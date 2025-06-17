
#include "main.h"
#include "uart.h"

extern unsigned char main_menu[4][16];
extern unsigned short menu_no;
extern unsigned short star;
extern unsigned char write_addr;
unsigned char read_addr = 0x00;
unsigned char download_data[10][16];

//void read_data()
//{
//    // Read the data and store
//    for (int i = 0; i < 10; i++)
//    {
//        for (int j = 0; j < 10; j++)
//        {
//            data[i][j] = read_external_eeprom(read_addr++);
//        }
//        data[i][10] = '\0';  
//    }
//}
char log_index = 0;  // Index to track the current log entry
void view_log(void)
{
    clcd_print("#", LINE1(0));
    clcd_print("TIME", LINE1(4));
    clcd_print("GP", LINE1(11));
    clcd_print("SP", LINE1(14));
    clcd_print("                ", LINE2(0));  // Clear second line


    unsigned char key = read_matrix_keypad(STATE_CHANGE);

    if (key == 2)  // Scroll forward
    {
        if( log_index < (write_addr / 10) - 1)
        {
            log_index++;
        }
    }
    else if (key == 1)  // Scroll backward
    {
        if(log_index > 0)
        {
            log_index--;
        }
    }
    
    if (write_addr == 0)
    {
        clcd_print("No Data found    ", LINE1(0));
        clcd_print("                ", LINE2(0));
        
        for (unsigned long delay = 500000; delay--;);
        state = e_main_menu;
        clcd_print("                ", LINE1(0));
        return;
        
    }
    else if (key == 12)  // Exit condition
    {
        log_index = 0;
        state = e_main_menu;  // Ensure 'state' is declared globally
        CLEAR_DISP_SCREEN;  // Clear the screen
    }

    clcd_putch(log_index + '0', LINE2(0));
    clcd_putch(' ', LINE2(1));
    
    // Corrected `log_index` usage
    clcd_putch(read_external_eeprom((log_index * 10)), LINE2(2));
    clcd_putch(read_external_eeprom((log_index * 10) + 1), LINE2(3));
    clcd_putch(':', LINE2(4));
    clcd_putch(read_external_eeprom((log_index * 10) + 2), LINE2(5));
    clcd_putch(read_external_eeprom((log_index * 10) + 3), LINE2(6));
    clcd_putch(':', LINE2(7));
    clcd_putch(read_external_eeprom((log_index * 10) + 4), LINE2(8));
    clcd_putch(read_external_eeprom((log_index * 10) + 5), LINE2(9));
    clcd_putch(' ', LINE2(10));
    clcd_putch(read_external_eeprom((log_index * 10) + 6), LINE2(11));
    clcd_putch(read_external_eeprom((log_index * 10) + 7), LINE2(12));
    clcd_putch(' ', LINE2(13));
    clcd_putch(read_external_eeprom((log_index * 10) + 8), LINE2(14));
    clcd_putch(read_external_eeprom((log_index * 10) + 9), LINE2(15));
}

void clear_data(void)
{
    for(int i = 0; i < 10; i++)
    {
        write_external_eeprom(read_addr++,0xFF);
    }
}
void clear_log(void)
{
    clear_data();
    
    write_addr = 0;
    
    clcd_print("The data is", LINE1(0));
    clcd_print("cleared", LINE2(4));
    
    unsigned char key = read_matrix_keypad(STATE_CHANGE);
    
    if(key == 12)
    {
        state = e_main_menu;
        CLEAR_DISP_SCREEN;
    }
}

void download_log(void)
{
    static unsigned char download_index = 0;
    char buffer[20];  
    
    clcd_print("DOWNLOADED",LINE1(1));
    clcd_print("SUCCESSFULLY...",LINE2(2));

    puts("# Time     EV SP \n\r");

    while(download_index<(write_addr/10))
    {
        buffer[0] = download_index + '0';
        buffer[1] = ' ';
        buffer[2] = read_external_eeprom((download_index * 10));      // Hour tens
        buffer[3] = read_external_eeprom((download_index * 10) + 1);  // Hour units
        buffer[4] = ':';
        buffer[5] = read_external_eeprom((download_index * 10) + 2);  // Minute tens
        buffer[6] = read_external_eeprom((download_index * 10) + 3);  // Minute units
        buffer[7] = ':';
        buffer[8] = read_external_eeprom((download_index * 10) + 4);  // Second tens
        buffer[9] = read_external_eeprom((download_index * 10) + 5);  // Second units
        buffer[10] = ' ';
        buffer[11] = read_external_eeprom((download_index * 10) + 6); // EV tens
        buffer[12] = read_external_eeprom((download_index * 10) + 7); // EV units
        buffer[13] = ' ';
        buffer[14] = read_external_eeprom((download_index * 10) + 8); // Speed tens
        buffer[15] = read_external_eeprom((download_index * 10) + 9); // Speed units
        buffer[16] = '\n';
        buffer[17] = '\r';
        buffer[18] = '\0';   

        puts(buffer);  // Print formatted string
        download_index++;
    }
    //download_index = 0;
    for(unsigned long wait=500000;wait--;);
    state =  e_main_menu;
    CLEAR_DISP_SCREEN;  // Clear the screen
    download_index = 0;
    return ;
}