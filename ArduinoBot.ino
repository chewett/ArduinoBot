#define DHT_ENABLED 1
#define GAS_ENABLED 1
#define SERVO_ENABLED 0
#define PING_ENABLED 1
#define LED_MATRIX_ENABLED 1
#define MOTION_SENSOR 1
#define SOUND_SENSOR_ARRAY 1

#if SERVO_ENABLED
#include <Servo.h>

Servo servo1;
int redPin = 4;
int bluePin = 7;
int greenPin = 8;
#endif

#if PING_ENABLED
#include <NewPing.h>
#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     9  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int pingPower = 10;

int getPingCm() {
  delay(200);
  int distance = 0;
  unsigned int uS = sonar.ping();
  //uS = sonar.ping(); //Do ping twice as the first time after powering off/on is sometimes 0
  distance = uS / US_ROUNDTRIP_CM;
  if(false && distance == 0) { 
    digitalWrite(pingPower, LOW);
    delay(2000);
    digitalWrite(pingPower, HIGH);
  }
  

  return distance;
}

int getPingCmBasic() {
  int distance = 0;
   unsigned int uS = sonar.ping();
  distance = uS / US_ROUNDTRIP_CM;

  return distance;
}

#endif

#if DHT_ENABLED
#include "DHT.h"
#define DHTPIN 7     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
#endif

#if LED_MATRIX_ENABLED
#include "LedControl.h"

LedControl lc=LedControl(12,11,10,2);
#endif

#if MOTION_SENSOR
#define MOTION_SENSOR_PIN 1
#endif

#if SOUND_SENSOR_ARRAY
#define SOUND_SENSOR_PIN1 13
#define SOUND_SENSOR_PIN2 14
#define SOUND_SENSOR_PIN3 15
#endif

int sensorValue;

void setup() {
  randomSeed(analogRead(0));
 Serial.begin(115200);

 #if DHT_ENABLED
  dht.begin();
 #endif

#if PING_ENABLED
  pinMode(pingPower, OUTPUT);
  digitalWrite(pingPower, HIGH);
#endif

#if LED_MATRIX_ENABLED
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
    lc.shutdown(1,false);
  lc.setIntensity(1,1);
  lc.clearDisplay(1);
#endif
  
  /*
   * 
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  servo1.attach(5);
  Serial.begin(115200);*/
}



/*
void setColor(int pin) {
  digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(greenPin, LOW);
  if(pin == redPin || pin == bluePin || pin == greenPin) {
     digitalWrite(pin, HIGH);
  }else{
    delay(100);
  }
  
}*/

void loop() {

#if LED_MATRIX_ENABLED
long randNumber;

for(int set = 0; set < 2; set++) {
  for(int i = 0; i < 8; i++) {
    randNumber = random(0, 255);
    lc.setRow(set,i, (byte)randNumber);
  }
}
 delay(1000);
#endif


Serial.print("{");
#if DHT_ENABLED
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();

 // Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
}

sensorValue = analogRead(0);       // read analog input pin 0

Serial.print("\"humidity\": \"");
Serial.print(h);
Serial.print("\", \"temp\": \"");
Serial.print(t);
Serial.print("\", \"toxicity\": \"");
Serial.print(sensorValue);
Serial.print("\",");

#endif

#if MOTION_SENSOR
sensorValue = analogRead(MOTION_SENSOR_PIN);
Serial.print("\"motion\": \"");
Serial.print(sensorValue);
Serial.print("\",");
#endif

#if SOUND_SENSOR_ARRAY
sensorValue = analogRead(SOUND_SENSOR_PIN1);
Serial.print("\"sound1\": \"");
Serial.print(sensorValue);
Serial.print("\",");
sensorValue = analogRead(SOUND_SENSOR_PIN2);
Serial.print("\"sound2\": \"");
Serial.print(sensorValue);
Serial.print("\",");
sensorValue = analogRead(SOUND_SENSOR_PIN3);
Serial.print("\"sound3\": \"");
Serial.print(sensorValue);
Serial.print("\",");
#endif


#if PING_ENABLED
Serial.print("\"distance\": \"");
Serial.print(getPingCmBasic());
Serial.print("\",");
#endif  
  
Serial.println("\"sending\":\"true\"}");

  
  /*
  while (Serial.available() == 0);
  int val = Serial.parseInt();

  setColor(val);

  /*
  Serial.println(val);
  servo1.write(val);
  delay(500);
  */
 
}

