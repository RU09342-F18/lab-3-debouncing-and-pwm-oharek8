#include <msp430.h>
#include <boardMacros.h>

/*
 *  Kevin O'Hare
 *  oharek8@students.rowan.edu
 */

/*
 * main.c
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // LED1 Setup
    L1DIR |= LED1;
    L1OUT |= LED1;

    // LED2 Setup
    L2DIR |= LED2;
    L2OUT &= ~LED2;

    // Button Setup
    B1DIR &= ~BUTTON1;                      // Sets button to input
    B1IE |= BUTTON1;                        // Enables interrupt on button
    B1IES |= BUTTON1;                       // Detect falling edge (push)
    B1REN |= BUTTON1;                       // Disable pullup/down resistor
    B1OUT |= BUTTON1;
    B1IFG &= ~BUTTON1;                      // Clear Interrupt Flag

    // Timer A Setup
    TA0CCTL0 = CCIE;                        // Enable CCR0 interrupt
    TA0CTL = TASSEL_2 + MC_1;               // Set Timer A to use aclk on up mode
    TA0CCR0 = 1000;                         // Set frequency to ~1 kHz, Setting CCR0 to 1001 prevents overlap with CCR1

    TA0CCTL1 = CCIE;                        // Enable CCR1 Interrupt
    TA0CCR1 = 500;
    TA0CCR2 = 800;                          // Allows debounce for 2000 cycles.

    __bis_SR_register(LPM0_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    L1OUT |= LED1;                          // Turns LED at start of period

    TA0CCTL0 &= ~CCIFG;                     // Clear Timer Flag
}

#pragma vector=TIMER0_A1_VECTOR             // Determines duty cycle
__interrupt void Timer_A1 (void)
{
    switch(TA0IV)
    {
        case 0: break;
        case 2: {
                L1OUT &= ~LED1;
                TA0CCTL1 &= ~CCIFG;         // Clear CCR1 Flag
                }
                break;
        case 4: {
                B1IE |= BUTTON1;            // Re-enable button interrupt
                B1IFG &= ~BUTTON1;          // Clear Flag
                TA0CCTL2 &= ~CCIE;
                TA0CCTL2 &= ~CCIFG;         // Clear CCR2 Flag
                TA0CTL |= TACLR;
                }
                break;
        case 10:break;
    }
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    B1IE &= ~BUTTON1;                       // Disable Interrupt to prevent bounce

    TA0CCR1 += 100;                         // Increase duty cycle by 10 percent

    if(TA0CCR1 == 1100)
    {
        TA0CCR1 = 0;                        // Set Duty Cycle to 0 percent
    }

    while((B1IN & BUTTON1) == 0)
    {
        L2OUT |= LED2;
    }

    L2OUT &= ~LED2;




    TA0CCTL2 |= CCIE;                       // Disable interrupt on CCR0 and CCR1 to prevent early interupt
    TA0CTL |= TACLR;                        // Set Timer A to continuous mode for debounce
    B1IFG &= ~BUTTON1;                      // Clear Flag
}
