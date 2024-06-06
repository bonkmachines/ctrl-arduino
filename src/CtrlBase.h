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

#ifndef CtrlBase_h
#define CtrlBase_h

#include "CtrlMux.h"

class Muxable
{
    protected:
        bool enabled = true;
        CtrlMux* mux = nullptr;
        bool muxed = false;

        explicit Muxable(
            CtrlMux* mux = nullptr
        );

        ~Muxable() = default;

    public:

        virtual void process() = 0;
        void enable();
        void disable();
        [[nodiscard]] bool isEnabled() const;
        [[nodiscard]] bool isDisabled() const;
        [[nodiscard]] bool isMuxed() const;
        void setMultiplexer(CtrlMux &mux);
};

void setDelayMicroseconds(uint64_t duration);

void setDelayMilliseconds(uint64_t duration);

extern uint8_t DISCONNECTED; // used to indicate if a pin is not connected.
extern uint8_t PULL_UP; // Used for indicating that an external resistor pull up is used.
extern uint8_t PULL_DOWN; // Used for indicating that an external resistor down up is used.

#ifndef INPUT_PULLUP
    #define INPUT_PULLUP 2 // Define a placeholder value for INPUT_PULLUP
#endif

#ifndef INPUT_PULLDOWN
    #define INPUT_PULLDOWN 3 // Define a placeholder value for INPUT_PULLDOWN
#endif

#endif