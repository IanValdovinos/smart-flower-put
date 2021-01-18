#include <Metro.h>

// Water level sensors
const int sensor1 = 2;
const int sensor2 = 3;
const int sensor3 = 4;
int sensor1State = 0;         
int sensor2State = 0;
int sensor3State = 0;

// Buttons to set how often to water
const int buttonDown = 5;
const int buttonUp = 6;
int buttonDownState = 0;
int buttonUpState = 0;

// Pins used to control the display with the SN74HC595N
const int latchPin = 7;
const int dataPin = 8;
const int clockPin = 9;
//shiftOut(dataPin, clockPin, MSBFIRST, 64);

const int numberDisplayList[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 103}; // Common cathode display. From 0 to 9
int dayCount = 1;

// LED pins to indicate water level to the user
const int LEDRed = 14;
const int LEDGreen = 16;
const int LEDBlue = 10;

// Buzzer to indicate a low water level
#define buzzer A0
boolean buzzerState = false;

int lastColorHit = 0;

const int waterPump = 15; 

int wateringTime = 1000; // How long the plant will be watered. In milliseconds 
int waitTime = 1000 + wateringTime; // How long it will take until the plant is watered again. In milliseconds
int sensorCheckTime = 1000; // How often the water level sensors are checked. In milliseconds 

// Variable setup for Metro library. Metro is used for running code at the same time
Metro checkButtonsMetro = Metro(50);
Metro sensorCheckMetro = Metro(sensorCheckTime);
Metro pumpWaterMetro = Metro(waitTime);

Metro tone_wait = Metro(10000); //How often the buzzer will sound
Metro tone_mini_wait = Metro(1000); // For how long the buzzer will sound

void setup() {
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);

  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(LEDRed, OUTPUT);
  pinMode(LEDBlue, OUTPUT);
  pinMode(LEDGreen, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(waterPump, OUTPUT);
  
  updateDisplay(numberDisplayList[dayCount]);
}

void loop() {

  
  checkButtons();

  if (sensorCheckMetro.check()){
    checkSensorStatus();
  }

  if (pumpWaterMetro.check()){
    pumpWater();
  }

  if (tone_mini_wait.check()) {
    playBuzzer();
  }

}

// Function to check the buttons and perform a task
void checkButtons(){
  if(digitalRead(buttonDown) == HIGH){
    delay(50);
    if(digitalRead(buttonDown) == LOW){
      // Logic when the "down" button is pressed
      if(dayCount > 1) {
        dayCount--;
        pumpWaterMetro.interval(1000*dayCount + wateringTime);
        pumpWaterMetro.reset();
        updateDisplay(numberDisplayList[dayCount]);
      }
    }
  } else if(digitalRead(buttonUp) == HIGH){
    delay(100);
    if(digitalRead(buttonUp) == LOW){
      // Logic when the "up" button is pressed
      if(dayCount < 9) {
        dayCount++;
        pumpWaterMetro.interval(1000*dayCount + wateringTime);
        pumpWaterMetro.reset();
        updateDisplay(numberDisplayList[dayCount]);
      }
    }
  }
}

void updateDisplay(int number) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);
  digitalWrite(latchPin, HIGH);
}

void checkSensorStatus() {
  sensor1State = digitalRead(sensor1);
  sensor2State = digitalRead(sensor2);
  sensor3State = digitalRead(sensor3);

  if (sensor1State == LOW) {
    updateColor(lastColorHit, LEDRed);
    lastColorHit = LEDRed;
  } if (sensor2State == LOW) {
    updateColor(lastColorHit, LEDBlue);
    lastColorHit = LEDBlue;
  } else if (sensor3State == LOW) {
    updateColor(lastColorHit, LEDGreen);
    lastColorHit = LEDGreen;
  }
}

void updateColor(int lastColor, int newColor){
  digitalWrite(lastColor, LOW);
  digitalWrite(newColor, HIGH);
}

void playBuzzer(){
  buzzerState = !buzzerState;
  digitalWrite(buzzer, buzzerState);
}

void pumpWater() {
  digitalWrite(waterPump, HIGH);
  delay(wateringTime);
  digitalWrite(waterPump, LOW);
}
