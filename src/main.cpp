#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"
#include <Adafruit_NeoPixel.h>
#include "dht-op.h"
#include "mqtt-conn.h"

// Onboard RGB LED
#define LED_PIN 48
#define NUMPIXEL 1

uint8_t ledState = 0; // Stores LED state
Adafruit_NeoPixel pixels(NUMPIXEL, LED_PIN, NEO_GRB + NEO_KHZ800);

void blinkLED(void *pvParameters) {
  pixels.clear();
  while(true){
    if(ledState){
      ledState = 0;
      pixels.setPixelColor(0, pixels.Color(150, 150, 150));
      pixels.show();
    }else{
      ledState++;
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
    }
    vTaskDelay(1500);
  }
}

void setup() {
  Serial.begin(115200);
  pixels.begin();
  
  xTaskCreate(wifiTask, "init wifi", 6 * 1024, nullptr, 3, nullptr);
  xTaskCreate(initTBtask, "init CoreIoT", 6 * 1024, nullptr, 2, nullptr);
  xTaskCreate(setupDHT, "DHT initial setup", 4096, NULL, 1, NULL);

  xTaskCreate(blinkLED, "blink LED", 3 * 1024, NULL, 1, NULL);
  xTaskCreate(updateDHT, "Update DHT readings", 6 * 1024, NULL, 3, NULL);
  xTaskCreate(sendTBData, "Send data to CoreIoT", 8 * 1024, NULL, 2, NULL);
  vTaskStartScheduler;
}

void loop() {
  //exists
}