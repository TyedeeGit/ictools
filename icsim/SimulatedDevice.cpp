/*
 * Copyright (C) 2024 Tyedee
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "SimulatedDevice.h"

SimulatedDevice::SimulatedDevice(uint32_t type_hash, const char *device_name) {
    this->name = device_name;
    this->device_name_hash = this->get_device_name_hash();
    this->device_type_hash = type_hash;
}

inline double SimulatedDevice::get_property(uint32_t property_hash)  {
    return this->device_properties[property_hash];
}

inline double SimulatedDevice::get_slot(uint32_t slot_var_hash, int32_t slot_num)  {
    return this->device_slots[slot_num][slot_var_hash];
}

inline double SimulatedDevice::get_reagent(uint32_t reagent, ic_reagent_mode reagent_mode)  {
    switch (reagent_mode) {
        case REAGENT_CONTENTS:
            return this->device_reagents_contents[reagent];
        case REAGENT_REQUIRED:
            return this->device_reagents_required[reagent];case REAGENT_RECIPE:return this->device_reagents_recipe[reagent];
    }
}

inline void SimulatedDevice::set_property(uint32_t property_hash, double value)   {
    this->device_properties[property_hash] = value;
}

void SimulatedDevice::set_slot(uint32_t slot_var_hash, int32_t slot_num, double value) {
    this->device_slots[slot_num][slot_var_hash] = value;
}

void SimulatedDevice::set_reagent(uint32_t reagent, ic_reagent_mode reagent_mode, double value) {
    switch (reagent_mode) {
        case REAGENT_CONTENTS:
            this->device_reagents_contents[reagent] = value;
        case REAGENT_REQUIRED:
            this->device_reagents_required[reagent] = value;
        case REAGENT_RECIPE:
            this->device_reagents_recipe[reagent] = value;
    }
}

inline uint32_t SimulatedDevice::get_device_name_hash() const  {
    return hash(this->name);
}

inline uint32_t SimulatedDevice::get_device_type_hash() const  {
    return this->device_type_hash;
}