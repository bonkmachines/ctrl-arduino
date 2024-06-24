/*!
 *  @file       CtrlGroup.cpp
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

#include "CtrlGroup.h"

void CtrlGroup::addObject(Groupable* object)
{
    if (objectCount < MAX_OBJECTS) {
        objects[objectCount++] = object;
    }
}

void CtrlGroup::process() const
{
    for (int i = 0; i < objectCount; ++i) {
        objects[i]->process();
    }
}

void CtrlGroup::setOnPress(void (*callback)(Groupable*))
{
    onPressCallback = callback;
}

void CtrlGroup::setOnRelease(void (*callback)(Groupable*))
{
    onReleaseCallback = callback;
}

void CtrlGroup::setOnDelayedRelease(void (*callback)(Groupable*))
{
    onDelayedReleaseCallback = callback;
}

void CtrlGroup::setOnTurnLeft(void (*callback)(Groupable*))
{
    onTurnLeftCallback = callback;
}

void CtrlGroup::setOnTurnRight(void (*callback)(Groupable*))
{
    onTurnRightCallback = callback;
}

void CtrlGroup::setOnValueChange(void (*callback)(Groupable*, int value))
{
    onValueChangeCallback = callback;
}