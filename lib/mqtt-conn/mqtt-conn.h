#ifndef MQTT_CONN_H
#define MQTT_CONN_H
#pragma once

#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include "dht-op.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#ifdef ESP32
#include <WiFi.h>
#endif // ESP32
#endif // ESP8266

#define ENCRYPTED false

void wifiTask(void *pvParameters);
void InitWiFi();
bool WiFireconnect();

void initThingsBoard();
void sendTBData();

#endif /*MQTT_CONN_H*/