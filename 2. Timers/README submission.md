##Part 2 - Timers

- TODO 1: Initalizing the LED

The first line, P1OUT &= ~BIT0;, clears the output latch for Pin P1.0 to ensure a defined power-on state. The output latch is used to hold the output value of a pin when the pin is configured as an output. By clearing the output latch, we ensure that the LED starts in a known state.

The second line, P1DIR |= BIT0;, sets the direction register for Pin P1.0 to output. The direction register is used to control the direction of a pin, either as an input or an output. By setting the direction register to output, we configure Pin P1.0 as an output, which will allow us to control the LED.

Overall, this code initializes Pin P1.0 as an output for the LED and ensures a defined power-on state for the pin.

- TODO 2: Initializing the button

This portion of the code is initializing Button 2.3 as an input on Pin P2.3 and configuring it to trigger an interrupt on a rising edge (when the button is released).

The first line, P2OUT |= BIT3;, configures Pin P2.3 as a pulled-up input. When a pin is configured as an input, we can use an external pull-up or pull-down resistor to define its state when it is not being driven by an external source. In this case, we are configuring Pin P2.3 with a pull-up resistor, which will cause the pin to read as a logic high when the button is not pressed.

The second line, P2REN |= BIT3;, enables the pull-up resistor for Pin P2.3 by enabling the pull-up register for the pin.

The third line, P2IES &= ~BIT3;, configures the interrupt trigger for Pin P2.3 to be a rising edge (when the button is released). By setting the corresponding bit in the Interrupt Edge Select Register (IES) to 0, we configure the interrupt to trigger on a low-to-high transition.

The fourth line, P2IE |= BIT3;, enables the interrupt for Pin P2.3 by setting the corresponding bit in the Interrupt Enable Register (IE). When the button is released, the interrupt service routine (ISR) will be called to handle the interrupt.

Overall, this code initializes Pin P2.3 as an input for the button, configures it with a pull-up resistor, and enables the interrupt on a rising edge trigger.

- TODO 3: Initializing the timer

This portion of the code initializes Timer B1 in Continuous Mode using ACLK as the source clock with interrupts turned on.

The first line, TB1CCR0 = 50000;, sets the maximum count for Timer B1. When the timer counts up to this value, it will generate an interrupt.

The second line, TB1CTL = TBSSEL_1 | MC_2;, configures Timer B1 to use ACLK as the source clock and to run in continuous mode. ACLK is an external oscillator or an internal oscillator that runs at a lower frequency than the main system clock, which allows for more power-efficient operation. Continuous mode means that the timer will continuously count up from 0 to the maximum count value set by TB1CCR0, and then start over.

The third line, TB1CCTL0 = CCIE;, enables interrupts for Timer B1. The CCIE bit in the Timer B1 Capture/Compare Control Register 0 (TB1CCTL0) enables interrupts for Timer B1 when the timer count reaches the value set in TB1CCR0.

Overall, this code initializes Timer B1 to generate interrupts based on a continuous count up from 0 to the maximum count value, using ACLK as the source clock. This allows for precise timing control in the system.

- TODO 4: GPIO Interrupt Service Routine Flag

This part of the code is related to servicing the GPIO interrupt for Pin P2.3. When a GPIO interrupt occurs, the corresponding interrupt flag is set to indicate that an interrupt event has occurred. It is important to clear the interrupt flag in the interrupt service routine, otherwise the system may enter an infinite loop of interrupts.

The line P2IFG &= ~BIT3; clears the interrupt flag for Pin P2.3. The &= operator performs a bitwise AND operation between the current value of P2IFG and the complement of BIT3. This clears the bit corresponding to Pin P2.3 in P2IFG. By clearing the interrupt flag, the system acknowledges that the interrupt event has been serviced, and can now return to its normal operation.

- TODO 5: GPIO Interrupt Service Routine actions

This part of the code is related to changing the blinking speed of the LED when the button is pressed. The variable blink_speed is incremented by 1 every time the button interrupt service routine is executed, which means that the blink_speed variable acts as a counter for the number of times the button has been pressed.

- TODO 6: Timer Service Routine actions

This part of the code is the Timer B1 interrupt service routine, which is executed when the Timer B1 interrupt is triggered. The first line toggles the state of Pin P1.0, which controls the LED.

The if-else statements adjust the blink speed based on the current value of the blink_speed variable. If blink_speed is 1, it means the button has been pressed once, and the LED should blink slowly, so the TB1CCR0 value is increased by 40000. If blink_speed is 2, the LED should blink at medium speed, so TB1CCR0 is increased by 2000. If blink_speed is 3, the LED should blink quickly, so TB1CCR0 is increased by 100. Finally, if blink_speed is 3, the blink_speed counter is reset to 0. By changing the value of TB1CCR0, the Timer B1 interrupt frequency is adjusted, which in turn adjusts the LED blink speed.

- Other additions:

A global variable blink_speed is initialized before the main function.