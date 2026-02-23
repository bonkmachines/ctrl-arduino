/*
  Group switching example (page/mode switching)

  Description:
  This sketch demonstrates how to use group enable/disable to implement
  page or mode switching. This is useful when you have a limited number
  of physical controls but want them to serve different functions depending
  on the active mode.

  In this example, a "mode" button switches between two groups:
  - Group A: the potentiometer controls volume.
  - Group B: the potentiometer controls filter cutoff.

  Only one group is active at a time. The potentiometer is registered to
  both groups, but only the enabled group's handler fires.

  Key concepts:
  - group.enable()     Enable the group (objects are processed).
  - group.disable()    Disable the group (objects are skipped).
  - group.isEnabled()  Check if the group is currently enabled.

  CtrlGroup methods:
  - enable()                        Enable the group.
  - disable()                       Disable the group.
  - isEnabled()                     Check if the group is enabled.
  - isDisabled()                    Check if the group is disabled.
  - reserve(n)                      Pre-allocate capacity for n objects.
  - process()                       Process all objects in the group.
  - process(count)                  Process 'count' objects (round-robin).
  - setOnPress(handler)             Set the on press handler (for buttons).
  - setOnRelease(handler)           Set the on release handler (for buttons).
  - setOnDelayedRelease(handler)    Set the on delayed release handler (for buttons).
  - setOnTurnLeft(handler)          Set the on turn left handler (for encoders).
  - setOnTurnRight(handler)         Set the on turn right handler (for encoders).
  - setOnValueChange(handler)       Set the on value change handler (for pots).
*/

#include <CtrlGroup.h>
#include <CtrlBtn.h>
#include <CtrlPot.h>

CtrlGroup volumeGroup;
CtrlGroup filterGroup;

CtrlPot knob(A0, 127, 0.5);

void onVolumeChange(Groupable& pot, int value) {
  Serial.print("Volume: ");
  Serial.println(value);
}

void onFilterChange(Groupable& pot, int value) {
  Serial.print("Filter: ");
  Serial.println(value);
}

void onModeSwitch() {
  if (volumeGroup.isEnabled()) {
    volumeGroup.disable();
    filterGroup.enable();
    knob.setGroup(&filterGroup);
    Serial.println("Switched to Filter mode");
  } else {
    filterGroup.disable();
    volumeGroup.enable();
    knob.setGroup(&volumeGroup);
    Serial.println("Switched to Volume mode");
  }
}

CtrlBtn modeButton(2, 15, onModeSwitch);

void setup() {
  Serial.begin(9600);

  volumeGroup.setOnValueChange(onVolumeChange);
  filterGroup.setOnValueChange(onFilterChange);

  knob.setGroup(&volumeGroup);

  // Start with volume mode active, filter mode disabled.
  volumeGroup.enable();
  filterGroup.disable();

  Serial.println("Volume mode active");
}

void loop() {
  modeButton.process();

  volumeGroup.process();
  filterGroup.process();
}
