# Summary of Code
This program allows the user to control the duty cycle of an LED blinking at 1 kHz. By pressing a button, the duty cycle increases by ten percent. At 100 percent, the duty cycle rolls over. As the duty cycl eof the signal increases, so does the brightness of the LED.

# Functionality of Code
Software PWM uses a timer, 2 capture/compare interrupts, and a button interrupt. The timer is set to use the SMCLK, which is roughly 1 MHz. In order to replicate a frequency of 1 kHz, the capture/compare register CCR0 is set to 1000. This allows SMCLK to act as a 1 kHZ frequency, as SMCLK can count up to the number 1000 1000 times, or hertz, a second. We control the duty cycle using an interrupt on CCR1. To make a duty cycle of 50 percent, we simply set CCR1 to 500. With the LED initialized as on, the interrupt at CCR1 turns the LED off. At CCR0, the LED is turned back on. Since 500 is half of 1000, the LED is on for half of the period, hence making a 50 percent duty cycle. This duty cycle can be increased by increaseing CCR1 by 10 percent of the period, in this case 100. We increase the duty cycle using a button interrupt. After the button is debounced, the CCR1 is increased by 100, unless it is already at 100 percent, in which case the duty cycle is reset to zero percent.

# Troubleshooting
When pressing the button you may find that the blinking LED turns off. Congradulations! You've caused interrupt to occur in the short period of time the LED in the off portion of its duty cycle. The led will resume blinking when the button is released.
