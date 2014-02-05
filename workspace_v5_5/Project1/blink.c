//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************

#include <msp430.h>				

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

	/* Initial code
	 P1DIR |= 0x01;					// Set P1.0 to output direction

	 for(;;) {
	 volatile unsigned int i;	// volatile to prevent optimization

	 P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR

	 i = 10000;					// SW Delay
	 do i--;
	 while(i != 0);
	 }
	 */

	/* Cleaner version
	 //Cleaning up; let's turn off all of the pins for power savings
	 P1DIR = 0xFF;
	 P2DIR = 0xFF;
	 P1SEL = 0x00;
	 P2SEL = 0x00;
	 P1OUT = 0x00;
	 P2OUT = 0x00;

	 P1DIR |= 0x01;					// Set P1.0 to output direction

	 for(;;) {
	 volatile unsigned int i;	// volatile to prevent optimization

	 P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR

	 i = 10000;					// SW Delay
	 do i--;
	 while(i != 0);
	 }
	 */

	/* With input and output buttons
	//Cleaning up; let's turn off all of the pins for power savings
	P1DIR = 0xFF;
	P2DIR = 0xFF;
	P1SEL = 0x00;
	P2SEL = 0x00;
	P1OUT = 0x00;
	P2OUT = 0x00;

	//Let's name some constants: LED is P1.0, output is P1.3, input is P1.1
	const unsigned char led = 0x01;
	const unsigned char outPin = 0x08;
	const unsigned char inPin = 0x02;

	//Disable pullup/pulldown on the input and output pins,
	//set input for inPin, output for others
	P1DIR &= ~(inPin);
	P1REN &= ~(inPin | outPin);
	P1DIR |= led | outPin;

	P1OUT &= ~(led);

	for (;;) {
		volatile unsigned int i; // volatile to prevent optimization

		for (i = 10000; i != 0; --i) {
			//P1.2 is on when i < 5000, off otherwise
			if (i <= 5000) {
				P1OUT |= outPin;
			}
			else {
				P1OUT &= ~(outPin);
			}

			//Turn on the LED if Pin 1.1 is high
			if (P1IN & inPin) {
				P1OUT |= led;
			}
			else {
				P1OUT &= ~(led);
			}
		}
	}
	*/

	//With different pins at different rates

	//Cleaning up; let's turn off all of the pins for power savings
	P1DIR = 0xFF;
	P2DIR = 0xFF;
	P1SEL = 0x00;
	P2SEL = 0x00;
	P1OUT = 0x00;
	P2OUT = 0x00;

	//Let's name some constants: LED is P1.0,
	//output pins are P1.3 and P1.4, input is P1.1
	const unsigned char led = 0x01;
	const unsigned char outFast = 0x10;
	const unsigned char outSlow = 0x08;
	const unsigned char inPin = 0x02;

	//Disable pullup/pulldown on the input and output pins,
	//set input for inPin, output for others
	P1DIR &= ~(inPin);
	P1REN &= ~(inPin | outFast | outSlow);
	P1DIR |= led | outFast | outSlow;

	P1OUT &= ~(led);

	for (;;) {
		volatile unsigned int i; // volatile to prevent optimization

		for (i = 10000; i != 0; --i) {
			//Output is on when i < 5000, off otherwise
			if (i <= 5000)
			{
				P1OUT |= outSlow;
			}
			else
			{
				P1OUT &= ~(outSlow);
			}
			//Fast pin alternates every 500
			if ( (i / 500)%2)
			{
				P1OUT |= outFast;
			}
			else
			{
				P1OUT &= ~(outFast);
			}

			//Turn on the LED if Pin 1.1 is high
			if (P1IN & inPin)
			{
				P1OUT |= led;
			}
			else
			{
				P1OUT &= ~(led);
			}
		}
	}


}
