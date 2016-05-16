// ==========================================================================
// Handles a couple different connections to a pc motherboard.
// (Power pin) : Used to turn on a pc from arduino.
// (Reset pin) : Used to reset the pc
// (State pin) : Gets if the motherboard is on and running.
// (hdd   pin) : Gets hdd activity.
// Under MIT License (c) APR, 2016 - Jacob Karleskint
// ==========================================================================

#include <Arduino.h>


class Mobo {
  public:
  // Constructor.  brings in all pins for Power button, Reset button, and Power State
  Mobo(byte pin_power, byte pin_reset, byte pin_state);
  
  void SetHarddrivePin(int pin_hdd);
  void Update();

  bool IsOn();
  byte GetError();

  void TurnOn();
  void TurnOff();
  void Reset();


  private:
  // Pins for buttons/data
  byte Pin_Power;   // Button : Powers on pc
  byte Pin_Reset;   // Button : Resets pc
  byte Pin_State;   // Data   : Reads if mobo is on or off
  int  Pin_HDD;     // Data   : Reads hdd activity from mobo

  bool bHddConnected = false;

  bool bMoboRunning = false;

  // Everything to deal with turning on the mobo.
  void TurnOnMobo();
  bool bInitMobo = false;        // True: runs the function to turn on mobo
  int bootTimeoutMax = 10000;   // How long before errors are thrown
  int bootTimeout = 0;          // current cycle counting before timeout

  byte ErrorCode = 0;
};

