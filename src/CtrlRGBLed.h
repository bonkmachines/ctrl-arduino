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
#include "CtrlBase.h"

/**
 * @brief A colour, as red, green and blue values (0 - 255 each).
 */
struct CtrlRGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

/**
 * @brief Ready-made colours, e.g. `led.setColor(CtrlColor::Red);`
 */
namespace CtrlColor
{
    constexpr CtrlRGB Off     = {0, 0, 0};
    constexpr CtrlRGB White   = {255, 255, 255};
    constexpr CtrlRGB Red     = {255, 0, 0};
    constexpr CtrlRGB Green   = {0, 255, 0};
    constexpr CtrlRGB Blue    = {0, 0, 255};
    constexpr CtrlRGB Yellow  = {255, 255, 0};
    constexpr CtrlRGB Cyan    = {0, 255, 255};
    constexpr CtrlRGB Magenta = {255, 0, 255};
}

#ifdef COMMON_CATHODE
    #undef COMMON_CATHODE
#endif
static constexpr uint8_t COMMON_CATHODE = 0;

#ifdef COMMON_ANODE
    #undef COMMON_ANODE
#endif
static constexpr uint8_t COMMON_ANODE = 1;

class CtrlRGBLed : public CtrlBase
{
    protected:
        uint8_t sig[3]; // Signal pins connected to the red, green & blue legs of the LED
        uint8_t type; // COMMON_CATHODE or COMMON_ANODE
        CtrlRGB color = CtrlColor::White; // Current colour of the LED
        bool on; // Current state of the LED
        uint8_t brightness; // Current brightness level
        uint8_t maxBrightness; // Maximum brightness value

    public:
        /**
        * @brief Instantiate an RGB LED object (4-pin RGB LED).
        *
        * All three signal pins need to be PWM-capable.
        *
        * @param sigR (uint8_t) The pin connected to the red leg of the LED.
        * @param sigG (uint8_t) The pin connected to the green leg of the LED.
        * @param sigB (uint8_t) The pin connected to the blue leg of the LED.
        * @param maxBrightness (uint8_t) Sets the maximum brightness of the LED, for calibration purposes (0 - 255).
        * @param type (uint8_t) COMMON_CATHODE (default) or COMMON_ANODE, depending on your LED.
        * @return A new instance of the CtrlRGBLed class.
        */
        CtrlRGBLed(
            uint8_t sigR,
            uint8_t sigG,
            uint8_t sigB,
            uint8_t maxBrightness,
            uint8_t type = COMMON_CATHODE
        );

        /**
        * @brief Turns the LED on or off according to the given state.
        *
        * @param state (bool) True to turn the LED on, false to turn it off.
        */
        void set(bool state);

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
        * @brief Sets the colour of the LED.
        *
        * The colour is kept when the LED is turned off and on again.
        * Setting a colour does not turn the LED on.
        *
        * @param r (uint8_t) Red (0 - 255).
        * @param g (uint8_t) Green (0 - 255).
        * @param b (uint8_t) Blue (0 - 255).
        */
        void setColor(uint8_t r, uint8_t g, uint8_t b);

        /**
        * @brief Sets the colour of the LED, e.g. `led.setColor(CtrlColor::Red);`
        *
        * @param color (CtrlRGB) The colour.
        */
        void setColor(CtrlRGB color);

        /**
        * @brief Sets the maximum brightness of the LED, for calibration purposes.
        *
        * @param maxBrightness (int) Sets the maximum brightness of the LED (0 - 255).
        */
        void setMaxBrightness(int maxBrightness);

        /**
        * @brief Sets the brightness of the LED in percentages.
        *
        * @param percentage (int) Sets the brightness. (0 - 100).
        */
        void setBrightness(int percentage);

        /**
        * @brief Returns the colour set for the LED, regardless of its brightness.
        *
        * @return The colour as a `CtrlRGB`.
        */
        [[nodiscard]] CtrlRGB getColor() const;

        /**
        * @brief Returns the colour the LED actually outputs: its colour scaled by its brightness.
        * Returns CtrlColor::Off while the LED is off.
        *
        * @return The output colour as a `CtrlRGB`.
        */
        [[nodiscard]] CtrlRGB getOutputColor() const;

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
        * @brief Checks if the LED is a common anode LED.
        *
        * @return True for a common anode LED, false for a common cathode LED.
        */
        [[nodiscard]] bool isCommonAnode() const;

    protected:
        bool initialized = false;
        void initialize();
        void processOutput() const;
        void writeChannel(uint8_t pin, uint8_t value) const;
};

#endif
