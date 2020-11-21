
#include "TimeBroadcast.h"

void broadcastTime()
{
    static unsigned long lastBroadcastTime = 0;

    if (millis() - lastBroadcastTime < 1000)
    {
        return;
    }

    lastBroadcastTime = millis();

    rtc->refresh();

    char buffer[64];
    sprintf(buffer, "^T,%d,%d,%d!", rtc->hour(), rtc->minute(), rtc->second());
    Serial.println(buffer);

    radio->setRFChannel(TIME_BROADCAST_CHANNEL);    
    radio->send(buffer, strlen(buffer));
}
