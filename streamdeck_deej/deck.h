#ifndef DECK_H
#define DECK_H

#include <Arduino.h>

class Deck {
  public:
    Deck(uint8_t rows, uint8_t cols);
    
    // Configuration
    static const uint16_t LONG_PRESS_MS = 500;
    static const uint8_t DEBOUNCE_MS = 20;
    static const uint16_t SCAN_INTERVAL_MS = 20;

    void begin(const uint8_t* rowPins, const uint8_t* colPins);
    void update();

    uint8_t getRows() const { return _rows; }
    uint8_t getCols() const { return _cols; }

  private:
    const uint8_t _rows;
    const uint8_t _cols;
    
    uint8_t* _rowPins;
    uint8_t* _colPins;
    
    struct KeyState {
      bool previous = false;
      bool current = false;
      uint32_t pressStart = 0;
      bool longFired = false;
    };
    KeyState** _state;
    
    void _readMatrix();
    void _processKeyEvents();
    void _initializeState();
    void _sendKeyEvent(const char* event, uint8_t keyNumber);
};

#endif