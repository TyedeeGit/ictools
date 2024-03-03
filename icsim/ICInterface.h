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

#ifndef ICASM_ICINTERFACE_H
#define ICASM_ICINTERFACE_H

#include "iclib.h"

class ICInterface {
    public:
        virtual double loadd(unsigned property_hash, int device) = 0;
        virtual double loadb(unsigned property_hash, unsigned device_hash, ic_batch_mode batch_mode) = 0;
        virtual double loadbn(unsigned property_hash, unsigned device_hash, ic_batch_mode batch_mode, unsigned name_hash) = 0;
        virtual double loadrd(unsigned reagent_hash, int device, ic_reagent_mode reagent_mode) = 0;
        virtual double loadrb(unsigned reagent_hash, unsigned device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode) = 0;
        virtual double loadrbn(unsigned reagent_hash, unsigned device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode, unsigned name_hash) = 0;
        virtual double loadsd(unsigned slot_var, int device, int slot) = 0;
        virtual double loadsb(unsigned slot_var, unsigned device_hash, int slot, ic_batch_mode batch_mode) = 0;
        virtual double loadsbn(unsigned slot_var, unsigned device_hash, int slot, ic_batch_mode batch_mode, unsigned name_hash) = 0;
        virtual void stored(double value, unsigned property_hash, int device) = 0;
        virtual void storeb(double value, unsigned property_hash, unsigned device_hash) = 0;
        virtual void storebn(double value, unsigned property_hash, unsigned device_hash, unsigned name_hash) = 0;
        virtual bool get_device_set(int device) = 0;
        virtual double *get_register(int register_index) = 0;
        virtual double get_stack_value() = 0;
        virtual void set_stack_value(double value) = 0;
};

#endif //ICASM_ICINTERFACE_H
