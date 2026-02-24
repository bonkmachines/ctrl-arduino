/*
  External ADC example (DMA / async ADC)

  Description:
  A real-time application is one where correctness depends not just on
  what the system computes, but on when it delivers the result. Missing a
  deadline — even by a few microseconds — can mean a dropped MIDI note,
  a motor control glitch, a skipped sensor sample, or a timing fault in
  a safety-critical system. The loop() must complete each iteration within
  a bounded, predictable time window.

  Calling analogRead() blocks the CPU for 10-100 microseconds per read.
  With 8 knobs that's up to 800us of dead time per loop — enough to blow
  past a real-time deadline and cause exactly the kind of jitter described
  above.

  The solution is to let a DMA controller or timer ISR fill a buffer with
  ADC readings in the background, call storeRaw() on each CtrlPot from the
  ISR, and then call process() as normal from the main loop. The library
  still handles:
  - Q16 fixed-point smoothing (filters jitter from noisy ADC readings)
  - Value mapping (raw 0-1023 to your output range, e.g. 0-127 for MIDI)
  - Change detection (only fires the callback when the value actually changes)

  This means you get zero-copy, non-blocking knob processing with no
  boilerplate smoothing, deduplication, or ready-flag management.

  Key concepts:
  - storeRaw(raw)   Called from the ISR. Stores the raw ADC value (0-1023)
                    into an internal volatile buffer. Returns immediately —
                    safe to call from an interrupt context.
  - process()       Called from loop() as normal. If a stored ISR value is
                    pending, it is consumed and processed (smoothing, mapping,
                    callback). Otherwise, falls back to analogRead() as usual.

  This example demonstrates a typical pattern: a timer ISR reads the ADC
  and calls storeRaw() on each pot. The main loop calls process() as usual.
*/

#include <CtrlPot.h>

void onVolumeChange(int value) {
  Serial.print("Volume: ");
  Serial.println(value);
}

void onFilterChange(int value) {
  Serial.print("Filter cutoff: ");
  Serial.println(value);
}

void onResonanceChange(int value) {
  Serial.print("Resonance: ");
  Serial.println(value);
}

void onDriveChange(int value) {
  Serial.print("Drive: ");
  Serial.println(value);
}

CtrlPot volumeKnob(A0, 127, 0.05, onVolumeChange);
CtrlPot filterKnob(A1, 100, 0.05, onFilterChange);
CtrlPot resonanceKnob(A2, 100, 0.05, onResonanceChange);
CtrlPot driveKnob(A3, 255, 0.05, onDriveChange);

// --- DMA / ISR side (runs in background) ---
// On Teensy/STM32/ESP32 you would configure a hardware timer
// or DMA descriptor to trigger this automatically.
// storeRaw() is ISR-safe: it only writes to a volatile buffer and sets a flag.
void timerISR() {
  volumeKnob.storeRaw(analogRead(A0));
  filterKnob.storeRaw(analogRead(A1));
  resonanceKnob.storeRaw(analogRead(A2));
  driveKnob.storeRaw(analogRead(A3));
}

void setup() {
  Serial.begin(9600);

  // In a real project you would configure your timer/DMA here, e.g.:
  // IntervalTimer myTimer;
  // myTimer.begin(timerISR, 1000); // read ADC every 1ms
}

void loop() {
  // Simulate the ISR firing (in a real project the timer does this).
  timerISR();

  // process() detects the pending ISR values and consumes them.
  // No analogRead() calls happen here — zero blocking time.
  volumeKnob.process();
  filterKnob.process();
  resonanceKnob.process();
  driveKnob.process();

  // Your audio/DSP processing goes here — uninterrupted by ADC reads.
}
