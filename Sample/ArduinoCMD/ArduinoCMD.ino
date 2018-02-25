/*
 WF8266R.js RESTful /serial/write service.
*/

#include <SoftwareSerial.h>
SoftwareSerial wf8266r(2, 3); // RX, TX
const uint8_t maxLength = 20;
char inData[maxLength];
char inChar=-1;
byte index = 0;

void setup() {
  Serial.begin(9600);
  wf8266r.begin(9600);
  pinMode(13,OUTPUT);
  Serial.println("Ready");
}

void loop() {

  if (Comp("GPIO13ON")) {
    Serial.println("GPIO 13 ON");
    digitalWrite(13,HIGH);
  }
  else if(Comp("GPIO13OFF")) {
    Serial.println("GPIO 13 OFF");
    digitalWrite(13,LOW);
  }
}

boolean Comp(char* cmd) {
  while (wf8266r.available() > 0)
  {
    if (index < maxLength -1)
    {
      inChar = wf8266r.read();
      inData[index] = inChar;
      index++;
      inData[index] = '\0';
    }
  }

  if (strcmp(inData, cmd)  == 0) {
    for (int i = 0; i < 19; i++) {
      inData[i] = 0;
    }
    index = 0;
    return true;
  }
  else {
    return false;
  }
}
