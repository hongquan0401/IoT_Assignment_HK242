#include "google_sheet.h"
#include <WiFiClientSecure.h>
void sendToGoogleSheet(const String &uid)
{
    WiFiClientSecure client;
    client.setInsecure();

    if (!client.connect(HOST_URL, 443))
    {
        Serial.println("Cannot connect to Google Script");
        return;
    }

    StaticJsonDocument<200> doc;
    doc["uid"] = uid;
    String payload;
    serializeJson(doc, payload);

    client.println("POST " + String(APP_SCRIPT_URL) + " HTTP/1.1");
    client.println("Host: " + String(HOST_URL));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + payload.length());
    client.println();
    client.println(payload);

    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
            break;
    }

    String response = client.readStringUntil('\n');
    Serial.println("📨 Google Response: " + response);

    StaticJsonDocument<200> resDoc;
    if (deserializeJson(resDoc, response) == DeserializationError::Ok)
    {
        if (resDoc["status"] == "allowed")
        {
            Serial.println("🟢 Welcome " + String(resDoc["name"].as<const char *>()));
        }
        else
        {
            Serial.println("Denied");
        }
    }
}

void checkUIDWithGoogleSheet(const String &uid)
{
    WiFiClientSecure client;
    client.setInsecure();

    if (!client.connect(HOST_URL, 443))
    {
        Serial.println("Cannot connect to Google Script");
        return;
    }

    // Prepare JSON payload
    StaticJsonDocument<200> doc;
    doc["uid"] = uid;
    String payload;
    serializeJson(doc, payload);

    // Send HTTP POST
    client.println("POST " + String(APP_SCRIPT_URL) + " HTTP/1.1");
    client.println("Host: " + String(HOST_URL));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + payload.length());
    client.println();
    client.println(payload);

    // Wait for response
    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
            break;
    }

    String response = client.readStringUntil('\n');
    Serial.println("📨 Google Response: " + response);

    // Parse response
    StaticJsonDocument<200> resDoc;
    if (deserializeJson(resDoc, response) == DeserializationError::Ok)
    {
        String status = resDoc["status"];
        String name = resDoc["name"] | "Unknown";

        if (status == "allowed")
        {
            Serial.println("Access granted to: " + name);
        }
        else
        {
            Serial.println("Access denied");
        }
    }
    else
    {
        Serial.println("Failed to parse response");
    }
}