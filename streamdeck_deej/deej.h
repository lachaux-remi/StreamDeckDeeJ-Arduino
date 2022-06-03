const int analogInputs[5] = { A10, A0, A1, A2, A3 };

void deej_setup() {
    for ( int i = 0; i < 5; i++ ) {
        pinMode( analogInputs[i], INPUT );
    }
}

void deej_loop() {
    String input = "{\"type\":\"deej\",\"value\":{";
    for ( int i = 0; i < 5; i++ ) {
        input += "\"" + String( i ) + "\":" + String( analogRead( analogInputs[i] ) );
        if ( i < 4 ) input += ",";
    }
    input += "}}";
    Serial.println( input );
}