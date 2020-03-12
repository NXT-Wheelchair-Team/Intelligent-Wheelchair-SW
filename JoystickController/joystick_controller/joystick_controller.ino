/**
 * Created for the intelligent wheelchair project at RIT.
 * 
 * Author: # TODO Sid
 * Author: Adam Del Rosso  avd5772@rit.edu
 */

#include <PacketSerial.h>

PacketSerial myPacketSerial;

void setup() {
  myPacketSerial.begin(115200);
  myPacketSerial.setPacketHandler(&onPacketReceived);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  myPacketSerial.update();

  if (myPacketSerial.overflow()) {
    // may need to increase recieve buffer via template parameters to PacketSerial (see PacketSerial/README.md).
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
  }
}

void onPacketReceived(const uint8_t* buffer, size_t size) {
  if (size != 2) {
    // TODO
  }
  auto x = static_cast<int8_t>(buffer[0]);
  auto y = static_cast<int8_t>(buffer[1]);
  updateControl(x, y);
}

/**
 * x: -100 (full back) to 100 (full forward)
 * y: -100 (full left) to 100 (full right)
 */
void updateControl(int8_t x, int8_t y) {
  // TODO add PWM commands here

  // TODO below is for test... remove
  uint8_t sendBuffer[2];
  sendBuffer[0] = ++x;
  sendBuffer[1] = ++y;
  myPacketSerial.send(sendBuffer, 2);
}
