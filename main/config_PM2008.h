#ifndef config_PM2008_h
#define config_PM2008_h

extern void setupPM2008();
extern void PM2008toMQTT();

#define TimeBetweenReadingPM2008 30000

/*----------------------------USER PARAMETERS-----------------------------*/
/*-------------DEFINE YOUR MQTT PARAMETERS BELOW----------------*/
#define PM25TOPIC "/CLIMAtoMQTT/pm25"

//Time used to wait for an interval before resending measured values
unsigned long timePM2008 = 0;

#endif