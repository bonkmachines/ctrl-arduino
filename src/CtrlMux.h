/*!
 *  @file       CtrlMux.h
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

#ifndef CTRLMUX_H
#define CTRLMUX_H

#include <Arduino.h>

class CtrlMux
{
    protected:
        uint8_t sig;
        uint8_t s0;
        uint8_t s1;
        uint8_t s2;
        uint8_t s3;
        bool occupied = false;
        static constexpr uint8_t switchInterval = 50; // 50 microseconds
        uint8_t currentPinMode = 0;

    public:
        CtrlMux(
            uint8_t sig,
            uint8_t s0,
            uint8_t s1,
            uint8_t s2,
            uint8_t s3
        );

        void setSignalPinToDigitalIn();
        void setSignalPinToAnalogIn();
        void setChannel(uint8_t channel) const;
        bool acquire();
        void release();
        [[nodiscard]] uint8_t digitalReader(uint8_t channel);
        [[nodiscard]] uint16_t analogReader(uint8_t channel);
};

#endif // CTRLMUX_H