int latchPin = 7;
int dataPin = 8;
int clockPin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 63);
  digitalWrite(latchPin, HIGH);
  delay(500);

}
