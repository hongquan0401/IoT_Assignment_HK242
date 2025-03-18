#ifndef DHT_OP_H
#define DHT_OP_H
#pragma once

#include "DHT.h"

// DHT sensor configuration
#define DHTPIN 5       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22

void setupDHT(void *pvParameters);
void updateDHT(void *pvParameters);

float getTemp();
float getHumid();

void dispHumid();
void dispTemp();

#endif /*DHT_OP_H*/