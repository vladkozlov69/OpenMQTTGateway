#include "User_config.h"

#ifdef ZsensorPM2008

#include "PM2008.h"

#define SERIAL2_RXPIN 14
#define SERIAL2_TXPIN 18

PM2008 pm2008(Serial2);

PM2008::DATA pmData;

void setupPM2008() 
{
    Serial2.begin(9600, SERIAL_8N1, SERIAL2_RXPIN, SERIAL2_TXPIN);
}

void MeasurePM2008() 
{
    if (millis() > (timePM2008 + TimeBetweenReadingPM2008)) 
    {
        if (pm2008.read(pmData))
        {
            char buf[20];
            itoa(pmData.PM_AE_UG_2_5, buf, 10);
            pub(PM25TOPIC, buf);
        }

        timePM2008 = millis();
    }
}


#endif
