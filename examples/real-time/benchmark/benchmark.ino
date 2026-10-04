/*
  Benchmark example

  Description:
  This sketch measures how long one process() call takes for each type of
  control on your board, so you can plan the time budget of your loop (for
  example in a real-time or audio application). Upload it, open the serial
  monitor at 115200 baud and read the table.

  Usage:
  This sketch needs more than 2 KB of RAM, so it runs on e.g. an Arduino Mega,
  Teensy, ESP32 or Raspberry Pi Pico, but not on an Arduino Uno.
  Nothing needs to be connected: the readings themselves don't matter, only
  the time they take. The times include the board's own digitalRead() and
  analogRead(), which is what your sketch pays for as well.

  What is measured (average per call, in microseconds):
  - Button                    process() of a button.
  - Rotary encoder            process() of a rotary encoder.
  - Potentiometer             process() of a potentiometer that reads its own pin (analogRead).
  - Potentiometer (storeRaw)  process() of a potentiometer fed through storeRaw(), as from an ISR or DMA.
  - LED                       setBrightness() of a PWM LED.
  - Multiplexer, 8 buttons    process() of a multiplexer with 8 buttons attached.
*/

#include <CTRL.h>

const uint16_t ITERATIONS = 1000;

CtrlBtn button(2, 15);
CtrlEnc encoder(3, 4);
CtrlPot potentiometer(A0, 100, 0.05);
CtrlPot storedPotentiometer(A0, 100, 0.05);
CtrlLed led(9, 255);

// An 8-channel multiplexer (no S3) with 8 buttons attached.
CtrlMux mux(8, 10, 11, 12);
CtrlBtn muxButtons[] = {
  CtrlBtn(0, 15), CtrlBtn(1, 15), CtrlBtn(2, 15), CtrlBtn(3, 15),
  CtrlBtn(4, 15), CtrlBtn(5, 15), CtrlBtn(6, 15), CtrlBtn(7, 15)
};

// Runs the given function ITERATIONS times and returns the average time per call.
template <typename Function>
float measure(Function function)
{
  function(); // Warm up (the first call also initializes the control).
  const unsigned long start = micros();
  for (uint16_t i = 0; i < ITERATIONS; i++) {
    function();
  }
  return static_cast<float>(micros() - start) / ITERATIONS;
}

void printRow(const char* name, const float microseconds)
{
  Serial.print(name);
  Serial.print(": ");
  Serial.print(microseconds, 2);
  Serial.println(" us");
}

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 3000) {} // Wait for the serial monitor on boards with native USB.

  for (CtrlBtn& muxButton : muxButtons) {
    muxButton.setMultiplexer(&mux);
  }

  Serial.println("CTRL benchmark: average time per call");
  printRow("Button                  ", measure([] { button.process(); }));
  printRow("Rotary encoder          ", measure([] { encoder.process(); }));
  printRow("Potentiometer           ", measure([] { potentiometer.process(); }));
  printRow("Potentiometer (storeRaw)", measure([] {
    storedPotentiometer.storeRaw(512);
    storedPotentiometer.process();
  }));
  uint8_t brightness = 0;
  printRow("LED                     ", measure([&brightness] { led.setBrightness(brightness++ % 101); }));
  printRow("Multiplexer, 8 buttons  ", measure([] { mux.process(); }));
}

void loop() {}
