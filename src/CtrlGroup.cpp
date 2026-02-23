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

CtrlGroup::CtrlGroup() = default;

CtrlGroup::~CtrlGroup() {
    for (size_t i = 0; i < this->objectCount; ++i) {
        this->objects[i]->group = nullptr;
        this->objects[i]->grouped = false;
    }
    delete[] this->objects;
}

void CtrlGroup::enable() { this->enabled = true; }

void CtrlGroup::disable() { this->enabled = false; }

bool CtrlGroup::isEnabled() const { return this->enabled; }

bool CtrlGroup::isDisabled() const { return !this->enabled; }

void CtrlGroup::addObject(Groupable* object) {
    if (this->objectCount == this->capacity) {
        resize();
    }
    this->objects[this->objectCount++] = object;
}

void CtrlGroup::removeObject(Groupable* object) {
    for (size_t i = 0; i < this->objectCount; ++i) {
        if (this->objects[i] == object) {
            for (size_t j = i; j < this->objectCount - 1; ++j) {
                this->objects[j] = this->objects[j + 1];
            }
            --this->objectCount;
            if (this->nextIndex >= this->objectCount && this->objectCount > 0) {
                this->nextIndex = 0;
            }
            return;
        }
    }
}

void CtrlGroup::reserve(const size_t capacity) {
    if (capacity <= this->capacity) return;
    auto** newObjects = new Groupable*[capacity];
    for (size_t i = 0; i < this->objectCount; ++i) {
        newObjects[i] = this->objects[i];
    }
    delete[] this->objects;
    this->objects = newObjects;
    this->capacity = capacity;
}

void CtrlGroup::process(const uint8_t count)
{
    if (!this->enabled || this->objectCount == 0) return;
    if (count == 0) {
        for (size_t i = 0; i < this->objectCount; ++i) {
            this->objects[i]->process();
        }
    } else {
        const uint8_t n = count > this->objectCount ? static_cast<uint8_t>(this->objectCount) : count;
        for (uint8_t i = 0; i < n; ++i) {
            this->objects[this->nextIndex]->process();
            this->nextIndex = (this->nextIndex + 1) % this->objectCount;
        }
    }
}

void CtrlGroup::setOnPress(void (*callback)(Groupable&))
{
    this->onPressCallback = callback;
}

void CtrlGroup::setOnRelease(void (*callback)(Groupable&))
{
    this->onReleaseCallback = callback;
}

void CtrlGroup::setOnDelayedRelease(void (*callback)(Groupable&))
{
    this->onDelayedReleaseCallback = callback;
}

void CtrlGroup::setOnTurnLeft(void (*callback)(Groupable&))
{
    this->onTurnLeftCallback = callback;
}

void CtrlGroup::setOnTurnRight(void (*callback)(Groupable&))
{
    this->onTurnRightCallback = callback;
}

void CtrlGroup::setOnValueChange(void (*callback)(Groupable&, int value))
{
    this->onValueChangeCallback = callback;
}

void CtrlGroup::resize() {
    const size_t newCapacity = this->capacity == 0 ? 4 : this->capacity * 2;
    auto** newObjects = new Groupable*[newCapacity];
    for (size_t i = 0; i < this->objectCount; ++i) {
        newObjects[i] = this->objects[i];
    }
    delete[] objects;
    this->objects = newObjects;
    this->capacity = newCapacity;
}