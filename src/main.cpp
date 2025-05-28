#include "globals.h"

void setup() {
  // put your setup code here, to run once:
   Serial.begin(UART_DEFAUT_BAUDRATE, SERIAL_8N1, UART_RXD_DEBUG_PIN, UART_TXD_DEBUG_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
}