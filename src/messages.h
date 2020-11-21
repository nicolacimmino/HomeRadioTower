#ifndef __HOME_RATIO_TWR_H__
#define __HOME_RATIO_TWR_H__

#include "VT100.h"

const char message0[] PROGMEM = "\e[33m     ____ _______ _____ ___  _  _   \r\n"
                                "    |  _ \\__   __/ ____|__ \\| || |     \e[32mRadio:\e[33m NRF24L01\r\n"
                                "    | |_) | | | | (___    ) | || |_    \e[32mS/N:\e[33m 202010-003\r\n"
                                "    |  _ <  | |  \\___ \\  / /|__   _|   \e[32mAssembled:\e[33m 2020-10-11\r\n"
                                "    | |_) | | |  ____) |/ /_ _ | |     \e[32mBuilt:\e[33m " __DATE__ " " __TIME__ "\r\n"
                                "    |____/  |_| |_____/|____(_)|_|  \r\n"
                                "                   \e[32m(c) Nicola 2020\r\n";

const char *const messages[] PROGMEM = {message0};

void printMessage(uint8_t messageId)
{
    char buffer[512];
    strcpy_P(buffer, (char *)pgm_read_word(&(messages[messageId])));
    Serial.print(buffer);
}

#endif