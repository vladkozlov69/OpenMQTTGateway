#include "Arduino.h"
#include "PM2008.h"

PM2008::PM2008(Stream& stream)
{
    this->_stream = &stream;
}

// Non-blocking function for parse response.
bool PM2008::read(DATA& data)
{
    data.PM_AE_UG_2_5 = millis() % 1000;
    return true;

    _data = &data;
    loop();

    return _status == STATUS_OK;
}

void PM2008::loop()
{
    _status = STATUS_WAITING;
    if (_stream->available())
    {
        uint8_t ch = _stream->read();

        switch (_index)
        {
            case 0:
                if (ch != 0x42)
                {
                    Serial.println("ch != 0x42");
                    return;
                }
                _calculatedChecksum = ch;
                break;

            case 1:
                if (ch != 0x4D)
                {
                    Serial.println("ch != 0x4D");
                    _index = 0;
                    return;
                }
                _calculatedChecksum += ch;
                break;

            case 2:
                _calculatedChecksum += ch;
                _frameLen = ch << 8;
                break;

            case 3:
                _frameLen |= ch;
                // Unsupported sensor, different frame length, transmission error e.t.c.
                if (_frameLen != 2 * 9 + 2 && _frameLen != 2 * 13 + 2)
                {
                    Serial.println("Unsupported sensor");
                    _index = 0;
                    return;
                }
                _calculatedChecksum += ch;
                break;

            default:
                if (_index == _frameLen + 2)
                {
                    _checksum = ch << 8;
                }
                else if (_index == _frameLen + 2 + 1)
                {
                    _checksum |= ch;

                    if (_calculatedChecksum == _checksum)
                    {
                        _status = STATUS_OK;

                        // Standard Particles, CF=1.
                        _data->PM_SP_UG_1_0 = makeWord(_payload[0], _payload[1]);
                        _data->PM_SP_UG_2_5 = makeWord(_payload[2], _payload[3]);
                        _data->PM_SP_UG_10_0 = makeWord(_payload[4], _payload[5]);

                        // Atmospheric Environment.
                        _data->PM_AE_UG_1_0 = makeWord(_payload[6], _payload[7]);
                        _data->PM_AE_UG_2_5 = makeWord(_payload[8], _payload[9]);
                        _data->PM_AE_UG_10_0 = makeWord(_payload[10], _payload[11]);
                    }

                    _index = 0;
                    return;
                }
                else
                {
                    _calculatedChecksum += ch;
                    uint8_t payloadIndex = _index - 4;

                    // Payload is common to all sensors (first 2x6 bytes).
                    if (payloadIndex < sizeof(_payload))
                    {
                        _payload[payloadIndex] = ch;
                    }
                }

                break;
        }

        _index++;
    }
}
