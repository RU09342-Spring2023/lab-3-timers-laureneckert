#Part 1 Code

- TODO 1

For the first To Do item, I added 'P2IES & BIT3' to the if statement.

Basically, P2IES is the Interrupt Edge Select register for Port 2. When a pin on Port 2 is configured to generate interrupts, this register determines whether the interrupt should be triggered on a rising or falling edge of the pin.

If P2IES has a 0 bit in a particular position, then a rising edge on the corresponding Port 2 pin will trigger an interrupt. Conversely, if P2IES has a 1 bit in a particular position, then a falling edge on the corresponding Port 2 pin will trigger an interrupt.

In the code, P2IES & BIT3 is a bitwise AND operation between P2IES and BIT3. BIT3 is a bit mask that corresponds to the third bit position, which is the position for Pin 2.3. If P2IES & BIT3 is non-zero, then the third bit in P2IES is set to 1, which means the interrupt is set to trigger on a falling edge of Pin 2.3.

So, if (P2IES & BIT3) checks if the interrupt was triggered off a rising edge by checking if the third bit of P2IES is not set, which means that the interrupt is set to trigger on a rising edge.

- TODO 2

For this To Do item, I added P2IES &= ~BIT3; to change the edge to a falling edge.

In order to change the interrupt edge for a specific pin on Port 2, you need to modify the corresponding bit in the Interrupt Edge Select register (P2IES).

In the code, P2IES &= ~BIT3 is a bitwise AND operation between P2IES and the bitwise complement of BIT3. BIT3 is a bit mask that corresponds to the third bit position, which is the position for Pin 2.3. The bitwise complement of BIT3 is all 1s except for the third bit position, which is 0. Therefore, ~BIT3 is equal to 0xFFFF_FF7F in hexadecimal representation.

The &= operator is a bitwise AND assignment operator, which performs a bitwise AND between P2IES and ~BIT3, and then stores the result back into P2IES. This operation sets the third bit of P2IES to 0, which means that the interrupt is set to trigger on a falling edge of Pin 2.3.

In summary, P2IES &= ~BIT3 changes the edge to a falling edge by setting the corresponding bit in the Interrupt Edge Select register to 0.

- TODO 3

For the third To Do item, I added P2IES != BIT3 to the else if statement.

The condition P2IES != BIT3 in the else if statement of the interrupt service routine checks if the interrupt was triggered by a falling edge on Pin 2.3.

P2IES is a register that controls the interrupt edge for each pin in Port 2, where a bit value of 1 corresponds to a rising edge and a bit value of 0 corresponds to a falling edge. BIT3 is a bit mask for Pin 2.3, which has a value of 1 in the third bit position.

If P2IES is not equal to BIT3, it means that the interrupt was triggered by a falling edge on Pin 2.3. This is because P2IES has been set to 0 by the previous if statement to trigger on a falling edge when the button is released. Therefore, if P2IES != BIT3, the else if statement is executed, and the LED color is set to 1 to turn on the red LED, and P2IES is set back to BIT3 to trigger on a rising edge the next time the button is pressed.

In summary, P2IES != BIT3 checks if the interrupt was triggered by a falling edge on Pin 2.3, and executes the corresponding code in the else if statement.

- TODO 4

For the last To Do item, I added P2IES |= BIT3; to change the edge sensitivity back to looking for the next rising edge.

In the else if statement of the interrupt service routine, P2IES |= BIT3; sets bit 3 of the P2IES register to 1, which sets the edge sensitivity of the interrupt to a rising edge.

Recall that in the gpioInit function, the edge sensitivity of the interrupt was set to a falling edge with the line P2IES &= ~BIT3;. In the if statement of the interrupt service routine, when the interrupt is triggered by a rising edge, the edge sensitivity is changed to a falling edge with P2IES &= ~BIT3; to detect the next falling edge.

Similarly, in the else if statement, when the interrupt is triggered by a falling edge, P2IES |= BIT3; is used to set the edge sensitivity to a rising edge, so that the next rising edge can be detected.

- Other additions

I also added P6OUT &= ~BIT6; in the else if statement to turn off the green LED and P1OUT &= ~BIT0; to turn off the red LED at the end of the interrupt service routine. This is so that after the interrupts the corresponding light will not be stuck in the on setting after it is done blinking.