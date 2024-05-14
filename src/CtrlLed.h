/*!
 *  @file       CtrlLed.h
 *  Project     Arduino CTRL Library
 *  @brief      CTRL Library for interfacing with common controls
 *  @author     Johannes Jan Prins
 *  @date       08/05/2024
 *  @license    MIT - Copyright (c) 2024 Johannes Jan Prins
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef CtrlLed_h
#define CtrlLed_h

#include "CtrlBase.h"
#include <Arduino.h>

class Led : public IMuxableOutput
{
  protected:
    int8_t sig; // Signal pin connected to the LED
    bool on; // Current state of the LED
    uint8_t brightness; // Current brightness level
    uint8_t maxBrightness; // Maximum brightness value

  public:
    explicit Led(
        int8_t sig,
        uint8_t maxBrightness = 255
    );

    void toggle();

    void turnOn();

    void turnOff();

    void setMaxBrightness(uint8_t maxBrightness);

    void setBrightness(uint8_t percentage);

    [[nodiscard]] uint8_t getMaxBrightness() const;

    [[nodiscard]] uint8_t getBrightness() const;

    [[nodiscard]] bool isOn() const;

    [[nodiscard]] bool isOff() const;
};

#endif