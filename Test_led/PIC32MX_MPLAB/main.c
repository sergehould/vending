  
/* ***************************************************************************
 * File: main.c
 * Description: Main source file for all Embedded Operating Systems labs.
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *                            
 *****************************************************************************/

/* peripheral library include */
#include <plib.h>
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h" 
#include "semphr.h"
#include "croutine.h"
/* Hardware specific includes. */
#include "ConfigPerformance.h"
#include "include/console32.h"
#include "include/Tick32_4.h"
#include "include/adc32.h"
#include "include/public.h"

/* Prototypes for the standard FreeRTOS callback/hook functions implemented within this file. */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );

int main( void )
{
    	/* Prepare the hardware to run this demo. */
	prvSetupHardware();
    initIO();
    TickInit();
    initADC();
    LCDInit();
    initUart1();
    initUart2_wInt();
    
    fprintf2(CONSOLE, "Hi LCD2\n");
    
    /* create tasks here */
    vTaskStartScheduler();
	return 0;
}
/*-----------------------------------------------------------*/


void vApplicationIdleHook( void ){
    long cnt=0;
    while(1){
        //your code here
    }
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    pxTask= pxTask;
    pcTaskName = pcTaskName;
		for( ;; );
}

