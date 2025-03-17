#include "SoftwareSerial.h"
#include "Radio.h"

// Constructor initializes the radio module type
Radio::Radio(ModuleType module) {
  moduleType = module;
}

// Destructor - Prevents memory leaks by freeing allocated memory
Radio::~Radio() {
  if (radioModule) {
    switch (moduleType) {
      case NRF24_1:
      case NRF24_2:
        delete static_cast<RF24*>(radioModule);  // Free NRF24 module memory
        break;
      case APC220:
        delete static_cast<SoftwareSerial*>(radioModule);  // Free APC220 memory
        break;
    }
    radioModule = nullptr;  // Avoid dangling pointers
  }
}

// Initialize the NRF24 module with CE and CSN pins and a communication channel
bool Radio::begin(uint8_t cePin, uint8_t csnPin, uint8_t channel) {
  if (radioModule)
    delete static_cast<RF24*>(radioModule);  // Prevent memory leak by deleting previous allocation

  switch (moduleType) {
    case NRF24_1:
      radioModule = new RF24(cePin, csnPin);
      if (!static_cast<RF24*>(radioModule)->begin())
        return false;
      static_cast<RF24*>(radioModule)->setPALevel(RF24_PA_MAX);
      static_cast<RF24*>(radioModule)->openReadingPipe(1, address[0][channel]);  // Read from pipe 0
      static_cast<RF24*>(radioModule)->openWritingPipe(address[1][channel]);     // Write to pipe 1
      static_cast<RF24*>(radioModule)->startListening();                         // Start receiving mode
      return true;
    case NRF24_2:
      radioModule = new RF24(cePin, csnPin);
      if (!static_cast<RF24*>(radioModule)->begin())
        return false;
      static_cast<RF24*>(radioModule)->setPALevel(RF24_PA_MAX);
      static_cast<RF24*>(radioModule)->openReadingPipe(1, address[1][channel]);  // Read from pipe 1
      static_cast<RF24*>(radioModule)->openWritingPipe(address[0][channel]);     // Write to pipe 0
      static_cast<RF24*>(radioModule)->startListening();                         // Start receiving mode
      return true;

    case APC220:
      Serial.println("Radio module is set to APC220");
      return false;  // APC220 is not initialized here

    default:
      Serial.println("Radio module is not set");
      return false;
  }
}

// Initialize APC220 module with RX, TX, and SET pins, and configure frequency
bool Radio::begin(uint8_t rxPin, uint8_t txPin, uint8_t setPin, uint8_t channel) {
  if (radioModule)
    delete static_cast<SoftwareSerial*>(radioModule);  // Prevent memory leaks

  radioModule = new SoftwareSerial(txPin, rxPin);
  pinMode(setPin, OUTPUT);
  digitalWrite(setPin, HIGH);  // Put APC220 back in operation mode
  delay(50);

  static_cast<SoftwareSerial*>(radioModule)->begin(9600);
  delay(50);

  digitalWrite(setPin, LOW);
  delay(50);
  static_cast<SoftwareSerial*>(radioModule)->println("WR " + String(baseFrequency + channel * 5) + "000 3 9 3 0");
  delay(50);

  // Wait for response with a timeout
  unsigned long start = millis();
  while (!static_cast<SoftwareSerial*>(radioModule)->available()) {
    if (millis() - start > 1000) {
      Serial.println("APC220 programming timed out");
      delete static_cast<SoftwareSerial*>(radioModule);
      radioModule = nullptr;
      return false;  // Timeout after 1 second
    }
  }

  // Read response
  while (static_cast<SoftwareSerial*>(radioModule)->available()) {
    Serial.write(static_cast<SoftwareSerial*>(radioModule)->read());
  }

  digitalWrite(setPin, HIGH);  // Put APC220 back in operation mode
  delay(100);
  return true;
}

// Check if data is available in the selected radio module
bool Radio::available() {
  if (!radioModule)
    return false;
  return (moduleType == APC220)
           ? static_cast<SoftwareSerial*>(radioModule)->available()
           : static_cast<RF24*>(radioModule)->available();
}

// Read data from the radio module
String Radio::read() {

  if (moduleType == APC220) {

    String msg = "";

    for (int i = 0; i <= 32; i++) {
      while (!static_cast<SoftwareSerial*>(radioModule)->available())
        ;
      char in = static_cast<SoftwareSerial*>(radioModule)->read();
      if (in == '\0') {  // Stop when null terminator is received
        static_cast<SoftwareSerial*>(radioModule)->read();
        return msg;  // Convert to Arduino String
      }
      msg += in;
    }

    Serial.println("There was no Null Terminator found.");
    Serial.print("Read data is: ");
    Serial.println(msg);
    return msg;

  } else if (moduleType == NRF24_1 || moduleType == NRF24_2) {
    char buffer[32] = "";
    static_cast<RF24*>(radioModule)->read(&buffer, sizeof(buffer));
    return String(buffer);
  } else {
    Serial.println("Radio module is not set");
    return "";
  }
}

// Send data using the selected radio module
void Radio::write(String data) {
  if (moduleType == APC220) {
    for (int i = 0; i <= data.length(); i++)
      static_cast<SoftwareSerial*>(radioModule)->write(data[i]);
  } else if (moduleType == NRF24_1 || moduleType == NRF24_2) {
    static_cast<RF24*>(radioModule)->stopListening();  // Switch to send mode
    char buffer[32];
    data.toCharArray(buffer, data.length() + 1);                        // Convert String to char array
    static_cast<RF24*>(radioModule)->write(buffer, data.length() + 1);  // Send data
    static_cast<RF24*>(radioModule)->startListening();                  // Switch back to receive mode
  } else
    Serial.println("Radio module is not set");
}

// **Potential Issues:**
// 1. **Destructor Issue:** If `radioModule` is not allocated before deletion, it may cause undefined behavior.
// 2. **Memory Management:** `delete` should only be called if `radioModule` is not nullptr.
// 3. **APC220 Timeout:** The timeout logic waits indefinitely if the module is unresponsive.

// 5. **Fixed Buffer Size in `write()`:** Ensure the string length doesn't exceed 32 bytes for RF24.
