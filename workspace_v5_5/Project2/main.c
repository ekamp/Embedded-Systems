#include <msp430.h> 

/*
Program Purpose:
If you connect P1.1 and P1.2 the led should turn on.
*/


/*
 * main.c
 */
//#define led = 0x01;
//good programming practice -- remember to enable and disable interrupts
//you must clear interrupt flags

volatile const unsigned char led = 0x01;
volatile const unsigned char inPin = 0x08;

#pragma vector = PORT1_VECTOR
__interrupt void portInterrupt(void)
{
	P1OUT ^= led;
	P1IFG &= ~(inPin);
}


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer

	P1DIR = 0xFF;
	P1SEL = 0;
	P1OUT = 0;

	//set up an input pin and an ourput in for the led
	P1DIR |= led;
	P1DIR &= ~(inPin);

	//set up a pull down register
	P1REN |= inPin;

	//sets up the interrupt
	P1IE |= inPin;

	//enables all interrupts
	__enable_interrupt();

	while(1);


//	WRONG
//	if(P1IN & inPin)
//	{
//		portInterrupt();
//	}

}
