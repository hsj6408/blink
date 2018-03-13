const char* host = "api.thingspeak.com";
String url = "/update?api_key=V0HR1V2GOSRQ7K5B";   // Your Own Key here
const int httpPort = 80;
int interval = 60000;

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdlib.h>

#define ONE_WIRE_BUS D4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "iptime";   // Your own ssid here
const char* password = "10292910";  // Your own password here

String working() { 
  float temp;
  Serial.print("Requesting Temp...");
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  
  return(String("field1=")+String(temp));
}

void delivering(String payload) { 
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpPort)) {
    Serial.print("connection failed: ");
    Serial.println(payload);
    return;
  }
  String getheader = "GET "+ String(url) +"&"+ String(payload) +" HTTP/1.1";
  client.println(getheader);
  client.println("User-Agent: ESP8266 Seok Jin Ha");  
  client.println("Host: " + String(host));  
  client.println("Connection: close");  
  client.println();

  Serial.println(getheader);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
  Serial.println("Done cycle.");
}

void connect_ap() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n Got WiFi, IP address: ");
  Serial.println(WiFi.localIP());  
}

void setup() {
  Serial.begin(115200);
  Serial.println("ESPArduinoThingSpeak.cpp - 2018/3/10");
  sensors.begin();
  connect_ap();

  
}

unsigned long mark = 0;
void loop() {
  if (millis() > mark ) {
     mark = millis() + interval;
     String payload = working();
     delivering(payload);
  }
}
