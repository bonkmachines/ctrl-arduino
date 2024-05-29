/*
  Multiplexed buttons example

  Description:
  This sketch demonstrates the implementation of a multiplexer with buttons.
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
#include <CtrlBtn.h>

// Create a multiplexer object. With:
// The amount of pins used, switchInterval (in microseconds), signal pin, s0, s1, s2 & s3 (optional).
CtrlMux mux(2, 10, 38, 34, 35, 36, 37);

// Define an onPress handler for button 1.
void onPress1() {
    Serial.println("Button 1 pressed");
}

// Define an onPress handler for button 2.
void onPress2() {
    Serial.println("Button 2 pressed");
}

// Create two buttons. With the: signal pin number (corresponds to the attached channel on the multiplexer),
// the bounce duration, an onPress handler, without onRelease handler (we don't need it for this example)
// & a reference (&mux) to the multiplexer.
CtrlBtn button1 = CtrlBtn::create(0, 15, onPress1, nullptr, &mux);
CtrlBtn button2 = CtrlBtn::create(1, 15, onPress2, nullptr, &mux);

void setup() {
    Serial.begin(9600);
}

void loop() {
    // The process methods will poll the button objects and handle all their functionality.
    button1.process();
    button2.process();
}