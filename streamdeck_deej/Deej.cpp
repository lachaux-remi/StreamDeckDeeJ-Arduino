#include "Deej.h"
#include <Arduino.h>

Deej::Deej(uint8_t numSliders) : _numSliders(numSliders) {
    _state = new SliderState[numSliders]();
}

void Deej::begin(const uint8_t* sliderPins) {
    _sliderPins = sliderPins;
    for (uint8_t i = 0; i < _numSliders; i++) {
        uint8_t pin = _sliderPins[i];
        if (pin > 0) {
          pinMode(pin, INPUT);
        }
    }
}

void Deej::update() {
    static uint32_t lastUpdate = 0;
    if (millis() - lastUpdate >= SLIDER_UPDATE_MS) {
        _readSliders();
        _processSliderEvents();
        lastUpdate = millis();
    }
}

void Deej::_readSliders() {
    for (uint8_t i = 0; i < _numSliders; i++) {
      uint8_t pin = _sliderPins[i];
      if (pin > 0) {
        _state[i].current = analogRead(_sliderPins[i]);
      } else {
        _state[i].current = 1023;
      }
    }
}

void Deej::_processSliderEvents() {
    bool hasChange = false;
    
    for (uint8_t i = 0; i < _numSliders; i++) {
        int diff = abs(_state[i].current - _state[i].previous);
        
        if (diff >= SLIDER_THRESHOLD) {
            _state[i].previous = _state[i].current;
            hasChange = true;
        }
    }
    
    if (hasChange) {
        _sendSliderEvent();
    }
}

void Deej::_sendSliderEvent() {
    Serial.print(F("{\"type\":\"deej\",\"value\":{"));
    
    for (uint8_t i = 0; i < _numSliders; i++) {
        Serial.print(F("\""));
        Serial.print(i);
        Serial.print(F("\":"));
        Serial.print(_state[i].current);
        
        if (i < _numSliders - 1) {
            Serial.print(F(","));
        }
    }
    
    Serial.println(F("}}"));
}