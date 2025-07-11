#include <Adafruit_TinyUSB.h>

#if !defined ARDUINO_ARCH_RP2040
#error ONLY RP2040 supported!
#endif

#if !defined USE_TINYUSB
#error Select "Adafruit TinyUSB" as USB Stack!
#endif

#include <Adafruit_MCP3008.h>

#include "SerialHandler.h"
#include "NeoPixelController.h"
#include "Deck.h"
#include "Deej.h"

// Configuration
const uint8_t DECK_ROWS = 4;
const uint8_t DECK_COLS = 4;
const uint8_t SLIDER_COUNT = 5;
const uint8_t RGB_LED_COUNT = 16;
const uint32_t SERIAL_BAUD = 115200;

// Broches
const uint8_t DECK_ROW_PINS[DECK_ROWS] = { 6, 7, 8, 9 };
const uint8_t DECK_COL_PINS[DECK_COLS] = { 5, 4, 3, 2 };
const uint8_t SLIDER_MISO_PIN = 16;  // RX - DOUT - MISO
const uint8_t SLIDER_CS_PIN = 17;    // CS
const uint8_t SLIDER_SCK_PIN = 18;   // SCK - CLK
const uint8_t SLIDER_MOSI_PIN = 19;  // TX - DIN - MOSI
const uint8_t RGB_LED_PIN = 10;
const uint8_t IR_LED_PIN = 11;

Adafruit_USBD_HID USBHID;
Adafruit_MCP3008 MCP;
SerialHandler SerialHandler(SERIAL_BAUD);
Deck Deck(DECK_ROWS, DECK_COLS);
Deej Deej(SLIDER_COUNT);
NeoPixelController NeoPixels(RGB_LED_COUNT);

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(1)),
  TUD_HID_REPORT_DESC_GENERIC_INOUT(64, HID_REPORT_ID(2))
};

void setup() {
  // Configuration USB HID
  USBHID.enableOutEndpoint(true);
  USBHID.setPollInterval(1);
  USBHID.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  TinyUSBDevice.setID(0x5239, 0x0001);
  TinyUSBDevice.setManufacturerDescriptor("LACHAUX Rémi");
  TinyUSBDevice.setProductDescriptor("Stream Deck DeeJ");

  // Initialisation des composants
  SerialHandler.begin(IR_LED_PIN, &USBHID);
  NeoPixels.begin(RGB_LED_PIN, &USBHID);
  Deck.begin(DECK_ROW_PINS, DECK_COL_PINS);
  Deej.begin(SLIDER_CS_PIN, SLIDER_MISO_PIN, SLIDER_MOSI_PIN, SLIDER_SCK_PIN, &MCP);

  USBHID.begin();

  // Attend que l'USB soit connecté
  while (!TinyUSBDevice.mounted()) {
    delay(10);
  }
}

void loop() {
  SerialHandler.update();
  NeoPixels.update();
  Deck.update();
  Deej.update();
}