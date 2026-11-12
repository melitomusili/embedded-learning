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
  // Part A: first 4 ON, last 4 OFF
  for (int i = 0; i < 4; i++)       // LEDs number 0, 1, 2, 3
  {
    digitalWrite(led[i], HIGH);
  }
  for (int i = 4; i < 8; i++)       // LEDs number 4, 5, 6, 7
  {
    digitalWrite(led[i], LOW);
  }
  delay(700);

  // Part B: first 4 OFF, last 4 ON
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(led[i], LOW);
  }
  for (int i = 4; i < 8; i++)
  {
    digitalWrite(led[i], HIGH);
  }
  delay(700);
}