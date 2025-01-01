#define LED_PIN 2 // Built-in LED on most ESP32 boards

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set LED_PIN as an output
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Turn the LED on
  delay(50);                 // Wait for 1 second
  digitalWrite(LED_PIN, LOW);  // Turn the LED off
  delay(50);                 // Wait for 1 second
}
