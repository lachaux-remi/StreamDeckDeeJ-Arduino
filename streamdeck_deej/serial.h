void serial_setup() {
    Serial.begin( 115200 );
}

void serial_loop() {
    String command = "";

    while ( Serial.available() ) {
        command += (char) Serial.read();
    }

    if ( command != "" )  {
        if ( command.startsWith("ir") ) { // ir:914,876,894,876,1794,862,894,876,894,876,894,1762,1810,848,894,1762,896,876,1780,878,894
            command.replace( "ir:", "" );

            int numStart = 0;
            int current_data_length = 0;
            uint16_t signal[30];

            for ( int i = 0; i <= command.length(); ++i ) {
                if ( command.charAt(i) == ',' || i == command.length() ) {
                    signal[current_data_length++] = command.substring( numStart, i ).toInt();
                    numStart = i + 1;
                }
            }

            IrSender.sendRaw( signal, current_data_length, NEC_KHZ );
        } else if ( command.startsWith("key") ) { // key:248
            command.replace( "key:", "" );
            Keyboard.write( command.toInt() );
        }

        command = "";
    }

}