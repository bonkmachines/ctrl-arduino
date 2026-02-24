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

#include <Arduino.h>
#include "CtrlBase.h"

class CtrlLed : public CtrlBase
{
    protected:
        uint8_t sig; // Signal pin connected to the LED
        bool on; // Current state of the LED
        uint8_t brightness; // Current brightness level (PWM mode only)
        uint8_t maxBrightness; // Maximum brightness value (PWM mode only)
        bool pwmMode; // True if LED is on a PWM-capable pin, false for digital pins

    public:
        /**
        * @brief Instantiate an LED object for a PWM-capable pin.
        *
        * The CtrlLed class can be instantiated to allow LED objects to be controlled.
        * When maxBrightness is provided, PWM mode is enabled for brightness control.
        *
        * @param sig (uint8_t) The signal pin of the LED.
        * @param maxBrightness (uint8_t) Sets the maximum brightness of the LED, for calibration purposes (0 - 255). PWM mode enabled.
        * @return A new instance of the CtrlLed class in PWM mode.
        */
        explicit CtrlLed(
            uint8_t sig,
            uint8_t maxBrightness
        );

        /**
        * @brief Instantiate an LED object for a digital (non-PWM) pin.
        *
        * The CtrlLed class can be instantiated to allow LED objects to be controlled.
        * When maxBrightness is omitted, digital mode is enabled for on/off control only.
        *
        * @param sig (uint8_t) The signal pin of the LED.
        * @return A new instance of the CtrlLed class in digital mode.
        */
        explicit CtrlLed(uint8_t sig);

        /**
        * @brief Toggles the LED's off/on status.
        */
        void toggle();

        /**
        * @brief Turns on the LED.
        */
        void turnOn();

        /**
        * @brief Turns off the LED.
        */
        void turnOff();

        /**
        * @brief Sets the maximum brightness of the LED, for calibration purposes (PWM mode only).
        *
        * This method is only available when the LED is connected to a PWM-capable pin.
        * In digital mode, this method is ignored.
        *
        * @param maxBrightness (int) Sets the maximum brightness of the LED, for calibration purposes (0 - 255).
        */
        void setMaxBrightness(int maxBrightness);

        /**
        * @brief Sets the brightness of the LED in percentages (PWM mode only).
        *
        * This method is only available when the LED is connected to a PWM-capable pin.
        * In digital mode, this method is ignored.
        *
        * @param percentage (int) Sets the brightness. (0 - 100).
        */
        void setBrightness(int percentage);

        /**
        * @brief Returns the maximum brightness set for the LED.
        *
        * @return The maximum brightness value (0 - 255) as a `uint8_t`.
        */
        [[nodiscard]] uint8_t getMaxBrightness() const;

        /**
        * @brief Returns the brightness of the LED.
        *
        * @return The brightness percentage (0 - 100) as a `uint8_t`.
        */
        [[nodiscard]] uint8_t getBrightness() const;

        /**
        * @brief Checks if the LED is turned on.
        *
        * @return True if the LED is turned on, false otherwise.
        */
        [[nodiscard]] bool isOn() const;

        /**
        * @brief Checks if the LED is turned off.
        *
        * @return True if the LED is turned off, false otherwise.
        */
        [[nodiscard]] bool isOff() const;

        /**
        * @brief Checks if the LED is in PWM mode.
        *
        * @return True if the LED is connected to a PWM-capable pin, false if in digital mode.
        */
        [[nodiscard]] bool isPwmMode() const;

    protected:
        bool initialized = false;
        void initialize();
        void processOutput() const;
};

#endif