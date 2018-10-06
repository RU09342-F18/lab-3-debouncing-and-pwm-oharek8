# Summary of Code
This code is similar to the Software PWM, but rather than write to the LEDs we use the timer outputs.

# Functionality of Code
Like the Software PWM, the CCR0 and CCR1 registers are setup to make an LED intially blink with a frequency of 1 kHz with a 50 percent duty cycle. When the button is pressed, the button interrupt is disabled, CCR1 is increased by 100, and the duty cycle is increased by 10 percent. At the end of the interrupt, the interrupt on CCR2 is enabled in order to implement a debounce. This debounce ends when the timer reaches the value stored in CCR2 and the button interrupt is re-enabled. The LED is reset and set every period using the OUTMOD function of CCR1. When the timer reaches the value in CCR1 the signal is reset to zero. When the timer reaches the value in CCR0, the signal is set to 1. Which pin this signal goes to depends on the PxSELy bits. It is different fo reach pin, but typically x refers to the port and y is some constant stated in the datasheet of the particular processor. When correctly set up, the pin will recieve the blink signal.

# Troubleshooting
Sometimes when the button is pressed the LED will stop blinking. Do not worry, this has happened because an interrupt has occured during the period of time the LED is off.

# Differences in Code
The main difference between the FR2311 and the G2553 is that unlike the G2, the FR only has a Timer B module. Fortunately incorperating the Timer B module was as simple as changing an A to a B. All of the functions appear to have functioned as expected.
