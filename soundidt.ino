#define LDR_PIN     A0
#define SOUND_PIN   A1
#define PIR_PIN     2
#define BUTTON_PIN  3
#define RELAY_PIN   4
#define BUZZER_PIN  5
#define LED_PIN     6
#define BODY_PIN    9

#define DARK_THRESHOLD  900
#define SOUND_THRESHOLD  500 // set correct value!
#define BUZZER_TIME      2000

bool lastButtonState = HIGH;
bool lastSoundState  = false;

void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);

  Serial.begin(9600);
  pinMode(PIR_PIN,    INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BODY_PIN,   INPUT);
  pinMode(SOUND_PIN,  INPUT);
  pinMode(RELAY_PIN,  OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN,    OUTPUT);

  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(RELAY_PIN,  HIGH);
  digitalWrite(LED_PIN,    LOW);

  Serial.println("System Ready!");
  delay(2000);
}

void loop() {
  int  ldrValue     = analogRead(LDR_PIN);
  int  soundValue   = analogRead(SOUND_PIN);
  bool pirDetected  = digitalRead(PIR_PIN);
  bool bodyDetected = digitalRead(BODY_PIN);
  bool buttonState  = digitalRead(BUTTON_PIN);

  Serial.print("LDR: ");      Serial.print(ldrValue);
  Serial.print(" | Sound: "); Serial.print(soundValue);
  Serial.print(" | PIR: ");   Serial.print(pirDetected);
  Serial.print(" | BTN: ");   Serial.println(buttonState == LOW ? "PRESSED" : "open");

  // ==========================================
  // FEATURE 1 — Street Light
  // ==========================================
  if (ldrValue > DARK_THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN,   HIGH);
    Serial.println(">> Dark: Street light ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN,   LOW);
  }

  // ==========================================
  // FEATURE 2 — Motion
  // ==========================================
  if (pirDetected || bodyDetected) {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println(">> Motion: Light ON");
    delay(5000);
  }

  // ==========================================
  // FEATURE 3 — Button triggers buzzer
  // ==========================================
  if (buttonState == LOW && lastButtonState == HIGH) {
    Serial.println(">> BUTTON PRESSED — Buzzer ON!");
    digitalWrite(BUZZER_PIN, LOW);
    delay(BUZZER_TIME);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println(">> Buzzer OFF");
    lastButtonState = HIGH; // reset after beep
  } else {
    lastButtonState = buttonState;
  }

  // ==========================================
  // FEATURE 4 — Sound triggers buzzer
  // ==========================================
  bool soundDetect = (soundValue > SOUND_THRESHOLD);

  if (soundDetect && !lastSoundState) {
    Serial.println(">> LOUD SOUND — Buzzer ON!");
    digitalWrite(BUZZER_PIN, LOW);
    delay(BUZZER_TIME);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println(">> Buzzer OFF");
    lastSoundState = false; // reset so it can trigger again!
  } else {
    lastSoundState = soundDetect;
  }

  delay(100);
}