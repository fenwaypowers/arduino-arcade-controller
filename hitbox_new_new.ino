// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// Ground digital pins 9, 10, 11, and 12 to press the joystick 
// buttons 0, 1, 2, and 3.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//
// ---------- Hitbox Style Arcade Controller ----------
// Adds 9 extra buttons to the original code.
// 
// by Fenway Powers
// 2021-4-19
//  
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick;

void setup() {
  // Initialize Button Pins
  for (int index = 1; index < 13; index++)
  {
    pinMode(index, INPUT_PULLUP);
  }

  // Initialize Joystick Library
  Joystick.begin();
}

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 1;

// Last state of the button
int lastButtonState[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {

  // Read pin values
  for (int index = 0; index < 13; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }

  delay(50);
}
