/*
  WF8266R.js WT+ Command sample
  IFTTT WEBHOOKS : https://ifttt.com/maker_webhooks
*/

#include <SoftwareSerial.h>
SoftwareSerial wf8266r(2, 3); // RX, TX
String apiKey = "your api key";

void setup() {
  Serial.begin(9600);
  wf8266r.begin(9600);

  Serial.println("Ready");
  triggerIFTTT("pm25", "1", "2", "3");
}

void loop() {
  if (wf8266r.available())
    Serial.print((char)wf8266r.read());
}

void triggerIFTTT(String event, String p1, String p2, String p3) {

  String parameters = "value1=" + p1 + "&value2=" + p2 + "&value3=" + p3;
  wf8266r.println("WTPOST+HOST:maker.ifttt.com,PORT:80,URI:trigger/" + event + "/with/key/" + apiKey + ",DATA:" + parameters);
}
