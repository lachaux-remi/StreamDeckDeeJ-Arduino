const byte colPins[4] = { 9, 8, 7, 6 };
const byte rowPins[4] = { 2, 3, 4, 5 };
char keys[4][4] = {
    { '0', '1', '2', '3' },
    { '4', '5', '6', '7' },
    { '8', '9', 'A', 'B' },
    { 'C', 'D', 'E', 'F' }
};
const Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, 4, 4 );

void deck_setup() {
    //
}

void deck_loop() {
    if ( keypad.getKeys() ) {
        for ( int i = 0; i < LIST_MAX; i++ ) {
            if ( keypad.key[i].stateChanged ) {
                char key = keypad.key[i].kchar;
                switch (keypad.key[i].kstate) {
                    case PRESSED:
                        Serial.println( "{\"type\":\"deck\",\"state\":\"pressed\",\"value\":\"" + String( key ) + "\"}" );
                        break;
                    case HOLD:
                        Serial.println( "{\"type\":\"deck\",\"state\":\"hold\",\"value\":\"" + String( key ) + "\"}" );
                        break;
                    case RELEASED:
                        Serial.println( "{\"type\":\"deck\",\"state\":\"released\",\"value\":\"" + String( key ) + "\"}" );
                        break;
                }
            }
        }
    }
}