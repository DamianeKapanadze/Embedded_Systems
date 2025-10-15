# PWM Signal Output using 16-bit Timer1 on 32U4

## Objective

The goal of this hands-on assignment is to create a PWM signal output using the 16-bit Timer1 on the 32U4 processor. We want to set up a PWM output at a frequency of **1 kHz** on either pin **OC1A** or **OC1B**. Since this is a 16-bit timer, some of the register settings differ from the example we did in class.

### Steps

1. Review the Timer1 registers starting on page 131 of the datasheet.
2. Set the relevant pins as outputs.
3. Configure **TCCR1A**, **TCCR1B**, and **TCCR1C** for **Fast PWM** mode:
    - Decide on **TOP** value, clock prescaler, etc.
    - Optimize tick resolution time.
4. Set up **OCR1A** / **OCR1B** appropriately.  
    > **Note:** These are 16-bit registers (high and low bytes). The initial PWM duty cycle should be **50%**.
5. Write the `loop` function that updates the duty cycle, counting from 0% to 100%, then back down to 0%, repeating continuously.
    - Delay between duty cycle changes should be **100 ms**.
6. Implement a `#define` to allow developers to change the **max duty cycle** anywhere between 0% and 100%.
7. Use the **Digilent Discovery Waveform Application** in **Oscilloscope Mode** to capture your PWM signal and attach the screenshot to the assignment.
    - Verify your design by observing measurements such as **DutyCycle** and **Average** using the **Add Measure** feature.

---

# Solution

For my implementation:

- I used **OCR1A** as the **TOP** value.
- I used **OCR1B** as the **compare match (duty cycle)** register.

### Frequency Calculation

To generate a **1 kHz PWM signal**, the formula is:

\[
\text{TOP} = \frac{\text{Clock Frequency}}{\text{Prescaler} \times \text{Target Frequency}} - 1
\]

Where:

| Parameter          | Value     |
|--------------------|-----------|
| Clock frequency    | 8 MHz     |
| Prescaler         | 1         |
| Target frequency  | 1 kHz     |
| Resulting TOP (OCR1A) | 7999      |

This configuration yields a **PWM frequency of 1 kHz**.

---

As seen in the picture below, the frequency is approximately 1 kHz. When the duty cycle is close to 50%, the output voltage is roughly half of 3.3 V, around **1.6 V**.

![Timer Image](HW2_Timers/20251015_154613.jpg)
