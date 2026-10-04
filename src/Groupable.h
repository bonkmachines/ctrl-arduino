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

/**
 * @brief Storage for an object's custom properties (setInteger(), setBoolean() & setString()).
 *
 * You normally never touch this: an object allocates its storage the first time
 * you set a property. If your project must avoid the heap entirely, declare one
 * per object yourself and hand it over with setProperties(), e.g.:
 *
 *   CtrlProperties buttonProperties;
 *   button.setProperties(buttonProperties);
 */
struct CtrlProperties
{
    static constexpr uint8_t MAX_PROPERTIES = 8;
    static constexpr uint8_t MAX_KEY_LENGTH = 15;
    static constexpr uint8_t MAX_STRING_LENGTH = 20;

    struct Property
    {
        char key[MAX_KEY_LENGTH + 1] = {};
        enum { NONE, INT, BOOL, STRING } type = NONE;
        int intValue = 0;
        bool boolValue = false;
        char stringValue[MAX_STRING_LENGTH + 1] = {};
    };

    Property properties[MAX_PROPERTIES] = {};
    uint8_t count = 0;
};

class Groupable
{
    friend class CtrlGroup;

    protected:
        CtrlGroup* group = nullptr;
        bool grouped = false;

        static constexpr uint8_t MAX_PROPERTIES = CtrlProperties::MAX_PROPERTIES;
        static constexpr uint8_t MAX_KEY_LENGTH = CtrlProperties::MAX_KEY_LENGTH;
        static constexpr uint8_t MAX_STRING_LENGTH = CtrlProperties::MAX_STRING_LENGTH;

        using Property = CtrlProperties::Property;

        // Allocated on first use, so objects that never set a property stay small.
        CtrlProperties* propertyStorage = nullptr;
        bool ownsPropertyStorage = false;

    public:
        Groupable() = default;
        Groupable(const Groupable& other);
        Groupable& operator=(const Groupable& other);
        virtual ~Groupable();

        /**
         * @brief Use your own storage for this object's custom properties instead of
         * allocating it on first use (for projects that must avoid the heap).
         *
         * Properties already set are copied over. The storage must outlive the object.
         *
         * @param storage The storage to use.
         */
        void setProperties(CtrlProperties& storage);

        /**
        * @brief The process method should be called within the loop method.
        * It handles all functionality.
        */
        virtual void process() = 0;

        /**
        * @brief Find out if an object is currently added to a group.
        *
        * @return True if object is added, false otherwise.
        */
        [[nodiscard]] bool isGrouped() const;

        /**
        * @brief Set the group on an object.
        *
        * @param group reference to the group object.
        */
        bool setGroup(CtrlGroup* group);

        /**
         * @brief Set a boolean on an object.
         *
         * @param key Reference to the name of the boolean.
         * @param value The value of the boolean.
         * @note If the key does not exist, a new boolean property will be added to the object.
         */
        void setBoolean(const char* key, bool value);

        /**
         * @brief Set an integer on an object.
         *
         * @param key The name of the integer.
         * @param value The value of the integer.
         * @note If the key does not exist, a new integer property will be added to the object.
         */
        void setInteger(const char* key, int value);

        /**
         * @brief Set a string on an object.
         *
         * @param key The name of the string.
         * @param value The value of the string.
         * @note If the key does not exist, a new string property will be added to the object.
         */
        void setString(const char* key, const char* value);

        /**
         * @brief Get a boolean from an object.
         *
         * @param key The name of the boolean.
         * @return The value of the boolean, or false if the key does not exist or is not a boolean.
         */
        [[nodiscard]] bool getBoolean(const char* key) const;

        /**
         * @brief Get an integer from an object.
         *
         * @param key The name of the integer.
         * @return The value of the integer, or 0 if the key does not exist or is not an integer.
         */
        [[nodiscard]] int getInteger(const char* key) const;

        /**
         * @brief Get a string from an object.
         *
         * @param key The name of the string.
         * @return The value of the string, or an empty string if the key does not exist or is not a string.
         */
        [[nodiscard]] const char* getString(const char* key) const;


    protected:
        [[nodiscard]] Property* findProperty(const char* key);
        [[nodiscard]] const Property* findProperty(const char* key) const;
        Property* addProperty(const char* key);
        void releasePropertyStorage();
};

#endif // GROUPABLE_H