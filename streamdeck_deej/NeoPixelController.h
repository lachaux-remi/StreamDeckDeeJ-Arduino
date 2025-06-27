#ifndef NEOPIXEL_CONTROLLER_H
#define NEOPIXEL_CONTROLLER_H

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

class NeoPixelController {
public:
    NeoPixelController(uint16_t count);

    void begin(const uint8_t pin, Adafruit_USBD_HID* usbHID);
    void update();

    static void receiveHIDPacket(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);
    
private:
    Adafruit_USBD_HID* _usbHID;
    Adafruit_NeoPixel strip;
    bool updateChannel;
    int packetCount;
    unsigned long lastPacketRcvd;

    // Configuration EEPROM
    enum EEPROM_Addresses {
        eeprom_Brightness = 0,
        eeprom_DefaultColor_r = 1,
        eeprom_DefaultColor_g = 2,
        eeprom_DefaultColor_b = 3
    };

    byte Brightness;
    byte DefaultColor[3];

    void loadEEPROMSettings();
    void processHIDPacket();
    void updateLEDsFromPacket();

    static bool newUSBpacketArrived;
    static byte usbPacket[64];
    static const byte firmwareVersion[3];
};

#endif