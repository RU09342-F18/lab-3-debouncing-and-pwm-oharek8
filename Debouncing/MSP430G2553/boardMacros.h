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
