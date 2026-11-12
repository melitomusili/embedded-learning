int led[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 8; i++)       // go through the LEDs one by one
  {
    digitalWrite(led[i], HIGH);     // turn this one ON
    delay(200);                     // keep it on for a moment
    digitalWrite(led[i], LOW);      // turn it OFF before moving on
  }
}