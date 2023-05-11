#include <MKL46Z4.h>

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
const int RED_LED_PIN = 29;
const int GREEN_LED_PIN = 5;
SIM_Type *global_SIM = SIM;
PORT_Type *global_PORTE = PORTE;
GPIO_Type *global_PTE = PTE;

void LED_Initialize(void)
{
  SIM->SCGC5 |= (1 << 13);
  PORTE->PCR[RED_LED_PIN] = (1 << 8);
  PTE->PDDR |= 1 << RED_LED_PIN;
  SIM->SCGC5 |= (1 << 12);
  PORTD->PCR[GREEN_LED_PIN] = (1 << 8);
  PTD->PDDR |= 1 << GREEN_LED_PIN;
  LED_Off();
};

/*---------------------------------------------------------------------------
 Three functions for toggling the current state of each LED individually
 ----------------------------------------------------------------------------*/
void LEDRed_Toggle(void)
{
  PTE->PTOR |= 1 << RED_LED_PIN;
};
void LEDGreen_Toggle(void)
{
  PTD->PTOR |= 1 << GREEN_LED_PIN;
};

/*---------------------------------------------------------------------------
 Three functions for toggling the turning ON LEDs individually
 ----------------------------------------------------------------------------*/
void LEDRed_On(void)
{
  PTE->PCOR |= 1 << RED_LED_PIN;
};
void LEDGreen_On(void)
{

  PTD->PCOR |= 1 << GREEN_LED_PIN;
};

/*---------------------------------------------------------------------------
 Three functions for toggling the turning OFF LEDs individually
 ----------------------------------------------------------------------------*/
void LEDRed_Off(void)
{
  PTE->PSOR |= (1 << RED_LED_PIN);
};

void LEDGreen_Off(void)
{
  PTD->PSOR |= (1 << GREEN_LED_PIN);
};

/*---------------------------------------------------------------------------
 One function turning OFF both LEDs
 ----------------------------------------------------------------------------*/
void LED_Off(void)
{
  LEDRed_Off();
  LEDGreen_Off();
};
