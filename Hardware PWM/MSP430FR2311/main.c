#include <msp430.h>
#include <boardMacros.h>

/*
 * Kevin O'Hare
 * oharek8@students.rowan.edu
 */

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    // LED1 Setup
    L1DIR |= LED1;
    L1OUT &= ~LED1;

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
    TB1CTL = TBSSEL_2 + MC_1;               // Set Timer A1 to use aclk on up mode
    TB1CCR0 = 1000;                         // Set frequency to ~1 kHz, Setting CCR0 to 1001 prevents overlap with CCR1
    //TB1CCTL0 = CLLD_0;
    TB1CCTL1 = /*CLLD_0 +*/ OUTMOD_7;           // Enable Toggle/Set
    TB1CCR1 = 500;                          // Sets duty to 50%
    TB1CCR2 = 800;                          // Allows debounce for 2000 cycles.



    // Timer Out Setup
    P2SEL0 = 1;


    __bis_SR_register(LPM0_bits + GIE);

    return 0;
}

#pragma vector=TIMER1_B1_VECTOR             // Determines duty cycle
__interrupt void Timer_B1 (void)
{
    switch(TB1IV)
    {
        case 0: break;
        case 2: break;
        case 4: {
                B1IE |= BUTTON1;                // Re-enable button interrupt
                B1IFG &= ~BUTTON1;              // Clear Flag
                TB1CCTL2 &= ~CCIE;
                TB1CCTL2 &= ~CCIFG;                     // Clear CCR2 Flag
                TB1CTL |= TBCLR;
                }
            break;
    case 10: break;
    }


    TB1CCTL2 &= ~CCIFG;                     // Clear CCR2 Flag
    TB1CCTL1 &= ~CCIFG;                     // Clear CCR1 Flag
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    B1IE &= ~BUTTON1;                       // Disable Interrupt to prevent bounce

    TB1CCR1 += 100;                         // Increase duty cycle by 10 percent

    if(TB1CCR1 == 1100)
    {
        TB1CCR1 = 0;                        // Set Duty Cycle to 0 percent
    }

    while((B1IN & BUTTON1) == 0)
    {
        L1OUT |= LED1;
    }

    L1OUT &= ~LED1;




    TB1CCTL2 |= CCIE;                      // Disable interrupt on CCR0 and CCR1 to prevent early interupt
    TB1CTL |= TBCLR;                     // Set Timer A to continuous mode for debounce
    B1IFG &= ~BUTTON1;                      // Clear Flag
}
