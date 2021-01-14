
/* File: adc.c
 * 
 * ADC converter functions
 *		
 *   *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      			Comments on this revision		
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould		December 15 2016     								-v1.1
 * Serge Hould		14 Jan. 2021     	Modify for PIC32				-v2.0
 *										Setup to POT as analog input pin by default 
 *										the channel is AN2 see note below
 *
 *  
 *
 **********************************************************************/

// The PIM socket pin numbers is not  a 1 to 1 match to the PIC pins:
// According to the PIM datasheet pin 20 on the Explorer16/32 (the pin actually connected to the potmeter),
// connects to pin 23 on the device, which is AN2. 

#include "include/adc32.h"

/* initialize the ADC for single conversion, select Analog input pins */
void initADC(void) 
{
    AD1PCFGbits.PCFG2 = 0; // AN2 is an adc pin for the pot
    AD1CON3bits.ADCS = 2; // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
    // 2*3*12.5ns = 75ns
    AD1CON1bits.ADON = 1; // turn on A/D converter
} //initADC

/**
  Prototype:        int readADC( int ch)
  Input:            Channel to read
  Output:           returns the conversion result
  Description:      Select the specified input channel, samples the channel 
                    and then returns the converted value.
  Comment:          
  Usage:           
*/
int readADC( int ch)
{
    // adc pin the pin should be configured as an
    // analog input in AD1PCFG
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = ch; // connect chosen pin to MUXA for sampling
    AD1CON1bits.SAMP = 1; // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) {
    ; // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0; // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
    ; // wait for the conversion process to finish
    }
    return ADC1BUF0; // read the buffer with the result
} // readADC

