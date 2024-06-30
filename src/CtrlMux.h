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

class Muxable;

class CtrlMux
{
    protected:
        uint8_t sig;
        uint8_t s0;
        uint8_t s1;
        uint8_t s2;
        uint8_t s3;
        bool s3Present;
        uint8_t switchInterval = 1; // In microseconds
        uint8_t currentPinMode = 0;
        Muxable** objects = nullptr;
        size_t objectCount = 0;
        size_t capacity = 0;

        void setPinMode(uint8_t pinModeType);

        void setChannel(uint8_t channel) const;

    public:
        /**
        * @brief Instantiate a Multiplexer object.
        *
        * The CtrlMux class can be instantiated to allow buttons,
        * rotary encoder & potentiometers to be multiplexed.
        *
        * @param sig (uint8_t) The signal (SIG) pin of the multiplexer.
        * @param s0 (uint8_t) The s0 channelselect pin.
        * @param s1 (uint8_t) The s1 channelselect pin.
        * @param s2 (uint8_t) The s2 channelselect pin.
        * @param s3 (uint8_t) (optional) The s3 channel select pin. Default is UINT8_MAX.
        * @return A new instance of the CtrlMux class.
        */
        CtrlMux(
            uint8_t sig,
            uint8_t s0,
            uint8_t s1,
            uint8_t s2,
            uint8_t s3 = UINT8_MAX // Default to a value indicating S3 is not used
        );

        /**
        * @brief Add an object to the mux.
        *
        * @param object Object to be added to the mux.
        */
        void addObject(Muxable* object);

        /**
        * @brief The process method should be called within the loop method.
        * It handles the functionality of all added objects.
        */
        void process() const;

        /**
        * @brief Set the switch interval of the multiplexer.
        *
        * This is the amount of time we need to give the mux in order to
        * complete switching a channel. Consult the datasheet of your
        * multiplexer to check how much time it needs to switch channels.
        * The minimum here is 1 microseconds, as the more basic microcontrollers
        * cannot get down to nanosecond level precision. It is unlikely that
        * you will need a switch interval of higher that 1 microsecond.
        *
        * @param interval (uint8_t) The switch interval (in microseconds).
        */
        void setSwitchInterval(uint8_t interval);

        [[nodiscard]] bool readBtnSig(uint8_t channel, uint8_t pinModeType);
        [[nodiscard]] bool readEncClk(uint8_t channel, uint8_t pinModeType);
        [[nodiscard]] bool readEncDt(uint8_t channel, uint8_t pinModeType);
        [[nodiscard]] uint16_t readPotSig(uint8_t channel, uint8_t pinModeType);

    private:
        void resize();
};

#endif // CTRLMUX_H