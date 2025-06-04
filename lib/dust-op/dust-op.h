#ifndef DUST_OP_H
#define DUST_OP_H
#pragma once

#include <GP2YDustSensor.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SHARP_LED_PIN 18  // Sharp Dust/particle sensor Led Pin
#define SHARP_VO_PIN 17   // Sharp Dust/particle analog out pin used for reading
#define SHARP_BASELINE 0.044
#define SHARP_CLBR_LVL 1.1

void initDustSensor(void* pvParam);
void updateDustSensor(void* pvParam);

uint16_t getPM2p5();
void dispPM2p5();

#endif /*DUST_OP_H*/