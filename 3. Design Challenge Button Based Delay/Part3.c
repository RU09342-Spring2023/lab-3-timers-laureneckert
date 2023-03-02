/*
 * Part3.c
 *
 *  Created on: Feb 12, 2023
 *      Author: Lauren Eckert
 *
 */
#include <msp430.h>

unsigned const int blink_period_initial = 50000;
unsigned int blink_period = 50000;

void gpioInit();
void timerInit();

void main(){
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;    // Disable the GPIO power-on default high-impedance mode to activate previously configured port settings

    gpioInit();
    timerInit();
    __enable_interrupt();       // Enable global interrupts

    while(1) {
        __bis_SR_register(LPM3_bits | GIE); // Enter low power mode with interrupts enabled
    }
}

void gpioInit(){
    //Initialize the Red and Green LED
    //Configure RED LED on P1.0 as Output
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction

    //Configure Green LED on P6.6 as Output
    P6OUT &= ~BIT6;                         // Clear P6.6 output latch for a defined power-on state
    P6DIR |= BIT6;                          // Set P6.6 to output direction

    //Initialize Button 2.3
    P2OUT |= BIT3;                          // Configure P2.3 as pulled-up
    P2REN |= BIT3;                          // P2.3 pull-up register enable
    //P2IES &= ~BIT3;                         // P2.3 Falling edge - rise up
    P2IES |= BIT3;                          // P2.3 Rising edge - press down
    P2IE |= BIT3;                           // P2.3 interrupt enabled

    //Initialize Button 4.1
    P4OUT |= BIT1;                          // Configure P2.3 as pulled-up
    P4REN |= BIT1;                          // P4.1 pull-up register enable
    //P4IES &= ~BIT1;                         // P4.1 Falling edge - rise up
    P4IES |= BIT1;                          // P4.1 Rising edge - press down
    P4IE |= BIT1;                           // P4.1 interrupt enabled

}

void timerInit(){
    //Initialize Timer A


    //Initialize Timer B
    TB1CCR0 = blink_period;      // Set the max count for Timer B1
    TB1CTL = TBSSEL_1 | MC_2;  // ACLK, continuous mode - change to up mode
    TB1CCTL0 = CCIE;       // TBCCR0 interrupt enabled
}

// Port 2 interrupt service routine - counts how long the button is pressed
#pragma vector = PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    if (P2IES & BIT3)   //check if the interrupt was triggered off a rising edge
    {
        //start timer A to measure how long the button is pressed


        P2IES &= ~BIT3; // Change edge to falling edge
    }
    else if (P2IES != BIT3) //check if the interrupt was triggered off a falling edge
    {
        //stop timer A to record how long the button was pressed
        //put timer A value into the max timer B CCR0


        P2IES |= BIT3; // Change edge sensitivity to look for next rising edge
    }

    P6OUT ^= BIT6;           // P6.6 = toggle - to test to see if it is reading the button press
    P2IFG &= ~BIT3;         // Clear interrupt flag for P2.3
}

// Port 4 interrupt service routine - resets to initial state
#pragma vector = PORT4_VECTOR
__interrupt void Port4_ISR(void)
{
    blink_period = blink_period_initial;    //set to initial
    TB1CCR0 = blink_period;         //set to initial
    //reset timer A value

    P4IFG &= ~BIT1;         // Clear interrupt flag for P4.1
}

// Timer B interrupt service routine - blinks LED based on the button press time
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{
    P1OUT ^= BIT0;          // Toggle P1.0 LED
}



