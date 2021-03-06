/* 
 * File:   main.c
 * Author: Andres D. Rebeil
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led0, led1, led2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = led0;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //Initialization functions
    initLEDs();
    initTimer1();
    
    
    while(1){

        //TODO: Implement a state machine to create the desired functionality
        switch(state){
                case led0:
                    turnOnLED(0);
                break;
                case led1:
                    turnOnLED(1);
                break;
                case led2:
                    turnOnLED(2);
                break;
        } 
    }
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed
void __ISR(_TIMER_1_VECTOR, IPL7SRS)_T1Interupt()
{
    IFS0bits.T1IF = 0;
    LATDbits.LATD0 = LATDbits.LATD0;
   
    if(state ==  led0) state = led1;
    else if(state == led1) state = led2;
    else if(state == led2) state = led0;
}

