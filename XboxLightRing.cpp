#include "XboxLightRing.h"
#include "EEPROM.h"

XboxLightRing::XboxLightRing(byte l1r, byte l1g, byte l2r, byte l2g){
  led1r = l1r;
  led1g = l1g;
  led2r = l2r;
  led2g = l2g;

  // check eeprom for power ring color
  eColor = EEPROM.read(5);
  if (eColor > 200) eColor = 0;
}



void XboxLightRing::SetValue(byte l1r_v, byte l1g_v, byte l2r_v, byte l2g_v){
    led1r_value = l1r_v;
    led1g_value = l1g_v;
    led2r_value = l2r_v;
    led2g_value = l2g_v;
}


void XboxLightRing::SetHDDPin(int pin){
  hddPin = pin;
  bHddActive = true;
}



void XboxLightRing::SetPowerColor(){
  eColor++;

  if (eColor > 4) eColor = 0;
  
  // store color mode in eeprom
  EEPROM.write(5, eColor);
}



void XboxLightRing::Update(byte err_code, bool isOn){
  if (err_code != 0){
    if (Animation.IsAnimating() == false) Animate(2); // General Error cycle
  }

  if (isOn && err_code == 0 && Animation.IsAnimating() == false){
    if (eColor == 0) { led1r_value = 0; led1g_value = 254; led2r_value = 0; led2g_value = 254;}
    if (eColor == 1) { led1r_value = 254; led1g_value = 254; led2r_value = 254; led2g_value = 254;}
    if (eColor == 2) { led1r_value = 254; led1g_value = 0; led2r_value = 254; led2g_value = 0;}
    if (eColor == 3) { led1r_value = 254; led1g_value = 0; led2r_value = 0; led2g_value = 254;}
    if (eColor == 4) { led1r_value = 0; led1g_value = 0; led2r_value = 0; led2g_value = 0;}
    
  }
  if (isOn == false && err_code == 0 && Animation.IsAnimating() == false){
    led1r_value = 0;
    led1g_value = 0;
    led2r_value = 0;
    led2g_value = 0;
  }

  // Update animations
  Animation.Update();

  // update leds
  analogWrite(led1g, led1g_value);
  analogWrite(led1r, led1r_value);
  analogWrite(led2g, led2g_value);
  analogWrite(led2r, led2r_value);

  if (bHddActive){
    if (analogRead(hddPin) > 100) analogWrite(led1r, analogRead(hddPin));
  }
}




void XboxLightRing::Animate(byte id){
  Animation.SetAnimation(id);
}






// ==================================== ~Privates~ ================================

void XboxLightRing::anim_error(){
  if (anim_frame < 5000){
    led1r_value = 254;
    led1g_value = 0;
    led2r_value = 0;
    led2g_value = 254;
  }

  if (anim_frame > 5000){
    led1r_value = 0;
    led1g_value = 254;
    led2r_value = 254;
    led2g_value = 0;
  }

  anim_frame++;
  if (anim_frame > 10000) anim_frame = 0;
}


















