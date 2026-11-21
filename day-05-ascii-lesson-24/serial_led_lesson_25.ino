const int led = 13;

void setup() {
  Serial.begin(9600);
  Serial.println("hello world");
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if (Serial.available())   // data has arrived in the serial buffer
  {
    int rxd = Serial.read();

    if (rxd == 'A')
    {
      digitalWrite(led, HIGH);
    }
    else if (rxd == 'B')
    {
      digitalWrite(led, LOW);
    }
  }
}