int led = 13;
int sw = 2;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(sw) == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}