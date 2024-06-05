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

class CtrlLed
{
    protected:
        uint8_t sig; // Signal pin connected to the LED
        bool on; // Current state of the LED
        uint8_t brightness; // Current brightness level
        uint8_t maxBrightness; // Maximum brightness value

    public:
        /**
        * @brief Instantiate an LED object.
        *
        * The CtrlLed class can be instantiated to allow LED objects to be controlled.
        *
        * @param sig (uint8_t) The signal pin of the LED.
        * @param maxBrightness (uint8_t) (optional) Sets the maximum brightness of the LED, for calibration purposes (0 - 255). Default is 255.
        * @return A new instance of the CtrlLed class.
        */
        explicit CtrlLed(
            uint8_t sig,
            uint8_t maxBrightness = 255
        );

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
        * @brief Sets the maximum brightness of the LED, for calibration purposes.
        *
        * @param maxBrightness (int) Sets the maximum brightness of the LED, for calibration purposes (0 - 255).
        */
        void setMaxBrightness(int maxBrightness);

        /**
        * @brief Sets the brightness of the LED in percentages.
        *
        * @param percentage (int) Sets the maximum brightness. (0 - 100).
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

    protected:
        static void processOutput(uint8_t sig, uint8_t brightness);
};

#endif