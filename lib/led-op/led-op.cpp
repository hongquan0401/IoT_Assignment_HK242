#include "led-op.h"
uint8_t ledState = 0; // Stores LED state
Adafruit_NeoPixel pixels(NUMPIXEL, LED_PIN, NEO_GRB + NEO_KHZ800);

void initLED(void* pvParameters){
    pixels.begin();
    pixels.clear();
    ledState = 0;
    vTaskDelete(nullptr);
}

void blinkLED(void *pvParameters) {
    pixels.clear();
    while(true){
        if(ledState){
            ledState = 0;
            pixels.setPixelColor(0, pixels.Color(69, 69, 69));
            pixels.show();
        }else{
            ledState++;
            pixels.setPixelColor(0, pixels.Color(0, 0, 0));
            pixels.show();
        }
        vTaskDelay(1500);
    }
}
  
void onLED(void *pvParameters){
    while(1){
        pixels.clear();
        pixels.setPixelColor(0, pixels.Color(0, 50, 0));
        pixels.show();
        vTaskDelay(10000);
    }
}

void offLED(void *pvParameters){
    while(1){
        pixels.clear();
        pixels.setPixelColor(0, pixels.Color(50, 0, 0));
        pixels.show();
        vTaskDelay(10000);
    }
}