#include "Melopero_RV3028.h"

Melopero_RV3028 rtc;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // First initialize and create the rtc device
  Wire.begin();
  rtc.initI2C();
  
  // Setup the device to use the EEPROM memory
  rtc.useEEPROM();
 
  // user eeprom address space : [0x00 - 0x2A]
  // configuration eeprom address space : [0x30 - 0x37]
  uint8_t eepromRegAddress = 0x11; // example 
  uint8_t value = 0x42; // example
  rtc.writeEEPROMRegister(eepromRegAddress, value);

  Serial.print("Writing value: ");
  Serial.print(value, HEX);
  Serial.print(" to eeprom register at address: ");
  Serial.println(eepromRegAddress, HEX);

  delay(10);

  Serial.print("Reading eeprom register at address: ");
  Serial.println(eepromRegAddress, HEX);
  
  uint8_t readValue = rtc.readEEPROMRegister(eepromRegAddress);

  Serial.print("Value: ");
  Serial.println(readValue, HEX);
}

void loop() {
  
}