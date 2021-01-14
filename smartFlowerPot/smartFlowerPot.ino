#include <Metro.h>

const int sensor1 = 2;
const int sensor2 = 3;
const int sensor3 = 4;
int sensor1State = 0;         
int sensor2State = 0;
int sensor3State = 0;

const int buttonDown = 5;
const int buttonUp = 6;
int buttonDownState = 0;
int buttonUpState = 0;

// Pins used to control the display by SN74HC595N
const int latchPin = 7;
const int dataPin = 8;
const int clockPin = 9;
//shiftOut(dataPin, clockPin, MSBFIRST, 64);

const int numberDisplayList[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 103}; // Common cathode display. From 0 to 9
int dayCount = 1;

const int LEDRed = 14;
const int LEDGreen = 16;
const int LEDBlue = 10;

int lastColorHit = 0;

const int waterPump = 15; 

int wateringTime = 5000; // How long the plant will be watered. In milliseconds 
int waitTime = 10000; // How long it will take until the plant is watered again. In milliseconds
int period = waitTime + wateringTime; 
int sensorCheckTime = 5000; // How often the water level sensors are checked. In milliseconds 
int sensorCheckForWatering = period/sensorCheckTime; 
int waterCheckCount = 0;

// Variable setup for Metro library. Metro is used for running code at the same time
Metro checkButtonsMetro = Metro(50);
Metro sensorCheckMetro = Metro(sensorCheckTime);


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

  pinMode(waterPump, OUTPUT);
  
  updateDisplay(numberDisplayList[dayCount]);
}

void loop() {

  // checkButtons();

  // actionCycle();
  // delay(sensorCheckTime);

  if(checkButtonsMetro.check()){
    checkButtons();
  }

  if(sensorCheckMetro.check()){
    actionCycle();
  }

}

// Function to check the buttons and perform a task
void checkButtons(){
  if(digitalRead(buttonDown) == HIGH){
    delay(100);
    if(digitalRead(buttonDown) == LOW){
      // Logic when the "down" button is pressed
      if(dayCount > 1) {
        dayCount--;
        updateDisplay(numberDisplayList[dayCount]);
      }
    }
  } else if(digitalRead(buttonUp) == HIGH){
    delay(100);
    if(digitalRead(buttonUp) == LOW){
      // Logic when the "up" button is pressed
      if(dayCount < 9) {
        dayCount++;
        updateDisplay(numberDisplayList[dayCount]);
      };
    }
  }
}

void updateDisplay(int number) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);
  digitalWrite(latchPin, HIGH);
}

void actionCycle() {
  waterCheckCount++;
  
  if (waterCheckCount == sensorCheckForWatering){
    pumpWater();
    waterCheckCount = 0;
  }
  
  checkSensorStatus();
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

void pumpWater() {
  digitalWrite(waterPump, HIGH);
  delay(wateringTime);
  digitalWrite(waterPump, LOW);
}
