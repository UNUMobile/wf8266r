#include <SoftwareSerial.h>
SoftwareSerial g5(2, 3); // RX, TX

static unsigned char ucRxBuffer[250];
static unsigned char ucRxCnt = 0;
long  pmcf10 = 0;
long  pmcf25 = 0;
long  pmcf100 = 0;
long  pmat10 = 0;
long  pmat25 = 0;
long  pmat100 = 0;
long  pmcount03 = 0;
long  pmcount05 = 0;
long  pmcount10 = 0;
long  pmcount25 = 0;
long  pmcount50 = 0;
long  pmcount100 = 0;

void setup() {
  Serial.begin(9600);
  g5.begin(9600);
}

void loop() {
  while (g5.available())
  {
    CopeSerialData(g5.read());
  }

  Serial.println("@G5 Reading...");
  delay(5000);

}

char CopeSerialData(unsigned char ucData)
{
  ucRxBuffer[ucRxCnt++] = ucData;

  if (ucRxBuffer[0] != 0x42 && ucRxBuffer[1] != 0x4D)
  {
    ucRxCnt = 0;
    return ucRxCnt;
  }
  if (ucRxCnt < 32) {
    return ucRxCnt;
  }
  else
  {
    for (int i = 0; i < 32; i++)
    {
      Serial.print(ucRxBuffer[i]);
      Serial.print("  ");
    }
    Serial.println("");
    pmcf10 = (float)ucRxBuffer[4] * 256 + (float)ucRxBuffer[5]; Serial.print("PM1.0_CF1:"); Serial.print(pmcf10); Serial.print("   ");
    pmcf25 = (float)ucRxBuffer[6] * 256 + (float)ucRxBuffer[7]; Serial.print("PM2.5_CF1:"); Serial.print(pmcf25); Serial.print("   ");
    pmcf100 = (float)ucRxBuffer[8] * 256 + (float)ucRxBuffer[9]; Serial.print("PM10_CF1:"); Serial.print(pmcf100); Serial.println("   ");
    pmat10 = (float)ucRxBuffer[10] * 256 + (float)ucRxBuffer[11];  Serial.print("PM1.0_AT:"); Serial.print(pmat10); Serial.print("   ");
    pmat25 = (float)ucRxBuffer[12] * 256 + (float)ucRxBuffer[13];  Serial.print("PM2.5_AT:"); Serial.print(pmat25); Serial.print("   ");
    pmat100 = (float)ucRxBuffer[14] * 256 + (float)ucRxBuffer[15];  Serial.print("PM10_AT:"); Serial.print(pmat100); Serial.println("   ");
    pmcount03 = (float)ucRxBuffer[16] * 256 + (float)ucRxBuffer[17];  Serial.print("PMcount0.3:"); Serial.print(pmcount03); Serial.print("   ");
    pmcount05 = (float)ucRxBuffer[18] * 256 + (float)ucRxBuffer[19];  Serial.print("PMcount0.5:"); Serial.print(pmcount05); Serial.print("   ");
    pmcount10 = (float)ucRxBuffer[20] * 256 + (float)ucRxBuffer[21];  Serial.print("PMcount1.0:"); Serial.print(pmcount10); Serial.println("   ");
    pmcount25 = (float)ucRxBuffer[22] * 256 + (float)ucRxBuffer[23];  Serial.print("PMcount2.5:"); Serial.print(pmcount25); Serial.print("   ");
    pmcount50 = (float)ucRxBuffer[24] * 256 + (float)ucRxBuffer[25];  Serial.print("PMcount5.0:"); Serial.print(pmcount50); Serial.print("   ");
    pmcount100 = (float)ucRxBuffer[26] * 256 + (float)ucRxBuffer[27];  Serial.print("PMcount10:"); Serial.print(pmcount100); Serial.println("   ");
    Serial.println(" *****************************************************************  ");
    Serial.println("   ");

    ucRxCnt = 0;
    return ucRxCnt;
  }
}
