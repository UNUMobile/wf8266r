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
  displayFull(2, 8);

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
  //聲線1 金小胖不要逼我
  wf8266rv.println("WTSEN+TTS:0,DATA:BDF0D0A1C5D6B2BBD2AAB1C6CED2");
  delay(3000);
  displayClear(0);
}

void play(int i)
{
  displayClear(0);
  displayIcon(7);
  // 號同學換你了 BAC5CDACD1A7BBBBC4E3C1CB
  sn = sn + i;
  displayNumber(String(sn));
  String vcmd = "WTSEN+TTS:0,DATA:" + toHex(String(sn)) + "BAC5CDACD1A7BBBBC4E3C1CB";
  wf8266rv.println(vcmd);
}

String toHex(String number)
{
  String rtnString = "";
  for (int i = 0; i < number.length(); i++)
  {
    if (number[i] == '.' || number[i] == ':')
      rtnString += "2E";
    else
      rtnString += String(number[i] - 18);
  }

  return rtnString;
}

void loop() {
  if (voiceSerial())
  {
    String cmd = String(serialBuffer);
    Serial.print("Voice command is : ");
    Serial.println(cmd);

    if (cmd.startsWith("VCMD,"))
      delay(3000);//等待回應語

    if (cmd == "VCMD,1")
    {
      play(1);
    }

    if (cmd == "VCMD,2")
    {
      play(-1);
    }

    if (cmd == "VCMD,3")
    {
      //台灣加權指數 https://api.thingspeak.com/apps/thinghttp/send_request?api_key=8W6G9ZKK1OZH6P0O
      wf8266rv.println("WTGET+HOST:api.thingspeak.com,PORT:80,URI:apps/thinghttp/send_request,DATA:api_key=8W6G9ZKK1OZH6P0O");
    }

    if (cmd == "VCMD,4")
    {
      //取得網路時間
      wf8266rv.println("WTCMD+AT:DATETIME");
    }

    if (cmd.startsWith("GET,"))
    {
      bool isPlus = true;
      String voiceString = "WTSEN+TTS:0,DATA:";
      //台灣加權指數 CCA8CDE5BCD3C8A8D6B8CAFD
      String TSE = cmd.substring(4, cmd.length());
      displayClear(0);
      displayNumber(TSE);
      displayIcon(6);
      //目前報價 C4BFC7B0B1A8BCDB, 上漲 C9CFD5C7, 下跌 CFC2B5F8
      voiceString += "C4BFC7B0B1A8BCDB";//目前報價
      if (cmd[4] == '-')
        voiceString += "CFC2B5F8";//下跌
      else
        voiceString += "C9CFD5C7";//上漲

      voiceString += toHex(TSE);
      wf8266rv.println(voiceString);
      delay(3000);
    }

    if (cmd.startsWith("DATETIME,"))
    {
      String voiceString = "WTSEN+TTS:0,DATA:";
      String timeString = cmd.substring(cmd.indexOf(' ') + 1, cmd.lastIndexOf(':'));

      displayClear(0);
      displayNumber(timeString);
      voiceString += toHex(timeString);
      wf8266rv.println(voiceString);
      delay(3000);
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
