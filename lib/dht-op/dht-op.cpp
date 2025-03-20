#include "dht-op.h"

DHT dht(DHTPIN, DHTTYPE);
float humid = 0.0;
float temp = 0.0;

void setupDHT(void *pvParameters){
    // Initialize DHT11
    dht.begin();
    Serial.println("DHT connected!");
    vTaskDelete(NULL);
}

void updateDHT(void *pvParameters){
    while(1){
        humid = dht.readHumidity();
        temp = dht.readTemperature();
        if (isnan(humid) || isnan(temp)) {
            Serial.println(F("Reading from DHT sensor FAILED!"));
        }
        vTaskDelay(5110);
    }
}
  
void dispHumid() {
    Serial.print("Humidity: ");
    Serial.print(humid, 1);
    Serial.println(" %");
}
  
void dispTemp() {
    Serial.print("Temperature: ");
    Serial.print(temp, 1);
    Serial.println(" °C");
}

float getTemp(){
    return temp;
}

float getHumid(){
    return humid;
}