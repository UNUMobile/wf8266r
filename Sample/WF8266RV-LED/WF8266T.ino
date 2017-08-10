//Display data 
//顯示資料，共7位數。要顯示的數字放這進這個陣列，對應位置 1~7。(請勿改到)
uint8_t displayBuffer[] = {255, 255, 255, 255, 255, 255, 255};
//Number start address
//每個數字使用3個Byte，指定起始位址。(請勿改到)
uint8_t numberCodeOffset [7] = {0xc0, 0xc4, 0xc8, 0xcc, 0xc1, 0xc7, 0xcb};
//Position 6 start byte
//位置6顯示需要4個 Byte，所以需要補上第一個Byte資料//位置6顯示需要4個 Byte，所以需要補上第一個Byte資料
//如有自行更換字型，這裡要記得改。
uint8_t numberCodeP6 [15] = {
  128, 0, 128, 128, 128, 128, 128, 128, 128, 128, 0, 0, 0 , 0 , 0
};
uint8_t fullBuffer[4][16] = {
  { 190, 138, 96, 134, 225, 133, 199, 11, 15, 0, 224, 15, 4, 10, 254, 0 }, // 0 conn l1
  { 190, 138, 96, 134, 225, 133, 199, 11, 15, 0, 224, 15, 4, 202, 147, 70 }, // 1 conn l2
  { 254, 249, 249, 66, 192, 252, 199, 17, 175, 7, 30, 1, 7, 192, 144, 48 }, // 2 Arduino
  { 255, 255, 243, 127, 254, 159, 255, 63, 15, 64, 96, 240, 251, 255, 6, 1 } //3 WF8266T
};
bool isIcon = false;

//Number Font 
//每個數字使用3個Byte，也就是24顆LED燈。
uint8_t numberCode [7] [15] [3] = {
  { // position 1
    {0xff, 0xfe, 0x01}, // 0
    {0x00, 0xfc, 0x01}, // 1
    {0xf9, 0x3f, 0x01}, // 2
    {0xc9, 0xff, 0x01}, // 3
    {0x0f, 0xfd, 0x01}, // 4
    {0xcf, 0xe7, 0x01}, // 5
    {127, 227, 1},      // 6
    {129, 252, 1},      // 7
    {0xff, 0xff, 0x01}, // 8
    {143, 253, 1},      // 9 
    {0x00, 0x00, 0x00}, //10 : space
    {0x00, 0x0c, 0x00}, //11 : :
    {128, 0, 0},        //12 : . up
    {0, 2, 0},          //13 : . down
    {20, 81, 0}         //14 : %
  },
  { //position 2
    {0xfe, 0xfd, 0x03},
    {0x00, 0xf8, 0x03},
    {0xf2, 0x7f, 0x02},
    {0x92, 0xff, 0x03},
    {0x1e, 0xfa, 0x03},
    {0x9e, 0xcf, 0x03}, //5
    {254, 198, 3},
    {2, 249, 3},
    {0xfe, 0xff, 0x03},
    {30, 251, 3},
    {0x00, 0x00, 0x00}, //10 : space
    {0x00, 0x0c, 0x00},  //11 : :
    {0, 1, 0},
    {0, 4, 0}, //13 : . down
    {40, 162, 0}
  },
  { //position 3
    {0xfc, 0xfb, 0x07},
    {0x00, 0xf0, 0x07},
    {0xe4, 0xff, 0x04},
    {0x24, 0xff, 0x07},
    {0x3c, 0xf4, 0x07},
    {0x3c, 0x9f, 0x07}, //5
    {252, 141, 7},
    {4, 242, 7},
    {0xfc, 0xff, 0x07},
    {60, 246, 7},
    {0x00, 0x00, 0x00}, //10 : space
    {0x00, 0x0c, 0x00},  //11 : :
    {0, 2, 0},
    {0, 8, 0},
    {80, 68, 1}
  },
  { //position 4
    {0xf8, 0xf7, 0x0f},
    {0x00, 0xe0, 0x0f},
    {0xc8, 0xff, 0x09},
    {0x48, 0xfe, 0x0f},
    {0x78, 0xe8, 0x0f},
    {0x78, 0x3e, 0x0f}, //5
    {248, 27, 15},
    {8, 228, 15},
    {0xf8, 0xff, 0x0f},
    {120, 236, 15},
    {0x00, 0x00, 0x00}, //10 : space
    {0x00, 0x0c, 0x00},  //11 : :
    {0, 4, 0},
    {0, 16, 0},
    {160, 136, 2}
  },
  { //position 5
    {0xf0, 0xef, 0x1f},
    {0x00, 0xc0, 0x1f},
    {0x90, 0xff, 0x13},
    {0x90, 0xfc, 0x1f},
    {0xf0, 0xd0, 0x1f},
    {0xf0, 0x7c, 0x1e}, //5
    {240, 55, 30},
    {16, 200, 31},
    {0xf0, 0xff, 0x1f},
    {240, 216, 31},
    {0x00, 0x00, 0x00}, //10 : space
    {0x00, 0x0c, 0x00},  //11 : :
    {0, 8, 0},
    {0, 32, 0},
    {64, 17, 5}
  },
  { //position 6
    {79, 228, 3},
    {0, 224, 3},
    {78, 229, 2},
    {74, 229, 3},
    {3, 225, 3},
    {75, 165, 3}, //5
    {79, 165, 3},
    {64, 224, 3},
    {79, 229, 3},
    {75, 229, 3},
    {0, 0, 0}, //10 : space
    {0, 5, 0},  //11 : :
    {16, 0, 0},
    {0, 4, 0},
    {130, 160, 0}
  },
  { //position 7
    {240, 137, 124},
    {0, 0, 124},
    {208, 169, 92},
    {80, 169, 124},
    {112, 32, 124},
    {112, 169, 116}, //5
    {240, 169, 116},
    {16, 8, 124},
    {240, 169, 124},
    {112, 169, 124},
    {0, 0, 0}, //10 : space
    {0, 160, 0},  //11 : :
    {0, 2, 0},
    {0, 128, 0},
    {80, 16, 20}
  }
};

