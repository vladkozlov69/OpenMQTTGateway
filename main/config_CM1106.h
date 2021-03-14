#ifndef config_CM1106_h
#define config_CM1106_h

extern void setupCM1106();
extern void CM1106toMQTT();

#define TimeBetweenReadingCM1106 30000

/*----------------------------USER PARAMETERS-----------------------------*/
/*-------------DEFINE YOUR MQTT PARAMETERS BELOW----------------*/
#define CO2TOPIC "/CLIMAtoMQTT/co2"

//Time used to wait for an interval before resending measured values
unsigned long timeCM1106 = 0;

#endif