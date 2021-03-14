#include "Arduino.h"
#include "CM1106.h"

CM1106::CM1106(Stream& stream)
{
    m_pStream = &stream;
}

bool CM1106::read(int * value)
{
    *value = millis() % 1000;
    return true;
    static uint8_t cmd[4] = {0x11, 0x01, 0x01, 0xED};  // Commands 0x01 Read ppm, 0x10 open/close ABC, 0x03 Calibrate
    static uint8_t response[8] = {0};                  // response 0x16, 0x05, 0x01, DF1, DF2, DF3, DF4, CRC.  ppm=DF1*256+DF2
    m_pStream->write(cmd, 4);
    m_pStream->readBytes(response, 8);
    int crc = 0;

    // for (int i = 0; i < 7; i++)
    // {
    //     Serial.print(response[i], HEX);
    //     Serial.print(" ");
    // }
    // Serial.println();
    
    for (int i = 0; i < 7; i++) crc += response[i];
    crc = 256 - crc % 256;
    if (((int)response[0] == 0x16) && ((int)response[7] == crc)) 
    {
        unsigned int responseHigh = (unsigned int)response[3];
        unsigned int responseLow = (unsigned int)response[4];
        *value =  (256 * responseHigh) + responseLow;
        return true;
    } 
    else 
    {
        while (m_pStream->available() > 0) m_pStream->read();  // Clear serial input buffer;
        return false;
    }
}