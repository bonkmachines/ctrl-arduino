# LED hookup guide

LEDs (Light Emitting Diodes) are the simplest way to give visual feedback 
in your projects: a status light, a level indicator or a button that lights 
up when it's active. In this guide, we will walk you through connecting a 
regular LED and a 4-pin RGB LED to an Arduino and controlling them with the 
CTRL library.

***

### Parts required

* An Arduino Uno (or any other Arduino-compatible board)
* 1x LED (any colour)
* 1x 4-pin RGB LED (common cathode or common anode)
* 4x 220Ω resistors
* A solderless breadboard
* Some jumper wires (male to male)

***

### Instructions

#### A single LED

An LED only lets current flow in one direction. The longer leg is the anode (+), 
the shorter leg is the cathode (-). An LED also needs a resistor in series to 
limit the current, otherwise it (or your Arduino's pin) can burn out. A 220Ω 
resistor is a safe value for most LEDs at 5V and 3.3V.

| LED leg             | Connects to                          |
|---------------------|--------------------------------------|
| Anode (long leg)    | 220Ω resistor → Arduino pin (e.g. 9) |
| Cathode (short leg) | GND                                  |

The CTRL library can drive an LED in two ways:

* Digital mode, on any pin: the LED is either on or off.
* PWM mode, on a PWM-capable pin: the brightness can also be set. On an Arduino 
Uno these are pins 3, 5, 6, 9, 10 & 11 (marked with a ~ on the board).

NOTE: On ESP32 boards, PWM mode and RGB LEDs need version 3.0 or later of the 
ESP32 board package (Tools > Board > Boards Manager), as older versions lack 
`analogWrite()`. Most pins on ESP32 and Raspberry Pi Pico boards are PWM-capable.

Example:
```c++
CtrlLed led(13);       // Digital mode, on/off only.
CtrlLed led(9, 255);   // PWM mode, with a maximum brightness of 255.
```

The maximum brightness (0 - 255) can be used to calibrate an LED. Some LEDs are 
much brighter than others, so when you use several of them you can lower the 
maximum brightness of the brightest ones to match the rest.

#### An RGB LED

A 4-pin RGB LED is three LEDs (red, green & blue) in one housing. By mixing the 
brightness of the three, it can show almost any colour. The longest leg is the 
common leg, shared by all three colours. There are two types:

* Common cathode: the common leg goes to GND. This is the most common type.
* Common anode: the common leg goes to 5V (or 3.3V on 3.3V boards).

If you're not sure which type you have, check its datasheet, or simply try 
both: with the wrong type set, the colours will be inverted (white shows as 
off and off shows as white).

The legs are usually in this order, with the longest leg second (check your LED's datasheet):

| RGB LED leg      | Common cathode         | Common anode             |
|------------------|------------------------|--------------------------|
| Red              | 220Ω resistor → pin 9  | 220Ω resistor → pin 9    |
| Common (longest) | GND                    | 5V (3.3V on 3.3V boards) |
| Green            | 220Ω resistor → pin 10 | 220Ω resistor → pin 10   |
| Blue             | 220Ω resistor → pin 11 | 220Ω resistor → pin 11   |

Each colour gets its own resistor; don't share one resistor on the common leg, 
or the colours will affect each other's brightness.

All three pins need to be PWM-capable, as the colour is made by setting the 
brightness of each leg.

Example:
```c++
CtrlRGBLed led(9, 10, 11, 255);                 // Common cathode.
CtrlRGBLed led(9, 10, 11, 255, COMMON_ANODE);   // Common anode.
```

A colour is set as red, green & blue values (0 - 255 each), or as one of the 
ready-made colours: `CtrlColor::Off`, `White`, `Red`, `Green`, `Blue`, `Yellow`, 
`Cyan` & `Magenta`. You can also define your own as a `CtrlRGB`. The brightness 
scales the whole colour, and the colour is kept when the LED is turned off and 
on again.

```c++
const CtrlRGB pink = {255, 51, 153};

led.setColor(255, 128, 0);       // Orange.
led.setColor(CtrlColor::Cyan);
led.setColor(pink);
led.setBrightness(50);           // Half brightness, same colour.
```

***

### Example code

We will assume you know how to use the Arduino IDE and upload your sketches 
to a board. If not, have a look at the tutorials at: https://www.arduino.cc/guide

Also make sure you have the CTRL library installed through the library manager.

This sketch lights up a regular LED on pin 13 while the RGB LED cycles through 
a few colours.

```c++
#include <CtrlLed.h>
#include <CtrlRGBLed.h>

CtrlLed led(13);
CtrlRGBLed rgbLed(9, 10, 11, 255);

void setup() {
  led.turnOn();
  rgbLed.turnOn();
}

void loop() {
  rgbLed.setColor(CtrlColor::Red);
  delay(500);
  rgbLed.setColor(CtrlColor::Green);
  delay(500);
  rgbLed.setColor(CtrlColor::Blue);
  delay(500);
}
```

For more, have a look at the LED examples: led_blink, led_fade, led_set, 
led_rgb & led_rgb_pot. They also list every available method.
