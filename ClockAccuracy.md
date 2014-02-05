#Clock Accuracy
- DCO is a digitally controller Ocillator

###Why do we have Oscillators
- The DCO takes us 6us to start and stablize
- It is fast and saves power
- Can awake from sleep quickly and then go back to sleep

###Using CLocks
- Dont use clocks directly
- Instead you set a clock as the source for different system timers
- In the MSP there are
  - The watchdog timer
  - Timer A and Timer B
  - Watchdog timer runs from either SMCLK or ACLK
  - set WDT to 0 or 1 if necessary
  
###Setting up the watchdog timer
    void main(void)
    {
      //set up the ports here
      
    }
    __interrupt void watchdog_ timer(void)
    {
      //If 1 second has passed toggle the LED
      //restore the reg
    }
