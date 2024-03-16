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

#ifndef SIMULATEDICINTERFACE_H
#define SIMULATEDICINTERFACE_H

#include <vector>
#include <algorithm>
#include "ICInterface.h"
#include "SimulatedDevice.h"

class SimulatedICInterface : public ICInterface {
    protected:
        uint32_t device_count;
        std::vector<double> registers;
        std::vector<double> stack;
        std::vector<int32_t> set_devices;
        std::vector<SimulatedDevice *> devices;
    public:
        explicit SimulatedICInterface(uint32_t count = 0, SimulatedDevice *devices[] = nullptr);
        inline SimulatedDevice find_device(int32_t pin);
        int32_t find_devices(SimulatedDevice found_devices[], uint32_t device_hash);
        int32_t find_devices(SimulatedDevice found_devices[], uint32_t device_hash, uint32_t name_hash);
        double loadd(uint32_t property_hash, int32_t device) override;
        double loadb(uint32_t property_hash, uint32_t device_hash, ic_batch_mode batch_mode) override;
        double loadbn(uint32_t property_hash, uint32_t device_hash, ic_batch_mode batch_mode, uint32_t name_hash) override;
        double loadrd(uint32_t reagent_hash, int32_t device, ic_reagent_mode reagent_mode) override;
        double loadrb(uint32_t reagent_hash, uint32_t device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode) override;
        double loadrbn(uint32_t reagent_hash, uint32_t device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode, uint32_t name_hash) override;
        double loadsd(uint32_t slot_var, int32_t device, int32_t slot) override;
        double loadsb(uint32_t slot_var, uint32_t device_hash, int32_t slot, ic_batch_mode batch_mode) override;
        double loadsbn(uint32_t slot_var, uint32_t device_hash, int32_t slot, ic_batch_mode batch_mode, uint32_t name_hash) override;
        void stored(double value, uint32_t property_hash, int32_t device) override;
        void storeb(double value, uint32_t property_hash, uint32_t device_hash) override;
        void storebn(double value, uint32_t property_hash, uint32_t device_hash, uint32_t name_hash) override;
        bool get_device_set(int32_t device) override;
        bool set_device(int32_t device, int32_t pin);
        double *get_register(int32_t register_index) override;
        double get_stack_value() override;
        void set_stack_value(double value) override;
};


#endif //SIMULATEDICINTERFACE_H
