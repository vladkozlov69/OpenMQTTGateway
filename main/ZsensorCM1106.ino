#include "User_config.h"

#ifdef ZsensorCM1106

#include "CM1106.h"

#define SERIAL1_RXPIN 17 
#define SERIAL1_TXPIN 16

CM1106 cm1106(Serial1);

int CO2 = 0;

void setupCM1106() 
{
    Serial1.begin(9600, SERIAL_8N1, SERIAL1_RXPIN, SERIAL1_TXPIN);
}

void MeasureCM1106() 
{
    if (millis() > (timeCM1106 + TimeBetweenReadingCM1106)) 
    {
        if (cm1106.read(&CO2))
        {
            Serial.print("CO2 (ppm): ");
            Serial.println(CO2);
            char buf[20];
            itoa(CO2, buf, 10);
            pub(CO2TOPIC, buf);
        }
        else
        {
            Serial.println("co2 err");
        }

        timeCM1106 = millis();
    }
}


#endif
