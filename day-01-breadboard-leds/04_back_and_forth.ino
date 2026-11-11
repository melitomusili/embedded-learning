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
  // forward: LED 1 to LED 9
  for (int i = 0; i < NUM_LEDS; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }

  // backward: LED 8 down to LED 2
  for (int i = NUM_LEDS - 2; i > 0; i--)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}