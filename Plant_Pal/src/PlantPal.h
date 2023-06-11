#include <Arduino.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include "DHT20.h"
#include "Wire.h"

class PlantPal
{
private:
    DHT20 humiditySensor;

    // sensor input pins
    int DAY_LIGHT_PIN;
    int SOIL_PIN;

    //actuator output pins
    int WATER_PIN;
    int MIST_PIN;

    // data members 
    float temperature;
    float humidity;
    float soilMoisture;
    
    int dayLight;

    void setTemperature();
    void setHumidity();
    void setSoilMoisture();
    void setDayLight();

public:
    PlantPal();
    PlantPal(int day, int soil, int water, int mist);
    ~PlantPal();

    void startHumiditySensor();
    void setAllValues();

    float getTemperature();
    float getHumidity();
    float getSoilMoisture();
    int   getDayLight();


    void  getAllValues();
    void  waterPlant();
    void  mistPlant();
};



