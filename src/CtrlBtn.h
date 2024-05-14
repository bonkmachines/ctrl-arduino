/*!
 *  @file       CtrlBtn.h
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

#ifndef CtrlBtn_h
#define CtrlBtn_h

#include "CtrlBase.h"
#include <Arduino.h>

class CtrlBtnBase : public IMuxableInput
{
    protected:
        uint8_t sig; // Signal pin
        bool currentState;
        bool lastState;
        unsigned long debounceStart = 0;
        uint16_t bounceDuration;

        CtrlBtnBase(
            uint8_t sig,
            uint16_t bounceDuration
        );

        virtual uint8_t processInput();

        virtual void onPress();

        virtual void onRelease();

    public:
        void process() override;

        [[nodiscard]] bool isPressed() const;

        [[nodiscard]] bool isReleased() const;
};

class CtrlBtn final : public CtrlBtnBase
{
    using CallbackFunction = void (*)();
    CallbackFunction onPressCallback;
    CallbackFunction onReleaseCallback;

    protected:
        CtrlBtn(
            uint8_t sig,
            uint16_t bounceDuration,
            CallbackFunction onPressCallback = nullptr,
            CallbackFunction onReleaseCallback = nullptr
        );

    public:
        static CtrlBtn create(
            uint8_t sig,
            uint16_t bounceDuration,
            CallbackFunction onPressCallback = nullptr,
            CallbackFunction onReleaseCallback = nullptr
        );

        void setOnPress(CallbackFunction callback);

        void setOnRelease(CallbackFunction callback);

    private:
        void onPress() override;

        void onRelease() override;
};

#endif