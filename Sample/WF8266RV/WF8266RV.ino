#include <SoftwareSerial.h>
SoftwareSerial wf8266rv(2, 3); // RX, TX
const uint8_t serialMax = 255;
char serialBuffer[serialMax];
uint8_t serialIndex = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  wf8266rv.begin(9600);

  /*TTS 文字轉語音，請使用以下服務將中文轉成16進位
  https://service.wf8266.com/api/voice/主人你好
  HEX : D6F7C8CBC4E3BAC3
  */

  //音量 1, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:1");
  delay(1000);
  //聲線1
  wf8266rv.println("WTSEN+TTS:0,DATA:D6F7C8CBC4E3BAC3");
  delay(3000);
  
  //音量 3, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:3");
  delay(1000);
  //聲線2
  wf8266rv.println("WTSEN+TTS:1,DATA:D6F7C8CBC4E3BAC3");
  delay(3000);

  //音量 5, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:5");
  delay(1000);
  //聲線3
  wf8266rv.println("WTSEN+TTS:2,DATA:D6F7C8CBC4E3BAC3");
  delay(3000);

  //音量 7, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:7");
  delay(1000);
  //聲線4
  wf8266rv.println("WTSEN+TTS:3,DATA:D6F7C8CBC4E3BAC3");
  delay(3000);

  //音量 9, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:9");
  delay(1000);
  //聲線5
  wf8266rv.println("WTSEN+TTS:4,DATA:D6F7C8CBC4E3BAC3");
  delay(3000);

  //音量 6, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:6");
  delay(1000);
  //聲線6
  wf8266rv.println("WTSEN+TTS:5,DATA:D6F7C8CBC4E3BAC3");
  delay(3000);

  //PLAY 自訂語音命令回應語句
  wf8266rv.println("WTSEN+VCMD:PlayFlashText,DATA:001");
  delay(5000);
  wf8266rv.println("WTSEN+VCMD:PlayFlashText,DATA:002");
  delay(5000);

  //PLAY 內置語音 0001～0046
  wf8266rv.println("WTSEN+VCMD:PlayFLASH,DATA:0000");
  delay(1000);
  wf8266rv.println("WTSEN+VCMD:PlayFLASH,DATA:0014");
  delay(1000);
  wf8266rv.println("WTSEN+VCMD:PlayFLASH,DATA:0015");
  delay(1000);
  wf8266rv.println("WTSEN+VCMD:PlayFLASH,DATA:0016");
  delay(1000);

  //Play TF卡裡的 MP3 0001.mp3
  wf8266rv.println("WTSEN+VCMD:PlayTF,DATA:0001");
  delay(15000);
  wf8266rv.println("WTSEN+VCMD:PlayTF,DATA:0003");
  delay(15000);
  wf8266rv.println("WTSEN+VCMD:StopPlaying,DATA:");
  //Ready 你可以開始說指令了
  wf8266rv.println("WTSEN+TTS:1,DATA:C4E3BFC9D2D4BFAACABCCBB5D6B8C1EEC1CB");
}

void loop() {
  if(voiceSerial())
  {
    String cmd = String(serialBuffer);
    Serial.print("Voice command is : ");
    Serial.println(cmd);

    if(cmd == "VCMD,1")
    {
      Serial.println("OPEN LED");
      digitalWrite(13,HIGH);
    }
    
    if(cmd == "VCMD,2")
    {
      Serial.println("CLOSE LED");
      digitalWrite(13,LOW);
    }
  }
}

bool voiceSerial() {
  if (wf8266rv.available())
  {
    while (wf8266rv.available())
    {
      uint8_t val = wf8266rv.read();
      wf8266rv.print((char)val);
      if (serialIndex > serialMax)
        wf8266rv.read();
      else
      {
        if (val == 10 && serialBuffer[serialIndex - 1] == 13) // /r/n
        {
          serialBuffer[serialIndex-1] = '\0';
          serialIndex = 0;
          return true;
        }
        else
        {
          //save to buffer
          serialBuffer[serialIndex++] = (char)val;
        }
      }
    }
  }

  return false;
}
