const int NB_INPUTS = 5;
const int analogInputs[NB_INPUTS] = { A3, A2, A1, A0, A10 };

void setupDeej() {
  for ( int i = 0; i < NB_INPUTS; i++ ) {
    pinMode( analogInputs[i], INPUT );
  }
}

void loopDeej() {
  String builtString = String( "" );

  for ( int i = 0; i < NB_INPUTS; i++ ) {
    builtString += String( analogRead( analogInputs[i] ) );

    if ( i < NB_INPUTS - 1 ) {
      builtString += String( "|" );
    }
  }
  
  Serial.println( builtString );
}
