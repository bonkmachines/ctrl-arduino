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
#include "Groupable.h"

class CtrlEnc : public Muxable, public Groupable
{
    protected:
        uint8_t clk; // CLK pin
        uint8_t dt; // DT pin
        uint8_t pinModeType = INPUT_PULLUP;
        uint8_t resistorPull = PULL_UP;
        int values[2] = { 0, 0 }; // State of the encoder
        bool initialized = false;
        using CallbackFunction = void (*)();
        CallbackFunction onTurnLeftCallback;
        CallbackFunction onTurnRightCallback;

    public:
        /**
        * @brief Instantiate a rotary encoder object.
        *
        * The CtrlEnc class can be instantiated to allow for specific
        * actions on turnign left, & on turning right.
        *
        * @param clk (uint8_t) The CLK signal pin of the encoder.
        * @param dt (uint8_t) The DT signal pin of the encoder.
        * @param onTurnLeftCallback (optional) The on turn left callback handler. Default is nullptr.
        * @param onTurnRightCallback (optional) The on turn right callback handler. Default is nullptr.
        * @param mux (CtrlMux) (optional) The multiplexer the button is connected to. Default is nullptr.
        * @return A new instance of the CtrlEnc class.
        */
        CtrlEnc(
            uint8_t clk,
            uint8_t dt,
            CallbackFunction onTurnLeftCallback = nullptr,
            CallbackFunction onTurnRightCallback = nullptr,
            CtrlMux* mux = nullptr
        );

        /**
        * @brief Sets the pinMode.
        *
        * @param pinModeType Set to INPUT, INPUT_PULLUP or INPUT_PULLDOWN.
        * @param resistorPull (optional) If pinModeType is set to INPUT,
        * there needs to be and external pull-up or pull-down resistor
        * implemented. Here you specify if it's configured 'PULL_UP' or 'PULL_DOWN'
        * (default is 'PULL_UP').
        */
        void setPinMode(uint8_t pinModeType, uint8_t resistorPull = PULL_UP);

        /**
        * @brief The process method should be called within the loop method. It handles all functionality.
        */
        void process() override;

        /**
        * @brief Find out if an encoder is currently turning left.
        *
        * @return True if encoder is turning left, false otherwise.
        */
        [[nodiscard]] bool isTurningLeft() const;

        /**
        * @brief Find out if an encoder is currently turning right.
        *
        * @return True if encoder is turning right, false otherwise.
        */
        [[nodiscard]] bool isTurningRight() const;

        /**
        * @brief Set the on turn left handler.
        *
        * Pass in a handler that is called whenever the encoder turns left.
        *
        * @param callback The callback handler method.
        */
        void setOnTurnLeft(CallbackFunction callback);

        /**
        * @brief Set the on turn right handler.
        *
        * Pass in a handler that is called whenever the encoder turns right.
        *
        * @param callback The callback handler method.
        */
        void setOnTurnRight(CallbackFunction callback);

    protected:
        void initialize();
        [[nodiscard]] bool isInitialized() const;
        virtual void processInput();
        virtual int8_t readEncoder();
        virtual void onTurnLeft();
        virtual void onTurnRight();
};

#endif