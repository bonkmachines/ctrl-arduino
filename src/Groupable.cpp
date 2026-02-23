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

#include "Groupable.h"
#include "CtrlGroup.h"

Groupable::~Groupable()
{
    if (this->group != nullptr) {
        this->group->removeObject(this);
    }
    const Node* current = properties;
    while (current != nullptr) {
        const Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool Groupable::isGrouped() const
{
    return this->grouped;
}

void Groupable::setGroup(CtrlGroup* group)
{
    if (this->group != nullptr) {
        this->group->removeObject(this);
    }
    this->group = group;
    this->grouped = group != nullptr;
    if (this->grouped) this->group->addObject(this);
}

void Groupable::setBoolean(const String& key, const bool value)
{
    Node* prop = findProperty(key);
    if (prop == nullptr) {
        prop = new Node{key, Property{0, value, "", Property::BOOL}, properties};
        properties = prop;
    } else {
        prop->value.boolValue = value;
        prop->value.type = Property::BOOL;
    }
}

void Groupable::setInteger(const String& key, const int value)
{
    Node* prop = findProperty(key);
    if (prop == nullptr) {
        prop = new Node{key, Property{value, false, "", Property::INT}, properties};
        properties = prop;
    } else {
        prop->value.intValue = value;
        prop->value.type = Property::INT;
    }
}

void Groupable::setString(const String& key, const String& value)
{
    Node* prop = findProperty(key);
    if (prop == nullptr) {
        prop = new Node{key, Property{0, false, value, Property::STRING}, properties};
        properties = prop;
    } else {
        prop->value.stringValue = value;
        prop->value.type = Property::STRING;
    }
}

bool Groupable::getBoolean(const String& key) const
{
    Node* prop = findProperty(key);
    if (prop != nullptr && prop->value.type == Property::BOOL) {
        return prop->value.boolValue;
    }
    return false;
}

int Groupable::getInteger(const String& key) const
{
    Node* prop = findProperty(key);
    if (prop != nullptr && prop->value.type == Property::INT) {
        return prop->value.intValue;
    }
    return 0;
}

String Groupable::getString(const String& key) const
{
    Node* prop = findProperty(key);
    if (prop != nullptr && prop->value.type == Property::STRING) {
        return prop->value.stringValue;
    }
    return "";
}

Groupable::Node* Groupable::findProperty(const String& key) const
{
    Node* current = properties;
    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}