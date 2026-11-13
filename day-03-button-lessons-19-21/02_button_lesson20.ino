int led = 13;
int led2 =4;
int sw1 = 2;
int sw2 = 3;
void setup() 
{
  pinMode(13, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
   pinMode(sw2, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(sw1) == LOW)
  {
    digitalWrite(led, HIGH);
  } 
  if (digitalRead(sw1) == HIGH)
  {
    digitalWrite(led, LOW);
  } 
  if (digitalRead(sw2) == LOW)
  {
    digitalWrite(led2, HIGH);
  } 
  if (digitalRead(sw2) == HIGH)
  {
    digitalWrite(led2, LOW);
  } 
}