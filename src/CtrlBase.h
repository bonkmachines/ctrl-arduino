/*!
 *  @file       CtrlBase.h
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

#ifndef CTRLBASE_H
#define CTRLBASE_H

#include <Arduino.h>

class CtrlBase
{
    protected:
        bool enabled = true;

    public:
        virtual ~CtrlBase() = default;

        void enable();

        void disable();

        [[nodiscard]] bool isEnabled() const;

        [[nodiscard]] bool isDisabled() const;
};

[[deprecated("Use delayMicroseconds() instead")]]
void setDelayMicroseconds(uint64_t duration);

[[deprecated("Use delay() instead")]]
void setDelayMilliseconds(uint64_t duration);

extern const uint8_t DISCONNECTED;
extern const uint8_t PULL_UP;
extern const uint8_t PULL_DOWN;

#ifndef INPUT_PULLUP
    #define INPUT_PULLUP 2 // Define a placeholder value for INPUT_PULLUP
#endif

#ifndef INPUT_PULLDOWN
    #define INPUT_PULLDOWN 3 // Define a placeholder value for INPUT_PULLDOWN
#endif

#endif