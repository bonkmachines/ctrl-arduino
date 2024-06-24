/*!
 *  @file       Groupable.h
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

#ifndef GROUPABLE_H
#define GROUPABLE_H

#include <Arduino.h>

class CtrlGroup;

class Groupable
{
    public:
        CtrlGroup* group = nullptr;
        bool grouped = false;

        struct Property
        {
            int intValue;
            bool boolValue;
            String stringValue;
            enum { INT, BOOL, STRING } type;
        };

        struct Node
        {
            String key;
            Property value;
            Node* next;
        };

        Node* properties = nullptr;

        Groupable();

        virtual ~Groupable();

        virtual void process();

        void setGroup(CtrlGroup* group);

        void setBoolean(const String& key, bool value);

        void setInteger(const String& key, int value);

        void setString(const String& key, const String& value);

        [[nodiscard]] bool getBoolean(const String& key) const;

        [[nodiscard]] int getInteger(const String& key) const;

        [[nodiscard]] String getString(const String& key) const;

    protected:
        [[nodiscard]] Node* findProperty(const String& key) const;
};

#endif // GROUPABLE_H
