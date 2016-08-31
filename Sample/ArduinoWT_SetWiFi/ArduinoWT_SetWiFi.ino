/*
  WF8266R.js WT+ Command sample
*/

#include <SoftwareSerial.h>
SoftwareSerial wf8266r(4, 5); // RX, TX
const uint8_t maxLength = 255;
const char* ssid = "your ap ssid";
const char* password = "ap password";
char inData[maxLength];
char inChar = -1;
byte index = 0;
String apiKey = "your key";

void setup() {
  Serial.begin(9600);
  wf8266r.begin(9600);


  Serial.println("Set SSID & Password");
  String ap = "WTCONN+SSID:" + String(ssid) + ",PASSWORD:" + String(password);
  wf8266r.println(ap);

  Serial.println("Waiting for WF8266R.Ready event back...");

}

void loop() {
  if (Comp("WF8266R.Ready"))
  {
    Serial.println();
    Serial.println("WF8266R is ready");
    wf8266r.println("WTCMD+AT:IP");
    delay(1000);
    Comp(""); //update buffer
    Serial.println("Upload date to server");
    sendValueToThingSpeak(1);
  }
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

boolean Comp(char* cmd) {
  while (wf8266r.available() > 0)
  {
    if (index < maxLength - 1)
    {
      inChar = wf8266r.read();
      Serial.print(inChar);

      inData[index] = inChar;
      index++;
      inData[index] = '\0';

      if (inChar == 10 || inChar == 13)
      {
        index = 0;
        inData[index - 1] = '\0';
      }
    }
  }
  if (strcmp(inData, cmd)  == 0) {
    for (int i = 0; i < maxLength - 1; i++) {
      inData[i] = 0;
    }
    index = 0;
    return true;
  }
  else {
    return false;
  }
}
