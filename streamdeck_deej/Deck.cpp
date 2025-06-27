#include "Deck.h"
#include <cstring>

Deck::Deck(uint8_t rows, uint8_t cols) : _rows(rows), _cols(cols) {
  _rowPins = new uint8_t[_rows];
  _colPins = new uint8_t[_cols];
  _initializeState();
}

void Deck::_initializeState() {
  _state = new KeyState*[_rows];
  for (uint8_t r = 0; r < _rows; r++) {
    _state[r] = new KeyState[_cols];
  }
}

void Deck::begin(const uint8_t* rowPins, const uint8_t* colPins) {
  // Copier les broches
  memcpy(_rowPins, rowPins, _rows * sizeof(uint8_t));
  memcpy(_colPins, colPins, _cols * sizeof(uint8_t));
  
  // Configurer les broches
  for (uint8_t c = 0; c < _cols; c++) {
    pinMode(_colPins[c], INPUT_PULLDOWN);
  }
}

void Deck::update() {
  static uint32_t lastScan = 0;
  if (millis() - lastScan >= SCAN_INTERVAL_MS) {
    _readMatrix();
    _processKeyEvents();
    lastScan = millis();
  }
}

void Deck::_sendKeyEvent(const char* event, uint8_t keyNumber) {
  Serial.print(F("{\"type\":\"deck\",\"state\":\""));
  Serial.print(event);
  Serial.print(F("\",\"value\":"));
  Serial.print(keyNumber);
  Serial.println(F("}"));
}

void Deck::_readMatrix() {
  for (uint8_t r = 0; r < _rows; r++) {
    pinMode(_rowPins[r], OUTPUT);
    digitalWrite(_rowPins[r], HIGH);
    delayMicroseconds(10);
    
    for (uint8_t c = 0; c < _cols; c++) {
      _state[r][c].current = (digitalRead(_colPins[c]) == HIGH);
    }
    
    digitalWrite(_rowPins[r], LOW);
    pinMode(_rowPins[r], INPUT);
  }
}

void Deck::_processKeyEvents() {
  uint32_t now = millis();
  
  for (uint8_t r = 0; r < _rows; r++) {
    for (uint8_t c = 0; c < _cols; c++) {
      // Calcul du numéro de touche à partir de la position
      uint8_t keyNumber = r * _cols + c;
      
      // Appui initial
      if (_state[r][c].current && !_state[r][c].previous) {
        _state[r][c].pressStart = now;
        _state[r][c].longFired = false;
        _sendKeyEvent("pressed", keyNumber);
      }

      // Maintien prolongé
      else if (_state[r][c].current && _state[r][c].previous && !_state[r][c].longFired && (now - _state[r][c].pressStart >= LONG_PRESS_MS)) {
        _state[r][c].longFired = true;
        _sendKeyEvent("hold", keyNumber);
      }

      // Relâchement
      else if (!_state[r][c].current && _state[r][c].previous) {
        _sendKeyEvent("released", keyNumber);
      }
      
      _state[r][c].previous = _state[r][c].current;
    }
  }
}