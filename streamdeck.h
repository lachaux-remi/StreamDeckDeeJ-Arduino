#include <HID-Project.h>
#include <Keypad.h>
#include <IRremote.h>

const int IR_LED = 14;
const uint16_t IR_SIGNAL_OFF[21] = { 914, 876, 894, 876, 1794, 862, 894, 876, 894, 876, 894, 1762, 1810, 848, 894, 1762, 896, 876, 1780, 878, 894 };
const byte ROWS = 3;
const byte COLS = 5;
char keys[ROWS][COLS] = {
  { '0', '1', '2', '3', '4' },
  { '5', '6', '7', '8', '9' },
  { 'A', 'B', 'C', 'D', 'E' }
};
const byte colPins[COLS] = { 9, 8, 7, 6, 5 };
const byte rowPins[ROWS] = { 2, 3, 4 };
const Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

void setupStreamDeck() {
  Keyboard.begin();
  Consumer.begin();
  IrSender.begin( IR_LED );
}

void loopStreamDeck() {
  char key = keypad.getKey();

  if (key) {
    switch (key) {
      case '0':
        Consumer.write( MEDIA_NEXT );
        break;
      case '1':
        Keyboard.write( KEY_F13 );
        break;
      case '2':
        Keyboard.write( KEY_F14 );
        break;
      case '3':
        Keyboard.write( KEY_F15 );
        break;
      case '4': // Eteindre / Alumer la TV
        IrSender.sendRaw( IR_SIGNAL_OFF, sizeof( IR_SIGNAL_OFF ) / sizeof( IR_SIGNAL_OFF[0] ), NEC_KHZ );
        break;
      case '5':
        Consumer.write( MEDIA_PLAY_PAUSE );
        break;
      case '6': // DISCORD Mute micro
        Keyboard.write( KEY_F17 );
        break;
      case '7':
        Keyboard.write( KEY_F18 );
        break;
      case '8':
        Keyboard.write( KEY_F19 );
        break;
      case '9':
        Keyboard.write( KEY_F20 );
        break;
      case 'A':
        Consumer.write( MEDIA_PREVIOUS );
        break;
      case 'B': // DISCORD Sourdine
        Keyboard.write( KEY_F21 );
        break;
      case 'C':
        Keyboard.write( KEY_F22 );
        break;
      case 'D':
        Keyboard.write( KEY_F23 );
        break;
      case 'E':
        Keyboard.write( KEY_F24 );
        break;
    }
    
    Keyboard.releaseAll();
    Consumer.releaseAll();
  }
}
