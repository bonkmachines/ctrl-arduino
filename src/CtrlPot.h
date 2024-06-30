/*!
 *  @file       CtrlPot.h
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

#ifndef CtrlPot_h
#define CtrlPot_h

#include <Arduino.h>
#include "CtrlBase.h"
#include "CtrlMux.h"
#include "Groupable.h"
#include "Muxable.h"

class CtrlPot : public CtrlBase, public Muxable, public Groupable
{
    protected:
        uint8_t sig; // Analog pin connected to the potentiometer.
        uint8_t pinModeType = INPUT;
        uint16_t lastValue = 0; // Last read value from the potentiometer.
        uint16_t lastMappedValue = 0; // Last mapped value based on a mapping to maxOutputValue.
        float smoothedValue = 0.0; // Smoothed value for the potentiometer.
        float alpha = 0.0005; // Smoothing factor (0.0001 - 1).
        float sensitivity = 0.05; // Sensitivity factor (0.01 - 100).
        int maxOutputValue; // The maximum output value at full turn.
        uint16_t analogMax = 1023; // Maximum value from analogRead().
        bool initialized = false;
        using CallbackFunction = void (*)(int);
        CallbackFunction onValueChangeCallback;

    public:
        /**
        * @brief Instantiate a potentiometer object.
        *
        * The CtrlPot class can be instantiated to allow for specific
        * actions whenever the value of a potentiometer changes.
        *
        * @param sig (uint8_t) The signal pin of the potentiometer.
        * @param maxOutputValue (int) The maximum output value of the potentiometer.
        * @param sensitivity (float) The sensitivity factor. Decrease this for instable (jittery) pots, min: 0.01, max: 100.
        * @param onValueChangeCallback (optional) The on value change callback handler. Default is nullptr.
        * @param mux (CtrlMux) (optional) The multiplexer the pot is connected to. Default is nullptr.
        * @return A new instance of the CtrlPot class.
        */
        CtrlPot(
            uint8_t sig,
            int maxOutputValue,
            float sensitivity,
            CallbackFunction onValueChangeCallback = nullptr,
            CtrlMux* mux = nullptr
        );

        /**
        * @brief The process method should be called within the loop method. It handles all functionality.
        */
        void process() override;

        /**
        * @brief Get the current value of the shaft position.
        *
        * @return The value as a `uint16_t`.
        */
        [[nodiscard]] uint16_t getValue() const;

        /**
        * @brief Set the on value changehandler.
        *
        * Pas in a handler that is called whenever the value of the
        * potentiometer changes. In other words, when it's turned.
        *
        * @param callback The callback handler method.
        */
        void setOnValueChange(CallbackFunction callback);

    protected:
        void initialize();
        [[nodiscard]] bool isInitialized() const;
        virtual uint16_t processInput();
        virtual void onValueChange(int value);
        void setSensitivity(float sensitivity);
        void updateAlpha();
};

#endif