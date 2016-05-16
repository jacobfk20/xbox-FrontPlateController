#include "PinButton.h"



PinButton::PinButton(byte Pin, int hold_time){
  pin = Pin;
  btn_hold = hold_time;

  // setup pin for input with pullup
  pinMode(Pin, INPUT_PULLUP);
}


void PinButton::Update(){
  // hold holding var temporarily to test if button has been released
  bool tempHolding = holding;
  released = false;
    
  if (digitalRead(pin) < 1){
    hold_amount++;

    if (hold_amount > btn_hold){
      holding = true;
      
      // Have button click active for one cycle
      if (hold_amount == btn_hold + 1) clicked = true;
      else clicked = false;
    }
  }
  else{
    hold_amount = 0;
    holding = false;
    clicked = false;

          // check if button has been released.
    if (tempHolding == true && holding == false) released = true;
  }

}



bool PinButton::Clicked(){
  return clicked;
}

bool PinButton::Holding(){
  return holding;
}

int PinButton::HoldAmount(){
  return hold_amount;
}

bool PinButton::Released(){
  return released;
}

