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

#ifndef ICASM_SIMULATEDICINTERFACE_H
#define ICASM_SIMULATEDICINTERFACE_H

#include "ICInterface.h"
#include "SimulatedDevice.h"

class SimulatedICInterface : public ICInterface {
    protected:
        int device_count;
        double registers[18] = {};
        double stack[512] = {};
        int set_devices[7] = {};
        SimulatedDevice *devices;
    public:
        SimulatedICInterface(int count, SimulatedDevice *devices);
        inline SimulatedDevice find_device(int device);
        int find_devices(SimulatedDevice found_devices[], unsigned device_hash);
        int find_devices(SimulatedDevice found_devices[], unsigned device_hash, unsigned name_hash);
        double loadd(unsigned property_hash, int device) override;
        double loadb(unsigned property_hash, unsigned device_hash, ic_batch_mode batch_mode) override;
        double loadbn(unsigned property_hash, unsigned device_hash, ic_batch_mode batch_mode, unsigned name_hash) override;
        double loadrd(unsigned reagent_hash, int device, ic_reagent_mode reagent_mode) override;
        double loadrb(unsigned reagent_hash, unsigned device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode) override;
        double loadrbn(unsigned reagent_hash, unsigned device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode, unsigned name_hash) override;
        double loadsd(unsigned slot_var, int device, int slot) override;
        double loadsb(unsigned slot_var, unsigned device_hash, int slot, ic_batch_mode batch_mode) override;
        double loadsbn(unsigned slot_var, unsigned device_hash, int slot, ic_batch_mode batch_mode, unsigned name_hash) override;
        void stored(double value, unsigned property_hash, int device) override;
        void storeb(double value, unsigned property_hash, unsigned device_hash) override;
        void storebn(double value, unsigned property_hash, unsigned device_hash, unsigned name_hash) override;
        bool get_device_set(int device) override;
        double *get_register(int register_index) override;
        double get_stack_value() override;
        void set_stack_value(double value) override;
};


#endif //ICASM_SIMULATEDICINTERFACE_H
