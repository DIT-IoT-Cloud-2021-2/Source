// 2 LED BLINK, Fuction
#define RED_PIN 5   // 5 : GPIO
#define BLUE_PIN 4  // 4 : GPIO

void setup() {
  pinMode(RED_PIN, OUTPUT);    // Initialize the LED_BUILTIN pin as an output
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(115200);
}

void blink_LED(int pinNo, int delayTime) {
  // pinNo : 핀번호, delayTime : delay 시간
  digitalWrite(pinNo, LOW);
  delay(delayTime);
}

// the loop function runs over and over again forever
void loop() {
  int random_PIN = random(4, 6);
  Serial.println(random_PIN);
  blink_LED(random_PIN, 1000);
}
