#ifndef DEEJ_H
#define DEEJ_H

#include <Arduino.h>
#include <Adafruit_MCP3008.h>

class Deej {
public:
  Deej(uint8_t numSliders);

  // Configuration
  static const uint16_t SLIDER_UPDATE_MS = 20;
  static const uint8_t SLIDER_THRESHOLD = 5;

  void begin(const uint8_t CS_PIN, const uint8_t MISO_PIN, const uint8_t MOSI_PIN, const uint8_t SCK_PIN, Adafruit_MCP3008* MCP);
  void update();
  void _sendSliderEvent();

private:
  Adafruit_MCP3008* _MCP;
  const uint8_t _numSliders;

  struct SliderState {
    int previous = 0;
    int current = 0;
  };
  SliderState* _state;

  void _readSliders();
  void _processSliderEvents();
};

#endif