#Quiz 1 Study guide

##Topics Covered : 
  - I/O
  - Interrupts
  - Timers
  - Low Power Mode


##Input/Output

###Ports
- Each port has 8 pins and the basic following properties
    - PxIN : read the register to get an output value
    - PxOUT : Write to this register to set an output value
    - PxDIR : Set the direction of the pin
    - PxSEL : turn on special functions for this pin , just set to 0 for normal use
    - PxIFG : The interrupt flag
    - PxIE : Enabling interrupts on this pin
    - PxIES : Enabling interrupts on edge selects low to high or high to low
    - PxREN : Enables the pull down resistor
    - To reduce power consumption set SEL to 0, DIR 1 and REN 1

###Setting up a Pin for input

    //Sets the inpin on pin 1
    volatile const unsigned char inPin = 0x08;
    //Sets led var to the actual LED
    volatile const unsigned char led = 0x01;
        
    //Also before running make sure the wdt is turned off
    WDTCTL = WDTPW + WDTHOLD;
        
    //Set the direction of pin one          
    P1DIR = 0xFF;
    //Set select for normal use
    P1SEL = 0;
    //Set the output default value to 0
    P1OUT = 0;
       
    //Set the output to go to the led
    P1DIR |= led;
    //Set the input for pin 1
    P1DIR &= ~(inPin);
    

The above code will setup Pin1 for input and set the output to the first LED</br>
Now if a user wishes to say togle the led or write to the first pin and change the value of the led they would do the following :

    P1OUT ^= led;


##Interrupts
- Interrupts are run when a value in a certain location is changed
- When the Interrupt is triggered the current state is saved and it jumps to a location/method in code
- Interrupts may mess up timing so turn them off in critical sections of code

###Interrupt setup

    //Setup the pull down resistor
    P1REN |= inPin;
      
    //Setup interrupt on pin 1
    P1IE |= inPin;
      
    //Enable all interrupts in this case only on pin one
    __enable_interrupt();

###Interrupt Method (Called when the value is changed)

    #pragma vector = PORT1_VECTOR
    __interrupt void portInterrupt(void)
    {
      //Some code here ^_^
      //Make sure to clear the flag when you are done so the interrupt can be thrown again
      P1IFG &= ~(inPin);
    }

The above code will setup an interrupt on port one and trigger the method shown when the value in port one is high

##Timers
- Watch Dog Timer is an example of a timer.
- Basically something that will keep track of the passing of time based on the system clock

###Setting up the WDT

    //sets up a wdt on 32ms
    WDTCTL = WDT_MDLY_32

In order to utilize this timer we can setup an interrupt on the timer firing the interrupt ever x amount of time.

    void main()
    {
      //Setup interrupt on wdt
      IE1 |= WDT1E
      //sets up a wdt on 32ms
      WDTCTL = WDT_MDLY_32
    }
        
    #pragma vector = WDT_VECTOR
    __interrupt void watchdog_timer(void)
    {
      //Do something every 32ms
      
      //reset the timer
      WDTCTL = WDT_MDLY_32
    }
    
###Changing the clock speed

    BCSCTL1 = CALBC1_12MHZ;
    DCOCTL = CALDCO_12MHZ;
    
The above will change the clock speed of your board from standard to 12 mhz can change to many different values.</br>
Changing the clock speed will change the timer speed also skewing the timer

##Low Power Mode
- Power consumption is of big concern within electronics such as mobile, and computers
- How we use the MSP430 will effect how much power it uses
- Our board has 4 different low power modes that control the clock which will result in less power consumption

###Turn off Inputs
- Turn unused I/O pins to output to prevent floating pins
- Use pullup/pulldown resistors to prevent floating

###Turning off all the pins in order to save power

    P1DIR = 0xFF;
    P2DIR = 0xFF;
    P1SEL = 0x00;
    P2SEL = 0x00;
    P1OUT = 0x00;
    P2OUT = 0x00;

###Low Power Mode Subsystems
- SCG1 : System Clock Generator 1
    - Turns off the SMCLK and peripherals
- SCG1 : System Clock Generator 0
    - Turns off DCO
- OSCOFF
    - Turns off the crystal oscillator 
- CPUOFF
    - Turns off the CPU

###Low Power Modes
- LPM0
    - Turns off the cpu
    - Goes from 360 micro amps to 56 micro amps
- LPM2
    - Turns off CPU and SMCLK
    - Goes from 330 to 22
- LPM3
    - Turns off CPU, SMCLK, DCO
    - Only uses .7 micro amps 
- LPM4
    - Turns off everything
    - Down to .1 micro amps

###Sleeping
- In order to save power we can sleep portions of the board using interrupts to wake those portions up
- LPM3 is the best one to use, LPM4 needs special interrupts to wake up from sleep
