#include <Servo.h>

Servo servo1;
int redPin = 4;
int bluePin = 7;
int greenPin = 8;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  servo1.attach(5);
  Serial.begin(9600);
}

void setColor(int pin) {
  digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(pin, HIGH);
}

void loop() {
  while (Serial.available() == 0);
  int val = Serial.parseInt();

  setColor(val);

  /*
  Serial.println(val);
  servo1.write(val);
  delay(500);
  */
 
}

