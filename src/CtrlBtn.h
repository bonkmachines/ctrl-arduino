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

#include <Arduino.h>
#include "CtrlBase.h"
#include "CtrlMux.h"

class CtrlBtnBase : public Muxable
{
    protected:
        uint8_t sig; // Signal pin
        bool currentState = HIGH;
        bool lastState = HIGH;
        unsigned long debounceStart = 0;
        uint16_t bounceDuration; // In milliseconds
        bool initialized = false;

        CtrlBtnBase(
            uint8_t sig,
            uint16_t bounceDuration,
            CtrlMux* mux = nullptr
        );

        ~CtrlBtnBase() = default;

        void initialize();
        [[nodiscard]] bool isInitialized() const;
        virtual uint8_t processInput();
        virtual void onPress();
        virtual void onRelease();

    public:
        /**
        * @brief The process method should be called within the loop method. It handles all functionality.
        */
        void process() override;

        /**
        * @brief Find out if a button is currently being pressed.
        *
        * @return True if button is being pressed, false otherwise.
        */
        [[nodiscard]] bool isPressed() const;

        /**
        * @brief Find out if a button is currently not being presed.
        *
        * @return True if button is not pressed, false otherwise.
        */
        [[nodiscard]] bool isReleased() const;
};

class CtrlBtn final : public CtrlBtnBase
{
    using CallbackFunction = void (*)();
    CallbackFunction onPressCallback;
    CallbackFunction onReleaseCallback;

    public:
        /**
        * @brief Instantiate a button object.
        *
        * The CtrlBtn class can be instantiated to allow for specific
        * actions on press, on release & on delayed release.
        *
        * @param sig (uint8_t) The signal (SIG) pin of the button.
        * @param bounceDuration (uint16_t) The bounce duration in milliseconds.
        * @param onPressCallback (optional) The on press callback handler. Default is nullptr.
        * @param onReleaseCallback (optional) The on release callback handler. Default is nullptr.
        * @param mux (CtrlMux) (optional) The multiplexer the button is connected to. Default is nullptr.
        * @return A new instance of the CtrlBtn class.
        */
        CtrlBtn(
            uint8_t sig,
            uint16_t bounceDuration,
            CallbackFunction onPressCallback = nullptr,
            CallbackFunction onReleaseCallback = nullptr,
            CtrlMux* mux = nullptr
        );

        /**
        * @brief Create a button object via this static method.
        *
        * The CtrlBtn class can be created to allow for specific actions
        * on press, on release & on delayed release.
        *
        * @param sig (uint8_t) The signal (SIG) pin of the button.
        * @param bounceDuration (uint16_t) The bounce duration in milliseconds.
        * @param onPressCallback (optional) The on press callback handler. Default is nullptr.
        * @param onReleaseCallback (optional) The on release callback handler. Default is nullptr.
        * @param mux (CtrlMux) (optional) The multiplexer the button is connected to. Default is nullptr.
        * @return A new instance of the CtrlBtn class.
        */
        static CtrlBtn create(
            uint8_t sig,
            uint16_t bounceDuration,
            CallbackFunction onPressCallback = nullptr,
            CallbackFunction onReleaseCallback = nullptr,
            CtrlMux* mux = nullptr
        );

        /**
        * @brief Set the on press handler.
        *
        * Pass in a handler that is called whenever the button enters the "pressed" state.
        *
        * @param callback The callback handler method.
        */
        void setOnPress(CallbackFunction callback);

        /**
        * @brief Set the on release handler.
        *
        * Pass in a handler that is called whenever the button enters the "released" state.
        *
        * @param callback The callback handler method.
        */
        void setOnRelease(CallbackFunction callback);

    private:
        void onPress() override;
        void onRelease() override;
};

#endif