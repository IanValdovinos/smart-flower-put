


const int sensor1 = 2;     
const int sensor2 = 3;
const int sensor3 = 4;

const int redLed =  7;      
const int greenLed = 8;
const int blueLed = 9;

// variables will change:
int sensor1State = 0;         // variable for reading the magnetic sensor 1 status
int sensor2State = 0;
int sensor3State = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  // initialize the sensor pin as an input:
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);
}

void loop() {
  sensor1State = digitalRead(sensor1);
  sensor2State = digitalRead(sensor2);
  sensor3State = digitalRead(sensor3);

  if (sensor1State == LOW) {
    digitalWrite(redLed, HIGH); 
  } else {
    digitalWrite(redLed, LOW); 
  }

  if (sensor2State == LOW) {
    digitalWrite(blueLed, HIGH); 
  } else {
    digitalWrite(blueLed, LOW); 
  }

  if (sensor3State == LOW) {
    digitalWrite(greenLed, HIGH); 
  } else {
    digitalWrite(greenLed, LOW); 
  }

  
  
}
