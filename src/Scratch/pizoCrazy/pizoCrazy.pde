
  
int buzzPin = 9;

void setup() {
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  int buzzerTime = 5;
  
  for (long i = 0; i < 2048 * buzzerTime; i++ )
  {
      // 1 / 2048Hz = 488uS, or 244uS high and 244uS low to create 50% duty cycle
      digitalWrite(buzzPin, HIGH);
      delayMicroseconds(244);
      digitalWrite(buzzPin, LOW);
      delayMicroseconds(244);
  }
  
  delay(3000);
}

