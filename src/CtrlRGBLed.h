/*!
 *  @file       CtrlRGBLed.h
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

#ifndef CtrlRGBLed_h
#define CtrlRGBLed_h

#include <Arduino.h>
#include <array>
#include "CtrlBase.h"

class CtrlRGBLed : public CtrlBase
{
    protected:
        uint8_t sigR; // Signal pin connected to the LED
        uint8_t sigG; // Signal pin connected to the LED
        uint8_t sigB; // Signal pin connected to the LED
        uint8_t sigArr[3];
        std::array<uint8_t, 3> rgbArr = {255, 255, 255}; // default to white
        bool on; // Current state of the LED
        uint8_t brightness; // Current brightness level (PWM mode only)
        uint8_t maxBrightness; // Maximum brightness value (PWM mode only)

    public:
        std::array<uint8_t, 3> kWhite = {255, 255, 255};
        std::array<uint8_t, 3> kOff = {0, 0, 0};
        std::array<uint8_t, 3> kRed = {255, 0, 0};
        std::array<uint8_t, 3> kGreen = {0, 255, 0};
        std::array<uint8_t, 3> kBlue = {0, 0, 255};
        
        /**
        * @brief Instantiate a 4-pin RGB LED
        * 
        * @param sigR (uint8_t) The Red channel pin of the LED.
        * @param sigG (uint8_t) The Green channel pin of the LED.
        * @param sigB (uint8_t) The Blue channel pin of the LED.
        * @param maxBrightness (uint8_t) Sets the maximum brightness of the LED, for calibration purposes (0 - 255).
        * @return A new CtrlRGBLed object
        */
        explicit CtrlRGBLed(
            uint8_t sigR,
            uint8_t sigG,
            uint8_t sigB,
            uint8_t maxBrightness
        );

        /**
        * @brief Set the LED to a specific on/off state.
        * 
        * @param state (bool) The target state.
        */
        void set(bool state);

        /**
         * @brief Set the RGB values for the LED.
         *
         * @param rgb (uint8_t[3]) Array with values {R, G, B} (0-255).
         */
        void setRGB(const uint8_t rgb[3]);

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
         * @brief Get the raw RGB values pushed to the LED.
         * 
         * @return The array of raw RGB values.
         */
        [[nodiscard]] std::array<uint8_t, 3> getRGBRaw() const;

        /**
         * @brief Get the scaled RGB values pushed to the LED.
         * 
         * Scaled values are multiplied by the LED's brightness percentage.
         * 
         * @return The array of scaled RGB values.
         */
        [[nodiscard]] std::array<uint8_t, 3> getRGB() const;

    protected:
        bool initialized = false;
        void initialize();
        void processOutput() const;
};

#endif