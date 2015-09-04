#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  mySerial.print("Hello, WF8266R?");
  Serial.println("Ready");
}

void loop() {
  if (mySerial.available())
    Serial.print(mySerial.read());


  for (int i = 0; i < 10; i++)
  {
    sendValueToThingSpeak(i);
    delay(20000); //20 secs
  }

}

void sendValueToThingSpeak(int value)
{
  mySerial.print("IoT+{1:" + String(value) + "}");
  Serial.print("Sent ");
  Serial.print(value);
  Serial.println(" to thingspeak.com");
}
