/*
  Multiplexers daisy chained

  Description:
  This sketch demonstrates the implementation of 3 daisy chained multiplexers.
  One multiplexer has buttons, the other has rotary encoders & the third has pots.
*/

#include <CTRL.h>

/*
  Now we create 3 multiplexers and provide the following parameters:
  - signal pin
  - s0 - s3: the channel select pins
  Note that all multiplexers use the same channel select pins (s0 - s3).
*/
CtrlMux mux1(8, 2, 3, 4, 5);  // Connect to a digital pin
CtrlMux mux2(A0, 2, 3, 4, 5); // This mux holds our pots, so make sure you connect it to an analog pin
CtrlMux mux3(9, 2, 3, 4, 5);  // Connect to a digital pin

void onPress1() { Serial.println("Button 1 pressed"); }
void onRelease1() { Serial.println("Button 1 released"); }
CtrlBtn button1(0, 15, onPress1, onRelease1, &mux1);

void onPress2() { Serial.println("Button 2 pressed"); }
void onRelease2() { Serial.println("Button 2 released"); }
CtrlBtn button2(1, 15, onPress2, onRelease2, &mux1);

void onValueChange1(int value) { Serial.print("Pot 1 value: "); Serial.println(value); }
CtrlPot pot1(0, 100, 25, onValueChange1, &mux2);

void onValueChange2(int value) { Serial.print("Pot 2 value: "); Serial.println(value); }
CtrlPot pot2(1, 100, 25, onValueChange2, &mux2);

void onTurnleft1() { Serial.println("Encoder 1 turn left"); }
void onTurnRight1() { Serial.println("Encoder 1 turn right"); }
CtrlEnc encoder1(0, 1, onTurnleft1, onTurnRight1, &mux3);

void onTurnleft2() { Serial.println("Encoder 2 turn left"); }
void onTurnRight2() { Serial.println("Encoder 2 turn right"); }
CtrlEnc encoder2(2, 3, onTurnleft2, onTurnRight2, &mux3);

void setup() {
    Serial.begin(9600);
}

void loop() {
    button1.process();
    button2.process();
    pot1.process();
    pot2.process();
    encoder1.process();
    encoder2.process();
}