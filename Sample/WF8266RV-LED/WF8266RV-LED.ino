#include <SoftwareSerial.h>
SoftwareSerial wf8266rv(2, 3); // RX, TX
const uint8_t serialMax = 255;
char serialBuffer[serialMax];
uint8_t serialIndex = 0;

const int clk = 5;
const int stb = 6;
const int dio = 7;

int sn = 0;

void setup() {
  pinMode(stb, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dio, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  wf8266rv.begin(9600);

  displayClear(255); // SHOW ALL LED
  delay(1000);
  displayClear(0);
  displayIcon(7);

  /*TTS 文字轉語音，請使用以下服務將中文轉成16進位
    https://service.wf8266.com/api/voice/主人你好
    HEX : D6F7C8CBC4E3BAC3
  */

  //音量 6, 0-9
  wf8266rv.println("WTSEN+VCMD:Volume,DATA:6");
  delay(500);
  //PLAY 內置語音 0001～0046
  wf8266rv.println("WTSEN+VCMD:PlayFLASH,DATA:0000");
  delay(1000);
  //聲線1 歡迎使用叫號系統
  wf8266rv.println("WTSEN+TTS:0,DATA:BBB6D3ADCAB9D3C3BDD0BAC5CFB5CDB3");
  delay(5000);

}

void play(int i)
{
  // 號同學換你了 BAC5CDACD1A7BBBBC4E3C1CB
  sn = sn + i;
  displayNumber(String(sn));
  String vcmd = "WTSEN+TTS:0,DATA:"+toHex(String(sn))+"BAC5CDACD1A7BBBBC4E3C1CB";
   wf8266rv.println(vcmd);
}

String toHex(String number)
{
  String rtnString ="";
  for(int i=0;i<number.length();i++)
  {
    rtnString+= String(number[i] - 18);
  }

  return rtnString;
}

void loop() {
  if (voiceSerial())
  {
    String cmd = String(serialBuffer);
    Serial.print("Voice command is : ");
    Serial.println(cmd);

    if (cmd == "VCMD,1")
    {
      play(1);
    }

    if (cmd == "VCMD,2")
    {
      play(-1);
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
          serialBuffer[serialIndex - 1] = '\0';
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
