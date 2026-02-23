/*!
 *  @file       CtrlEnc.cpp
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

#include "CtrlEnc.h"
#include "CtrlGroup.h"

CtrlEnc::CtrlEnc(
    const uint8_t clk,
    const uint8_t dt,
    const CallbackFunction onTurnLeftCallback,
    const CallbackFunction onTurnRightCallback,
    CtrlMux* mux
) : Muxable(mux)
{
    this->clk = clk;
    this->dt = dt;
    this->onTurnLeftCallback = onTurnLeftCallback;
    this->onTurnRightCallback = onTurnRightCallback;
}

void CtrlEnc::setPinMode(const uint8_t pinModeType, const uint8_t resistorPull)
{
    if (pinModeType != INPUT && pinModeType != INPUT_PULLUP && pinModeType != INPUT_PULLDOWN) {
        return; // Invalid pinModeType, do nothing
    }
    if (resistorPull != PULL_DOWN && resistorPull != PULL_UP) {
        return; // Invalid resistorPull, do nothing
    }
    this->pinModeType = pinModeType;
    if (pinModeType == INPUT && (resistorPull == PULL_UP || resistorPull == PULL_DOWN)) {
        this->resistorPull = resistorPull;
    }
    if (pinModeType == INPUT_PULLUP) {
        this->resistorPull = PULL_UP;
    }
    if (pinModeType == INPUT_PULLDOWN) {
        this->resistorPull = PULL_DOWN;
    }
}

void CtrlEnc::process()
{
    if (!this->isInitialized()) this->initialize();
    if (this->isDisabled()) return;
    if (this->readEncoder()) {
        if (this->isTurningLeft()) {
            this->onTurnLeft();
        } else if (this->isTurningRight()) {
            this->onTurnRight();
        }
    }
}

bool CtrlEnc::isTurningLeft() const { return this->values[0] == 0x0b; }

bool CtrlEnc::isTurningRight() const { return this->values[0] == 0x07; }

void CtrlEnc::setOnTurnLeft(const CallbackFunction callback)
{
    this->onTurnLeftCallback = callback;
}

void CtrlEnc::setOnTurnRight(const CallbackFunction callback)
{
    this->onTurnRightCallback = callback;
}

void CtrlEnc::initialize()
{
    if (!this->isMuxed()) pinMode(clk, this->pinModeType);
    if (!this->isMuxed()) pinMode(dt, this->pinModeType);
    this->initialized = true;
}

bool CtrlEnc::isInitialized() const { return this->initialized; }

void CtrlEnc::processInput()
{
    bool clkState, dtState;

    if (this->isMuxed()) {
        clkState = this->mux->readEncClk(this->clk, this->pinModeType);
        dtState = this->mux->readEncDt(this->dt, this->pinModeType);
    } else {
        clkState = digitalRead(clk);
        dtState = digitalRead(dt);
    }

    if (this->resistorPull == PULL_DOWN) {
        // Invert the states if using external pull-down resistors
        clkState = !clkState;
        dtState = !dtState;
    }

    if (clkState) values[0] |= 0x01;
    if (dtState) values[0] |= 0x02;
}


int8_t CtrlEnc::readEncoder()
{
    static constexpr int8_t table[] = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
    this->values[0] <<= 2;
    this->processInput();
    this->values[0] &= 0x0f;
    if (table[this->values[0]]) {
        this->values[1] <<= 4;
        this->values[1] |= this->values[0];
        if ((this->values[1] & 0xff) == 0x2b) return -1;
        if ((this->values[1] & 0xff) == 0x17) return 1;
    }
    return 0;
}

void CtrlEnc::onTurnLeft()
{
    if (this->isGrouped() && this->group->onTurnLeftCallback) {
        this->group->onTurnLeftCallback(*this);
    }
    if (this->onTurnLeftCallback) {
        this->onTurnLeftCallback();
    }
}

void CtrlEnc::onTurnRight()
{
    if (this->isGrouped() && this->group->onTurnRightCallback) {
        this->group->onTurnRightCallback(*this);
    }
    if (this->onTurnRightCallback) {
        this->onTurnRightCallback();
    }
}