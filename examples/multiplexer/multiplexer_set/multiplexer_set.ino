/*
  Multiplexer set daisy chained

  Description:
  This sketch demonstrates the implementation of 2 daisy chained multiplexers.
  One multiplexer has buttons, the other has rotary encoders.
  You can easily adapt this sketch to use it for rotary encoders or potentiometers.
  Just have a look at the other multiplexer examples.
*/

#include <CtrlMuxSet.h>
#include <CtrlMux.h>
#include <CtrlBtn.h>
#include <CtrlEnc.h>

/*
  To manage all requests from our multiplexers and their channels,
  we create a mux set. This mux set acts as a traffic controller,
  ensuring equal processing time for all subscribers. Next, we
  create a mux set for two multiplexers.
 */
CtrlMuxSet muxSet(2);

/*
  Now we create two multiplexers and provide the following parameters:
  - count: the number of channels used on the multiplexer
  - switchInterval: the number of microseconds the multiplexer takes to switch channels
    (Check the datasheet of you mux, to see how long it needs to switch)
  - signal pin
  - s0 - s3: the channel select pins
  - a reference to the mux set: &muxSet
  Note that both multiplexers use the same channel select pins (s0 - s3).
*/
CtrlMux mux1(4, 1, 10, 2, 3, 4, 5, &muxSet);
CtrlMux mux2(2, 1, 11, 2, 3, 4, 5, &muxSet);

// Create some encoders & handlers
void onTurnLeft1() { Serial.println("Encoder 1 on mux 2 turn left"); }
void onTurnRight1() { Serial.println("Encoder 1 on mux 2 turn right"); }
CtrlEnc encoder1 = CtrlEnc::create(0, 1, onTurnLeft1, onTurnRight1, &mux1);

void onTurnLeft2() { Serial.println("Encoder 2 on mux 2 turn left"); }
void onTurnRight2() { Serial.println("Encoder 2 on mux 2 turn right"); }
CtrlEnc encoder2 = CtrlEnc::create(2, 3, onTurnLeft2, onTurnRight2, &mux1);

// Create some buttons & handlers
void onPress1() { Serial.println("Button 1 on mux 1 pressed"); }
void onRelease1() { Serial.println("Button 1 on mux 1 released"); }
CtrlBtn button1 = CtrlBtn::create(0, 15, onPress1, onRelease1, &mux2);

void onPress2() { Serial.println("Button 2 on mux 1 pressed"); }
void onRelease2() { Serial.println("Button 2 on mux 1 released"); }
CtrlBtn button2 = CtrlBtn::create(1, 15, onPress2, onRelease2, &mux2);

void setup() {
    Serial.begin(9600);
}

void loop() {
    button1.process();
    button2.process();
    encoder1.process();
    encoder2.process();
}