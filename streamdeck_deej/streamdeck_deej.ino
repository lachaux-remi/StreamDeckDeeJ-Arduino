#include <Adafruit_TinyUSB.h>

#if !defined ARDUINO_ARCH_RP2040
  #error ONLY RP2040 supported!
#endif

#if !defined USE_TINYUSB
  #error Select "Adafruit TinyUSB" as USB Stack!
#endif

#include "SerialHandler.h"
#include "NeoPixelController.h"
#include "Deck.h"
#include "Deej.h"

// Configuration
const uint8_t DECK_ROWS = 4;
const uint8_t DECK_COLS = 4;
const uint8_t SLIDER_COUNT = 5;
const uint32_t SERIAL_BAUD = 115200;
const uint8_t RGB_LED_COUNT = 16;

// Broches
const uint8_t deckRowPins[DECK_ROWS] = {6, 7, 8, 9};
const uint8_t deckColPins[DECK_COLS] = {5, 4, 3, 2};
const uint8_t sliderPins[SLIDER_COUNT] = {26, 0, 27, 0, 28}; // 0 pour les sliders desactivé
const uint8_t rgbLedPin = 10;
const uint8_t irLedPin = 11;

Adafruit_USBD_HID usbHID;
SerialHandler serialHandler(SERIAL_BAUD);
Deck deck(DECK_ROWS, DECK_COLS);
Deej deej(SLIDER_COUNT);
NeoPixelController neoPixels(RGB_LED_COUNT);

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(1)),
  TUD_HID_REPORT_DESC_GENERIC_INOUT(64, HID_REPORT_ID(2))
};

void setup() {
  // Configuration USB HID
  usbHID.enableOutEndpoint(true);
  usbHID.setPollInterval(1);
  usbHID.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  TinyUSBDevice.setID(0x5239, 0x0001);
  TinyUSBDevice.setManufacturerDescriptor("LACHAUX Rémi");
  TinyUSBDevice.setProductDescriptor("Stream Deck DeeJ");

  // Initialisation des composants
  serialHandler.begin(irLedPin, &usbHID);
  neoPixels.begin(rgbLedPin, &usbHID);
  deck.begin(deckRowPins, deckColPins);
  deej.begin(sliderPins);

  usbHID.begin();

  // Attend que l'USB soit connecté
  while (!TinyUSBDevice.mounted()) {
    delay(10);
  }
}

void loop() {
  serialHandler.update();
  neoPixels.update();
  deck.update();
  deej.update();
}