#ifndef TB_OP_H
#define TB_OP_H
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ArduinoJson.h> 
#include <OTA_Firmware_Update.h>
#include <Shared_Attribute_Update.h>
#include <Attribute_Request.h>
#include <Espressif_Updater.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include <PubSubClient.h>

#include "dht-op.h"
#include "dust-op.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#ifdef ESP32
#include <WiFi.h>
#endif // ESP32
#endif // ESP8266

#define ENCRYPTED false

//WiFi configuration
constexpr char WIFI_SSID[] = "DAMA-LAPTOP";
constexpr char WIFI_PASSWORD[] = "111111119";
//CoreIOT MQTT configuration
constexpr char TOKEN[] = "unhqjrXzucOqfQR07vY5";
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";
//THINGSBOARD configuration
#if ENCRYPTED
constexpr uint16_t THINGSBOARD_PORT = 8883U;
#else
constexpr uint16_t THINGSBOARD_PORT = 1883U;
#endif
// Size of each firmware chunck downloaded over MQTT,
// increased packet size, might increase download speed
constexpr uint16_t FIRMWARE_PACKET_SIZE = 4096U;
constexpr uint16_t MAX_MESSAGE_SEND_SIZE = FIRMWARE_PACKET_SIZE + 50U;
constexpr uint16_t MAX_MESSAGE_RECEIVE_SIZE = FIRMWARE_PACKET_SIZE + 50U;
// OTA update parameter
constexpr char CURRENT_FIRMWARE_TITLE[] = "ESP32_OTA";
constexpr char CURRENT_FIRMWARE_VERSION[] = "1.0";
// Maximum amount of retries we attempt to download each firmware chunk over MQTT
constexpr uint8_t FIRMWARE_FAILURE_RETRIES = 12U;
constexpr uint64_t REQUEST_TIMEOUT_MICROSECONDS = 10000U * 1000U;

void wifiTask(void *pvParameters);
void initTBtask(void *pvParameters);

void WiFiReconnect(void *pvParameters);

void sendTBData(void *pvParameters);

void OTAupdate (void *pvParameters);

void startTasks();

#endif /*MQTT_CONN_H*/