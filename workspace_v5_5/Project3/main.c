#include <msp430.h> 

/*
Program Purpose:
Get the LED to blink every 1 second.
*/


volatile const unsigned char led = 0x01;
volatile const unsigned char inPin = 0x08;
unsigned int wdtCounter = 0;

#pragma vector = WDT_VECTOR
__interrupt void WATCHDOG_TIMER(void)
{

	if(wdtCounter == 31)
	{
		P1OUT ^= led;
		wdtCounter = 0;
	}
	else
	{
		wdtCounter++;
		P1OUT = 0;
	}

	//restore the register so the timer fires again
	WDTCTL = WDT_MDLY_32;
}


int main(void)
{

	P1DIR = 0xFF;
	P1SEL = 0;
	P1OUT = 0;

	//set up an input pin and an output in for the led
	P1DIR |= led;
	P1DIR &= ~(inPin);

	//Enable the watchdog timer interrupt and global interrupt
	IE1 |= WDTIE;

	//enables all interrupts
	__enable_interrupt();

	//set watchdog timer to 32 seconds
	WDTCTL = WDT_MDLY_32;


	//Adding these two lines of code will make the led blink 12 times faster.
	BCSCTL1 = CALBC1_12MHZ;
	DCOCTL = CALDCO_12MHZ;
	
	while(1);


}
