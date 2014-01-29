#Lecture 3
- 16 bit RISC 
- 16 registers
  - First four are dedicated to the PC stack pointer status register and constant generator
- 16 MHz clock
- Its slow
- There are several memory sections
- If you build  a program open the asdlfja;lskdjf;asd.cmd file
  - This has ever single memory segment and interrupt labelled
  - Good way to quickly check sizes of different sections
- The important parts 
  - 16kB of main memory for code and interrupt vecotrs
  - 512 bytes
  
##Data Section
- The .sysmem segment is for dynamic memory allocation
- The exact memory address moves so nothing is overwritten

##Interrupts
- MCU looks for interrupts at specific memory locations
- A function in an interrupt location is run
- When an interrupt is triggered the MCU will save the current stack and go to the interrupt
  - Just as if u called a function
  - But the interrupt might mess up the timing of your function
  - Disable interrupts in crit sections
  - Interrupt flags  are set whe the interrupt occurs
  - The programmer is responsible for clearing the flags
  - P1FG has the interrupt flags
  - P1IE enables interrupts
  - P1ES sets rising 0 or falling 1



