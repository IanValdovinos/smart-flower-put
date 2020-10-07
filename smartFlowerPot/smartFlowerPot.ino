const int sensor1 = 2;
const int sensor2 = 3;
const int sensor3 = 4;

const int LED1 = 14;
const int LED2 = 16;
const int LED3 = 10;

const int waterPump = 8; 

void setup() {
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(sensor3, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(waterPump, OUTPUT);
  
}

void loop() {
  

}
