#include <SoftwareSerial.h>

/*
Smart Street Light + Emergency GSM Alert
Connections:
- LDR AO  -> A0 [cite: 1]
- Sound AO-> A1 [cite: 2]
- PIR OUT -> D2
- Buzzer IN -> D5 (Active Buzzer 3-pin) [cite: 10]
- LED PWM -> D6 
- GSM TX -> D7 (Connect to GSM RX) 
- GSM RX -> D8 (Connect to GSM TX)
- Button -> D3 (Push to GND)
*/

// Existing Pins
const int LDR_PIN   = A0; 
const int SOUND_PIN = A1; 
const int PIR_PIN   = 2;
const int LED_PWM_PIN = 6; 
const int BUZZER_PIN  = 5; 

// New Pins
const int BUTTON_PIN = 3; 
SoftwareSerial gsmSerial(8, 7); // RX, TX

// Thresholds & Settings
int LDR_DARK_THRESHOLD   = 600; 
int SOUND_THRESHOLD      = 450; 
int DIM_BRIGHTNESS       = 60; 
int BRIGHT_BRIGHTNESS    = 255; 
bool BUZZER_LOW_TRIGGER  = true; 

unsigned long motionHoldMs = 5000; 
unsigned long lastMotionTime = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PWM_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); 
  pinMode(BUTTON_PIN, INPUT_PULLUP); // New Button

  analogWrite(LED_PWM_PIN, 0);
  buzzerOff();

  Serial.begin(9600);
  gsmSerial.begin(9600); // Initialize GSM
  
  delay(1000); // Wait for GSM to stabilize
}

void loop() {
  int ldrValue   = analogRead(LDR_PIN); 
  int soundValue = analogRead(SOUND_PIN); 
  int pirState   = digitalRead(PIR_PIN); 
  int buttonState = digitalRead(BUTTON_PIN); // Read Button
  bool smsSent = false;

  // --- Button & GSM Logic ---
  if (buttonState == LOW && !smsSent ) { // Button pressed
    buzzerOn();
    sendSMS();
    smsSent = true;
    delay(200); // Prevent spamming messages
  } else if (buttonState == HIGH) {
  smsSent = false;  // Reset when button released
}

  // --- Night detection ---
  bool isDark = (ldrValue >= LDR_DARK_THRESHOLD); 

  // --- Motion handling ---
  if (pirState == HIGH) {
    lastMotionTime = millis(); 
  }
  bool motionRecently = (millis() - lastMotionTime) < motionHoldMs; 

  // --- LED control ---
  if (!isDark) {
    analogWrite(LED_PWM_PIN, 0); 
  } else {
    if (motionRecently) analogWrite(LED_PWM_PIN, BRIGHT_BRIGHTNESS); 
    else                analogWrite(LED_PWM_PIN, DIM_BRIGHTNESS);
  }

  // --- Buzzer control (sound threshold) ---
  if (soundValue >= SOUND_THRESHOLD) {
    buzzerOn();
  } else if (buttonState == HIGH) { // Only turn off if button isn't pressed
    buzzerOff();
  }

  delay(100); 
}

// --- New GSM Function ---
void sendSMS() {
  Serial.println("Sending Emergency SMS...");
  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1\r\n"); // Set to SMS mode
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+917411996680\r\n"); // REPLACE WITH YOUR PHONE NUMBER
  delay(1000);
  gsmSerial.print("EMERGENCY! Assistance needed at Road Safety Node.");
  delay(100);
  gsmSerial.write(26); // ASCII code for Ctrl+Z to send
  delay(5000);
}

void buzzerOn() {
  if (BUZZER_LOW_TRIGGER) digitalWrite(BUZZER_PIN, LOW); 
  else                    digitalWrite(BUZZER_PIN, HIGH);
}

void buzzerOff() {
  if (BUZZER_LOW_TRIGGER) digitalWrite(BUZZER_PIN, HIGH); 
  else                    digitalWrite(BUZZER_PIN, LOW);
}