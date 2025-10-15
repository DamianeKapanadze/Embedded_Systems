#include <Arduino.h>
// 16 bit timer - Timer1
// use Fast PWM mode
// 1kHz frequency
#define DUTY_CYCLE 50 // in percent
bool increasing = true;
uint16_t duty = 0;
void setup() {
  Serial.begin(115200);
  // configure timer1
  // Set OC1B as output, PB6
  DDRB = 0;
  DDRB |= (1 << PB6);
  TCCR1B = 0;
  TCCR1A = 0;

  TCCR1A |= (1 << COM1B1); // Non-inverting mode on OC1B
  TCCR1A |= (1 << WGM10) | (1 << WGM11); // Fast PWM mode using OCR1A as TOP
  
  TCCR1B |= (1 << WGM13) | (1 << WGM12); 
  TCCR1B |=  (1 << CS10); // Prescaler 1
  OCR1A = 7999; // TOP value for 1kHz at 8MHz with prescaler 1
  OCR1B = 0; // 50% duty cycle

}

void loop() {
  // if increasing, increase duty cycle by 64 (to have less steps and be faster)
  // increase till we reach the max duty cycle
  // else decrease duty cycle by 64
  if(increasing){
    duty += 64;
    if(duty >= (uint16_t)(OCR1A-64)*(DUTY_CYCLE/100.0)){
      increasing = false;
    }
  } else {
    duty -= 64;
    if(duty <= 0){
      increasing = true;
    }
  }
  OCR1B = duty;
  delay(100);
}
