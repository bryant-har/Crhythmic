#ifndef LED_H
#define LED_H

/*----------------------------------------------------------------------------
  The two lines above prevent the library from being included multiple times.
  Since we only include it from a single file it is not strictly necessary here 
  but it is good practice for writing libraries.
 -----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
  Function that initializes LEDs

  Note: You need to perform the following steps
  1. Turn on the clock gating to the appropriate ports
  2. Set the pin MUX to GPIO
  3. Set the pin to output
  4. The LEDs should be OFF after this function runs
 ----------------------------------------------------------------------------*/
void LED_Initialize(void);



/*---------------------------------------------------------------------------
 Three functions for toggling the current state of each LED individually
 ----------------------------------------------------------------------------*/
void LEDRed_Toggle (void);
void LEDGreen_Toggle (void);



/*---------------------------------------------------------------------------
 Three functions for toggling the turning ON LEDs individually
 ----------------------------------------------------------------------------*/
void LEDRed_On (void);
void LEDGreen_On (void);



/*---------------------------------------------------------------------------
 Three functions for toggling the turning OFF LEDs individually
 ----------------------------------------------------------------------------*/
void LEDRed_Off (void);
void LEDGreen_Off (void);



/*---------------------------------------------------------------------------
 One function turning OFF both LEDs
 ----------------------------------------------------------------------------*/
void LED_Off (void);

#endif