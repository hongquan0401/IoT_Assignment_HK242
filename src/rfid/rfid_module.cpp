#include "rfid_module.h"

// MFRC522 rfid(SDA, RST);

// void initRFID()
// {
//     SPI.begin(SCK, MISO, MOSI, SDA);
//     rfid.PCD_Init();
// }

// String readUIDs()
// {
//     if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
//         return "";

//     String uid = "";
//     for (byte i = 0; i < rfid.uid.size; i++)
//     {
//         uid += String(rfid.uid.uidByte[i], HEX);
//     }
//     uid.toUpperCase();

//     rfid.PICC_HaltA();
//     rfid.PCD_StopCrypto1();
//     Serial.print("readUID\n");
//     return uid;
// }
