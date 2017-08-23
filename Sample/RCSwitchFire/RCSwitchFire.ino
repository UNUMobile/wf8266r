#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  //4號腳接 433M 發射器 DATA
  mySwitch.enableTransmit(4);
  //按鍵，當按下時電位會變 低
  pinMode(3,INPUT_PULLUP);
}

void loop() {
  //當 腳位3 低電位時
  if(digitalRead(3) == LOW)
  {
    Serial.println("Send code 8266");
    //發送 54631308 按鍵碼
    mySwitch.send(8266, 24);
    delay(1000);
  }
}

