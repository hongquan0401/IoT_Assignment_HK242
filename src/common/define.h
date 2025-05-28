#ifndef _DEFINE_H_
#define _DEFINE_H_
// SPI PORT
#define MISO 19
#define MOSI 23
#define SCK 18
#define SDA 5
#define RST 22

// UART COMMON
#define UART_RXD_DEBUG_PIN 16
#define UART_TXD_DEBUG_PIN 17
#define UART_DEFAUT_BAUDRATE 9600

// DEFINE MQTT
#define MQTT_MAX_PACKAGE_SIZE 1024
#define MQTT_MAX_BUFFER_SIZE 128

#define MQTT_SERVER "app.coreiot.io"
#define MQTT_PORT 1883
#define MQTT_USERS "pole_1"
#define MQTT_PASSWORD "16012003"

#define MQTT_FEED_NOTHING ""
// #define MQTT_FEED_POLE_02 "BK_SmartPole/feeds/V20"
#define MQTT_GATEWAY_TELEMETRY_TOPIC "v1/gateway/telemetry"
#define MQTT_GATEWAY_ATTRIBUTES_TOPIC "v1/gateway/attributes"
#define MQTT_REQUEST_TOPIC "v1/devices/me/rpc/request/+"

// DEFINE WIFI AP
#define WIFI_SSID "Fatcat"
#define WIFI_PASS "lnss2136"

// TOKEN GATEWAY
#define TOKEN_GATEWAY "I4pP9auSdf6KzYU0PmWV"
#endif