/*!
   @file  i2c.ino
   @brief  Control the voice recognition module via I2C
   @n  Get the recognized command ID and play the corresponding reply audio according to the ID;
   @n  Get and set the wake-up state duration, set mute mode, set volume, and enter the wake-up state
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence  The MIT License (MIT)
   @author  [qsjhyy](yihuan.huang@dfrobot.com)
   @version  V1.0
   @date  2022-12-30
   @url  https://github.com/DFRobot/DFRobot_DF2301Q
*/
// running on a arduino uno with a relay shild
#include "DFRobot_DF2301Q.h"
#define relay1Pin 7
#define relay2Pin 6
#define relay3Pin 5
#define relay4Pin 4
//I2C communication
DFRobot_DF2301Q_I2C DF2301Q;

void setup()
{
  Serial.begin(9600);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);
  pinMode(relay4Pin, OUTPUT);
  // Init the sensor
  while ( !( DF2301Q.begin() ) ) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
//  Serial.println("Begin ok!");

  /**
     @brief Set voice volume
     @param voc - Volume value(1~7)
  */
  DF2301Q.setVolume(20);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  DF2301Q.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  DF2301Q.setWakeTime(90);

  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
//  uint8_t wakeTime = 0;
//  wakeTime = DF2301Q.getWakeTime();
//  Serial.print("wakeTime = ");
//  Serial.println(wakeTime);

  /**
     @brief Play the corresponding reply audio according to the command word ID
     @param CMDID - Command word ID
     @note Can enter wake-up state through ID-1 in I2C mode
  */
//  DF2301Q.playByCMDID(1);   // Wake-up command
//  DF2301Q.playByCMDID(23);   // Common word ID

}

//void loop()
//{
//  /**
//     @brief Get the ID corresponding to the command word
//     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
//  */
//  uint8_t CMDID = 0;
//  CMDID = DF2301Q.getCMDID();
//  if (0 != CMDID) {
//    Serial.print("ID=");
//    Serial.println(CMDID);
//  }
//  delay(3000);
//}

void loop() {
  uint8_t CMDID = 0;
  CMDID = DF2301Q.getCMDID();
  if (0 != CMDID) {
    //Serial.print("ID=");
    Serial.println("ID=" + String(CMDID, DEC));
  }
  if (Serial.available() > 0) {
    char state = Serial.read();
    switch (state) {
      // trun on relays
      case '1':
        digitalWrite(relay1Pin, HIGH);
        //Serial.println("relay 1 ON");
        break;
      case '2':
        digitalWrite(relay2Pin, HIGH);
        //Serial.println("relay 2 ON");
        break;
      case '3':
        digitalWrite(relay3Pin, HIGH);
        //Serial.println("relay 3 ON");
        break;
      case '4':
        digitalWrite(relay4Pin, HIGH);
        //Serial.println("relay 4 ON");
        break;
      // trun off relays
      case '5':
        digitalWrite(relay1Pin, LOW);
        //Serial.println("relay 1 OFF");
        break;
      case '6':
        digitalWrite(relay2Pin, LOW);
        //Serial.println("relay 2 OFF");
        break;
      case '7':
        digitalWrite(relay3Pin, LOW);
        //Serial.println("relay 3 OFF");
        break;
      case '8':
        digitalWrite(relay4Pin, LOW);
        //Serial.println("relay 4 OFF");
        break;
      case '9':          // turn all relays off
        digitalWrite(relay4Pin, LOW);
        digitalWrite(relay3Pin, LOW);
        digitalWrite(relay2Pin, LOW);
        digitalWrite(relay1Pin, LOW);
        //Serial.println("All relays OFF");
        break;
      case '0':         // trun all relays on
        digitalWrite(relay4Pin, HIGH);
        digitalWrite(relay3Pin, HIGH);
        digitalWrite(relay2Pin, HIGH);
        digitalWrite(relay1Pin, HIGH);
        //Serial.println("All relays ON");
        break;
      case 0x40:  // unmute
        DF2301Q.setMuteMode(0);
        //Serial.println("setMuteMode(0)");
        break;
      // change volume
      case 0x41:
        DF2301Q.setVolume(2);
        //Serial.println("setVolume(1)");
        break;
      case 0x42:
        DF2301Q.setVolume(5);
        //Serial.println("setVolume(2)");
        break;
      case 0x43:
        DF2301Q.setVolume(8);
        //Serial.println("setVolume(3)");
        break;
      case 0x44:
        DF2301Q.setVolume(11);
        //Serial.println("setVolume(4)");
        break;
      case 0x45:
        DF2301Q.setVolume(14);
        //Serial.println("setVolume(5)");
        break;
      case 0x46:
        DF2301Q.setVolume(17);
        //Serial.println("setVolume(6)");
        break;
      case 0x47:
        DF2301Q.setVolume(20);
        //Serial.println("setVolume(7)");
        break;
      case 0x48:
        DF2301Q.setMuteMode(1);  // mute
        //Serial.println("setMuteMode(1)");
        break;
      case 0x49:
        DF2301Q.playByCMDID(1);  // wake up
        Serial.println("ID=2");
        break;
    }
  }
  delay(50);
}
