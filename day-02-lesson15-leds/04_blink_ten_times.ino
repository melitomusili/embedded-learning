int led[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);
  }

  // setup() runs only ONCE, so a blink loop placed here happens just 10 times
  for (int count = 0; count < 10; count++)
  {
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(led[i], HIGH);   // all ON
    }
    delay(500);

    for (int i = 0; i < 8; i++)
    {
      digitalWrite(led[i], LOW);    // all OFF
    }
    delay(500);
  }
}

void loop()
{
  // Empty on purpose: nothing more to do after the 10 blinks
}