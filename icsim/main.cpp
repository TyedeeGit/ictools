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

#include <chrono>
#include <iostream>
#include "icsimlib.h"

int main() {
    constexpr int total_instructions = 4;
    constexpr int ticks = 100000;
    ic_instruction buffer[total_instructions] = {{OP_MISC,{.op_misc = OP_JUMP_TAG},COMPARE_NULL,0,{{ARG_JUMP_TAG, 25}}},
                                                 {OP_MATH, {.op_math = OP_ASIN}, COMPARE_NULL, 0, {{ARG_REGISTER, {1, 0}}, {}, {}, {}, {}, {}, {}, {ARG_REGISTER, {1, 0}}}},
                                                 {OP_MISC,{.op_misc = OP_YIELD}, COMPARE_NULL},
                                                 {BRANCH,{},COMPARE_NULL,0,{{ARG_JUMP_TAG, 25}}}
                                 };

    auto device = SimulatedDevice(true);
    auto ic_interface = SimulatedICInterface(1, &device);
    auto simulation = SimulatedIC<SimulatedICInterface>(&ic_interface, buffer, total_instructions);



    auto start = std::chrono::system_clock::now();
    int instructions_run = simulation.run(ticks);
    auto end = std::chrono::system_clock::now();
    std::printf("r0: %f\n", *simulation.get_register_directly(0));

    std::chrono::duration<double> elapsed_seconds = end-start;

    std::printf("total instructions run: %d\n", instructions_run);
    std::printf("elapsed time: %.2fms\n", (elapsed_seconds.count()*1000));
    std::printf("elapsed time per instruction: %.2fns\n", ((elapsed_seconds.count()/instructions_run)*1000000000));
    return 0;
}