##Part 3, Button based LED blinking

Overall function of the program:

- This code is for a microcontroller program written in C language. The program is designed to blink an LED (Light Emitting Diode) connected to pin P1.0 of the microcontroller at a frequency that is determined by the amount of time that a button connected to pin P2.3 is pressed. The program also includes a second button connected to pin P4.1, which when pressed resets the LED blink frequency to an initial value.

The program initializes the microcontroller's general-purpose input/output (GPIO) pins and sets up two timers, Timer B0 and Timer B1. Timer B0 is used to measure the duration of a button press on pin P2.3, while Timer B1 is used to generate a square wave output to drive the LED on pin P1.0 at the desired frequency. The program also enables interrupts and sets the microcontroller to enter low-power mode with interrupts enabled.

The program's main loop runs indefinitely and is structured to wait for an interrupt to occur, at which point the corresponding interrupt service routine is executed. The Port 2 interrupt service routine counts the duration of a button press on pin P2.3 using Timer B0 and sets the count value as the max count for Timer B1. The Port 4 interrupt service routine resets the LED blink frequency to an initial value, and the Timer B1 interrupt service routine toggles the state of the LED on pin P1.0 at the desired frequency.

Information on parts of the code:

- void gpioInit()

This is a function called gpioInit that initializes the GPIO (General Purpose Input/Output) pins of a microcontroller for the following tasks:

Initializing the Red and Green LED:
Configure the Red LED on Pin P1.0 as output by setting P1DIR bit 0 to 1.
Clear the output latch of Pin P1.0 by setting P1OUT bit 0 to 0.
Configure the Green LED on Pin P6.6 as output by setting P6DIR bit 6 to 1.
Clear the output latch of Pin P6.6 by setting P6OUT bit 6 to 0.
Initializing Button 2.3 and Button 4.1:
Configure the Button 2.3 on Pin P2.3 and Button 4.1 on Pin P4.1 as input.
Enable the pull-up resistor for Button 2.3 and Button 4.1 by setting P2REN bit 3 and P4REN bit 1 to 1.
Configure the Button 2.3 and Button 4.1 to detect the rising edge of the signal by setting P2IES bit 3 and P4IES bit 1 to 1.
Enable interrupts for Button 2.3 and Button 4.1 by setting P2IE bit 3 and P4IE bit 1 to 1.
Overall, this function sets up the necessary pins for input and output, and enables interrupts for the two buttons, which will trigger a response from the microcontroller when pressed.

- void timerInit()

This part of the code initializes two timer modules, Timer B0 and Timer B1.

For Timer B0, it sets the capture/compare register (TB0CCR0) to an arbitrary initial value of 300, sets the clock source to ACLK, stops the timer, and clears it. It also sets the capture/compare control register (TB0CCTL0) to capture mode and to capture both edges.

For Timer B1, it sets the capture/compare register (TB1CCR0) to a specific value called "blink_period", sets the clock source to ACLK, and sets it to up mode. It also sets the capture/compare control register (TB1CCTL0) to enable the Timer B1 capture/compare register 0 interrupt (CCIE).

ID_3: This sets the input clock divider for Timer B0 to 8. It divides the input clock frequency by 8 before it's used as the input for Timer B0.

MC_0: This sets the mode of Timer B0 to "stop mode", which means the timer is stopped and does not count.

TBCLR: This bit is used to clear the timer. When it's set, it clears the count in the timer to 0.

The combination of TBSSEL_1 and ID_3 divides the input clock by 8 and selects the ACLK (Auxiliary Clock) as the input source for Timer B0. The ACLK is typically a low-frequency clock source that is derived from an external crystal or oscillator.

So overall, Timer B0 in this code is in stop mode and is using ACLK as its input source, with a clock divider of 8. The timer is also cleared when TBCLR is set.

The mode of Timer B1 is "up mode". In this mode, the timer counts up from zero until it reaches the value in the Timer B1CCR0 register, which is set to blink_period in the code. Once the timer reaches this value, it generates an interrupt and resets back to zero, starting the count all over again. This process repeats indefinitely as long as the timer is enabled.

Additionally, Timer B1 is configured to use ACLK (Auxiliary Clock) as its clock source. ACLK is a low-frequency clock with a typical frequency of 32.768 kHz, and is often used in low-power applications where high accuracy is not required. The clock source and count mode are set using the TB1CTL register, while the interrupt enable is set using the TB1CCTL0 register.

- __interrupt void Port2_ISR(void)

This code defines an interrupt service routine (ISR) for the button connected to Port 2, Bit 3. The ISR is triggered when the button is pressed or released. The purpose of this ISR is to measure how long the button is pressed.

When the ISR is triggered, it checks whether the interrupt was triggered by a rising edge or a falling edge. If it was triggered by a rising edge (i.e., the button was pressed), it starts Timer B0 to measure how long the button is pressed. The mode of Timer B0 is set to continuous-up mode (MC_2) to measure the time interval. It also changes the edge sensitivity of the button to detect a falling edge.

If the interrupt was triggered by a falling edge (i.e., the button was released), it stops Timer B0 and records the button press time. The value of Timer B0 is stored in the variable button_press_time which is then used to set the max count for Timer B1. Timer B0 is then cleared for the next button press, and the edge sensitivity is changed back to look for the next rising edge.

The code also toggles the state of the green LED connected to P6.6 to provide a visual indication of whether the button press is being detected. Finally, the interrupt flag for P2.3 is cleared.

- __interrupt void Port4_ISR(void)

This code defines an interrupt service routine (ISR) that is triggered when an interrupt is detected on Port 4. Specifically, the ISR is triggered when a rising edge is detected on pin P4.1, which is configured as an input with an external pull-up resistor.

When the ISR is triggered, the first thing it does is reset the blink period variable to its initial value. This variable is used to set the frequency of the blinking LED, so resetting it to its initial value will cause the LED to blink at its original frequency.

The code also resets Timer B0 to its initial state, just in case it was still running from a previous button press. This is done by stopping Timer B0 (clearing the MC0 and MC1 bits) and then clearing the timer (using TBCLR).

Finally, the interrupt flag for pin P4.1 is cleared, which acknowledges the interrupt and allows the system to respond to further interrupts on this pin.

- __interrupt void Timer1_B0_ISR(void)

This is an interrupt service routine for Timer B1. It is triggered when the timer counter reaches its maximum count value, which is set by the value of TB1CCR0 in the timer initialization function.

In this particular ISR, the P1OUT register is being XORed with BIT0 to toggle the state of the P1.0 LED. This creates a blinking effect, where the LED turns on and off periodically based on the value of TB1CCR0. The period of the blinking is determined by the value of TB1CCR0, which is set to the button press time when the button is pressed, and is reset to its initial value when the reset button is pressed.



