#include <msp430.h> 
#include <boardMacros.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    // LED Setup
    L1DIR |= LED1;
    L1OUT &= ~LED1;

    // Button Setup
    B1DIR &= ~BUTTON1;                      // Sets button to input
    B1IE |= BUTTON1;                        // Enables interrupt on button
    B1IES |= BUTTON1;                       // Detect falling edge (push)
    B1REN |= BUTTON1;                       // Enable pullup/down resistor
    B1OUT |= BUTTON1;                       // Set resistor to pull-up
    B1IFG &= ~BUTTON1;                      // Clear Interrupt Flag

    // Timer A Setup
    TA0CCTL0 = CCIE;                        // Enable CCR0 interrupt
    TA0CTL = TASSEL_1 + MC_0 + ID_3;        // Set Timer A to use aclk/8 on stop mode
    TA0CCR0 = 4000;                         // Set frequency to ~10 Hz

    __bis_SR_register(LPM0_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    B1IE |= BUTTON1;                        // Re-enable button interrupt
    B1IFG &= ~BUTTON1;                      // Clear Flag

    TA0CTL |= MC_0 + TACLR;                 // Set Timer A to stop mode and clear TA register
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)

{
    L1OUT ^= LED1;                          // Toggle LED1

    B1IE &= ~BUTTON1;                       // Disable Interrupt to prevent bounce
    B1IFG &= ~BUTTON1;                      // Clear Flag

    TA0CTL |= MC_1;                         // Set Timer A to up mode

}
