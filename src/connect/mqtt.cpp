#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

/*<=================================Private Function=================================>*/

/*<=================================Private Function=================================>*/

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("[MQTT] Message arrived: ");
    Serial.println(topic);
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("[MQTT] Payload: ");
    Serial.println(message);
}

void reconnectMQTT()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");

        String clientId = CLIENT_ID;
        if (client.connect(clientId.c_str(), TOKEN, ""))
        {
            Serial.println("MQTT Connected");
            Serial.println("Start");
        }
        else
        {
            Serial.print("MQTT connection failed, rc=");
            Serial.println(String(client.state()));
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void mqtt_init()
{
    xTaskCreate(taskMQTT, "TaskMQTT", 4096, NULL, 1, NULL);
}

/*<=================================Public Function=================================>*/
bool publishData(String feedName, String message)
{
    String topic = feedName;
    Serial.print("Publishing to topic: ");
    Serial.print(feedName + " ");
    Serial.print("Status: ");

    if (client.publish(topic.c_str(), message.c_str(), 1))
    {
        Serial.println("Success!: " + message);
        return 1;
    }
    Serial.println("Failed!: " + message);
    return 0;
}

void taskMQTT(void *pvParameters)
{
    // Wait connecting Wifi
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
    }

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setKeepAlive(30);
    client.setCallback(callback);

    while (true)
    {
        if (!client.connected())
        {
            reconnectMQTT();
        }

        client.loop();
        vTaskDelay(delay_mqtt / portTICK_PERIOD_MS);
    }
}