uint8_t iconCode [16] [6] = {
  {0, 0, 0, 0, 0, 0}, // 0 space
  {0, 96, 182, 97, 216, 102}, // 1 %
  {0, 0, 184, 223, 1, 0}, // 2 offline
  {0, 0, 248, 255, 1, 0}, // 3 online
  {0, 231, 68, 34, 157, 56}, //4 plugin
  {0, 232, 143, 199, 253, 76}, //5 oil
  {192, 39, 50, 185, 76, 34}, //6 mail
  {128, 169, 250, 253, 86, 88}, //7 human
  {128, 225, 127, 252, 31, 126}, //8 rain
  {0, 0, 254, 171, 209, 0}, //9 temperature
  {0, 193, 240, 251, 25, 8}, //10 UP
  {0, 193, 241, 33, 240, 120 }, //11 LEFT
  {0, 128, 71, 248, 56, 8 }, //12 RIGHT
  {0, 129, 249, 101, 18, 127 }, //13 TurnLeft
  {224, 159, 200, 252, 48, 8 }, //14 TurnRight
  {0, 128, 240, 39, 18, 0 } //15 facebook 
};

void displayIcon(uint8_t n)
{
  isIcon = true;
  uint8_t firstValue = 0;
  uint8_t value = 0;

  if (displayBuffer[4] < 255)
    firstValue += numberCode[4][displayBuffer[4]][2];

  for (uint8_t i = 0; i < 6; i++)
  {
    value = iconCode[n][i];
    if (i == 0)
      value += firstValue;

    led_begin(0x44);
    shiftOut(dio, clk, LSBFIRST, 0xC5 + (i * 2));
    shiftOut(dio, clk, LSBFIRST, value);
    led_end(0x8f);
  }
}

void displayNumber(uint8_t n, uint8_t index)
{
  if (n == 255)
    return;

  if (index > 4 && isIcon)
    return;

  uint8_t startAddr = numberCodeOffset[index];
  uint8_t value, currentAddr;

  for (uint8_t i = 0; i < 3; i ++)
  {
    value = numberCode[index][n][i];

    if (i == 0 && index > 0 && displayBuffer[index - 1] < 255) //check pre number
    {
      if (index != 5)
        value += numberCode[index - 1][displayBuffer[index - 1]][2];
    }
    if (i == 2 && index < 6 && displayBuffer[index + 1] < 255) //check last number
    {
      if (index != 4)
        value += numberCode[index + 1][displayBuffer[index + 1]][0];
      else
        value += numberCodeP6[displayBuffer[5]];
    }

    led_begin(0x44);
    currentAddr = startAddr + (i * 2);
    if (startAddr == 0xcc && i * 2 == 4)
      currentAddr = 0xc1;

    shiftOut(dio, clk, LSBFIRST, currentAddr);
    shiftOut(dio, clk, LSBFIRST, value);

    led_end(0x8f);
  }
}

void displayFull(uint8_t n, uint8_t light)
{
  uint8_t index = 0;
  for (uint8_t i = 0; i < 8; i++)
  {
    index =  i * 2;

    led_begin(0x44);
    shiftOut(dio, clk, LSBFIRST, 0xC0 + index);
    shiftOut(dio, clk, LSBFIRST, fullBuffer[n][i]);
    led_end(light);
    led_begin(0x44);
    shiftOut(dio, clk, LSBFIRST, 0xC0 + index + 1);
    shiftOut(dio, clk, LSBFIRST, fullBuffer[n][8 + i]);
    led_end(light);
  }
}

void displayNumber(String number)
{
  for (uint8_t i = 0; i < number.length() ; i++)
  {
    if (number[i] - 48 == 47)
      displayBuffer[i] = 10;  // _ = space
    else
      displayBuffer[i] = number[i] - 48 ;
  }

  displayAllBuffer();
}

void displayAllBuffer() {
  for (uint8_t i = 0; i < 7; i++)
  {
    displayNumber(displayBuffer[i], i);

  }
}

void displayClear(uint8_t n)
{
  isIcon = false;
  
  for (uint8_t i = 0; i < 16; i++)
  {
    if(i<7)
      displayBuffer[i] = 255;
      
    led_begin(0x44);
    shiftOut(dio, clk, LSBFIRST, 0xC0 + i);
    shiftOut(dio, clk, LSBFIRST, n);
    led_end(0x8f);
  }
}

void led_begin(uint8_t addr)
{
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, addr); //data control FIXED 44 AUTO 40
  digitalWrite(stb, HIGH);
  digitalWrite(stb, LOW);
}

void led_end(uint8_t light)
{
  digitalWrite(stb, HIGH);
  digitalWrite(stb, LOW);
  shiftOut(dio, clk, LSBFIRST, light); //display control
  digitalWrite(stb, HIGH);
}
