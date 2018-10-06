# Summary of Code
This program debounces the button by temporarily disabling its interrupt capabilities, then re-enabling them after a timer has reached its max.

# Functionality of Code
Debounce uses two interrupts: a button interrupt and a CCR interrupt. When the button interrupt occurs, the interrupt on the button pin is disabled, and an LED is toggled. Before exiting the interrupt Timer A0 is set to up mode. When this timer reaches the value stored in CCR0, The button interrupt is re-enabled.
# Differences between boards
Being apart of the MSP432 family, the P401R requires an almost entirely differnt interrupt setup than the MSP430 family. For the 430s, all that is required is to enable the interrupt and use the proper interrupt function format:
```
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

}
```
The 432 on the other hand requires an interrupt enable, sleep logic, and the interrupts must be initialized with an extra statement. Not only that, but the interrupt function is structured differently.
```

void TA0_0_IRQHandler(void)
{

}
```

# Flag Complications
While the code wroks fine for the G2553, I was not able to get a working program for the P401R. For some reason, despite using multiple methods to clear the CCR0 interrupt flag, nothing could stop the program from leaving the Timer A0 interrupt. The CCIFG bit simply would not change back to zero.
