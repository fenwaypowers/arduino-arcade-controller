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

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  8, 1,                  // Button Count, Hat Switch Count
  false, false, false,     // X, Y, Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

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
const int pinToButtonMap = 5;

// Last state of the button
int lastButtonState[2][4]={{0,0,0,0},{0,0,0,0}};
int lastButtonState_2[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

void loop() {

  bool valueChanged[1] = {false};
  int currentPin = 1;

  // Read pin values
  int hatSwitch = 0;
    for (int index = 0; index < 4; index++)
    {
      int currentButtonState = !digitalRead(currentPin++);
      if (currentButtonState != lastButtonState[hatSwitch][index])
      {
        valueChanged[hatSwitch] = true;
        lastButtonState[hatSwitch][index] = currentButtonState;
      }
    }

    if (valueChanged[hatSwitch]) {
      
      if ((lastButtonState[hatSwitch][0] == 0)
        && (lastButtonState[hatSwitch][1] == 0)
        && (lastButtonState[hatSwitch][2] == 0)
        && (lastButtonState[hatSwitch][3] == 0)) {
          Joystick.setHatSwitch(hatSwitch, -1);
      }
      if (lastButtonState[hatSwitch][0] == 1) {
        Joystick.setHatSwitch(hatSwitch, 0);
      }
      if (lastButtonState[hatSwitch][1] == 1) {
        Joystick.setHatSwitch(hatSwitch, 90);
      }
      if (lastButtonState[hatSwitch][2] == 1) {
        Joystick.setHatSwitch(hatSwitch, 180);
      }
      if (lastButtonState[hatSwitch][3] == 1) {
        Joystick.setHatSwitch(hatSwitch, 270);
      }
      
    } // if the value changed

  // Read pin values
  for (int index = 0; index < 9; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState_2[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState_2[index] = currentButtonState;
    }
  }

  delay(50);
}
