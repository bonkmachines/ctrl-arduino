/*!
 *  @file       CtrlBtn.cpp
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

#include "CtrlBtn.h"

CtrlBtnBase::CtrlBtnBase(
    const uint8_t sig,
    const uint16_t bounceDuration
) {
    this->sig = sig;
    this->bounceDuration = bounceDuration;
    pinMode(sig, INPUT_PULLUP);
    this->currentState = CtrlBtnBase::processInput();
    this->lastState = currentState;
}

uint8_t CtrlBtnBase::processInput()
{
    #ifdef UNIT_TEST
        // Simulated digitalRead testing
        extern uint8_t mockButtonInput;
        return mockButtonInput;
    #else
        // Normal operation with real hardware
        return digitalRead(this->sig);
    #endif
}

void CtrlBtnBase::process()
{
    if (this->isDisabled()) return;

    const unsigned long currentTime = millis();
    const bool reading = this->processInput();

    if (reading != this->lastState) {
        this->debounceStart = currentTime;
    }
    if ((currentTime - this->debounceStart) > bounceDuration) {
        if (reading != this->currentState) {
        this->currentState = reading;
            if (this->currentState == LOW) {
                onPress();
            } else {
                onRelease();
            }
        }
    }
    this->lastState = reading;
}

bool CtrlBtnBase::isPressed() const { return this->currentState == LOW; }

bool CtrlBtnBase::isReleased() const { return this->currentState == HIGH; }

void CtrlBtnBase::onPress() { }

void CtrlBtnBase::onRelease() { }

CtrlBtn::CtrlBtn(
    const uint8_t sig,
    const uint16_t bounceDuration,
    const CallbackFunction onPressCallback,
    const CallbackFunction onReleaseCallback
): CtrlBtnBase(sig, bounceDuration), onPressCallback(onPressCallback), onReleaseCallback(onReleaseCallback) { }

void CtrlBtn::setOnPress(const CallbackFunction callback)
{
    this->onPressCallback = callback;
}

void CtrlBtn::setOnRelease(const CallbackFunction callback)
{
    this->onReleaseCallback = callback;
}

void CtrlBtn::onPress()
{
    if (this->onPressCallback) {
        this->onPressCallback();
    }
}

void CtrlBtn::onRelease()
{
    if (this->onReleaseCallback) {
        this->onReleaseCallback();
    }
}

CtrlBtn CtrlBtn::create(
    const uint8_t sig,
    const uint16_t bounceDuration,
    const CallbackFunction onPressCallback,
    const CallbackFunction onReleaseCallback
) {
      CtrlBtn button(sig, bounceDuration);
      button.setOnPress(onPressCallback);
      button.setOnRelease(onReleaseCallback);
      return button;
}