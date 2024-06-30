/*
  Multiplexers daisy chained

  Description:
  This sketch demonstrates the implementation of 3 daisy chained multiplexers.
  One multiplexer has buttons, the other has rotary encoders & the third has pots.
*/

#include <CTRL.h>

/*
  Now we create 3 multiplexers and provide the following parameters:
  - signal pin (sig)
  - s0 - s3: the channel select pins
  Note that all multiplexers use the same channel select pins (s0 - s3).
*/

// The button mux. Connect 'sig' to a digital pin on your board.
CtrlMux btnMux(1, 3, 4, 5, 6);

// The potentiometer mux. Connect 'sig' to an analog pin on your board.
CtrlMux potMux(A0, 3, 4, 5, 6);

// The encoder mux. Connect 'sig' to a digital pin on your board.
CtrlMux encMux(2, 3, 4, 5, 6);

void onPress1() { Serial.println("Button 1 pressed"); }
void onRelease1() { Serial.println("Button 1 released"); }
CtrlBtn button1(0, 15, onPress1, onRelease1, nullptr, &btnMux);

void onPress2() { Serial.println("Button 2 pressed"); }
void onRelease2() { Serial.println("Button 2 released"); }
CtrlBtn button2(1, 15, onPress2, onRelease2, nullptr, &btnMux);

void onValueChange1(int value) { Serial.print("Pot 1 value: "); Serial.println(value); }
CtrlPot pot1(0, 100, 0.05, onValueChange1, &potMux);

void onValueChange2(int value) { Serial.print("Pot 2 value: "); Serial.println(value); }
CtrlPot pot2(1, 100, 25, onValueChange2, &potMux);

void onTurnleft1() { Serial.println("Encoder 1 turn left"); }
void onTurnRight1() { Serial.println("Encoder 1 turn right"); }
CtrlEnc encoder1(0, 1, onTurnleft1, onTurnRight1, &encMux);

void onTurnleft2() { Serial.println("Encoder 2 turn left"); }
void onTurnRight2() { Serial.println("Encoder 2 turn right"); }
CtrlEnc encoder2(2, 3, onTurnleft2, onTurnRight2, &encMux);

void setup() {
    Serial.begin(9600);
    btnMux.setSwitchInterval(2); // In microseconds.
    potMux.setSwitchInterval(2); // In microseconds.
    encMux.setSwitchInterval(2); // In microseconds.
}

void loop() {
    btnMux.process();
    potMux.process();
    encMux.process();
}