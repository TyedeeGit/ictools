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

#ifndef SIMULATEDIC_H
#define SIMULATEDIC_H

#include <unordered_map>
#include <random>
#include "iclib.h"

template <typename T>
class SimulatedIC {
    protected:
        ic_instruction *instruction_buffer{};
        uint32_t total_instructions{};
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution;
        void handle_branch(ic_instruction current_instruction);
        void handle_select(ic_instruction current_instruction);
        void handle_math_op(ic_instruction current_instruction);
        void handle_logic_op(ic_instruction current_instruction);
        void handle_stack_op(ic_instruction current_instruction);
        void handle_io_op(ic_instruction current_instruction);
        void handle_misc_op(ic_instruction current_instruction);
    public:
        int32_t instruction_counter = 0;
        int32_t yielding = 0;
        T *ic_interface;
        std::unordered_map<uint32_t, double*> register_aliases;
        std::unordered_map<uint32_t, int32_t> device_aliases;
        std::unordered_map<uint32_t, double> definitions;
        std::unordered_map<uint32_t, int32_t> jump_tags;

        SimulatedIC(T *device_interface, ic_instruction *instruction_buffer, uint32_t total_instructions);
        double *resolve_register_reference(ic_reference reference);
        inline double *get_register(ic_arg arg);
        inline double *get_register_directly(int32_t i);
        inline double resolve_argument(ic_arg arg);
        inline int32_t resolve_line_number(ic_arg line);
        inline bool compute_compare(ic_instruction instruction);
        inline bool step();
        inline uint32_t run_single_tick(uint32_t max_instructions = 128);
        inline uint32_t run(int32_t ticks = 1, uint32_t max_instructions = 128);
};

#endif //SIMULATEDIC_H
