const int sensor1 = 2;
const int sensor2 = 3;
const int sensor3 = 4;
int sensor1State = 0;         
int sensor2State = 0;
int sensor3State = 0;

const int LEDRed = 14;
const int LEDGreen = 16;
const int LEDBlue = 10;

const int waterPump = 8; 

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

  pinMode(LEDRed, OUTPUT);
  pinMode(LEDBlue, OUTPUT);
  pinMode(LEDGreen, OUTPUT);

  pinMode(waterPump, OUTPUT);
  
}

void loop() {

  actionCycle();
  delay(sensorCheckTime);

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
  } 

  if (sensor2State == LOW) {
    updateColor(lastColorHit, LEDBlue);
    lastColorHit = LEDBlue;
  } 

  if (sensor3State == LOW) {
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
