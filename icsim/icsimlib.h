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

#pragma once
#ifndef ICSIMLIB_H
#define ICSIMLIB_H


#include <limits>
#include <cmath>
#include <ctime>
#include "iclib.h"
#include "SimulatedDevice.h"
#include "SimulatedICInterface.h"
#include "SimulatedIC.h"
#include "parser.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned hash;
    double value;
} icsim_device_var;

typedef struct {
    unsigned hash;
    double value;
    int slot;
} icsim_slot_var;

typedef struct {
    unsigned hash;
    double value;
    ic_reagent_mode mode;
} icsim_reagent_var;

typedef union {
    icsim_device_var device_var;
    icsim_slot_var slot_var;
    icsim_reagent_var reagent_var;
} icsim_io_var;

typedef struct {
    size_t total_var_count;
    size_t device_var_count;
    size_t slot_var_count;
    size_t reagent_var_count;
    unsigned type_hash;
    char name[32];
    icsim_io_var *io_vars;
} icsim_device;

typedef struct {
    size_t instruction_count;
    int pins[7];
} icsim_chip;

typedef struct {
    size_t chips_count;
    size_t devices_count;
    size_t counts[];
} icsim_header;

#ifdef __cplusplus
}

typedef struct icsim_chip_data {
    SimulatedICInterface interface;
    SimulatedIC<SimulatedICInterface> chip;
    icsim_chip *serialized_chip = nullptr;
    ic_instruction *instructions = nullptr;
} icsim_chip_data;

void deserialize_device(SimulatedDevice *, icsim_device *);
void deserialize_interface(SimulatedICInterface *, icsim_header *, std::vector<icsim_device>);
void deserialize_chip(SimulatedIC<SimulatedICInterface> *, icsim_header *, icsim_chip *, SimulatedICInterface *, ic_instruction []);
#endif

#endif //ICSIMLIB_H