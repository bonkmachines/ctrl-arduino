/*
  Multiplexed potentiometers example

  Description:
  This sketch demonstrates the implementation of a multiplexer with potentiometers.
  You can hook up a multiplexer with a maximum of 16 channels.

  Usage:
  Create a multiplexer with reference to:
  - sig              (required) Signal pin.
  - switchInterval   (required) The amount of time the multiplexer needs to switch.
                     Try what works best for you (usually between 10 and 50 microseconds).
  - s0               (required) Select input 0 (used internally for switching channels).
  - s1               (required) Select input 1 (used internally for switching channels).
  - s2               (required) Select input 2 (used internally for switching channels).
  - s3               (optional) Select input 3 (used internally for switching channels).
                     Only needed if you use a 16 channel mux. Not needed for 8 channels.
*/

#include <CtrlMux.h>
#include <CtrlPot.h>

// Create a multiplexer object. With:
// The amount of pins used, switchInterval (in microseconds), signal pin, s0, s1, s2 & s3 (optional).
CtrlMux mux(2, 10, 38, 34, 35, 36, 37);

// Define an onValueChange handler for pot 1
void onValueChange1(int value) {
    Serial.print("Pot 1 value: ");
    Serial.println(value);
}

// Define an onValueChange handler for pot 2
void onValueChange2(int value) {
    Serial.print("Pot 2 value: ");
    Serial.println(value);
}

// Define an onValueChange handler for empty pots
void onValueChangeEmptyPot(int value) {
//
}

// Create two potentiometers. With the: signal pin number (corresponds to the attached channel on the multiplexer),
// max. output value, sensitivity margin (can be 0.01 to 100) & onValueChange handler
// & a reference (&mux) to the multiplexer.
CtrlPot potentiometer1 = CtrlPot::create(0, 100, 0.50, onValueChange1, &mux);
CtrlPot potentiometer2 = CtrlPot::create(1, 100, 0.50, onValueChange2, &mux);

void setup() {
    Serial.begin(9600);
}

void loop() {
    // The process methods will poll the potentiometer objects and handle all their functionality.
    potentiometer1.process();
    potentiometer2.process();
}