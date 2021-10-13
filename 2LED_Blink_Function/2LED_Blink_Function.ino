// 2 LED BLINK, Fuction
#define RED_PIN D1   // 5 : GPIO
#define BLUE_PIN D2  // 4 : GPIO

void setup() {
  pinMode(RED_PIN, OUTPUT);    // Initialize the LED_BUILTIN pin as an output
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(115200);
}


void blink_LED(int pinNo, int delayTime) {
  // pinNo : 핀번호, delayTime : delay 시간
  digitalWrite(pinNo, LOW);
  delay(delayTime);
//  digitalWrite(pinNo, HIGH)
//  delay(delayTime);
}

// the loop function runs over and over again forever
void loop() {
  int random_PIN = random(4, 6);
  // RED LED BLINK
  //blink_LED(RED_PIN, 1000);
  
  // BLUE LED BLINK
  //blink_LED(BLUE_PIN, 1000);   
  Serial.println(random_PIN);
  blink_LED(random_PIN, 1000);
}
