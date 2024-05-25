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

CtrlEncBase::CtrlEncBase(
    const uint8_t clk,
    const uint8_t dt,
    CtrlMux* mux
) : Muxable(mux)
{
    this->clk = clk;
    this->dt = dt;
    if (!this->isMuxed()) pinMode(clk, INPUT);
    if (!this->isMuxed()) pinMode(dt, INPUT);
}

void CtrlEncBase::process()
{
    if (this->isDisabled()) return;
    if (this->readEncoder()) {
        if (this->isTurningLeft()) {
            this->onTurnLeft();
        } else if (this->isTurningRight()) {
            this->onTurnRight();
        }
    }
}

void CtrlEncBase::processInput()
{
    if (this->isMuxed()) {
        if (this->mux->acquire(this->clk)) {
            const uint8_t clkReading = this->mux->digitalReader(this->clk);
            this->mux->release();
            if (clkReading) values[0] |= 0x01;
        }
        if (this->mux->acquire(this->dt)) {
            const uint8_t dtReading = this->mux->digitalReader(this->dt);
            this->mux->release();
            if (dtReading) values[0] |= 0x02;
        }
    } else {
        #ifdef UNIT_TEST
            // Simulated pin states for testing
            extern int8_t mockClkInput;
            extern int8_t mockDtInput;
            if (mockClkInput) this->values[0] |= 0x01;
            if (mockDtInput) this->values[0] |= 0x02;
        #else
        // Normal operation with real hardware
            if (digitalRead(clk)) values[0] |= 0x01;
            if (digitalRead(dt)) values[0] |= 0x02;
        #endif
    }
}

int8_t CtrlEncBase::readEncoder()
{
    static int8_t table[] = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
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

bool CtrlEncBase::isTurningLeft() const { return this->values[0] == 0x0b; }

bool CtrlEncBase::isTurningRight() const { return this->values[0] == 0x07; }

void CtrlEncBase::onTurnLeft() { }

void CtrlEncBase::onTurnRight() { }

CtrlEnc::CtrlEnc(
    const uint8_t clk,
    const uint8_t dt,
    const CallbackFunction onTurnLeftCallback,
    const CallbackFunction onTurnRightCallback,
    CtrlMux* mux
) : CtrlEncBase(clk, dt, mux),
    onTurnLeftCallback(onTurnLeftCallback),
    onTurnRightCallback(onTurnRightCallback) { }

void CtrlEnc::setOnTurnLeft(const CallbackFunction callback)
{
    this->onTurnLeftCallback = callback;
}

void CtrlEnc::setOnTurnRight(const CallbackFunction callback)
{
    this->onTurnRightCallback = callback;
}

void CtrlEnc::onTurnLeft()
{
    if (this->onTurnLeftCallback) {
        this->onTurnLeftCallback();
    }
}

void CtrlEnc::onTurnRight()
{
    if (this->onTurnRightCallback) {
        this->onTurnRightCallback();
    }
}

CtrlEnc CtrlEnc::create(
    const uint8_t clk,
    const uint8_t dt,
    const CallbackFunction onTurnLeftCallback,
    const CallbackFunction onTurnRightCallback,
    CtrlMux* mux
) {
    CtrlEnc encoder(
        clk,
        dt,
        onTurnLeftCallback,
        onTurnRightCallback,
        mux
    );
    return encoder;
}