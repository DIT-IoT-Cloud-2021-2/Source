#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN D4     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11

const char* ssid = "jhkim3217"; 
const char* password = "deitcs3217";
DHT dht(DHTPIN, DHTTYPE);
 
WiFiServer server(80);  // 웹서버용 포트 번호
 
void setup() 
{
  Serial.begin(9600);
  
  // 와이파이 네트워크에 접속
  Serial.print("Connecting to ");                                                                                               
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  dht.begin(); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
 
  // 웹서버 개시
  server.begin();
  Serial.println("HTTP server started");
 
  // 접속할 IP 주소 표시
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() 
{
  // 클라이언트가 접속되었는지 확인
  WiFiClient client = server.available();
  
  if (!client) {
    return; // 함수 실행 종료
  } 
 
  Serial.println("new client");

  // Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
 
  // 클라이언트 리퀘스트의 첫번째 줄을 읽어들임. http 요청
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // 클라이언트 리퀘스트에 대한 응답 메시지를 시리얼통신으로 클라이언트에 전송
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");  // 필수 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv=\"refresh\" content=\"5\">");
  client.println("<br />"); 
  client.println(""); //  do not forget this one
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
 
  client.print("<h2>DIT Weather Station</h2>");
  client.print("Temperature (C): "); 
  client.println(t);  
  client.println("<p />");  

  client.print("Humidity (%): ");
  client.println(h);  
  client.println("<p />");   

  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
}
