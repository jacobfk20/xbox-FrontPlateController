// ==========================================================================
// Quick class to handle buttons on pins written for Xbox Front Panel Buttons
// Under MIT License (c) APR, 2016 - Jacob Karleskint
// ==========================================================================

#include <Arduino.h>

class PinButton {
  public:
  PinButton(byte Pin, int hold_time);
  void Update();

  bool Clicked();
  bool Holding();
  bool Released();

  int HoldAmount();




  private:
  byte pin;                     // Which pin this button is assigned

  int hold_amount = 100;        // Amount this button must be held before it's enabled
  
  int btn_hold = 0;             // Increment of how long the button has been held down

  bool holding = false;         // Enabled when this button is being held
  bool clicked = false;         // Enabled when this button has been held for amount of time
  bool released = false;        // Enabled when this button has been released.
  
};

