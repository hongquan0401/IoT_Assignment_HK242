#ifndef _WIFI_H_
#define _WIFI_H_
#include <globals.h>

extern WiFiClient espClient;
extern PubSubClient client;

// MQTT function
void reconnectMQTT();
void taskMQTT(void* pvParams);
bool publishData(const String &feedName, String message);
bool subcriptData();

// Connect Wifi function
void taskWifi(void* pvParams);

#endif