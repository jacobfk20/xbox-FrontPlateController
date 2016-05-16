// ==========================================================================
// Handles the Original Xbox's 2 segment LED ring of light.
// Standard format is Left side LED Red -> Green / Right Side Red -> Green
// So use it like: XLRing.SetValue(1 Red, 1 Green, 2 Red, 2 Green);
// All light values are handeled in bytes.  0-255.
// Under MIT License (c) APR, 2016 - Jacob Karleskint
// ==========================================================================

#include <Arduino.h>
#include "XLRingAnimations.h"

class XboxLightRing {
  public:
    XboxLightRing(byte l1r, byte l1g, byte l2r, byte l2g);
    void SetValue(byte l1r_v, byte l1g_v, byte l2r_v, byte l2g_v);
    void SetHDDPin(int pin);
    void Update(byte err_code = 0, bool isOn = false);
    void SetPowerColor();

    void Animate(byte id);


  private:
  XLRingAnimations Animation = XLRingAnimations(&led1r_value, &led1g_value, &led2r_value, &led2g_value);
  
  byte led1r, led1g, led2r, led2g;
  byte led1r_value, led1g_value, led2r_value, led2g_value;

  bool bHddActive = false;
  int hddPin = 0;

  int anim_time = 0;
  int anim_frame = 0;
  void anim_error();

  // EEPROM color storeing
  byte eColor = 0;
};

