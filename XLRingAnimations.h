// ==========================================================================
// Quick class to handle Xbox Ring of Light Animations
// Under MIT License (c) APR, 2016 - Jacob Karleskint
// ==========================================================================
#include<Arduino.h>

class XLRingAnimations{
  public:
  XLRingAnimations(byte *led1r_v, byte *led1g_v, byte *led2r_v, byte *led2g_v);

  void Update();
  void SetAnimation(byte id, byte loop_amount = 0);

  bool IsAnimating();


  

  private:
  // Animation Functions:
  void TestCycle();
  void ErrorState_General();
  void SyncController();

  
  // LED values (get ref)
  byte *led1r;
  byte *led1g;
  byte *led2r;
  byte *led2g;

  // Which animation to animate
  byte AnimID = 0;

  // Loop amount
  byte loopAmount = 0;
  byte loopFrame = 0;   // How many times it has been looped.

  // Frame variables
  bool Animating = false;
  int Frame = 0;
  int KeyFrame = 0;

  // Updates frames and keyframes.  Must be called in all animation functions
  void update_frames(int keyFrameInt);

  // Clears out leds
  void clear_leds();
  
};

