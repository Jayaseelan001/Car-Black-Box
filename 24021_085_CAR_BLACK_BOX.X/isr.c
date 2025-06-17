#include <xc.h>

void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR2IF)
	{
		TMR2 = TMR2 + 8;

		if (count++ == 20000)
		{
			count = 0;
			//LED1 = !LED1;
		}
		TMR2IF = 0;
	}
}
