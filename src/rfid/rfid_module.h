#ifndef RFID_MODULE_H
#define RFID_MODULE_H

#include <globals.h>

void initRFID();
String readUID();
bool isUIDStored(const String &uid);
void storeUID(const String &uid);

#endif
