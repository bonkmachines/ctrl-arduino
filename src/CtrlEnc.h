/*!
 *  @file       CtrlEnc.h
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

#ifndef CtrlEnc_h
#define CtrlEnc_h

#include <Arduino.h>
#include "CtrlBase.h"
#include "CtrlMux.h"

class CtrlEncBase : public Muxable
{
    protected:
        uint8_t clk; // CLK pin
        uint8_t dt; // DT pin
        int values[2] = { 0, 0 }; // State of the encoder

        CtrlEncBase(
            uint8_t clk,
            uint8_t dt,
            CtrlMux* mux = nullptr
        );

        ~CtrlEncBase() = default;

        virtual void processInput();
        virtual int8_t readEncoder();
        virtual void onTurnLeft();
        virtual void onTurnRight();

    public:
        void process() override;
        [[nodiscard]] bool isTurningLeft() const;
        [[nodiscard]] bool isTurningRight() const;
};

class CtrlEnc final : public CtrlEncBase
{
    using CallbackFunction = void (*)();
    CallbackFunction onTurnLeftCallback;
    CallbackFunction onTurnRightCallback;

    protected:
        CtrlEnc(
            uint8_t clk,
            uint8_t dt,
            CallbackFunction onTurnLeftCallback = nullptr,
            CallbackFunction onTurnRightCallback = nullptr,
            CtrlMux* mux = nullptr
        );

    public:
        static CtrlEnc create(
            uint8_t clk,
            uint8_t dt,
            CallbackFunction onTurnLeftCallback = nullptr,
            CallbackFunction onTurnRightCallback = nullptr,
            CtrlMux* mux = nullptr
        );

        void setOnTurnLeft(CallbackFunction callback);
        void setOnTurnRight(CallbackFunction callback);

    private:
        void onTurnLeft() override;
        void onTurnRight() override;
};

#endif