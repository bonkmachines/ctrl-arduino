/*
  Time-sliced processing example (real-time safe)

  Description:
  A real-time application is one where correctness depends not just on
  what the system computes, but on when it delivers the result. The loop()
  must complete each iteration within a bounded, predictable time window —
  whether that window is driven by an audio callback, a USB polling interval,
  a PID control rate, or any other time-critical constraint.

  Processing all controls in a single loop iteration can cause that window
  to be exceeded unpredictably, depending on how many controls are attached.
  This example demonstrates how to use process(count) to spread the work
  across multiple loop iterations using round-robin scheduling, keeping each
  iteration's execution time short and constant.

  Key concepts:
  - reserve(n)       Pre-allocate memory for n objects to avoid heap reallocation
                     as objects are added. Call this before registering objects
                     (e.g. before calling setMultiplexer()). When objects are
                     declared globally and passed a mux via the constructor,
                     they register during global initialization — before setup()
                     runs — so reserve() has no effect in that case.
  - process(count)   Process 'count' objects per call in round-robin order.
                     When count is 0 (default), all objects are processed at once.

  In this example we have 8 buttons on a multiplexer and process only 2 per
  loop iteration. This means all 8 buttons are serviced every 4 iterations,
  keeping each loop cycle short and predictable.
*/

#include <CtrlMux.h>
#include <CtrlBtn.h>

CtrlMux mux(1, 2, 3, 4, 5);

void onPress0() { Serial.println("Button 0 pressed"); }
void onPress1() { Serial.println("Button 1 pressed"); }
void onPress2() { Serial.println("Button 2 pressed"); }
void onPress3() { Serial.println("Button 3 pressed"); }
void onPress4() { Serial.println("Button 4 pressed"); }
void onPress5() { Serial.println("Button 5 pressed"); }
void onPress6() { Serial.println("Button 6 pressed"); }
void onPress7() { Serial.println("Button 7 pressed"); }

CtrlBtn btn0(0, 15, onPress0, nullptr, nullptr, &mux);
CtrlBtn btn1(1, 15, onPress1, nullptr, nullptr, &mux);
CtrlBtn btn2(2, 15, onPress2, nullptr, nullptr, &mux);
CtrlBtn btn3(3, 15, onPress3, nullptr, nullptr, &mux);
CtrlBtn btn4(4, 15, onPress4, nullptr, nullptr, &mux);
CtrlBtn btn5(5, 15, onPress5, nullptr, nullptr, &mux);
CtrlBtn btn6(6, 15, onPress6, nullptr, nullptr, &mux);
CtrlBtn btn7(7, 15, onPress7, nullptr, nullptr, &mux);

void setup() {
  Serial.begin(9600);

  // If you register objects dynamically (e.g. via setMultiplexer()), call
  // reserve() here first to pre-allocate for the expected number of objects
  // and avoid heap reallocation as each one is added:
  //
  // mux.reserve(8);
  // btn0.setMultiplexer(&mux);
  // btn1.setMultiplexer(&mux);
  // ...
}

void loop() {
  // Process 2 buttons per loop iteration (round-robin).
  // All 8 buttons are serviced every 4 iterations.
  mux.process(2);

  // Your audio/DSP processing goes here.
  // The short, predictable control processing time per iteration
  // ensures minimal interference with time-critical audio code.
}
