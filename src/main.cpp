#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "dht-op.h"
#include "mqtt-conn.h"
#include "led-op.h"

void setup() {
  Serial.begin(115200);

  xTaskCreate(wifiTask, "init wifi", 6 * 1024, nullptr, 3, nullptr);
  xTaskCreate(initTBtask, "init CoreIoT", 6 * 1024, nullptr, 2, nullptr);
  xTaskCreate(setupDHT, "DHT initial setup", 4096, NULL, 1, NULL);
  xTaskCreate(initLED, "start LED", 3 * 1024, NULL, 1, NULL);

  xTaskCreate(onLED, "led state on", 6 * 1024, NULL, 1, NULL);
  xTaskCreate(updateDHT, "Update DHT readings", 6 * 1024, NULL, 3, NULL);
  xTaskCreate(sendTBData, "Send data to CoreIoT", 8 * 1024, NULL, 2, NULL);
  vTaskStartScheduler;
}

void loop() {
  //exists
}