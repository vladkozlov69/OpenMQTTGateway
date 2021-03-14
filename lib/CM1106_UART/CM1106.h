#ifndef CM1106_H_
#define CM1106_H_

#include "Stream.h"

class CM1106
{
private:
    Stream * m_pStream;
    int CO2 = 0;
    bool dataReady = false;
public:
    CM1106(Stream&);
    bool read(int * value);
};


#endif