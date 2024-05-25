/*
  Multiplexed buttons example

  Description:
  This sketch demonstrates the implementation of a multiplexer.
  You can hook up a multiplexer with a maximum of 16 channels.

  Usage:
  Create a multiplexer with reference to:
  - Sig  (required) Signal pin.
  - S0   (required) Select input 0.
  - S1   (required) Select input 1.
  - S2   (required) Select input 2.
  - S3   (optional) Select input 2. Not needed for an 8 channel multiplexer.

  Available methods:
  - acquire()                       Acquires control of the multiplexer so there's no interference with other objects.
  - release()                       Releases control of the multiplexer so other objects can poll it.
  - digitalReader(uint8_t channel)  Reads a digital signal from a certain channel.
  - analogReader(uint8_t channel)   Reads an analog signal from a certain channel.
*/

#include <CtrlBtn.h>
#include <CtrlMux.h>

// Create a multiplexer object. With:
// The amount of pins used (starting from 0), Signal pin, S0, S1, S2 & S3 (optional).
CtrlMux mux(2, 1, 2, 3, 4, 5);

// Define an onPress handler for the buttons.
void onPress() {
    Serial.println("Button pressed");
}

// Define an onRelease handler for the buttons.
void onRelease() {
    Serial.println("Button released");
}

// Create some buttons. With the signal pin number, bounce duration,
// onPress handler, onRelease handler & reference to the multiplexer.
CtrlBtn button1 = CtrlBtn::create(36, 15, onPress, onRelease, &mux);
CtrlBtn button2 = CtrlBtn::create(37, 15, onPress, onRelease, &mux);

void setup() {
    Serial.begin(9600);
}

void loop() {
    // The process method will poll the button object and handle all it's functionality
    button1.process();
    button2.process();
}