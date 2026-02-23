/*!
 *  @file       Muxable.h
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

#ifndef MUXABLE_H
#define MUXABLE_H

class CtrlMux;

class Muxable
{
    friend class CtrlMux;

    protected:
        CtrlMux* mux = nullptr;
        bool muxed = false;

    public:
        explicit Muxable(
            CtrlMux* mux = nullptr
        );

        virtual ~Muxable();

        /**
        * @brief The process method should be called within the loop method.
        * It handles all functionality.
        */
        virtual void process() = 0;

        /**
        * @brief Find out if an object is currently added to a multiplexer.
        *
        * @return True if object is added, false otherwise.
        */
        [[nodiscard]] bool isMuxed() const;

        /**
        * @brief Set the multiplexer on an object.
        *
        * @param mux reference to the multiplexer object.
        */
        void setMultiplexer(CtrlMux* mux);
};

#endif //MUXABLE_H
