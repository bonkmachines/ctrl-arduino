/*!
 *  @file       CtrlMuxSet.h
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

#ifndef CTRLMUXSET_H
#define CTRLMUXSET_H

#include <Arduino.h>

class CtrlMuxSet
{
    public:
        int16_t count;
        int16_t subscribers[255] = { }; // A maximum of 255 multiplexers can subscribe
        int16_t previousSubscriber = 0;
        bool occupied = false;

        explicit CtrlMuxSet(
            int16_t count
        );

        int16_t subscribe();
        [[nodiscard]] bool subscribed(int16_t muxId) const;
        [[nodiscard]] bool subscriptionComplete() const;
        [[nodiscard]] bool subscriberIsNext(int16_t muxId) const;
};

#endif // CTRLMUXSET_H