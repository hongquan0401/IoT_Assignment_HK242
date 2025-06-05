#include "tb-op.hpp"

#if ENCRYPTED
WiFiClientSecure espClient;
#else
WiFiClient espClient;
#endif

//----------------FUNCTIONS----------------

OTA_Firmware_Update<> ota;
const std::array<IAPI_Implementation*, 1U> apis = {
    &ota
};
    
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_RECEIVE_SIZE, MAX_MESSAGE_SEND_SIZE, Default_Max_Stack_Size, apis);

Espressif_Updater<> updater;
bool currentFWSent = false;
bool updateRequestSent = false;

bool wifiStarted = false;
void InitWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi.");
    while (WiFi.status() != WL_CONNECTED) {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      Serial.print(".");
    }
    wifiStarted = true;
    Serial.println(" ");
    Serial.print("WiFi connected @ IP address: ");
    // Print ESP32 Local IP Address
    vTaskDelay(500);
    Serial.println(WiFi.localIP());
    
    vTaskDelete(NULL);  // Delete the task when done
}

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

void WiFiReconnect(void *pvParameters){
    while (1){
        if (WiFi.status() != WL_CONNECTED && wifiStarted) {
            Serial.println("WiFi DISCONNECTED! Trying to reconnect.");

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

            if(WiFi.status() == WL_CONNECTED){
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
        }
        vTaskDelay(510);
    }
}

void initTBtask(void *pvParameters){
    while (1){
        if(WiFi.status() == WL_CONNECTED){
            if (!tb.connected()) {
                Serial.printf("Connecting to: (%s) with token (%s)\n", THINGSBOARD_SERVER, TOKEN);
                if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
                    Serial.println("Failed to connect");
                    return;
                }else{
                    Serial.println("CoreIoT server connected!");
                }
            }
            vTaskDelete(nullptr);
        }
        vTaskDelay(500);
    }
}

void sendTBData(void *pvParameters){
    while (1){
        if(!(isnan(getTemp())) && !(isnan(getHumid()))){
            // Send temperature to the CoreIoT server
            if(tb.sendTelemetryData<int>("temperature", getTemp())){
                Serial.println("Temperature sent to CoreIoT successfullly!");
                dispTemp();
            }else{
                Serial.println("Temperature FAILED to send.");
            }

            // Send temperature to the CoreIoT server
            if(tb.sendTelemetryData<int>("humidity", getHumid())){
                Serial.println("Humidity sent to CoreIoT successfullly!");
                dispHumid();
            }else{
                Serial.println("Humidity FAILED to send.");
            }

            if(tb.sendTelemetryData<int>("pm2.5", getPM2p5())){
                Serial.println("PM 2.5 Dust density sent to CoreIoT successfullly!");
                dispPM2p5();
            }else{
                Serial.println("PM 2.5 Dust density FAILED to send.");
            }
        }
        Serial.println("-----------------------------------------");
        vTaskDelay(5220);
    }
}

void update_starting_callback() {
  // Nothing to do
}
void finished_callback(const bool & success) {
  if (success) {
    Serial.println("Done, Reboot now");
    esp_restart();
    return;
  }
  Serial.println("Downloading firmware failed");
}

void progress_callback(const size_t & current, const size_t & total) {
  Serial.printf("Progress %.2f%%\n", static_cast<float>(current * 100U) / total);
}

void OTAupdate (void *pvParameters) {
  while (1) {
    if (!currentFWSent) {
      currentFWSent = ota.Firmware_Send_Info(CURRENT_FIRMWARE_TITLE, CURRENT_FIRMWARE_VERSION);
    }
  
    if (!updateRequestSent) {
      Serial.println("Firwmare Update...");
      const OTA_Update_Callback callback(CURRENT_FIRMWARE_TITLE, CURRENT_FIRMWARE_VERSION, &updater,
                                        &finished_callback, &progress_callback, &update_starting_callback,
                                        FIRMWARE_FAILURE_RETRIES, FIRMWARE_PACKET_SIZE);
      updateRequestSent = ota.Start_Firmware_Update(callback);
    }
  
    tb.loop();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

}