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

#ifndef DEVICE_H
#define DEVICE_H

#include "iclib.h"

class Device {
    public:
        virtual double get_property(uint32_t property_hash) = 0;
        virtual double get_slot(uint32_t slot_var_hash, int32_t slot_num) = 0;
        virtual double get_reagent(uint32_t reagent, ic_reagent_mode reagent_mode) = 0;
        virtual void set_property(uint32_t property_hash, double value) = 0;
        virtual uint32_t get_device_name_hash() const = 0;
        virtual uint32_t get_device_type_hash() const = 0;
};

#endif //DEVICE_H
