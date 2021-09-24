/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

#define RED_PIN D1   // 5 : GPIO
#define BLUE_PIN D2  // 4 : GPIO

void setup() {
  pinMode(RED_PIN, OUTPUT);    // Initialize the LED_BUILTIN pin as an output
  pinMode(BLUE_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // RED LED BLINK
  digitalWrite(RED_PIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);                      // Wait for a second
  digitalWrite(RED_PIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);   

  // BLUE LED BLINK
  digitalWrite(BLUE_PIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);                      // Wait for a second
  digitalWrite(BLUE_PIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);       
}
