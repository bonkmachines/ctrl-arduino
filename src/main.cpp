// #include "../examples/button/button_basic/button_basic.ino"
// #include "../examples/button/button_alternative/button_alternative.ino"
// #include "../examples/button/button_advanced/button_advanced.ino"

// #include "../examples/led/led_blink/led_blink.ino"
// #include "../examples/led/led_fade/led_fade.ino"

// #include "../examples/multiplexer/multiplexed_buttons/multiplexed_buttons.ino"
// #include "../examples/multiplexer/multiplexed_potentiometers/multiplexed_potentiometers.ino"
// #include "../examples/multiplexer/multiplexed_rotary_encoder/multiplexed_rotary_encoder.ino"
// #include "../examples/multiplexer/multiplexer_set/multiplexer_set.ino"

// #include "../examples/potentiometer/potentiometer_basic/potentiometer_basic.ino"
// #include "../examples/potentiometer/potentiometer_alternative/potentiometer_alternative.ino"
// #include "../examples/potentiometer/potentiometer_advanced/potentiometer_advanced.ino"

// #include "../examples/rotary_encoder/rotary_encoder_basic/rotary_encoder_basic.ino"
// #include "../examples/rotary_encoder/rotary_encoder_alternative/rotary_encoder_alternative.ino"
// #include "../examples/rotary_encoder/rotary_encoder_advanced/rotary_encoder_advanced.ino"

#include <CtrlMuxSet.h>
#include <CtrlMux.h>
#include <CtrlBtn.h>
#include <CtrlEnc.h>
#include <CtrlPot.h>

CtrlMuxSet muxSet(3);

CtrlMux mux1(2, 1, 8, 2, 3, 4, 5, &muxSet);
CtrlMux mux2(16, 1, A0, 2, 3, 4, 5, &muxSet);
CtrlMux mux3(4, 1, 9, 2, 3, 4, 5, &muxSet);

void onPress1() { Serial.println("Button 1 pressed"); }
void onRelease1() { Serial.println("Button 1 released"); }
CtrlBtn button1 = CtrlBtn::create(0, 15, onPress1, onRelease1, &mux1);

void onPress2() { Serial.println("Button 2 pressed"); }
void onRelease2() { Serial.println("Button 2 released"); }
CtrlBtn button2 = CtrlBtn::create(1, 15, onPress2, onRelease2, &mux1);

void onValueChange1(int value) { Serial.print("Pot 1 value: "); Serial.println(value); }
CtrlPot pot1 = CtrlPot::create(0, 100, 25, onValueChange1, &mux2);

void onValueChange2(int value) { Serial.print("Pot 2 value: "); Serial.println(value); }
CtrlPot pot2 = CtrlPot::create(1, 100, 25, onValueChange2, &mux2);

void onValueChangeEmpty(int value) { Serial.print("Pot empty value: "); Serial.println(value); }
CtrlPot pot3 = CtrlPot::create(2, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot4 = CtrlPot::create(3, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot5 = CtrlPot::create(4, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot6 = CtrlPot::create(5, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot7 = CtrlPot::create(6, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot8 = CtrlPot::create(7, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot9 = CtrlPot::create(8, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot10 = CtrlPot::create(9, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot11 = CtrlPot::create(10, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot12 = CtrlPot::create(11, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot13 = CtrlPot::create(12, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot14 = CtrlPot::create(13, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot15 = CtrlPot::create(14, 100, 25, onValueChangeEmpty, &mux2);
CtrlPot pot16 = CtrlPot::create(15, 100, 25, onValueChangeEmpty, &mux2);

void onTurnleft1() { Serial.println("Encoder 1 turn left"); }
void onTurnRight1() { Serial.println("Encoder 1 turn right"); }
CtrlEnc encoder1 = CtrlEnc::create(0, 1, onTurnleft1, onTurnRight1, &mux3);

void onTurnleft2() { Serial.println("Encoder 2 turn left"); }
void onTurnRight2() { Serial.println("Encoder 2 turn right"); }
CtrlEnc encoder2 = CtrlEnc::create(2, 3, onTurnleft2, onTurnRight2, &mux3);

void setup() {
    Serial.begin(9600);
}

void loop() {
    button1.process();
    button2.process();
    pot1.process();
    pot2.process();
    pot3.process();
    pot4.process();
    pot5.process();
    pot6.process();
    pot7.process();
    pot8.process();
    pot9.process();
    pot10.process();
    pot11.process();
    pot12.process();
    pot13.process();
    pot14.process();
    pot15.process();
    pot16.process();
    encoder1.process();
    encoder2.process();
}