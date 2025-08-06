#include "SerialHandler.h"

#define SEND_PWM_BY_TIMER
#include <IRremote.hpp>

SerialHandler::SerialHandler(uint32_t baudrate)
  : _baudrate(baudrate) {
  Serial.begin(_baudrate);
}

void SerialHandler::begin(const uint8_t pin, Adafruit_USBD_HID* USBHID) {
  _USBHID = USBHID;

  pinMode(pin, OUTPUT);
  IrSender.begin(pin);
}

void SerialHandler::update() {
  String command = "";

  while (Serial.available()) {
    char c = Serial.read();
    if (c != '\r' && c != '\n') command += c;
  }

  command.trim();
  if (command.isEmpty()) return;

  processCommand(command);
}

void SerialHandler::processCommand(const String& command) {
  if (command.startsWith("ir:")) {
    sendIR(command.substring(3));
  } else if (command.startsWith("macro:")) {
    executeMacro(command.substring(6));
  }
}

void SerialHandler::sendIR(const String& command) {
  uint16_t signals[30];
  uint8_t index = 0;
  int startPos = 0;

  Serial.println(command);

  while (startPos < command.length()) {
    int endPos = command.indexOf(',', startPos);
    if (endPos == -1) endPos = command.length();

    signals[index++] = command.substring(startPos, endPos).toInt();
    startPos = endPos + 1;

    if (index >= 30) break;  // Protection contre le débordement
  }

  IrSender.sendRaw(signals, index, 38);
}

void SerialHandler::executeMacro(const String& command) {
  uint8_t keyValue = command.toInt();

  if (keyValue == 0) return;

  _keycode[0] = keyValue;
  _USBHID->keyboardReport(1, 0, _keycode);  // Appui

  delay(10);

  _keycode[0] = 0;
  _USBHID->keyboardReport(1, 0, _keycode);  // Relâche
}