const int analogInputs[5] = { A3, A2, A1, A0, A10 };
ulong lastDebounceTime = 0;

void deej_setup() {
    for ( int i = 0; i < 5; i++ ) {
        pinMode( analogInputs[i], INPUT );
    }
}

void deej_loop() {
    if ( ( millis() - lastDebounceTime ) > 500 ) {
        lastDebounceTime = millis();

        String input = "{\"type\":\"deej\",\"value\":{";
        for ( int i = 0; i < 5; i++ ) {
            input += "\"" + String( i ) + "\":" + String( analogRead( analogInputs[i] ) );
            if ( i < 4 ) input += ",";
        }
        input += "}}";
        Serial.println( input );
    }
}