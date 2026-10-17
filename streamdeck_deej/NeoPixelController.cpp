#include "NeoPixelController.h"

bool NeoPixelController::newUSBpacketArrived = false;
byte NeoPixelController::usbPacket[64] = { 0 };
const byte NeoPixelController::firmwareVersion[3] = { 1, 2, 5 };

NeoPixelController::NeoPixelController(uint16_t count)
  : strip(count, 0, NEO_GRB + NEO_KHZ800) {
}

void NeoPixelController::begin(const uint8_t pin, Adafruit_USBD_HID* usbHID) {
  _usbHID = usbHID;

  _usbHID->setReportCallback(NULL, receiveHIDPacket);

  pinMode(pin, OUTPUT);
  strip.setPin(pin);

  EEPROM.begin(256);
  loadEEPROMSettings();

  strip.begin();
  strip.show();
}

void NeoPixelController::update() {
  if (newUSBpacketArrived) {
    processHIDPacket();
    newUSBpacketArrived = false;
  }
}

void NeoPixelController::receiveHIDPacket(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
  if (!newUSBpacketArrived) {
    // Copy at most one packet and clear the rest, so a short report never
    // reads past the received buffer.
    uint16_t length = bufsize < sizeof(usbPacket) ? bufsize : sizeof(usbPacket);
    memset(usbPacket, 0, sizeof(usbPacket));
    memcpy(usbPacket, buffer, length);
    newUSBpacketArrived = true;
  }
}

void NeoPixelController::processHIDPacket() {
  if (usbPacket[0] && usbPacket[1] == 0xAA) {
    lastPacketRcvd = millis();
    updateLEDsFromPacket();
    return;
  }
}

void NeoPixelController::updateLEDsFromPacket() {
  // A packet holds a 2-byte header and 3 bytes per LED: 20 LEDs at most.
  const uint16_t packetLeds = (sizeof(usbPacket) - 2) / 3;
  const uint16_t count = strip.numPixels() < packetLeds ? strip.numPixels() : packetLeds;
  for (uint16_t i = 0; i < count; i++) {

    uint8_t r, g, b;
    r = usbPacket[2 + i * 3];
    g = usbPacket[3 + i * 3];
    b = usbPacket[4 + i * 3];

    strip.setPixelColor(i, r, g, b);
  }

  strip.show();

  updateChannel = true;
  packetCount = 0;
}

void NeoPixelController::loadEEPROMSettings() {
  Brightness = EEPROM.read(eeprom_Brightness);
  DefaultColor[0] = EEPROM.read(eeprom_DefaultColor_r);
  DefaultColor[1] = EEPROM.read(eeprom_DefaultColor_g);
  DefaultColor[2] = EEPROM.read(eeprom_DefaultColor_b);

  // Set default values if EEPROM is empty (0xFF)
  if (Brightness == 0xFF) Brightness = 127;
}