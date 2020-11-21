

// void serveTerminal()
// {
//      while (Serial.available())
//   {
//     char c = Serial.read();
    
//     if (c == '\r')
//     {
//       Serial.println(buffer);
//       radio->send(buffer, strlen(buffer));
//       bufferIx = 0;
//       memset(buffer, 0, dataBufferSize);
//       return;
//     }
//     buffer[bufferIx++] = c;
//   }

//   uint8_t dataLen = 64;
//   if (radio->receive(buffer, &dataLen, 1000))
//   {
//     Serial.println(buffer);
//     memset(buffer, 0, dataBufferSize);
//     bufferIx = 0;
//   }
// }