#include "google_sheet.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
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

// void checkUIDWithGoogleSheet(const String &uid)
// {
//     WiFiClientSecure client;
//     client.setInsecure();

//     if (!client.connect(HOST_URL, 443))
//     {
//         Serial.println("Cannot connect to Google Script");
//         return;
//     }

//     // Prepare JSON payload
//     StaticJsonDocument<200> doc;
//     doc["uid"] = uid;
//     String payload;
//     serializeJson(doc, payload);

//     // Send HTTP POST
//     client.println("POST " + String(APP_SCRIPT_URL) + " HTTP/1.1");
//     client.println("Host: " + String(HOST_URL));
//     client.println("Content-Type: application/json");
//     client.println("Content-Length: " + payload.length());
//     client.println();
//     client.println(payload);

//     // Wait for response
//     while (client.connected())
//     {
//         String line = client.readStringUntil('\n');
//         if (line == "\r")
//             break;
//     }

//     // String response = client.readStringUntil('\n');
//     String response = client.readString();
//     Serial.println("📨 Google Response: " + response);

//     // Parse response
//     StaticJsonDocument<200> resDoc;
//     if (deserializeJson(resDoc, response) == DeserializationError::Ok)
//     {
//         String status = resDoc["status"];
//         String name = resDoc["name"] | "Unknown";

//         if (status == "allowed")
//         {
//             Serial.println("Access granted to: " + name);
//         }
//         else
//         {
//             Serial.println("Access denied");
//         }
//     }
//     else
//     {
//         Serial.println("Failed to parse response");
//     }
// }

// void checkUIDWithGoogleSheet(const String &uid)
// {
//     WiFiClientSecure client;
//     client.setInsecure();

//     if (!client.connect("script.google.com", 443))
//     {
//         Serial.println("❌ Cannot connect to Google Script");
//         return;
//     }

//     // Create JSON body
//     StaticJsonDocument<200> doc;
//     doc["uid"] = uid;
//     String payload;
//     serializeJson(doc, payload);

//     // Build HTTP request manually (CORRECT FORMAT)
//     client.println("POST /macros/s/AKfycbwFaIbANEpqM4q88uKiFOMPTBhdV5r3WO2HMRh1-np2MuYOyS7UmEKqTO2ul6eUTOBvZg/exec HTTP/1.1");
//     client.println("Host: script.google.com");
//     client.println("Connection: close"); // <-- THIS IS IMPORTANT
//     client.println("Content-Type: application/json");
//     client.print("Content-Length: ");
//     client.println(payload.length());
//     client.println(); // <---- EMPTY LINE REQUIRED
//     client.println(payload);
//     Serial.println("📦 Payload: " + payload);
//     // Read full response (not just one line!)
//     String response = client.readString();
//     Serial.println("📨 Google Response:\n" + response);

//     StaticJsonDocument<200> resDoc;
//     DeserializationError err = deserializeJson(resDoc, response);
//     if (err)
//     {
//         Serial.println("❌ JSON Parse Error: " + String(err.c_str()));
//         return;
//     }

//     String status = resDoc["status"] | "";
//     String name = resDoc["name"] | "Unknown";

//     if (status == "allowed")
//     {
//         Serial.println("✅ Access granted to: " + name);
//     }
//     else if (status == "denied")
//     {
//         Serial.println("❌ Access denied");
//     }
//     else
//     {
//         Serial.println("🤷 Unknown response");
//     }
// }

void checkUIDWithGoogleSheet(const String &uid)
{
    HTTPClient http;
    String url = "https://script.google.com/macros/s/AKfycbwFaIbANEpqM4q88uKiFOMPTBhdV5r3WO2HMRh1-np2MuYOyS7UmEKqTO2ul6eUTOBvZg/exec";

    // Start HTTPS connection
    http.begin(url);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS); // Required to follow 302
    http.addHeader("Content-Type", "application/json");     // Must be exactly this

    // Format JSON body
    String payload = "{\"uid\":\"" + uid + "\"}";
    Serial.println("Payload: " + payload);

    // Send POST request
    int httpResponseCode = http.POST(payload);

    // Handle response
    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String response = http.getString();
        Serial.println("Response:");
        Serial.println(response);
    }
    else
    {
        Serial.print("POST failed. Error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}
