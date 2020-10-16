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

const int latchPin = 7;
const int dataPin = 8;
const int clockPin = 9;
//shiftOut(dataPin, clockPin, MSBFIRST, 64);

const int LEDRed = 14;
const int LEDGreen = 16;
const int LEDBlue = 10;

const int waterPump = 15; 

int lastColorHit = 0;


int wateringTime = 5000; // In milliseconds 
int period = 20000 - wateringTime; // In milliseconds
int sensorCheckTime = 5000; // In milliseconds 
int sensorCheckForWatering = period/sensorCheckTime; // 
int waterCheckCount = 0;


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
  
}

void loop() {

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 102);
  digitalWrite(latchPin, HIGH);
  delay(1000);

//  if(digitalRead(buttonDown) == HIGH){
//    delay(100);
//    if(digitalRead(buttonDown) == LOW){
//      // Logic when the "down" button is pressed
//      
//      
//    }
//  } else if(digitalRead(buttonUp) == HIGH){
//    delay(100);
//    if(digitalRead(buttonUp) == LOW){
//      // Logic when the "up" button is pressed
//      
//      
//    }
//  } 

//  actionCycle();
//  delay(sensorCheckTime);

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
