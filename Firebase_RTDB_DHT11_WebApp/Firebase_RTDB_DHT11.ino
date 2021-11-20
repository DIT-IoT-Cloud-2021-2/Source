#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

// Config Firebase
#define FIREBASE_HOST "dht11-firebase-1be7c.firebaseio.com"
#define FIREBASE_AUTH "TL7KC9siggd94YhnZMxjnk0RCm2GObY1dA6F9wUP"

// Config connect WiFi
#define WIFI_SSID "GENIUS_2G" // Put here your Wi-Fi SSID
#define WIFI_PASSWORD "peter8490" // Put here your Wi-Fi password

// Config DHT
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA);  // Wi-Fi 초기화 
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting......");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  // Firebase 실시간 데이터베이스 인증
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  delay(5000);

  // Read temp & Humidity for DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(500);
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("   Temperature: ");
  Serial.print(t);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;  // root[key] = value
  root["humidity"] = h;
 
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.println("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  Serial.println("");
  Serial.print("   pushed: /logDHT/");
  Serial.println(name + "\n");
  delay(5000);
}
