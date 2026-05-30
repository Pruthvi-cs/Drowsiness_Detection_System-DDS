// --- PIN DEFINITIONS ---
const int ledPin = 2;       // LED 
const int buzzerPin = 4;    // Buzzer
const int motorIn1 = 18;    // Motor Controller IN1 (Forward)
const int motorIn2 = 19;    // Motor Controller IN2 (Backward)

void setup() {
  Serial.begin(9600);

  // Configure the pins as outputs
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

  // Ensure all components are turned OFF at startup
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingSignal = Serial.read();

    // --- DROWSINESS DETECTED ---
    if (incomingSignal == '1') {
      
      // 1. Turn Motor ON
      digitalWrite(motorIn1, LOW);
      digitalWrite(motorIn2, LOW);

      // 2. Blink LED and High Beep Buzzer for ~2 seconds
      // Loops 5 times (200ms ON + 200ms OFF = 400ms per loop * 5 = 2000ms / 2 seconds)
      for (int i = 0; i < 5; i++) {
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH); 
        delay(200);                    // ON for 200 milliseconds
        
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(200);                    // OFF for 200 milliseconds
      }
      
      // 3. Clear out the Serial Buffer
      // Since Python kept sending data during our 2-second delay, 
      // we throw away the old data so the system doesn't lag.
      while (Serial.available() > 0) {
        Serial.read(); 
      }
    }
    
    // --- USER IS AWAKE ---
    else if (incomingSignal == '0') {
      // 1. Turn LED and Buzzer OFF
      digitalWrite(ledPin, LOW);       
      digitalWrite(buzzerPin, LOW);    
      
      // 2. Motor Brake (Setting both LOW stops it, 
      // setting both HIGH applies an electronic "hard brake")
      digitalWrite(motorIn1, HIGH);
      digitalWrite(motorIn2, LOW);
    }
  }
}