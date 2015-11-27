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
  sendValueToThingSpeak(1);
}

void loop() {
  if (wf8266r.available())
    Serial.print((char)wf8266r.read());
}

void sendValueToThingSpeak(int value)
{
  char parameters[150];
  sprintf(parameters, "&field1=%d&field2=%d&field3=%d&field4=%d&field5=%d&field6=%d&field7=%d&field8=%d", 
  value, value + 1, value + 2, value + 3, value + 4, value + 5, value + 6, value + 7);

  wf8266r.println("WTPOST+HOST:api.thingspeak.com,PORT:80,URI:update.json,DATA:api_key=" + apiKey + String(parameters));
  Serial.print("Sent ");
  Serial.print(value);
  Serial.println(" to thingspeak.com");
}
