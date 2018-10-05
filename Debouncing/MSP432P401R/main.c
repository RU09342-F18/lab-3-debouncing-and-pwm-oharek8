#include "msp.h"
#include "boardMacros.h"

/**
 * main.c
 */
/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP432 CODE EXAMPLE DISCLAIMER
 *
 * MSP432 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see http://www.ti.com/tool/mspdriverlib for an API functional
 * library & https://dev.ti.com/pinmux/ for a GUI approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP432P401 Demo - Software Port Interrupt Service on P1.1 from LPM4
//
//  Description: MSP432 device is configured to enter LPM4 mode with GPIOs
//  properly terminated. P1.1 is configured as an input. Pressing the button
//  connect to P1.1 results in device waking up and servicing the Port1 ISR.
//  LPM3 current can be measured when P1.0 is output low (e.g. LED off).
//
//  ACLK = 32kHz, MCLK = SMCLK = default DCO
//
//
//               MSP432P401x
//            -----------------
//        /|\|                 |
//         | |                 |
//         --|RST              |
//     /|\   |                 |
//      --o--|P1.1         P1.0|-->LED
//     \|/
//
//   Dung Dang
//   Texas Instruments Inc.
//   Oct 2016 (updated) | November 2013 (created)
//   Built with CCSv6.1, IAR, Keil, GCC
//******************************************************************************
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    // LED Setup
    L1DIR |= LED1;
    L1OUT &= ~LED1;

    // Button Setup
    B1DIR &= ~BUTTON1;                              // Sets button to input
    B1IE |= BUTTON1;                                // Enables interrupt on button
    B1IES |= BUTTON1;                               // Detect falling edge (push)
    B1REN &= ~BUTTON1;                              // Disable pullup/down resistor
    B1IFG &= ~BUTTON1;                              // Clear Interrupt Flag

    // Timer A Setup
    TA0CCTL0 |= CCIE;                                // Enable CCR0 interrupt

    TA0CCR0 = 1000;                                  // Set frequency to ~10 Hz

    // Configure Port J
    PJ->DIR |= (BIT0| BIT1 | BIT2 | BIT3);
    PJ->OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);

    // Enable PCM rude mode, which allows to device to enter LPM3 without waiting for peripherals
    PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;

    // Enable PCM rude mode, which allows to device to enter LPM3 without waiting for peripherals
    PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;

    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);

    // Setting the sleep deep bit
    SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk);

    // Do not wake up on exit from ISR
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;

    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();

    // Enable global interrupt
    __enable_irq();
    while (1)
        {
            __sleep();

            __no_operation();                   // For debugger
        }
}



void TA0_0_IRQHandler(void)
{
    TA0CCTL0 = 0x00; // Turn off Interrupt Flag
    B1IE |= BUTTON1;                    // Re-enable button interrupt
    P1->IFG &= ~BIT1;                  // Clear Flag
    TA0CCTL0 &= ~CCIE;                                // Enable CCR0 interrupt

    TA0CTL = TIMER_A_CTL_MC__STOP | TACLR;              // Set Timer A to up mode and clear TA register
    TA0CTL &= ~MC_3;

}


void PORT1_IRQHandler(void)
{
    L1OUT ^= LED1;                      // Toggle LED1

    B1IE &= ~BUTTON1;                   // Disable Interrupt to prevent bounce
    P1->IFG &= ~BIT1;                  // Clear Flag

    TA0CCTL0 |= CCIE;                                // Enable CCR0 interrupt

    TA0CTL = TIMER_A_CTL_SSEL__SMCLK + MC_1;     // Set Timer A to up mode
}
