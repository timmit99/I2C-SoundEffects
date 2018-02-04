

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>

int code=0;
int prevCode;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  Wire.begin(99);
  Wire.onReceive(receiveEvent);  // Set up interrupt handler
  Serial.begin(115200);

  mySoftwareSerial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(25);  //Set volume value. From 0 to 30

}

void loop() {
  if( code != prevCode){
    Serial.println(code);         // print the character
    myDFPlayer.play(code);
    prevCode = code;
  }
}

void receiveEvent()
{

  while(Wire.available())    // slave may send less than requested
  {
    code = Wire.read();    // receive a byte as character
    Serial.print(c);         // print the character
  }
}
