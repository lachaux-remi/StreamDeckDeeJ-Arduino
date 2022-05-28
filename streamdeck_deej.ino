#include "corsair_led.h";
#include "deej.h";
#include "streamdeck.h";

void setup() {
  Serial.begin( 115200 );

  setupLed();
  setupDeej();
  setupStreamDeck();
}

void loop() {
  loopLed();
  loopDeej();
  loopStreamDeck();
}
