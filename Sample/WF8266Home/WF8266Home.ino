/*
   WF8266Home for Arduino IDE
   PIN

   RF R 12
   RF S 16
   IR R 14
   IR S 15
   Buzzer 13
   SDA 4
   SCL 5
   LED 2
   Button 0

   Reference : 
   IRLibrary : https://github.com/markszabo/IRremoteESP8266
*/
#include <ESP8266WiFi.h>
#include "IRremoteESP8266.h"
#include "IRrecv.h"
#include "IRutils.h"
#include "RCSwitch.h"
#include "IRsend.h"

const char* ssid     = "your ssid";
const char* password = "your password";

//RF
RCSwitch mySwitch = RCSwitch();

//IR
IRrecv irrecv(14);
IRsend irsend(15);
decode_results irData;


void setup(void) {
  Serial.begin(115200);
  initPin();

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    beep();
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  checkRF();
  checkIR();

  if (digitalRead(0) == LOW)
  {
    toggleRF();
    toggleIR();
  }
}

void initPin() {

  pinMode(0, INPUT); //KEY
  pinMode(2, OUTPUT);//LED
  pinMode(13, OUTPUT);//Buzzer
  digitalWrite(13, LOW);

  mySwitch.enableReceive(12);
  mySwitch.enableTransmit(16);

  irrecv.enableIRIn();
  irsend.begin();
}

void beep() {
  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);
}

void checkRF() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("RF Code : ");
      Serial.println(value);
      delay(10);
      digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
    }

    mySwitch.resetAvailable();

  }
}

void checkIR() {
  if (irrecv.decode(&irData)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    Serial.print("IR Code : ");
    serialPrintUint64(irData.value, HEX);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
}

void toggleRF()
{
  mySwitch.send(16000001, 24);
}

void toggleIR()
{
  irsend.sendNEC(0xFF00FF, 32);
}


