#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>

// Define module types
enum ModuleType { NRF24_1, NRF24_2, APC220 };

class Radio {
private:
  ModuleType moduleType;
  void* radioModule = nullptr;  // Generic pointer for NRF24L01 or APC220

  // NRF24L01 uses 5-byte addresses (fixed size to avoid excess memory usage)
const uint64_t address[2][10] = {
    { 0xAABBCCDDEE, 0x1122334455, 0x66778899AA, 0xBBCCDDEEFF, 0x123456789A,
      0xABCDEF1234, 0xDEADBEEF12, 0xFEEDFACE01, 0xCAFEBABE02, 0xF00DF00D03 },
    { 0x0A1B2C3D4E, 0x5F6A7B8C9D, 0xE1F2030405, 0x66778899FF, 0x99AABBCCDD,
      0xDEADFADED1, 0xFACEB00C12, 0xBABEC0DE34, 0xC0FFEE1234, 0xBEEFC0DE56 }
};


  const uint16_t baseFrequency = 432;  // + channel * 5

  // Internal initialization functions
  bool begin(uint8_t rxPin, uint8_t txPin, uint8_t setPin, uint8_t channel);
  bool begin(uint8_t cePin, uint8_t csnPin, uint8_t channel);

public:
  Radio(ModuleType module);

  // Templated begin() for compile-time channel validation
  template<uint8_t channel>
  bool begin(uint8_t cePin, uint8_t csnPin) {
    static_assert(channel >= 1 && channel <= 10, "Channel must be between 1 and 10");
    return begin(cePin, csnPin, channel - 1);
  }

  template<uint8_t channel>
  bool begin(uint8_t rxPin, uint8_t txPin, uint8_t setPin) {
    static_assert(channel >= 1 && channel <= 10, "Channel must be between 1 and 10");
    return begin(rxPin, txPin, setPin, channel - 1);
  }

  void write(String data);
  bool available();
  String read();
  
  ~Radio();
};

#endif
