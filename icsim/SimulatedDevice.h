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

#ifndef SIMULATEDDEVICE_H
#define SIMULATEDDEVICE_H

#include <unordered_map>
#include "Device.h"

#define DEVICE_SLOTS 3

class SimulatedDevice : public Device {
    private:
        std::unordered_map<uint32_t, double> device_properties;
        std::unordered_map<uint32_t, double> device_slots[DEVICE_SLOTS];
        std::unordered_map<uint32_t, double> device_reagents_contents;
        std::unordered_map<uint32_t, double> device_reagents_required;
        std::unordered_map<uint32_t, double> device_reagents_recipe;
        uint32_t device_type_hash;
        uint32_t device_name_hash;
        const char *name;
    public:
        explicit SimulatedDevice(uint32_t type_hash = 0, const char *device_name = "");
        double get_property(uint32_t property_hash) override;
        double get_slot(uint32_t slot_var_hash, int32_t slot_num) override;
        double get_reagent(uint32_t reagent, ic_reagent_mode reagent_mode) override;
        void set_property(uint32_t property_hash, double value) override;
        void set_slot(uint32_t slot_var_hash, int32_t slot_num, double value);
        void set_reagent(uint32_t reagent, ic_reagent_mode reagent_mode, double value);
        uint32_t get_device_name_hash() const override;
        uint32_t get_device_type_hash() const override;
};


#endif //SIMULATEDDEVICE_H
