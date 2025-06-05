#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "dht-op.h"
#include "tb-op.hpp"
#include "led-op.h"
#include "dust-op.h"

void setup() {
  Serial.begin(115200);
  delay(2000);

  xTaskCreate(wifiTask, "init wifi", 6 * 1024, nullptr, 0, nullptr);
  xTaskCreate(initTBtask, "init CoreIoT", 6 * 1024, nullptr, 1, nullptr);

  xTaskCreate(initLED, "start LED", 3 * 1024, NULL, 4, NULL);
  xTaskCreate(onLED, "led state on", 6 * 1024, NULL, 8, NULL);

  xTaskCreate(setupDHT, "DHT initial setup", 4096, NULL, 1, NULL);
  xTaskCreate(initDustSensor, "Dust sensor initial setup", 4096, NULL, 1, NULL);

  xTaskCreate(OTAupdate, "Update firmware", 50 * 1024, NULL, 0, NULL);
  
  startTasks();
  vTaskStartScheduler;
}

void loop() {
  //exists
}