/*
  Multiplexed buttons example

  Description:
  This sketch demonstrates the implementation of a multiplexer with buttons.
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
#include <CtrlBtn.h>

/*
  Create a multiplexer and provide the following parameters:
  - signal pin.
  - s0 - s3: the channel select pins (s3 is optional).
*/
CtrlMux mux(38, 34, 35, 36, 37);

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
CtrlBtn button1(0, 15, onPress1, nullptr, &mux);
CtrlBtn button2(1, 15, onPress2, nullptr, &mux);

void setup() {
    Serial.begin(9600);
    mux.setSwitchInterval(2); // In microseconds.
}

void loop() {
    // The process methods will poll the button objects and handle all their functionality.
    button1.process();
    button2.process();
}