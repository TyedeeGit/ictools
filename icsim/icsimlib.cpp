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

#include "icsimlib.h"

void deserialize_device(SimulatedDevice *pointer, icsim_device *serialized_device) {
    *pointer = SimulatedDevice(serialized_device->type_hash, serialized_device->name);

    const unsigned DEVICE_VARS_END = serialized_device->device_var_count;
    const unsigned SLOT_VARS_END = serialized_device->device_var_count + serialized_device->slot_var_count;
    const unsigned REAGENT_VARS_END = serialized_device->device_var_count + serialized_device->slot_var_count + serialized_device->reagent_var_count;

    for (unsigned i = 0; i < DEVICE_VARS_END; i++)
        pointer->set_property(serialized_device->io_vars[i].device_var.hash,
                            serialized_device->io_vars[i].device_var.value);

    for (unsigned i = DEVICE_VARS_END; i < SLOT_VARS_END; i++)
        pointer->set_slot(serialized_device->io_vars[i].slot_var.hash,
                        serialized_device->io_vars[i].slot_var.slot,
                        serialized_device->io_vars[i].slot_var.value);

    for (unsigned i = SLOT_VARS_END; i < REAGENT_VARS_END; i++)
        pointer->set_reagent(serialized_device->io_vars[i].reagent_var.hash,
                           serialized_device->io_vars[i].reagent_var.mode,
                           serialized_device->io_vars[i].reagent_var.value);
}

void deserialize_interface(SimulatedICInterface *pointer, icsim_header *header, std::vector<icsim_device> buffer) {
    std::vector<SimulatedDevice> devices(header->devices_count);
    std::vector<SimulatedDevice *> device_pointers(header->devices_count);
    for (int i = 0; i < header->devices_count; i++) {
        device_pointers[i] = &devices[i];
        deserialize_device(device_pointers[i], &buffer[i]);
    }
    *pointer = SimulatedICInterface(header->devices_count, device_pointers.data());
}

void deserialize_chip(SimulatedIC<SimulatedICInterface> *pointer, icsim_header *header, icsim_chip *chip, SimulatedICInterface *interface, ic_instruction instructions[]) {
    *pointer = SimulatedIC<SimulatedICInterface>(interface, instructions, chip->instruction_count);
}