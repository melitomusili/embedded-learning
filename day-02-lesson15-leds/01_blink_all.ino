// The pins my 8 LEDs are plugged into
int led[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{
  // Tell the Arduino that all 8 pins send power OUT
  for (int i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

void loop()
{
  // Turn ALL 8 LEDs on
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led[i], HIGH);   // HIGH = on
  }
  delay(500);                     // wait half a second

  // Turn ALL 8 LEDs off
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(led[i], LOW);    // LOW = off
  }
  delay(500);                     // wait half a second
}