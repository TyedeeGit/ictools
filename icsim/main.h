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

#ifndef MAIN_H
#define MAIN_H
#define MAX_INSTRUCTIONS 128

#include <cstdio>
#include <cstring>
#include <unordered_set>
#include "icsimlib.h"

static std::unordered_set<icsim_breakpoint> breakpoints();
static std::unordered_set<icsim_var_watch> watches();
static std::unordered_map<std::string, std::vector<ic_instruction>> assembled_instructions;

inline bool step_all_chips(const std::vector<SimulatedIC<SimulatedICInterface>*>&);
inline uint32_t tick_all_chips(const std::vector<SimulatedIC<SimulatedICInterface>*>&, uint32_t = MAX_INSTRUCTIONS);
uint32_t run_all_chips(const std::vector<SimulatedIC<SimulatedICInterface>*>&, uint32_t, uint32_t = MAX_INSTRUCTIONS);
int32_t process_commands(const std::vector<SimulatedIC<SimulatedICInterface>*>&, FILE * = nullptr);
void print_help();
int32_t main(int32_t argc, char *argv[]);

#endif //MAIN_H
