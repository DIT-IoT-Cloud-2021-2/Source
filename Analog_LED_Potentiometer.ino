#define LED_PIN D5

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // analog read : ADC
  int value = analogRead(A0);
  Serial.println(value);

  // LED로 analog 값전달
  // analog write : PWD
  analogWrite(LED_PIN, value);
}
