#ifndef PM2008_H_
#define PM2008_H_

#include "Stream.h"

class PM2008
{
public:
    struct DATA {
        // Standard Particles, CF=1
        uint16_t PM_SP_UG_1_0;
        uint16_t PM_SP_UG_2_5;
        uint16_t PM_SP_UG_10_0;

        // Atmospheric environment
        uint16_t PM_AE_UG_1_0;
        uint16_t PM_AE_UG_2_5;
        uint16_t PM_AE_UG_10_0;
    };

  PM2008(Stream&);
  bool read(DATA& data);
//  bool readUntil(DATA& data, uint16_t timeout = SINGLE_RESPONSE_TIME);

private:
    enum STATUS { STATUS_WAITING, STATUS_OK };
    uint8_t _payload[12];
    Stream* _stream;
    DATA* _data;
    STATUS _status;

    uint8_t _index = 0;
    uint16_t _frameLen;
    uint16_t _checksum;
    uint16_t _calculatedChecksum;

    void loop();
};

#endif