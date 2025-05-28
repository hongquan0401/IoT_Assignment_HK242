#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <esp_task_wdt.h>
#include <vector>
#include <esp32-hal-ledc.h>
#include <DHT20.h>

// include common files
#include "../src/common/define.h"

// include connect
#include "../src/connect/wifi.h"

// include device
// #include "../src/device/device_init.h"

// include task
// #include "../src/task/task_init.h"

// include json file
// #include "../src/utils/on_off_json.h"
// #include "../src/utils/print_debug.h"
// #include "../src/utils/light_control.h"
// #include "utils/basic_queue.h"
// #include "utils/loraTaskCallback.h"

// include hal file
// #include "../src/hal/watch_dog.h"

#endif /* GLOBAL_H */