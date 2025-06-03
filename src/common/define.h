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

#define MQTT_FEED_NOTHING ""
// #define MQTT_FEED_POLE_02 "BK_SmartPole/feeds/V20"
#define MQTT_GATEWAY_TELEMETRY_TOPIC "v1/gateway/telemetry"
#define MQTT_GATEWAY_ATTRIBUTES_TOPIC "v1/gateway/attributes"
#define MQTT_REQUEST_TOPIC "v1/devices/me/rpc/request/+"

// DEFINE WIFI AP
#define WIFI_SSID "Fatcat"
#define WIFI_PASS "lnss2136"

// DEFINE DELAY TIME
#define delay_connect_wifi 5000
#define delay_mqtt 100
#define delay_toggle_led 1000
#define delay_read_adc 1000
#define I2C_clockRate 400000
#define delay_DHT20_read 5000
#define delay_connect 1000
#define led_callback 500

// MQTT
#define MQTT_PORT 1883
// #define MQTT_SERVER "app.coreiot.io"
#define MQTT_SERVER "demo.thingsboard.io"
#define delay_mqtt 100
#define MQTT_TELEMETRY "v1/devices/me/telemetry"
#define MQTT_ATTRIBUTES "v1/devices/me/rpc/response"
#define MQTT_SUBCRIBE_TOPIC "v1/devices/me/rpc/request/+"
#define MAX_MSG_SIZE 1024U
#define CLIENT_ID "xxxx"

// TOKEN GATEWAY
#define TOKEN "PmSBDmKS9x2p3Xy9zMbP"

// APP SCRIPT
#define APP_SCRIPT_URL "/macros/s/AKfycbwFaIbANEpqM4q88uKiFOMPTBhdV5r3WO2HMRh1-np2MuYOyS7UmEKqTO2ul6eUTOBvZg/exec"
#define HOST_URL "script.google.com"
#endif