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
    protected:
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

    public:
        virtual ~Groupable();

        /**
        * @brief The process method should be called within the loop method.
        * It handles all functionality.
        */
        virtual void process() = 0;

        /**
        * @brief Find out if an object is currently added to a group.
        *
        * @return True if objected is added, false otherwise.
        */
        [[nodiscard]] bool isGrouped() const;

        /**
        * @brief Set the group on an object.
        *
        * @param group reference to the group object.
        */
        void setGroup(CtrlGroup* group);

        /**
         * @brief Set a boolean on an object.
         *
         * @param key Reference to the name of the boolean.
         * @param value The value of the boolean.
         * @note If the key does not exist, a new boolean property will be added to the object.
         */
        void setBoolean(const String& key, bool value);

        /**
         * @brief Set an integer on an object.
         *
         * @param key Reference to the name of the integer.
         * @param value The value of the integer.
         * @note If the key does not exist, a new integer property will be added to the object.
         */
        void setInteger(const String& key, const int value);

        /**
         * @brief Set a string on an object.
         *
         * @param key Reference to the name of the string.
         * @param value The value of the string.
         * @note If the key does not exist, a new string property will be added to the object.
         */
        void setString(const String& key, const String& value);

        /**
         * @brief Get a boolean from an object.
         *
         * @param key Reference to the name of the boolean.
         * @return The value of the boolean, or false if the key does not exist or is not a boolean.
         */
        [[nodiscard]] bool getBoolean(const String& key) const;

        /**
         * @brief Get an integer from an object.
         *
         * @param key Reference to the name of the integer.
         * @return The value of the integer, or 0 if the key does not exist or is not an integer.
         */
        [[nodiscard]] int getInteger(const String& key) const;

        /**
         * @brief Get a string from an object.
         *
         * @param key Reference to the name of the string.
         * @return The value of the string, or an empty string if the key does not exist or is not a string.
         */
        [[nodiscard]] String getString(const String& key) const;


    protected:
        [[nodiscard]] Node* findProperty(const String& key) const;
};

#endif // GROUPABLE_H