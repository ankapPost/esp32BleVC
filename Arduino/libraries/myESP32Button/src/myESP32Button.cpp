/*
 * ESP32Button.cpp
 *
 *      Author: ........
 */
#include <myESP32Button.h>

  Button::Button(uint8_t reqPin) {
    pinMode(PIN, INPUT_PULLUP);
    attachInterrupt(PIN, std::bind(&Button::isr,this), FALLING);
  };
  Button::~Button() {
    detachInterrupt(PIN);
  }

  void Button::IRAM_ATTR isr() {
    numberKeyPresses += 1;
    pressed = true;
  }

  void Button::checkPressed() {
    if (pressed) {
      Serial.printf("Button on pin %u has been pressed %u times\n", PIN, numberKeyPresses);
      pressed = false;
    }
  }
