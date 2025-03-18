#include "mqtt-conn.h"

//WiFi configuration
constexpr char WIFI_SSID[] = "DAMA-LAPTOP";
constexpr char WIFI_PASSWORD[] = "111111119";
//CoreIOT MQTT configuration
constexpr char TOKEN[] = "unhqjrXzucOqfQR07vY5";
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";

//THINGSBOARD configuration
#if ENCRYPTED
constexpr uint16_t THINGSBOARD_PORT = 8883U;
#else
constexpr uint16_t THINGSBOARD_PORT = 1883U;
#endif
constexpr uint16_t MAX_MESSAGE_SEND_SIZE = 256U;
constexpr uint16_t MAX_MESSAGE_RECEIVE_SIZE = 256U;

#if ENCRYPTED
WiFiClientSecure espClient;
#else
WiFiClient espClient;
#endif
    
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_RECEIVE_SIZE, MAX_MESSAGE_SEND_SIZE);

void wifiTask(void *pvParameters) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi.");
    while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      Serial.print(".");
    }
    Serial.println(" ");
    Serial.print("WiFi connected @ IP address: ");
    // Print ESP32 Local IP Address
    vTaskDelay(500);
    Serial.println(WiFi.localIP());
    vTaskDelete(NULL);  // Delete the task when done
}

void InitWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi.");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println(" ");
    Serial.print("WiFi connected @ IP address: ");
    // Print ESP32 Local IP Address
    delay(500);
    Serial.println(WiFi.localIP());
}

bool WiFireconnect(){
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    InitWiFi();
    return true;
}

StaticJsonDocument<256> doc;
char buffer[256];
size_t len;

void initThingsBoard(){
    if (!tb.connected()) {
        Serial.printf("Connecting to: (%s) with token (%s)\n", THINGSBOARD_SERVER, TOKEN);
        if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
            Serial.println("Failed to connect");
            return;
        }else{
            Serial.println("CoreIoT server connected!");
        }
    }
}

void sendTBData(){
    tb.sendTelemetryData<float>("temperature", getTemp());
    tb.sendTelemetryData<float>("humidity", getHumid());
}

