// Board Manager ESP8266 by community 2.7.4  downgrade
// https://www.grc.com/fingerprints.htm

// 6E:F3:55:47:6D:F1:0E:5B:2B:04:F2:F8:C0:8B:E8:05:65:0F:1A:C1

#include <FirebaseArduino.h>
//#include <FirebaseESP8266.h>

// 아두이노 Firebase 라이브러리
#include <ESP8266WiFi.h>                                               


// 데이터 베이스 호스트 이름
#define FIREBASE_HOST  "fir-led-test-default-rtdb.firebaseio.com"

// 데이터 베이스 비밀번호
#define FIREBASE_AUTH "kd5a56mQiTK33XPULehO5lfvyuM1c44AwBLma4Cg"

// Wi-Fi 설정
#define WIFI_SSID "GENIUS_2G"
#define WIFI_PASSWORD "peter8490"

String fireStatus = "";   // firebase DB로 부터 받은 값 저장
int led = D7                                                ;        // NodeMCU LED pin                                                     

void setup() 
{
    Serial.begin(9600);
    delay(1000);    
    pinMode(led, OUTPUT);                 
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) {
       Serial.print(".");
       delay(500);
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // firebase에 연결
    Firebase.setString("LED_STATUS", "OFF");              //초기 LED 상태를 OFF로 설정

    // handle error
    if (Firebase.failed()) {
      Serial.print("setting /string failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

void loop() 
{
    fireStatus = Firebase.getString("LED_STATUS"); // Firebase 데이터베이스로 부터 LED 상태 값 읽음 
    if (fireStatus == "ON")   {       // Firebase 데이터베이스로 부터 받은 LED 상태 값이 “ON”이면 LED 켜기
      Serial.println("Led Turned ON"); // Serial Monitor에 “Led Turned ON” 문자열 출력                                                       
      digitalWrite(led, HIGH);          // LED OFF
  } else if (fireStatus == "OFF")  {    // Firebase 데이터베이스로 부토 LED 상태 값 읽음 
    Serial.println("Led Turned OFF");  // Serial Monitor에 “Led Turned OFF” 문자열 출력 
    digitalWrite(led, LOW);          // LED OFF
  } else {
     Serial.println("Command Error! Please send ON/OFF");
  }
  delay(500);
}
