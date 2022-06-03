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

}

void deck_loop() {
    char key = keypad.getKey();
    if (key) {
        Serial.println( "{\"type\":\"deck\",\"value\":\"" + String( key ) + "\"}" );
    }
}