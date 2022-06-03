#include <Keypad.h>
#include <CorsairLightingProtocol.h>
#include <FastLED.h>
#include <IRremote.h>
#include "Keyboard.h"

#include "serial.h";
#include "deck.h";
#include "deej.h";
#include "corsair.h";

void setup() {
    IrSender.begin( 14 );
    Keyboard.begin();
    
    serial_setup();
    deck_setup();
    deej_setup();
    corsair_setup();
}

void loop() {
    serial_loop();
    deck_loop();
    deej_loop();
    corsair_loop();
}