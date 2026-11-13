void setup()
{
  pinMode(4, INPUT_PULLUP);   // button: built-in pull-up resistor
  pinMode(2, OUTPUT);         // LED
}

void loop()
{
  if (digitalRead(4) == LOW)  // LOW = pressed
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }
}