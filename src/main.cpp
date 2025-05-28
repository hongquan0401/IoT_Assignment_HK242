#include "globals.h"

void setup() {
  // put your setup code here, to run once:
   Serial.begin(UART_DEFAUT_BAUDRATE, SERIAL_8N1);
   Serial.println("Log:");
   delay(2000);
   connect_init();
}

void loop() {
  // put your main code here, to run repeatedly:
}