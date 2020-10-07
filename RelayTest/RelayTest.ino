int myPump = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(myPump, OUTPUT);
}

void loop() {
  pumpWater();
  delay(10000);
}

void pumpWater() {
  digitalWrite(myPump, HIGH);
  delay(10000);
  digitalWrite(myPump, LOW);
}
