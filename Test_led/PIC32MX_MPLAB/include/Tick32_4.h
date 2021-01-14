/*********************************************************************
 *
 *                  Tick Manager for PIC Tick32_4.h
 *
 *********************************************************************
 * FileName:        
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Author               Date    				Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould			28 December 2016		New version of Tick library
 *													modified to use timer4 
 *													rather than Timer1.
 * SH                   13 Jan. 2021  			Add PIC32MX features. 
 *
 * The original file is located in :
 * 247-511-VA Microcontroller Applications\Projects\common
 ********************************************************************/
#ifndef __TICK4_H
#define __TICK4_H
#include "GenericTypeDefs.h"

#ifndef _SUPPRESS_PLIB_WARNING
    #define _SUPPRESS_PLIB_WARNING
#endif
#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
    #define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif
#include <plib.h>

#define GetSystemClock()		(40000000ul)      // Hz		
#define GetPeripheralClock()	GetSystemClock()

// All TICKS are stored as 32-bit unsigned integers.
typedef DWORD TICK;

// This value is used by TCP to implement timeout actions.
// For this definition, the Timer must be initialized to use 
// a 1:256 prescalar in Tick.c.  If using a 32kHz watch crystal 
// as the time base, modify the Tick.c file to use no prescalar.
#define TICKS_PER_SECOND		((GetPeripheralClock()+128ull)/256ull)	// Internal core clock drives timer
//#define TICKS_PER_SECOND		((GetPeripheralClock()+128ull))	// DEBUG only
//#define TICKS_PER_SECOND		(32768ul)								// 32kHz crystal drives timer with no scalar

// Represents one second in Ticks
#define TICK_SECOND				((QWORD)TICKS_PER_SECOND)
// Represents one minute in Ticks
#define TICK_MINUTE				((QWORD)TICKS_PER_SECOND)*60ull)
// Represents one hour in Ticks
#define TICK_HOUR				((QWORD)TICKS_PER_SECOND*3600ull)

// Deprecated.  Do not use this function.
#define TickGetDiff(a, b)       ((a)-(b))

void TickInit(void);
DWORD TickGet(void);
DWORD TickGetDiv256(void);
DWORD TickGetDiv64K(void);
DWORD TickConvertToMilliseconds(DWORD dwTickValue);
void TickUpdate(void);

#endif
