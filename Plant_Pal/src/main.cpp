
#include "PlantPal.h"
const char* ssid = "FG-Network"; // stick this in a file?
const char* password = "Felipe0331";

String serverAddress = "18.189.194.161";  // this changes depending on instance

WiFiClient wc;
HttpClient client = HttpClient(wc, serverAddress, 5000);

PlantPal pal; // Instantiate Plant Pal object with default constructor 

void connectToWifi();
void makePost(int temperature, int humidity, int soil, int daylight);


void setup() {
  Serial.begin(115200); // start communication
  connectToWifi();
  Wire.begin();
  pal.startHumiditySensor(); // instantiate humidity sensor
  pal.setAllValues(); // take first reading
}

void loop() {
  pal.setAllValues();

  Serial.println("\n=================");
  Serial.print("====PLANT PAL====");
  Serial.println("\n=================");
  Serial.print("Temperature:\t");
  Serial.println(pal.getTemperature());

  Serial.print("Humidity:\t");
  Serial.println(pal.getHumidity());

  Serial.print("Soil Moisture:\t");
  Serial.println(pal.getSoilMoisture());

  Serial.print("Daylight:\t");
  Serial.println(pal.getDayLight());
  Serial.println("=================\n");

  makePost(pal.getTemperature(),pal.getHumidity(),pal.getSoilMoisture(),pal.getDayLight());
  
  delay(2000);
}

void makePost(int temperature, int humidity, int soil, int daylight){
      // This needs to change when we have multiple values
    Serial.println("making POST request");
    client.beginRequest();
    client.post("/?temp=" + String(temperature) + "&hum="+String(humidity)+ "&soil="+ String(soil)+ "&daylight="+ String(daylight)); // needs to be this format
    client.endRequest();
    
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();


    if(response == "Water"){
        pal.waterPlant();
        Serial.println("Watering the plant....");
    }

    if(response == "Mist"){
        pal.mistPlant();
        Serial.println("Misting the plant....");
        response = "Do Nothing";
    }

    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);

    Serial.println("Wait 2 seconds");
    delay(2000);
}

void connectToWifi(){
    delay(1000);

    WiFi.mode(WIFI_STA); // Put the wifi code in a functino - init
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}
