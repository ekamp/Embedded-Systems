#include <msp430.h>
#include <msp430g2553.h>

/*
 * main.c
 */

#define LED0 BIT0
#define LED1 BIT6
#define BUTTON 0x08

const unsigned char led = BIT0;
const unsigned char led2 = BIT6;
const unsigned char xin = BIT6;
const unsigned char xout = BIT7;
unsigned char led_on = 0;
unsigned char led2_on = 0;
volatile unsigned int i;//to prevent optimization

double buttonLengths[5];

int numberOfLengths = 0;

//#pragma vector=PORT1_VECTOR
//__interrupt void Port_1(void)
//{
////wdtCounter = 0; // reset watchdog timer counter
////P1OUT |= 0x01; // turn LED on
//P1IFG = 0x0;
//_BIC_SR(LPM3_EXIT); // wake up from low power mode
//
//}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void timerA(void)
{
	P1OUT = LED0;
	P1OUT = 0x00;
	//Now clear everything
	numberOfLengths = 0;
	TACCR0 = 0;
}

#pragma vector=PORT1_VECTOR
 __interrupt void Port_1(void)
 {
	 //P1OUT = 0x00;
	 //P1OUT = LED1; // P1.0 = toggle
	 P1IES ^= BUTTON; // toggle the interrupt edge,
	 if((P1IN & BIT3)==0) //rising edge
	 {
		 TACCR0 = 0;
		 TA0CTL = MC_1 | TASSEL_1 | ID_3;
		 TA0CCR0 = 4095*2;
		 //Enable timer Timer A0 CCR interrupts
		 TA0CCTL0 |= CCIE;
	 }
	 else//falling edge
	 {
		 buttonLengths[numberOfLengths] = TA0R;
		 numberOfLengths++;
//		 timing = 0;
		 //Reset the timer so the timer counts for 2 seconds in between
		 TACCR0 = 0;
		 TA0CTL = MC_1 | TASSEL_1 | ID_3;
		 TA0CCR0 = 4095*4;
		 //Enable timer Timer A0 CCR interrupts
		 TA0CCTL0 |= CCIE;

		 P1OUT ^= LED1; // P1.0 = toggle
		 P1OUT = 0x00; // P1.0 = toggle
	//	 __enable_interrupt();
	 }

	 P1IE |= BUTTON; // P1.3 interrupt enabled
	 P1IFG &= ~BUTTON; // P1.3 IFG cleared
	 //P1IES ^= BUTTON;
	 //start TACCR0 here
	 //timing = 1;
 }


int main(void) {
	//Stop the watchdog timer
	double referenceValues[9][5] = {{0,1,1,1,1},{0,0,1,1,1},{0,0,0,1,1},{0,0,0,0,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,0,0},{1,1,1,0,0},{1,1,1,1,0}};
//	int timing = 0;
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR|=LED1;//set all bits in P1 to input except BIT0
	P1DIR|=LED0;
	P1DIR |= BIT4;
	P1OUT = BIT4;
	//ACLK divider is 0
	BCSCTL1 |= DIVA_0;
	//12.5pF cap for the crystal oscillator
	BCSCTL3 |= XCAP_3;

	P1REN |= BUTTON; //Pull up resistor
	P1IE |= BUTTON; // P1.3 interrupt enabled
	P1IFG &= ~BUTTON; // P1.3 IFG cleared
	__enable_interrupt();
	//_BIS_SR(LPM3_bits + GIE); // Enter LPM3 w/interrupt

	//__enable_interrupt();

	for(;;)
	{
		//P1DIR |= BIT4;
		P1OUT = BIT4;
		if(numberOfLengths == 4)
		{
			//Find the largest
			__disable_interrupt();
			int k = 0;
			long largest = 0 ;
			for(;k<5;k++)
			{
				if(largest < buttonLengths[k])
				{
					largest = buttonLengths[k];
				}
			}
			int currentArray[5];
			//If its 1/2 the length of the largest than its a dash
			//If its less than 1/2 then its a dot
			int i = 0;
			for(;i<5;i++)
			{
				if(buttonLengths[i] >= largest*.5)
				{
					currentArray[i] = 1;
				}
				else
				{
					currentArray[i] = 0;
				}
			}
			i = 0;
			int j = 0 , answer = -1;
			//Need to lookup the value in the array
			for(;i<9;i++)
			{
				for(;j<5;j++)
				{
					if(currentArray[j] != referenceValues[i][j])
					{
						break;
					}
					else
					{
						if(j == 4)
						{
							//we found a match
							answer = i;
						}
					}
				}
			}
			if(answer == -1)
			{
				//blink red led
				P1OUT = LED0;
				P1OUT = 0x00;
			}
			//blink the green led for the number blink it answer number of times :)
			int blinkTimes = 0 ;
			for(; blinkTimes <= answer ;blinkTimes++)
			{
				P1OUT = LED0;
				P1OUT = 0x00;
			}
		}
	}
}
