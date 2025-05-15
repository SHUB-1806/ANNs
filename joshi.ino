/*
 * Simple Dual Potentiometer Control System
 * POT1 (A0): Controls three buzzers (pins 2-4)
 * POT2 (A1): Controls LED sequence speed (pins 5-9)
 */

// Define pins
int pot1 = A0;
int pot2 = A1;
int buzzer1 = 2;
int buzzer2 = 3;
int buzzer3 = 4;
int leds[] = {5, 6, 7, 8, 9};
int currentLed = 0;
unsigned long lastChange = 0;

void setup() {
  // Set pin modes
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Read potentiometer values
  int pot1Value = analogRead(pot1);
  int pot2Value = analogRead(pot2);
  
  // Control buzzers based on POT1
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
  digitalWrite(buzzer3, LOW);
  
  if (pot1Value < 341) {
    digitalWrite(buzzer1, HIGH);
  } else if (pot1Value < 682) {
    digitalWrite(buzzer2, HIGH);
  } else {
    digitalWrite(buzzer3, HIGH);
  }
  
  // Control LED sequence based on POT2
  int delayTime = map(pot2Value, 0, 1023, 50, 500);
  
  if (millis() - lastChange >= delayTime) {
    lastChange = millis();
    
    // Turn off all LEDs
    for (int i = 0; i < 5; i++) {
      digitalWrite(leds[i], LOW);
    }
    
    // Turn on current LED
    digitalWrite(leds[currentLed], HIGH);
    
    // Move to next LED
    currentLed = (currentLed + 1) % 5;
  }
}