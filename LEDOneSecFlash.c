#include <msp430.h>

const char LED = BTT0;

#pragma vector = TIMER0_A0_VECTOR
interupt void timerA(void)
{
	P1OUT ^= LED;
}

void main (void)
{
	
	WDRCTL  = WDTPW + WDTHOLD;
	//mode 1 source SMCLK div by 8

	P1DIR |= LED;
	P1OUT = 0;


	//Setting up the control register
	//divider control and source
	TABCTL = MC_1 | ID_3 | TASSEL_2;

	//Closest to its max so this is a shit-head move but who cares BOLO
	//We are dividing by 8
	TACCR0 = 65250;
	//Setup interrupt enable, sets up a vector in order to turn on the LED
	TACCTL0 = CCIE;
	_enable_interrupt();
	while(1);

}
