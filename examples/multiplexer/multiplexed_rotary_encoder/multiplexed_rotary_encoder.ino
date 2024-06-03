/*
  Multiplexed rotary encoders example

  Description:
  This sketch demonstrates the implementation of a multiplexer with rotary encoders.
  You can hook up a multiplexer with a maximum of 16 channels.

  Usage:
  Create a multiplexer with reference to:
  - sig              (required) Signal pin.
  - s0               (required) Select input 0 (used internally for switching channels).
  - s1               (required) Select input 1 (used internally for switching channels).
  - s2               (required) Select input 2 (used internally for switching channels).
  - s3               (optional) Select input 3 (used internally for switching channels).
                     Only needed if you use a 16 channel mux. Not needed for 8 channels.

  Available methods:
  - setSwitchInterval()  Sets the time we allow the multiplexer to switch (in microseconds)
                         The default value is 1 microsecond.

    NOTE: Make sure to check the datasheet of your multiplexer to determine if the default
    1 microsecond switching interval is sufficient. For example, a Sparkfun CD74HC4067
    running at 5 volts will probably operate fine at a switching speed of 1 microsecond.
    However, if you run it at 3.3 volts, it will need a switching interval of around 2
    microseconds or higher. You can set this with: mux.setSwitchInterval(2).
    There are, however, more factors that determine how responsive your MUX is, such as
    signal integrity and power supply noise. Always add some decoupling capacitors to your
    MUX power supply and at any other place where noise might be created.
*/

#include <CtrlMux.h>
#include <CtrlEnc.h>

/*
  Create a multiplexer and provide the following parameters:
  - signal pin.
  - s0 - s3: the channel select pins (s3 is optional).
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
CtrlEnc encoder1(0, 1, onTurnleft1, onTurnRight1, &mux);
CtrlEnc encoder2(2, 3, onTurnleft2, onTurnRight2, &mux);

void setup() {
    Serial.begin(9600);
    mux.setSwitchInterval(2); // In microseconds.
}

void loop() {
    // The process methods will poll the encoder objects and handle all their functionality.
    encoder1.process();
    encoder2.process();
}