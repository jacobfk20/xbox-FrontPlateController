#include <RF360.h>                          // Xbox 360 RF module 
#include <Adafruit_NeoPixel.h>              // bottom LED RGB strip
#include "PinButton.h"                      // Easy objects to handle front panel buttons
#include "Mobo.h"                           // Easy class to handle motherboard control
#include "XboxLightRing.h"                  // Class that handles the front panel lights / animation


// RF360: clock pin-12, data pin-13.
RF360 rf = RF360(12, 13);

// RGB LED Strip
int strip_pin = 3;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, strip_pin, NEO_RGB + NEO_KHZ800);

// Create buttons from pins 2 and 4.
PinButton btnEject = PinButton(4, 200);
PinButton btnPower = PinButton(2, 200);

// Create the object that handles the motherboard connections.   [ Pin_power, Pin_Reset, Pin_State ]
byte Pin_Power = 7;
Mobo motherBoard = Mobo(Pin_Power, 8, A1);

// Create Xbox Ring of Light (2*2 Array) Object.   [LED: 1Green, 1Red, 2Green, 2Red]
XboxLightRing XLRing = XboxLightRing(9, 6, 10, 5);


bool oldMoboState = false;



void setup() {
  // Set Pin for harddrive activity
  if (motherBoard.GetError() == 0) motherBoard.SetHarddrivePin(A1);
  
  // Init 4 channel RGB Strip
  strip.begin();
  strip.show();

  // Start Serial at a safe baud
  Serial.begin(9600);

  // Sets the hdd light active and animates hdd activity on led1r
  //XLRing.SetHDDPin(A1);

  delay(500);
}



void loop() {
  // Activated when eject button was pushed and released fairly quickly
  if (btnEject.HoldAmount() == 20000){
    byte error = rf.init();
    error = rf.syncController();
    Serial.print("Error return on RFSync: ");
    Serial.println(error);
    if (error > 0) XLRing.Animate(2);
    else XLRing.Animate(3);
  }


  // Activates when both Power and Reset are held together
  if (btnEject.Holding() && btnPower.Clicked()) {
    XLRing.SetPowerColor();
  }
  else
  {

    // Activates when just power button is pushed alone.  acts as a standard power button.
    if (btnPower.HoldAmount() > 100 && !btnEject.Holding()) digitalWrite(Pin_Power, HIGH);
    else digitalWrite(Pin_Power, LOW);
    
  }

  // Object updates
  btnPower.Update();
  btnEject.Update();
  motherBoard.Update();
  XLRing.Update(motherBoard.GetError(), motherBoard.IsOn());

}




void RGB_test(byte times, byte speed_rate, byte skip){
  byte r = 0;

  for (byte t = 0; t < times; t++){
    for (int i = 0; i < 4; i++){
      for (int c = 0; c < 255; c += 1 + skip){
        strip.setPixelColor(i, c);
        strip.show();
        delay(speed_rate + 1);
      }

      for (int c = 255; c > 0; c -= 1 + skip){
        strip.setPixelColor(i, c);
        strip.show();
        delay(speed_rate);
      }
    }
  }
}













