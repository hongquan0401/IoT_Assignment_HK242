#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "dht-op.h"
#include "tb-op.hpp"
#include "led-op.h"
#include "dust-op.h"

void setup() {
  Serial.begin(115200);

  xTaskCreate(wifiTask, "init wifi", 6 * 1024, nullptr, 3, nullptr);
  xTaskCreate(initTBtask, "init CoreIoT", 6 * 1024, nullptr, 2, nullptr);
  xTaskCreate(setupDHT, "DHT initial setup", 4096, NULL, 1, NULL);
  xTaskCreate(initDustSensor, "Dust sensor initial setup", 4096, NULL, 1, NULL);
  xTaskCreate(initLED, "start LED", 3 * 1024, NULL, 1, NULL);

  xTaskCreate(onLED, "led state on", 6 * 1024, NULL, 1, NULL);
  xTaskCreate(updateDHT, "Update DHT readings", 6 * 1024, NULL, 3, NULL);
  xTaskCreate(updateDustSensor, "Update dust readings", 6 * 1024, NULL, 3, NULL);
  xTaskCreate(sendTBData, "Send data to CoreIoT", 8 * 1024, NULL, 2, NULL);
  xTaskCreate(OTAupdate, "OTA update", 2048 * 20, NULL, 2, NULL);
  vTaskStartScheduler;
}

void loop() {
  //exists
}