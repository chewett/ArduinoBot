#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(5);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0);
  int val = Serial.parseInt();
  
  Serial.println(val);
  servo1.write(val);
  delay(500);
 
}

