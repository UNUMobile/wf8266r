/*
  WF8266R.js WT+ Command sample
*/

#include <SoftwareSerial.h>
SoftwareSerial wf8266r(2, 3); // RX, TX

const char server[] = "Your server IP or Name";
const char service[] = "post.php";

void setup() {
  Serial.begin(9600);
  wf8266r.begin(9600);

  Serial.println("Ready");
  sendValueToMySQL(1, 2, 3, 4);
}

void loop() {
  if (wf8266r.available())
    Serial.print((char)wf8266r.read());
}

void sendValueToMySQL(int field1, int field2, int field3, int field4)
{
  char parameters[50]; //buffer
  sprintf(parameters, "field1=%d&field2=%d&field3=%d&field4=%d", field1, field2, field3, field4);

  wf8266r.println("WTGET+HOST:" + String(server) + ",PORT:80,URI:" + String(service) + ",DATA:" + String(parameters));
  Serial.print("field1=");
  Serial.print(field1);
  Serial.print(" field2=");
  Serial.print(field2);
  Serial.print(" field3=");
  Serial.print(field3);
  Serial.print(" field4=");
  Serial.print(field4);
  Serial.println(" to MySQL database");
}
