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
    - To reduce power consumption set SEL to 0, DIR 1 and REN 1


