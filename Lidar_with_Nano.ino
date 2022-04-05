#include <TFT.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "TFMini.h"
TFMini tfmini;

#define cs 10
#define dc 9
#define rst 12

TFT TFTscreen = TFT(cs,dc,rst);
char sensorPrintout[4];

SoftwareSerial SerialTFMini(7, 8);          //The only value that matters here is the first one, 2, Rx
 
void getTFminiData(int* distance, int* strength)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  if (SerialTFMini.available())
  {
    rx[i] = SerialTFMini.read();
    if (rx[0] != 0x59)
    {
      i = 0;
    }
    else if (i == 1 && rx[1] != 0x59)
    {
      i = 0;
    }
    else if (i == 8)
    {
      for (j = 0; j < 8; j++)
      {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256))
      {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
      }
      i = 0;
    }
    else
    {
      i++;
    }
  }
}
 
 
void setup()
{
  //Serial.begin(9600);       //Initialize hardware serial port (serial debug port)
  //while (!Serial);            // wait for serial port to connect. Needed for native USB port only
  //Serial.println ("Initializing...");
  SerialTFMini.begin(TFMINI_BAUDRATE);    //Initialize the data rate for the SoftwareSerial port
  tfmini.begin(&SerialTFMini);            //Initialize the TF Mini sensor

  TFTscreen.begin();
  TFTscreen.background(0,0,0);
  TFTscreen.stroke(255,255,255);
  TFTscreen.setTextSize(2);
  TFTscreen.text("Distance: ",15,15);
  TFTscreen.setTextSize(5);
}
 
void loop()
{
  int distance = 0;
  int strength = 0;

  getTFminiData(&distance, &strength);
  while (!distance)
  {
    getTFminiData(&distance, &strength);
    if (distance)
    {
      //Serial.print(distance);
      //Serial.print("cm\t");
      //Serial.print("strength: ");
      //Serial.println(strength);

      if(distance >= 100){
        String sensorVal = String(distance/100);
        sensorVal.toCharArray(sensorPrintout, 4);

        TFTscreen.stroke(255,255,255);
        TFTscreen.text(sensorPrintout, 15,35);
        TFTscreen.text("m", 75,35);
        delay(200);
        TFTscreen.stroke(0,0,0);
        TFTscreen.text(sensorPrintout, 15,35);
        TFTscreen.text("m", 75,35);
      }
      
      if(distance < 100){
        String sensorVal = String(distance);
        sensorVal.toCharArray(sensorPrintout, 4);

        TFTscreen.stroke(255,255,255);
        TFTscreen.text(sensorPrintout, 15,35);
        TFTscreen.text("cm",75,35);
        delay(200);
        TFTscreen.stroke(0,0,0);
        TFTscreen.text(sensorPrintout, 15,35);
        TFTscreen.text("cm",75,35);
      }
    }
  }
  
}
