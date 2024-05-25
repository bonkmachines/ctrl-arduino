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
    public:
        uint8_t count;
        uint8_t switchInterval;
        uint8_t sig;
        uint8_t s0;
        uint8_t s1;
        uint8_t s2;
        uint8_t s3;
        bool s3Present;
        uint8_t subscribers[16] = { };
        uint8_t previousSubscriber = 0;
        bool occupied = false;
        uint8_t currentPinMode = 0;

        void setSignalPinToDigitalIn();
        void setSignalPinToAnalogIn();
        void setChannel(uint8_t channel) const;

    public:
        CtrlMux(
            uint8_t count,
            uint8_t switchInterval,
            uint8_t sig,
            uint8_t s0,
            uint8_t s1,
            uint8_t s2,
            uint8_t s3 = UINT8_MAX // Default to a value indicating S3 is not used
        );

        void subscribe(uint8_t channel);
        [[nodiscard]] bool subscribed(uint8_t channel) const;
        [[nodiscard]] bool subscriptionComplete() const;
        [[nodiscard]] bool subscriberIsNext(uint8_t channel) const;
        bool acquire(uint8_t channel);
        void release();
        [[nodiscard]] uint8_t digitalReader(uint8_t channel);
        [[nodiscard]] uint16_t analogReader(uint8_t channel);
};

#endif // CTRLMUX_H