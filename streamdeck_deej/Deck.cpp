#include "Deck.h"
#include <cstring>

Deck::Deck(uint8_t rows, uint8_t cols) : _rows(rows), _cols(cols) {
  _ROW_PINS = new uint8_t[_rows];
  _COL_PINS = new uint8_t[_cols];

  _initializeState();
}

void Deck::_initializeState() {
  _state = new KeyState*[_rows];

  for (uint8_t row = 0; row < _rows; row++) {
    _state[row] = new KeyState[_cols];
  }
}

void Deck::begin(const uint8_t* ROW_PINS, const uint8_t* COL_PINS) {
  // Copier les broches
  memcpy(_ROW_PINS, ROW_PINS, _rows * sizeof(uint8_t));
  memcpy(_COL_PINS, COL_PINS, _cols * sizeof(uint8_t));

  // Configurer les broches
  for (uint8_t col = 0; col < _cols; col++) {
    pinMode(_COL_PINS[col], INPUT_PULLDOWN);
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
  for (uint8_t row = 0; row < _rows; row++) {
    pinMode(_ROW_PINS[row], OUTPUT);
    digitalWrite(_ROW_PINS[row], HIGH);
    delayMicroseconds(10);

    for (uint8_t col = 0; col < _cols; col++) {
      _state[row][col].current = (digitalRead(_COL_PINS[col]) == HIGH);
    }

    digitalWrite(_ROW_PINS[row], LOW);
    pinMode(_ROW_PINS[row], INPUT);
  }
}

void Deck::_processKeyEvents() {
  uint32_t now = millis();

  for (uint8_t row = 0; row < _rows; row++) {
    for (uint8_t col = 0; col < _cols; col++) {
      // Calcul du numéro de touche à partir de la position
      uint8_t keyNumber = row * _cols + col;

      // Appui initial
      if (_state[row][col].current && !_state[row][col].previous) {
        _state[row][col].pressStart = now;
        _state[row][col].longFired = false;
        _sendKeyEvent("pressed", keyNumber);
      }

      // Maintien prolongé
      else if (_state[row][col].current && _state[row][col].previous && !_state[row][col].longFired && (now - _state[row][col].pressStart >= LONG_PRESS_MS)) {
        _state[row][col].longFired = true;
        _sendKeyEvent("hold", keyNumber);
      }

      // Relâchement
      else if (!_state[row][col].current && _state[row][col].previous) {
        _sendKeyEvent("released", keyNumber);
      }

      _state[row][col].previous = _state[row][col].current;
    }
  }
}