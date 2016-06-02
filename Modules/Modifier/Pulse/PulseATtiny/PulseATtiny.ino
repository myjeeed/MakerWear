/*
**  PulseATtiny.ino
**  MakerWear Pulse Module's ATtiny Program.
**
**  Pulses 5V in a frequency proportional to voltage input (higher voltage
**  equals higher pulse rate)
**
**
**  ATtiny85 Pin Configurations:  
**
**  Pin 1 (Reset): N/U                   Pin 8 (PWR):         5V
**  Pin 2 (D3/A3): Module Input          Pin 7 (D2/A1/SCK):   N/U
**  Pin 3 (D4/A2): N/U                   Pin 6 (D1/PWM/MISO): Module Output
**  Pin 4 (GND):   GND                   Pin 5 (D0/PWM/MOSI): N/U
**
**
**  Created on 8/10/15.
**  By Majeed Kazemitabaar
**  Modified on 8/25/15.
**  By Majeed Kazemitabaar
**
**  MakerWear Link:
**  Github Link:      github.com/myjeeed/MakerWear
**
*/

#include <FilteredAnalogInput.h>

int input_pin = 3;                           //Pin 2 on ATtiny
int output_pin = 1;                          //Pin 6 on ATtiny
int filter_size = 2;                        //Noise reduction filter size
int min_period = 25;
int max_period = 1000;

FilteredAnalogInput input(input_pin, filter_size);

unsigned long interval = 1000;
unsigned long previousMillis = 0;

int ledState = LOW; 

void setup() 
{
  pinMode(output_pin, OUTPUT);
}

void loop()
{
  int input_val = map(input.filteredAnalogRead(AVERAGE), 50, 975, 0, 1023);
  
  if(input_val < 0)
    input_val = 0;
  else if(input_val > 1023)
    input_val = 1023;

  interval = map(input_val, 0, 1023, max_period, min_period);
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
      analogWrite(output_pin, input_val/4);
    } else {
      ledState = LOW;
      analogWrite(output_pin, 0);
    }
  }
}