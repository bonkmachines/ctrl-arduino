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

#ifndef CTRLBASE_H
#define CTRLBASE_H

#include <Arduino.h>

#if defined(ARDUINO_ARCH_AVR)
    using CtrlInterruptState = uint8_t;
    inline CtrlInterruptState ctrlSaveInterrupts() {
        uint8_t sreg = SREG;
        cli();
        return sreg;
    }
    inline void ctrlRestoreInterrupts(CtrlInterruptState state) {
        SREG = state;
    }
#elif defined(TEENSYDUINO) || defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_NRF52) || defined(ARDUINO_ARCH_STM32) || defined(ARDUINO_ARCH_MBED) || defined(ARDUINO_ARCH_RP2040)
    using CtrlInterruptState = uint32_t;
    inline CtrlInterruptState ctrlSaveInterrupts() {
        uint32_t primask;
        __asm__ volatile ("mrs %0, primask" : "=r" (primask));
        __asm__ volatile ("cpsid i" ::: "memory");
        return primask;
    }
    inline void ctrlRestoreInterrupts(CtrlInterruptState state) {
        __asm__ volatile ("msr primask, %0" :: "r" (state) : "memory");
    }
#elif defined(ARDUINO_ARCH_ESP32)
    using CtrlInterruptState = unsigned int;
    inline CtrlInterruptState ctrlSaveInterrupts() {
        return portSET_INTERRUPT_MASK_FROM_ISR();
    }
    inline void ctrlRestoreInterrupts(CtrlInterruptState state) {
        portCLEAR_INTERRUPT_MASK_FROM_ISR(state);
    }
#else
    using CtrlInterruptState = uint8_t;
    inline CtrlInterruptState ctrlSaveInterrupts() {
        noInterrupts();
        return 0;
    }
    inline void ctrlRestoreInterrupts(CtrlInterruptState) {
        interrupts();
    }
#endif

class CtrlBase
{
    protected:
        bool enabled = true;

    public:
        virtual ~CtrlBase() = default;

        void enable();

        void disable();

        [[nodiscard]] bool isEnabled() const;

        [[nodiscard]] bool isDisabled() const;
};

extern const uint8_t DISCONNECTED;

#ifdef PULL_UP
    #undef PULL_UP
#endif
static constexpr uint8_t PULL_UP = 1;

#ifdef PULL_DOWN
    #undef PULL_DOWN
#endif
static constexpr uint8_t PULL_DOWN = 0;

#ifndef INPUT_PULLUP
    #define INPUT_PULLUP 2 // Define a placeholder value for INPUT_PULLUP
#endif

#ifndef INPUT_PULLDOWN
    #define INPUT_PULLDOWN 3 // Define a placeholder value for INPUT_PULLDOWN
#endif

#endif