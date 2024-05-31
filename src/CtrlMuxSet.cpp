/*!
 *  @file       CtrlMuxSet.cpp
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

#include "CtrlMuxSet.h"

CtrlMuxSet::CtrlMuxSet(
    const int16_t count
) : count(count) { }

int16_t CtrlMuxSet::subscribe()
{
    for (int16_t i = 0; i < 255; ++i) {
        if (this->subscribers[i] == 0) {
            this->subscribers[i] = 1;
            return i;
        }
    }
    return -1;
}

bool CtrlMuxSet::subscribed(const int16_t muxId) const
{
    if (muxId == -1) return false;
    return this->subscribers[muxId] == 1;
}

bool CtrlMuxSet::subscriptionComplete() const
{
    for (int16_t i = 0; i < this->count; i++) {
        if (this->subscribers[i] != 1) return false;
    }
    return true;
}

bool CtrlMuxSet::subscriberIsNext(const int16_t muxId) const
{
    if (this->count == 1) return true; // If there is only 1 subscriber, it's always next :)
    if (this->previousSubscriber == this->count - 1) return muxId == 0; // We reach the final subscriber and go back to 0
    return this->previousSubscriber == muxId - 1;
}