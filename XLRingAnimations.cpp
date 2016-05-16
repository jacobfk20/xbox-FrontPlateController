#include "XLRingAnimations.h"

XLRingAnimations::XLRingAnimations(byte *led1r_v, byte *led1g_v, byte *led2r_v, byte *led2g_v){
  led1r = led1r_v;
  led1g = led1g_v;
  led2r = led2r_v;
  led2g = led2g_v;
}


void XLRingAnimations::SetAnimation(byte id, byte loop_amount){
  AnimID = id;
  Animating = true;
  Frame = 0;
  KeyFrame = 0;
  loopAmount = loop_amount;
  loopFrame = 0;
}


bool XLRingAnimations::IsAnimating(){
  return Animating;
}



void XLRingAnimations::Update(){
  if (Animating){
    if (AnimID == 1) TestCycle();
    if (AnimID == 2) ErrorState_General();
    if (AnimID == 3) SyncController();
  }
}







void XLRingAnimations::TestCycle(){
  if (Frame == 0) clear_leds();
  
  if (Frame < 801){
    if (KeyFrame == 1){
      *led1r+=25;
      *led2r+=25;
    }
  }
  if (Frame > 800 && Frame < 1601){
    if (KeyFrame == 1){
      *led1r-=25;
      *led2r-=25;
    }
  }
  if (Frame > 1600 && Frame < 2401){
    if (KeyFrame == 1){
      *led1g+=25;
      *led2g+=25;
    }
  }
  if (Frame > 2400){
    if (KeyFrame == 1){
      *led1g-=25;
      *led2g-=25;
    }
  }

  if (Frame > 3200){
    clear_leds();

    Animating = 0;
    AnimID = 0;
  }

  update_frames(100);
}



void XLRingAnimations::ErrorState_General(){
  if (Frame == 0) clear_leds();

  if (Frame == 1000){
    clear_leds();
    *led1g = 254;
    *led2r = 254;
  }

  if (Frame == 2000){
    clear_leds();
    *led1r = 254;
    *led2g = 254;
  }

  // this animation should loop
  if (Frame == 2001){
    Frame = 0;
  }

  update_frames(2001);
}


void XLRingAnimations::SyncController(){
  if (Frame == 0) clear_leds();

  if (Frame == 1000){
    clear_leds();
    *led1g = 254;
  }

  if (Frame == 2000){
    clear_leds();
    *led2g = 254;
  }

  update_frames(2001);
}






// ------------------------------------------~ Privates ~-----------------------------------------
void XLRingAnimations::update_frames(int keyFrameInt){
  // Handle Frames
  Frame++;
  KeyFrame++;
  if (KeyFrame > keyFrameInt) KeyFrame = 0;
}


void XLRingAnimations::clear_leds(){
    *led1g=0;
    *led2g=0;
    *led1r=0;
    *led2r=0;
}

