#include <CorsairLightingProtocol.h>
#include <FastLED.h>

const int PIN_LED = 0; // RX1

CRGB ledsChannel[96];
CorsairLightingFirmwareStorageEEPROM firmwareStorage;
CorsairLightingFirmware firmware( CORSAIR_LIGHTING_NODE_PRO, &firmwareStorage );
FastLEDControllerStorageEEPROM storage;
FastLEDController ledController( &storage );
CorsairLightingProtocolController cLP( &ledController, &firmware );
CorsairLightingProtocolHID cHID( &cLP );

void setupLed() {
  FastLED.addLeds<WS2812B, PIN_LED, GRB>( ledsChannel, 96 );
  ledController.addLEDs( 0, ledsChannel, 96 );
}

void loopLed() {
  cHID.update();
  if ( ledController.updateLEDs() ) {
    FastLED.show();
  }
}
