
#include "RF24_Terminal.h"
#include <VT100.h>
#include "messages.h"

uint8_t askChannel()
{
    char line[16];
    memset(line, 0, 16);

    VT100.setCursor(9, 1);
    VT100.clearLine();
    VT100.setTextColor(VT_RED);
    Serial.print("Channel: ");

    while (!Serial.available())
    {
        delay(1);
    }

    Serial.readBytesUntil('\r', line, 16);

    VT100.setCursor(9, 1);
    VT100.clearLine();
    VT100.setTextColor(VT_GREEN);

    return (uint8_t)atoi(line);
}

void serveTerminal()
{
    char buffer[64];
    uint8_t bufferIx = 0;
    uint8_t dataBufferSize = 64;
    unsigned long lastTerminalActivityTime = millis();
    memset(buffer, 0, 64);

    VT100.clearScreen();
    VT100.setCursor(0, 0);
    printMessage(0);
    VT100.cursorOn();
    
    radio->setRFChannel(askChannel());

    while (true)
    {
        if (millis() - lastTerminalActivityTime > 10000)
        {
            VT100.clearScreen();
            VT100.cursorOff();
            return;
        }

        while (Serial.available())
        {
            char c = Serial.read();

            VT100.setTextColor(VT_GREEN);
            Serial.print(c);

            if (c == '\r')
            {
                Serial.println("");
                radio->send(buffer, strlen(buffer));
                bufferIx = 0;
                memset(buffer, 0, dataBufferSize);

                uint8_t dataLen = 64;
                if (radio->receive(buffer, &dataLen, 1000))
                {
                    VT100.setTextColor(VT_YELLOW);
                    Serial.println(buffer);
                    memset(buffer, 0, dataBufferSize);
                    bufferIx = 0;
                }
            }
            else if (c == TERMINAL_KEY_ESC)
            {
                VT100.clearScreen();
                VT100.cursorOff();
                return;
            }
            else
            {
                buffer[bufferIx++] = c;
            }

            lastTerminalActivityTime = millis();
        }
    }
}