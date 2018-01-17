/*
  WF8266R.js WT+ Command sample
*/

#include <SoftwareSerial.h>
SoftwareSerial wf8266r(2, 3); // RX, TX
String apiKey = "your api key";

void setup() {
  Serial.begin(9600);
  wf8266r.begin(9600);

  Serial.println("Ready");
  sendValueToThingSpeak(30, 28.93);
}

void loop() {
  if (wf8266r.available())
    Serial.print((char)wf8266r.read());
}

void sendValueToThingSpeak(int pm25, float temp)
{
  char parameters[50]; //buffer
  sprintf(parameters, "&field1=%d&field2=%.2f", 
  pm25, temp);

  wf8266r.println("WTPOST+HOST:api.thingspeak.com,PORT:80,URI:update.json,DATA:api_key=" + apiKey + String(parameters));
  Serial.print("Sent temp=");
  Serial.print(temp);
  Serial.print(" pm2.5=");
  Serial.print(pm25);
  Serial.println(" to thingspeak.com");
}
