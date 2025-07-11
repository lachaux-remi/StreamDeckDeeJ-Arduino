#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

class SerialHandler {
public:
  SerialHandler(uint32_t baudrate);

  void begin(const uint8_t pin, Adafruit_USBD_HID* USBHID);
  void update();

private:
  const uint32_t _baudrate;

  Adafruit_USBD_HID* _USBHID;
  uint8_t _keycode[6] = { 0 };

  void processCommand(const String& command);
  void sendIR(const String& command);
  void executeMacro(const String& key);
};

#endif