#include <msp430.h> 

volatile const unsigned char LED = 0x01;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void intA1(void) {

    P1OUT ^= LED;

}



/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    P1DIR = 0xFF;
    P1OUT = 0;
    P1SEL = 0;

    P1DIR |= LED;

    BCSCTL3 |= LFXT1S_2;
    TA0CTL = MC_1 | TASSEL_1 | ID_3;

    TA0CCR0 = 1500;
    TA0CCTL0 = CCIE;

    _BIS_SR(LPM3_bits +GIE);

    __enable_interrupt();

    while(1);

    return 0;
}
