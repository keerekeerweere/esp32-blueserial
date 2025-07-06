#include <Arduino.h>
#include "AsyncBluetoothSerial.h"

AsyncBluetoothSerial SerialBTAsync;
uint8_t smaBTAddress[6];
const char btPin[] = {'0','0','0','0',0};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Async Bluetooth Serial...");

  if (!SerialBTAsync.begin("ESP32-Async", true)) {
    Serial.println("Failed to start BT!");
    return;
  }
  SerialBTAsync.setPin(&btPin[0],4);

  sscanf("00:80:25:01:02:03", "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx", 
    &smaBTAddress[0], &smaBTAddress[1], &smaBTAddress[2], &smaBTAddress[3], &smaBTAddress[4], &smaBTAddress[5]);

  SerialBTAsync.connect(smaBTAddress, []() {
    log_d("hello");
    yield();
});  // REPLACE WITH YOUR REMOTE BT MAC
}

void loop() {
  if (SerialBTAsync.connected()) {
    while (SerialBTAsync.available()) {
      int c = SerialBTAsync.read();
      Serial.write(c);
    }
  }

  delay(1000);
}
