#ifndef LED_OP_
#define LED_OP_
#pragma once

#include <Adafruit_NeoPixel.h>

// Onboard RGB LED
#define LED_PIN 48
#define NUMPIXEL 1

void initLED(void* pvParameters);
void blinkLED(void *pvParameters);
void onLED(void *pvParameters);
void offLED(void *pvParameters);

#endif /*LED_OP_*/