/*!
 *  @file       Groupable.cpp
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

#include <new>
#include "Groupable.h"
#include "CtrlGroup.h"

Groupable::Groupable(const Groupable& other)
{
    *this = other;
}

Groupable& Groupable::operator=(const Groupable& other)
{
    if (this == &other) return *this;
    this->group = other.group;
    this->grouped = other.grouped;
    this->releasePropertyStorage();
    if (other.propertyStorage != nullptr) {
        if (other.ownsPropertyStorage) {
            // Each copy gets its own storage, so it can't free the other's.
            this->propertyStorage = new (std::nothrow) CtrlProperties(*other.propertyStorage);
            this->ownsPropertyStorage = this->propertyStorage != nullptr;
        } else {
            this->propertyStorage = other.propertyStorage;
        }
    }
    return *this;
}

Groupable::~Groupable()
{
    if (this->group != nullptr) {
        this->group->removeObject(this);
    }
    this->releasePropertyStorage();
}

void Groupable::releasePropertyStorage()
{
    if (this->ownsPropertyStorage) {
        delete this->propertyStorage;
    }
    this->propertyStorage = nullptr;
    this->ownsPropertyStorage = false;
}

void Groupable::setProperties(CtrlProperties& storage)
{
    if (this->propertyStorage == &storage) return;
    if (this->propertyStorage != nullptr) {
        storage = *this->propertyStorage;
    }
    this->releasePropertyStorage();
    this->propertyStorage = &storage;
}

Groupable::Property* Groupable::addProperty(const char* key)
{
    if (this->propertyStorage == nullptr) {
        this->propertyStorage = new (std::nothrow) CtrlProperties();
        if (this->propertyStorage == nullptr) return nullptr;
        this->ownsPropertyStorage = true;
    }
    CtrlProperties& storage = *this->propertyStorage;
    if (storage.count >= MAX_PROPERTIES) return nullptr;
    Property* prop = &storage.properties[storage.count++];
    strncpy(prop->key, key, MAX_KEY_LENGTH);
    prop->key[MAX_KEY_LENGTH] = '\0';
    return prop;
}

bool Groupable::isGrouped() const
{
    return this->grouped;
}

bool Groupable::setGroup(CtrlGroup* group)
{
    if (this->group != nullptr) {
        this->group->removeObject(this);
    }
    this->group = group;
    this->grouped = group != nullptr;
    if (this->grouped) {
        if (!this->group->addObject(this)) {
            this->group = nullptr;
            this->grouped = false;
            return false;
        }
    }
    return true;
}

void Groupable::setBoolean(const char* key, const bool value)
{
    if (key == nullptr) return;
    Property* prop = findProperty(key);
    if (prop == nullptr) {
        prop = this->addProperty(key);
        if (prop == nullptr) return;
    }
    prop->boolValue = value;
    prop->type = Property::BOOL;
}

void Groupable::setInteger(const char* key, const int value)
{
    if (key == nullptr) return;
    Property* prop = findProperty(key);
    if (prop == nullptr) {
        prop = this->addProperty(key);
        if (prop == nullptr) return;
    }
    prop->intValue = value;
    prop->type = Property::INT;
}

void Groupable::setString(const char* key, const char* value)
{
    if (key == nullptr || value == nullptr) return;
    Property* prop = findProperty(key);
    if (prop == nullptr) {
        prop = this->addProperty(key);
        if (prop == nullptr) return;
    }
    strncpy(prop->stringValue, value, MAX_STRING_LENGTH);
    prop->stringValue[MAX_STRING_LENGTH] = '\0';
    prop->type = Property::STRING;
}

bool Groupable::getBoolean(const char* key) const
{
    const Property* prop = findProperty(key);
    if (prop != nullptr && prop->type == Property::BOOL) {
        return prop->boolValue;
    }
    return false;
}

int Groupable::getInteger(const char* key) const
{
    const Property* prop = findProperty(key);
    if (prop != nullptr && prop->type == Property::INT) {
        return prop->intValue;
    }
    return 0;
}

const char* Groupable::getString(const char* key) const
{
    const Property* prop = findProperty(key);
    if (prop != nullptr && prop->type == Property::STRING) {
        return prop->stringValue;
    }
    return "";
}

Groupable::Property* Groupable::findProperty(const char* key)
{
    if (key == nullptr) return nullptr;
    if (this->propertyStorage == nullptr) return nullptr;
    for (uint8_t i = 0; i < this->propertyStorage->count; ++i) {
        if (strcmp(this->propertyStorage->properties[i].key, key) == 0) {
            return &this->propertyStorage->properties[i];
        }
    }
    return nullptr;
}

const Groupable::Property* Groupable::findProperty(const char* key) const
{
    if (key == nullptr) return nullptr;
    if (this->propertyStorage == nullptr) return nullptr;
    for (uint8_t i = 0; i < this->propertyStorage->count; ++i) {
        if (strcmp(this->propertyStorage->properties[i].key, key) == 0) {
            return &this->propertyStorage->properties[i];
        }
    }
    return nullptr;
}