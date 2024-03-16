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

#ifndef ICINTERFACE_H
#define ICINTERFACE_H

#include "iclib.h"

class ICInterface {
    public:
        virtual double loadd(uint32_t property_hash, int32_t device) = 0;
        virtual double loadb(uint32_t property_hash, uint32_t device_hash, ic_batch_mode batch_mode) = 0;
        virtual double loadbn(uint32_t property_hash, uint32_t device_hash, ic_batch_mode batch_mode, uint32_t name_hash) = 0;
        virtual double loadrd(uint32_t reagent_hash, int32_t device, ic_reagent_mode reagent_mode) = 0;
        virtual double loadrb(uint32_t reagent_hash, uint32_t device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode) = 0;
        virtual double loadrbn(uint32_t reagent_hash, uint32_t device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode, uint32_t name_hash) = 0;
        virtual double loadsd(uint32_t slot_var, int32_t device, int32_t slot) = 0;
        virtual double loadsb(uint32_t slot_var, uint32_t device_hash, int32_t slot, ic_batch_mode batch_mode) = 0;
        virtual double loadsbn(uint32_t slot_var, uint32_t device_hash, int32_t slot, ic_batch_mode batch_mode, uint32_t name_hash) = 0;
        virtual void stored(double value, uint32_t property_hash, int32_t device) = 0;
        virtual void storeb(double value, uint32_t property_hash, uint32_t device_hash) = 0;
        virtual void storebn(double value, uint32_t property_hash, uint32_t device_hash, uint32_t name_hash) = 0;
        virtual bool get_device_set(int32_t device) = 0;
        virtual double *get_register(int32_t register_index) = 0;
        virtual double get_stack_value() = 0;
        virtual void set_stack_value(double value) = 0;
};

#endif //ICINTERFACE_H
