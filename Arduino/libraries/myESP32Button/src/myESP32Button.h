#include <Arduino.h>
#include <FunctionalInterrupt.h>

class Button
{
public:
  Button(uint8_t reqPin) : PIN(reqPin)
  ~Button()

  void IRAM_ATTR isr()
  void checkPressed()

private:
  const uint8_t PIN;
    volatile uint32_t numberKeyPresses;
    volatile bool pressed;
};

