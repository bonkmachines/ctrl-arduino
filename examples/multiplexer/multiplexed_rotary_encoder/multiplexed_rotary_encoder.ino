/*
  Multiplexed rotary encoders example

  Description:
  This sketch demonstrates the implementation of a multiplexer with rotary encoders.
  You can hook up a multiplexer with a maximum of 16 channels.

  It is not advisable (although it is possible) to put pots on the same mux
  as buttons & rotary encoders. This has to do with performance and the
  potential for interference. But feel free to test it out yourself.

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
#include <CtrlEnc.h>

/*
  Create a multiplexer and provide the following parameters:
  - count: the number of channels used on the multiplexer
  - switchInterval: the number of microseconds the multiplexer takes to switch channels
    (Check the datasheet of your mux, to see how long it needs to switch)
  - signal pin
  - s0 - s3: the channel select pins
*/
CtrlMux mux(38, 34, 35, 36, 37);

// Define an onTurnleft handler for encoder 1.
void onTurnleft1() {
    Serial.println("Rotary encoder 1 turn left");
}

// Define an onTurnRight handler for encoder 1.
void onTurnRight1() {
    Serial.println("Rotary encoder 1 turn right");
}

// Define an onTurnleft handler for encoder 2.
void onTurnleft2() {
    Serial.println("Rotary encoder 2 turn left");
}

// Define an onTurnRight handler for encoder 2.
void onTurnRight2() {
    Serial.println("Rotary encoder 2 turn right");
}

// Create two rotary encoders with the following parameters:
// clk signal pin & dt signal pin (both correspond to the attached channels on the multiplexer),
// onTurnleft (optional) & onTurnRight (optional) handler,
// & a reference (&mux) to the multiplexer.
CtrlEnc encoder1 = CtrlEnc::create(0, 1, onTurnleft1, onTurnRight1, &mux);
CtrlEnc encoder2 = CtrlEnc::create(2, 3, onTurnleft2, onTurnRight2, &mux);

void setup() {
    Serial.begin(9600);
}

void loop() {
    // The process methods will poll the encoder objects and handle all their functionality.
    encoder1.process();
    encoder2.process();
}