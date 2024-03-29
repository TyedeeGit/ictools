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


#include "SimulatedICInterface.h"

SimulatedICInterface::SimulatedICInterface(uint32_t count, SimulatedDevice *devices[]) {
    this->device_count = count;
    this->devices = std::vector<SimulatedDevice *>(count, reinterpret_cast<SimulatedDevice *const>(devices));
    this->set_devices = std::vector<int32_t>(7, {});
    this->registers = std::vector<double>(18, {});
    this->stack = std::vector<double>(512, {});
}

SimulatedDevice SimulatedICInterface::find_device(int32_t pin) {
    return *this->devices[this->set_devices[pin]];
}

int32_t SimulatedICInterface::find_devices(SimulatedDevice found_devices[], uint32_t device_hash) {
    int32_t count = 0;
    for (int32_t i = 0; i < this->device_count; i++)
        if (this->devices[i]->get_device_type_hash() == device_hash) {
            found_devices[count] = *this->devices[i];
            count++;
        }
    return count;
}

int32_t SimulatedICInterface::find_devices(SimulatedDevice found_devices[], uint32_t device_hash, uint32_t name_hash) {
    int32_t count = 0;
    for (int32_t i = 0; i < this->device_count; i++)
        if (this->devices[i]->get_device_type_hash() == device_hash & this->devices[i]->get_device_name_hash() == name_hash) {
            found_devices[count] = *this->devices[i];
            count++;
        }
    return count;
}

double SimulatedICInterface::loadd(uint32_t property_hash, int32_t device)  {
    return this->find_device(device).get_property(property_hash);
}

double SimulatedICInterface::loadb(uint32_t property_hash, uint32_t device_hash, ic_batch_mode batch_mode)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash);
    double sum = 0;
    double min, max = 0;
    double current_property;
    for (int32_t i = 0; i < count; i++) {
        current_property = batch_devices[i].get_property(property_hash);
        sum += current_property;
        if (current_property < min)
            min = current_property;
        if (current_property > max)
            max = current_property;
    }
    switch (batch_mode) {
        case BATCH_AVERAGE:
            return sum / count;
        case BATCH_SUM:
            return sum;case BATCH_MIN:return min;case BATCH_MAX:return max;
    }
}

double SimulatedICInterface::loadbn(uint32_t property_hash, uint32_t device_hash, ic_batch_mode batch_mode, uint32_t name_hash)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash, name_hash);
    double sum = 0;
    double min, max = 0;
    double current_property;
    for (int32_t i = 0; i < count; i++) {
        current_property = batch_devices[i].get_property(property_hash);
        sum += current_property;
        if (current_property < min)
            min = current_property;
        if (current_property > max)
            max = current_property;
    }
    switch (batch_mode) {
        case BATCH_AVERAGE:
            return sum / count;
        case BATCH_SUM:
            return sum;case BATCH_MIN:return min;case BATCH_MAX:return max;
    }
}

double SimulatedICInterface::loadrd(uint32_t reagent_hash, int32_t device, ic_reagent_mode reagent_mode)  {
    return this->find_device(device).get_reagent(reagent_hash, reagent_mode);
}

double SimulatedICInterface::loadrb(uint32_t reagent_hash, uint32_t device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash);
    double sum = 0;
    double min, max = 0;
    double current_property;
    for (int32_t i = 0; i < count; i++) {
        current_property = batch_devices[i].get_reagent(reagent_hash, reagent_mode);
        sum += current_property;
        if (current_property < min)
            min = current_property;
        if (current_property > max)
            max = current_property;
    }
    switch (batch_mode) {
        case BATCH_AVERAGE:
            return sum / count;
        case BATCH_SUM:
            return sum;case BATCH_MIN:return min;case BATCH_MAX:return max;
    }
}

double SimulatedICInterface::loadrbn(uint32_t reagent_hash, uint32_t device_hash, ic_reagent_mode reagent_mode, ic_batch_mode batch_mode, uint32_t name_hash)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash, name_hash);
    double sum = 0;
    double min, max = 0;
    double current_property;
    for (int32_t i = 0; i < count; i++) {
        current_property = batch_devices[i].get_reagent(reagent_hash, reagent_mode);
        sum += current_property;
        if (current_property < min)
            min = current_property;
        if (current_property > max)
            max = current_property;
    }
    switch (batch_mode) {
        case BATCH_AVERAGE:
            return sum / count;
        case BATCH_SUM:
            return sum;case BATCH_MIN:return min;case BATCH_MAX:return max;
    }
}

double SimulatedICInterface::loadsd(uint32_t slot_var, int32_t device, int32_t slot)  {
    return this->find_device(device).get_slot(slot_var, slot);
}

double SimulatedICInterface::loadsb(uint32_t slot_var, uint32_t device_hash, int32_t slot, ic_batch_mode batch_mode)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash);
    double sum = 0;
    double min, max = 0;
    double current_property;
    for (int32_t i = 0; i < count; i++) {
        current_property = batch_devices[i].get_slot(slot_var, slot);
        sum += current_property;
        if (current_property < min)
            min = current_property;
        if (current_property > max)
            max = current_property;
    }
    switch (batch_mode) {
        case BATCH_AVERAGE:
            return sum / count;
        case BATCH_SUM:
            return sum;case BATCH_MIN:return min;case BATCH_MAX:return max;
    }
}

double SimulatedICInterface::loadsbn(uint32_t slot_var, uint32_t device_hash, int32_t slot, ic_batch_mode batch_mode, uint32_t name_hash)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash, name_hash);
    double sum = 0;
    double min, max = 0;
    double current_property;
    for (int32_t i = 0; i < count; i++) {
        current_property = batch_devices[i].get_slot(slot_var, slot);
        sum += current_property;
        if (current_property < min)
            min = current_property;
        if (current_property > max)
            max = current_property;
    }
    switch (batch_mode) {
        case BATCH_AVERAGE:
            return sum / count;
        case BATCH_SUM:
            return sum;case BATCH_MIN:return min;case BATCH_MAX:return max;
    }
}

void SimulatedICInterface::stored(double value, uint32_t property_hash, int32_t device)  {
    this->find_device(device).set_property(property_hash, value);
}

void SimulatedICInterface::storeb(double value, uint32_t property_hash, uint32_t device_hash)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash);
    for (int32_t i = 0; i < count; i++)
        this->devices[i]->set_property(property_hash, value);
}

void SimulatedICInterface::storebn(double value, uint32_t property_hash, uint32_t device_hash, uint32_t name_hash)  {
    SimulatedDevice batch_devices[this->device_count];
    int32_t count = this->find_devices(batch_devices, device_hash, name_hash);
    for (int32_t i = 0; i < count; i++)
        this->devices[i]->set_property(property_hash, value);
}

inline bool SimulatedICInterface::get_device_set(int32_t device)  {
    struct is_device {
        const int32_t d;
        explicit is_device(int32_t n) : d(n) {}
        bool operator()(int32_t n) const { return d == n;}
    };
    return std::any_of(this->set_devices.cbegin(), this->set_devices.cend(), is_device(device));
}

bool SimulatedICInterface::set_device(int32_t device, int32_t pin) {
    auto device_was_set = this->get_device_set(device);
    if (!device_was_set)
        this->set_devices[pin] = device;
    return device_was_set;
}

inline double *SimulatedICInterface::get_register(int32_t register_index)  {
    return &(this->registers[register_index]);
}

inline double SimulatedICInterface::get_stack_value()  {
    return this->stack[(int32_t) this->registers[16]];
}

inline void SimulatedICInterface::set_stack_value(double value)  {
    this->stack[(int32_t) this->registers[16]] = value;
}