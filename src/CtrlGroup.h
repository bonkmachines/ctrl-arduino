/*!
 *  @file       CtrlGroup.h
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

#ifndef CTRLGROUP_H
#define CTRLGROUP_H

#include "Groupable.h"

class CtrlGroup final
{
    public:
        Groupable** objects = nullptr;
        size_t objectCount = 0;
        size_t capacity = 0;
        void (*onPressCallback)(Groupable&) = nullptr; // For buttons
        void (*onReleaseCallback)(Groupable&) = nullptr; // For buttons
        void (*onDelayedReleaseCallback)(Groupable&) = nullptr; // For buttons
        void (*onTurnLeftCallback)(Groupable&) = nullptr; // For rotary encoders
        void (*onTurnRightCallback)(Groupable&) = nullptr; // For rotary encoders
        void (*onValueChangeCallback)(Groupable&, int value) = nullptr; // For potentiometers

        CtrlGroup();

        ~CtrlGroup();

        /**
        * @brief Add an object to the group.
        *
        * @param object Object to be added to the group.
        */
        void addObject(Groupable* object);

        /**
        * @brief The process method should be called within the loop method.
        * It handles the functionality of all added objects.
        */
        void process() const;

        /**
        * @brief Set the on press handler (for buttons).
        *
        * Pass in a handler that is called whenever a button in the group enters the "pressed" state.
        *
        * @param callback The callback handler method.
        */
        void setOnPress(void (*callback)(Groupable&));

        /**
        * @brief Set the on release handler (for buttons).
        *
        * Pass in a handler that is called whenever a button in the group enters the "released" state.
        *
        * @param callback The callback handler method.
        */
        void setOnRelease(void (*callback)(Groupable&));

        /**
        * @brief Set the on delayed release handler (for buttons).
        *
        * Pass in a handler that is called whenever the button enters the "released" state,
        * after a specified amount of time the button has been held down (default is 500ms).
        * If onDelayedRelease is triggered, the normal onRelease is not executed.
        *
        * @param callback The callback handler method.
        */
        void setOnDelayedRelease(void (*callback)(Groupable&));

        /**
        * @brief Set the on turn left handler (for rotary encoders).
        *
        * Pass in a handler that is called whenever the encoder turns left.
        *
        * @param callback The callback handler method.
        */
        void setOnTurnLeft(void (*callback)(Groupable&));

        /**
        * @brief Set the on turn right handler (for rotary encoders).
        *
        * Pass in a handler that is called whenever the encoder turns right.
        *
        * @param callback The callback handler method.
        */
        void setOnTurnRight(void (*callback)(Groupable&));

        /**
        * @brief Set the on value change handler (for potentiometers).
        *
        * Pass in a handler that is called whenever the potentiometer shaft changes position.
        *
        * @param callback The callback handler method.
        */
        void setOnValueChange(void (*callback)(Groupable&, int value));

    private:
        void resize();
};

#endif // CTRLGROUP_H
