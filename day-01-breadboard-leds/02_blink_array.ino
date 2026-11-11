const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const int NUM_LEDS = 9;

void setup()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(3000);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
  delay(3000);
}