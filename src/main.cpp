#include "globals.h"
WiFiClientSecure client;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(UART_DEFAUT_BAUDRATE, SERIAL_8N1);
  initRFID();
  Serial.println("Log:");
  delay(2000);
  connect_init();
  Serial.println("Ready to scan RFID cards...");
}

void loop()
{
  String uid = readUID();
  if (uid != "")
  {
    Serial.println("Scanned UID: " + uid);
    checkUIDWithGoogleSheet(uid);
    delay(2000);
  }
}