#include "Mobo.h"


Mobo::Mobo(byte pin_power, byte pin_reset, byte pin_state){
  Pin_Power = pin_power;
  Pin_Reset = pin_reset;
  Pin_State = pin_state;
}



void Mobo::SetHarddrivePin(int pin_hdd){
  Pin_HDD = pin_hdd;
  bHddConnected = true;
}




void Mobo::Update(){
  // Check if Mobo is turned on
  if (analogRead(Pin_State) > 800){
    bMoboRunning = true;
  }
  else{
    bMoboRunning = false;
  }


  // if Power Button has been pushed, turn on board with timout error throwing if failed
  if (bInitMobo) TurnOnMobo();
}





void Mobo::TurnOn(){
  bInitMobo = true;
}



bool Mobo::IsOn(){
  return bMoboRunning;
}



byte Mobo::GetError(){
  return ErrorCode;
}



// -------------------------------- ~ Privates ~ -----------------------------------

void Mobo::TurnOnMobo(){
  // Hold power button for 100 cycles
  //if (bootTimeout < 100) digitalWrite(Pin_Power, HIGH);
  //else digitalWrite(Pin_Power, LOW);

//  if (analogRead(Pin_State) < 10){
//    bInitMobo = false;
//    bMoboRunning = true;
//  }
//
//  if (bootTimeout > bootTimeoutMax){
//    ErrorCode = 1;
//    bInitMobo = false;
//    
//  }



  bootTimeout++;
}





