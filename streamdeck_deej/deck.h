const byte ROWS = 3;
const byte COLS = 5;
const byte colPins[COLS] = { 9, 8, 7, 6, 5 };
const byte rowPins[ROWS] = { 2, 3, 4 };
char keys[ROWS][COLS] = {
  { '0', '1', '2', '3', '4' },
  { '5', '6', '7', '8', '9' },
  { 'A', 'B', 'C', 'D', 'E' }
};
const Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

void deck_setup() {

}

void deck_loop() {
    char key = keypad.getKey();
    if (key) {
        Serial.println( "{\"type\":\"deck\",\"value\":\"" + String( key ) + "\"" );
    }
}