/*
 * boardMacros.h
 *
 *  Created on: Sep 29, 2018
 *      Author: kohar
 */

#ifndef BOARDMACROS_H_
#define BOARDMACROS_H_

#endif /* BOARDMACROS_H_ */


#ifdef __MSP430G2553__
    //LED1
    #define LED1        BIT0
    #define L1DIR       P1DIR
    #define L1OUT       P1OUT

    //LED2
    #define LED2        BIT6
    #define L2DIR       P1DIR
    #define L2OUT       P1OUT

    //BUTTON1
    #define BUTTON1     BIT3
    #define B1DIR       P1DIR
    #define B1IN        P1IN
    #define B1OUT       P1OUT
    #define B1REN       P1REN
    #define B1IE        P1IE
    #define B1IES       P1IES
    #define B1IFG       P1IFG
#endif

#ifdef __MSP430F5529__
    //LED1
    #define LED1        BIT0
    #define L1DIR       P1DIR
    #define L1OUT       P1OUT

    //LED2
    #define LED2        BIT7
    #define L2DIR       P4DIR
    #define L2OUT       P4OUT

    //BUTTON1
    #define BUTTON1     BIT1
    #define B1DIR       P1DIR
    #define B1IN        P1IN
    #define B1OUT       P1OUT
    #define B1REN       P1REN
    #define B1IE        P1IE
    #define B1IES       P1IES
    #define B1IFG       P1IFG

    //BUTTON2
    #define BUTTON2     BIT1
    #define B2DIR       P2DIR
    #define B2IN        P2IN
    #define B2OUT       P2OUT
    #define B2REN       P2REN
    #define B2IE        P2IE
    #define B2IES       P2IES
    #define B2IFG       P2IFG
#endif

#ifdef __MSP430FR2311__
    //LED1
    #define LED1        BIT0
    #define L1DIR       P1DIR
    #define L1OUT       P1OUT

    //LED2
    #define LED2        BIT0
    #define L2DIR       P2DIR
    #define L2OUT       P2OUT

    //BUTTON1
    #define BUTTON1     BIT1
    #define B1DIR       P1DIR
    #define B1IN        P1IN
    #define B1OUT       P1OUT
    #define B1REN       P1REN
    #define B1IE        P1IE
    #define B1IES       P1IES
    #define B1IFG       P1IFG
#endif

#ifdef __MSP432P401R__
    //LED1
    #define LED1        BIT0
    #define L1DIR       P1DIR
    #define L1OUT       P1OUT

    //BUTTON1
    #define BUTTON1     BIT1
    #define B1DIR       P1DIR
    #define B1IN        P1IN
    #define B1OUT       P1OUT
    #define B1REN       P1REN
    #define B1IE        P1IE
    #define B1IES       P1IES
    #define B1IFG       P1IFG

    //BUTTON2
    #define BUTTON2     BIT4
    #define B2DIR       P1DIR
    #define B2IN        P1IN
    #define B2OUT       P1OUT
    #define B2REN       P1REN
    #define B2IE        P1IE
    #define B2IES       P1IES
    #define B2IFG       P1IFG
#endif

