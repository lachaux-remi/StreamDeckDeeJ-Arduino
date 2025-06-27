#ifndef DEEJ_H
#define DEEJ_H

#include <Arduino.h>

class Deej {
  public:
      Deej(uint8_t numSliders);
      
      // Configuration
      static const uint16_t SLIDER_UPDATE_MS = 20;
      static const uint8_t SLIDER_THRESHOLD = 5;

      void begin(const uint8_t* sliderPins);
      void update();

      uint8_t getCount() const { return _numSliders; }

  private:
      const uint8_t _numSliders;
      const uint8_t* _sliderPins;
      
      struct SliderState {
          int previous = 0;
          int current = 0;
      };
      SliderState* _state;

      void _readSliders();
      void _processSliderEvents();
      void _sendSliderEvent();
};

#endif