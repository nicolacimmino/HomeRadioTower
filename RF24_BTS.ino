//  Copyright (C) 2020 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "src/NRF24L01RadioDriver.h"
#include "src/TimeBroadcast.h"
#include "src/RF24_Terminal.h"
#include <VT100.h>

NRF24L01RadioDriver *radio;
uRTCLib *rtc;

void setup(void)
{
  Serial.begin(9600);
  //byte hwVersion = EEPROM.read(EEPROM_HW_VERSION);
  radio = new NRF24L01RadioDriver(2);
  radio->setRXExtendedPreamble(643234);
  radio->setTXExtendedPreamble(643234);
  radio->setTXPower(3);

  Wire.begin();
  rtc = new uRTCLib(0x68);
  //rtc->set(0, 0, 13, 6, 21, 11, 20);

   VT100.begin(Serial);
}

void loop()
{
  broadcastTime();

  if (Serial.read() == TERMINAL_KEY_ESC)
  {  
    serveTerminal();
  }
}
