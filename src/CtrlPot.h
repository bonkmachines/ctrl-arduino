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

/**
 * @brief Response curves for CtrlPot::getNormalized().
 *
 * - Linear:  the output follows the shaft position (halfway = 0.5).
 * - Log:     "audio taper", slow start, for volume (halfway is about 0.09).
 * - AntiLog: "reverse audio taper", fast start (halfway is about 0.91).
 */
enum class CtrlTaper : uint8_t
{
    Linear,
    Log,
    AntiLog
};

class CtrlPot : public CtrlBase, public Muxable, public Groupable
{
    protected:
        uint8_t sig; // Analog pin connected to the potentiometer.
        uint8_t pinModeType = INPUT;
        uint16_t lastValue = 0; // Last read value from the potentiometer.
        uint16_t lastMappedValue = 0; // Last mapped value based on a mapping to maxOutputValue.
        uint32_t smoothedValue_q16 = 0; // Smoothed value in Q16 fixed-point.
        uint32_t alpha_q16 = 33; // Smoothing factor in Q16 fixed-point (0.0005 * 65536).
        float sensitivity = 0.05; // Sensitivity factor (0.01 - 100).
        int maxOutputValue; // The maximum output value at full turn.
        uint16_t analogMax = 1023; // Maximum value from analogRead().
        bool initialized = false;
        volatile uint16_t isrRawValue = 0;
        volatile bool isrValuePending = false;
        volatile bool changed = false; // Set when the value changes, cleared by hasChanged().
        using CallbackFunction = void (*)(int);
        CallbackFunction onValueChangeCallback = nullptr;

    public:
        /**
        * @brief Instantiate a potentiometer object.
        *
        * The CtrlPot class can be instantiated to allow for specific
        * actions whenever the value of a potentiometer changes.
        *
        * @param sig (uint8_t) The signal pin of the potentiometer.
        * @param maxOutputValue (int) The maximum output value of the potentiometer.
        * @param sensitivity (float) The sensitivity factor. Decrease this value to apply more smoothing for unstable (jittery) pots, min: 0.01, max: 100.
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
        * @brief Provide an externally-read raw ADC value.
        *
        * Use this instead of process() when reading the ADC externally
        * (e.g., via DMA or async ADC). Smoothing and value change
        * detection are still applied.
        *
        * @param rawValue The raw ADC reading (0 - 1023).
        */
        void setRawValue(uint16_t rawValue);

        /**
        * @brief Store a raw ADC value from an ISR or DMA callback.
        *
        * Call this from your timer ISR or DMA completion handler. It stores
        * the value in an internal volatile buffer without any processing.
        * The next call to process() will consume the stored value and apply
        * smoothing, mapping, and change detection as normal.
        *
        * @param rawValue The raw ADC reading (0 - 1023).
        */
        void storeRaw(uint16_t rawValue);

        /**
        * @brief Get the current value of the shaft position.
        *
        * @return The value as a `uint16_t`.
        */
        [[nodiscard]] uint16_t getValue() const;

        /**
        * @brief Get the current value of the shaft position as a percentage
        * of the maximum output value.
        *
        * @return The value as a `uint8_t` (0 - 100).
        */
        [[nodiscard]] uint8_t getPercentage() const;

        /**
        * @brief Get the current value as a fraction of the maximum output value,
        * optionally shaped by a response curve.
        *
        * Handy for audio parameters, e.g. `gain = pot.getNormalized(CtrlTaper::Log);`
        *
        * @param taper (CtrlTaper) The response curve: Linear (default), Log or AntiLog.
        * @return The value as a `float` (0.0 - 1.0).
        */
        [[nodiscard]] float getNormalized(CtrlTaper taper = CtrlTaper::Linear) const;

        /**
        * @brief Checks if the value changed since the last call.
        *
        * Use it to poll for changes instead of (or next to) the onValueChange handler.
        * Safe to call from an interrupt, e.g. an audio callback.
        *
        * @return True once after each change, false otherwise.
        */
        bool hasChanged();

        /**
        * @brief Set the maximum value returned by analogRead().
        *
        * Defaults to 1023 (10-bit ADC). Set to 4095 for boards with
        * 12-bit ADCs (ESP32, Teensy, RP2040, STM32, etc.).
        *
        * @param analogMax The maximum raw ADC value.
        */
        void setAnalogMax(uint16_t analogMax);

        /**
        * @brief Get the maximum value returned by analogRead().
        *
        * @return The maximum raw ADC value as a `uint16_t`.
        */
        [[nodiscard]] uint16_t getAnalogMax() const;

        /**
        * @brief Get the maximum value returned by getValue(), as set in the constructor.
        *
        * @return The maximum output value as a `uint16_t`.
        */
        [[nodiscard]] uint16_t getMaxOutputValue() const;

        /**
        * @brief Set the on value change handler.
        *
        * Pass in a handler that is called whenever the value of the
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
        uint16_t applySmoothing(uint16_t rawValue);
        void processSmoothedValue(uint16_t newValue);
};

#endif