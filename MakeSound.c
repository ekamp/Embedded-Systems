#include <msp430.h> 
#include <Math.h>
#define period 200
const float sawtooth_step = (1.0/period)*3*3.14159;	//leave, irrational quotient
unsigned int sawtooth_counter = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void intA0(void) {

	sawtooth_counter++;
	
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void intA1(void) {

	if(sawtooth_counter == 36)
	{
	  TACCR1 = TACCR0;
	}
}


/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    TA0CCR0 = 255;

    /*
     * setting up clock source
     * Mode 1, source SMCLK, div by 4
     */
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;
    TA0CTL = MC_1 | ID_2 | TASSEL_2;

    /*
	 * initialize TA0CCTL1 to OUTMOD_7 which is a pulse setting.
	 * set up TA0CCR1 to one quarter of the bin width, or 64 so that it pulses 1/4th of the time
	 * TA0CCR1 should have a value between 0 and 255
	 */
   // TA0CCTL1 = OUTMOD_7;
    TA0CCR1 = 0;

    /*
     * set up pin 1.6 for output
     */
    P1DIR = BIT6;
	P1OUT = 0;
	P1SEL = BIT6;


	/*
	 *
	 */
	TA0CCTL1 = OUTMOD_7 | CCIE;
	__enable_interrupt();


	return 0;
}
