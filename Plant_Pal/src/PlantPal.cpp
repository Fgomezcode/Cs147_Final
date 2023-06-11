#include "PlantPal.h"
const int frequency = 20;

PlantPal::PlantPal()
{
    this->DAY_LIGHT_PIN = 38; 
   

    this->SOIL_PIN = 39;

    pinMode(DAY_LIGHT_PIN, INPUT); 
    pinMode(SOIL_PIN, INPUT);
    
    this->MIST_PIN = 15;
    this->WATER_PIN = 13;
    pinMode(WATER_PIN,OUTPUT);
    pinMode(MIST_PIN,OUTPUT);
    
}

PlantPal::PlantPal(int day, int soil, int water, int mist)
{
    this->DAY_LIGHT_PIN = day;
    
    this->SOIL_PIN = soil;
    this->WATER_PIN = water;
    this->MIST_PIN = mist;
};

PlantPal::~PlantPal(){}
void PlantPal::startHumiditySensor(){
    this->humiditySensor.begin();
}

void PlantPal::setTemperature(){
    this->temperature = (humiditySensor.getTemperature() * (9/5)) + 32;
};

void PlantPal::setHumidity(){
    float value = 0;
    
    for(int i =0; i <frequency; i++){
        humiditySensor.read();
        value += humiditySensor.getHumidity();
        
    } 
    this->humidity = value/frequency;
};

void PlantPal::setSoilMoisture(){
    float value = 0;
    for(int i =0; i <frequency; i++){
        value += analogRead(this->SOIL_PIN);
    } 
    this->soilMoisture = map(4095 - (value/frequency), 0,4095,0,100);
};


void PlantPal::setDayLight(){
    this->dayLight = map(analogRead(this->DAY_LIGHT_PIN), 0, 4095, 0, 100);
};

void PlantPal::setAllValues(){
    setTemperature();
    setHumidity();
    setSoilMoisture();
    setDayLight();
}


float PlantPal::getHumidity(){
    return this->humidity;
};

float PlantPal::getTemperature(){
    return this->temperature;
};


float PlantPal::getSoilMoisture(){
    return this->soilMoisture;
};

int   PlantPal::getDayLight(){
    return this->dayLight;
};

void  PlantPal::waterPlant(){
    int timer = 3000;
    float startTime = millis();

    while(millis() < timer + startTime){
        digitalWrite(this->WATER_PIN,HIGH);
    }
    digitalWrite(this->WATER_PIN,LOW);

}

void  PlantPal::mistPlant(){
    int timer = 2000;
    float startTime = millis();

    while(millis() < timer + startTime){
        digitalWrite(this->MIST_PIN,HIGH);
    }
    digitalWrite(this->MIST_PIN,LOW);

}