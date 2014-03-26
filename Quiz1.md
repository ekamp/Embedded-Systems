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
    //Setup the pull down resistor
    P1REN |= inPin;
      
    //Setup interrupt on pin 1
    P1IE |= inPin;
      
    //Enable all interrupts in this case only on pin one
    __enable_interrupt();
    

The above code will setup Pin1 for input and set the output to the first LED
