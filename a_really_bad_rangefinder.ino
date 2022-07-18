#include <LiquidCrystal_I2C.h>

/*
 The MIT License (MIT)

Copyright © 2022 Kasyanov Nikolay Alexeyevich (Unbewohnte)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

bool active = false;

unsigned int trigger_pin = 5;
unsigned int echo_pin = 6;
unsigned int button_pin = 13; 

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup() {
   Serial.begin(9600);
   // turn on/off button
   pinMode(button_pin, INPUT_PULLUP);
   
   // ultrasonic sensor
   pinMode(trigger_pin, OUTPUT);
   pinMode(echo_pin, INPUT);

   // display is initialized during a mainloop
}

void loop() {
  int button_state = digitalRead(button_pin);
  if (button_state == LOW && !active) {
    active = true;
    lcd.init();
    lcd.backlight();
    lcd.clear();
    delay(250);
  } else if (button_state == LOW && active) {
    active = false;
    lcd.noBacklight();
    lcd.clear();
    delay(250);
  }

  if (active) {
    unsigned int duration, distance_cm;
    float distance_m;
    
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
  
    // initialize the sensor
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
  
    // get sensor's measurements and calculate distance
    duration = pulseIn(echo_pin, HIGH);
    distance_cm = duration / 58;
    distance_m = (float) distance_cm / 100;
  
    // print distance to the screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(distance_cm);
    lcd.print(" cm");
  
    lcd.setCursor(8, 0);
    lcd.print("(");
    lcd.print(distance_m);
    lcd.print(" m)");
    
    delay(150); 
  }
}
