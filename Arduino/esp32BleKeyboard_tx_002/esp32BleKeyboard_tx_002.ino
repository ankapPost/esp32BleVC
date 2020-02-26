//#include <myESP32Button.h>
//#include "Button.cpp"
#include <BfButton.h>
#include <myESP32Encoder.h>
#include <BleKeyboard.h>

#define BUTN1 34
#define ENC_A 36
#define ENC_B 39

//Button button1(BUTN1);
BfButton btn(BfButton::STANDALONE_DIGITAL, BUTN1, false, HIGH);
ESP32Encoder encoder(ENC_A, ENC_B);
BleKeyboard bleKeyboard("XXX");

long oldPosition  = -999;
long newPosition;

void volume_up() {
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    Serial.println("in volume_up function: " + String(newPosition));
}
void volume_down() {
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    Serial.println("in volume_down function: " + String(newPosition));
}
void play_pause() {
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    Serial.print("in play_pause function: ");
    Serial.println(btn.getID());
}
void open_calc() {
    bleKeyboard.write(KEY_MEDIA_CALCULATOR);
    Serial.print("in open_calc function: ");
    Serial.println(btn.getID());
}
void open_explorer() {
    bleKeyboard.write(KEY_MEDIA_LOCAL_MACHINE_BROWSER);
    Serial.print("in open_explorer function: ");
    Serial.println(btn.getID());
}
 
void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
//    Serial.print(btn->getID());
    switch (pattern) {
      case BfButton::SINGLE_PRESS:
        play_pause();
        break;
      case BfButton::DOUBLE_PRESS:
        open_calc();
        break;
      case BfButton::LONG_PRESS:
        open_explorer();
        break;
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Basic Encoder Test:");
    
    bleKeyboard.begin();
    
    encoder.setCount(37);
    Serial.println("Encoder Start = "+String((int32_t)encoder.getCount()));

    btn.onPress(pressHandler)
       .onDoublePress(pressHandler) // default timeout
       .onPressFor(pressHandler, 3000); // custom timeout for 1 second
}

void loop() {
  newPosition = encoder.getCount();
  if (       newPosition > oldPosition) {
    volume_up();
  } else if (newPosition < oldPosition) {
    volume_down();
  }
  oldPosition = newPosition;
  btn.read();

// button1.checkPressed();
}
