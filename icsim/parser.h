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

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#define MAX_ARG_COUNT 6
#define TOTAL_COMMANDS 16

#ifdef __cplusplus
extern "C" {
#endif

static const char* main_help_message = "List of commands:\n    step: Steps the simulation.\n        step \n\n    tick: Ticks the simulation. 128 max instructions will be run by default.\n        tick \n        tick <max-instructions>\n\n    run: Runs the simulation for a given number of ticks. 128 max instructions will be run by default.\n        run <ticks>\n        run <ticks> <max-instructions>\n\n    info: Read the value of a register or address.\n        info <chip-id> <register|address> <register-or-address>\n\n    load: Read a property of a device or several devices.\n        load <d> <chip-id> <device-pin> <property>\n        load <b> <device-hash> <property> <batch-mode>\n        load <bn> <device-hash> <property> <batch-mode> <name-hash>\n        load <s> <chip-id> <device-pin> <slot-property> <slot>\n        load <sb> <device-hash> <slot-property> <batch-mode> <slot>\n        load <sbn> <device-hash> <slot-property> <batch-mode> <name-hash> <slot>\n        load <r> <chip-id> <device-pin> <reagent-hash> <reagent-mode>\n        load <rb> <device-hash> <reagent-hash> <batch-mode> <reagent-mode>\n        load <rbn> <device-hash> <reagent-hash> <batch-mode> <name-hash> <reagent-mode>\n\n    store: Write a property of a device or several devices.\n        store <d> <chip-id> <device-pin> <property>\n        store <b> <device-hash> <property> <value>\n        store <bn> <device-hash> <property> <value> <name-hash>\n        store <s> <chip-id> <device-pin> <slot-property> <slot>\n        store <sb> <device-hash> <slot-property> <value> <slot>\n        store <sbn> <device-hash> <slot-property> <value> <name-hash> <slot>\n        store <r> <chip-id> <device-pin> <reagent-hash> <reagent-mode>\n        store <rb> <device-hash> <reagent-hash> <value> <reagent-mode>\n        store <rbn> <device-hash> <reagent-hash> <value> <name-hash> <reagent-mode>\n\n    set: Set the value of a register or address.\n        set <chip-id> <register|address> <register-or-address> <value>\n\n    watch: Watch the value of a register or address.\n        watch <chip-id> <register|address> <register-or-address>\n\n    break: Set a breakpoint.\n        break <line>\n\n    jump: Jump to line or function.\n        jump <line>\n        jump <function>\n\n    return: Jump to return address.\n        return \n\n    disasm: Disassemble bytecode.\n        disasm <chip-id>\n        disasm <chip-id> <line>\n        disasm <chip-id> <line-start> <line-end>\n        dis <chip-id>\n        dis <chip-id> <line>\n        dis <chip-id> <line-start> <line-end>\n        disassemble <chip-id>\n        disassemble <chip-id> <line>\n        disassemble <chip-id> <line-start> <line-end>\n\n    asm: Assemble code.\n        asm <name>\n        assemble <name>\n\n    hash: Hash a string.\n        hash \n\n    help: Displays usage of the command given. Displays all commands if no argument is provided\n        help \n        help <command>\n\n    quit: Exits icsim\n        quit \n        exit \n";
static const char* command_names[TOTAL_COMMANDS] = {
   "step",
   "tick",
   "run",
   "info",
   "load",
   "store",
   "set",
   "watch",
   "break",
   "jump",
   "return",
   "disasm",
   "asm",
   "hash",
   "help",
   "quit",
};

static const char* help_messages[TOTAL_COMMANDS] = {
    "step: Steps the simulation.\n    step \n",
    "tick: Ticks the simulation. 128 max instructions will be run by default.\n    tick \n    tick <max-instructions>\n",
    "run: Runs the simulation for a given number of ticks. 128 max instructions will be run by default.\n    run <ticks>\n    run <ticks> <max-instructions>\n",
    "info: Read the value of a register or address.\n    info <chip-id> <register|address> <register-or-address>\n",
    "load: Read a property of a device or several devices.\n    load <d> <chip-id> <device-pin> <property>\n    load <b> <device-hash> <property> <batch-mode>\n    load <bn> <device-hash> <property> <batch-mode> <name-hash>\n    load <s> <chip-id> <device-pin> <slot-property> <slot>\n    load <sb> <device-hash> <slot-property> <batch-mode> <slot>\n    load <sbn> <device-hash> <slot-property> <batch-mode> <name-hash> <slot>\n    load <r> <chip-id> <device-pin> <reagent-hash> <reagent-mode>\n    load <rb> <device-hash> <reagent-hash> <batch-mode> <reagent-mode>\n    load <rbn> <device-hash> <reagent-hash> <batch-mode> <name-hash> <reagent-mode>\n",
    "store: Write a property of a device or several devices.\n    store <d> <chip-id> <device-pin> <property>\n    store <b> <device-hash> <property> <value>\n    store <bn> <device-hash> <property> <value> <name-hash>\n    store <s> <chip-id> <device-pin> <slot-property> <slot>\n    store <sb> <device-hash> <slot-property> <value> <slot>\n    store <sbn> <device-hash> <slot-property> <value> <name-hash> <slot>\n    store <r> <chip-id> <device-pin> <reagent-hash> <reagent-mode>\n    store <rb> <device-hash> <reagent-hash> <value> <reagent-mode>\n    store <rbn> <device-hash> <reagent-hash> <value> <name-hash> <reagent-mode>\n",
    "set: Set the value of a register or address.\n    set <chip-id> <register|address> <register-or-address> <value>\n",
    "watch: Watch the value of a register or address.\n    watch <chip-id> <register|address> <register-or-address>\n",
    "break: Set a breakpoint.\n    break <line>\n",
    "jump: Jump to line or function.\n    jump <line>\n    jump <function>\n",
    "return: Jump to return address.\n    return \n",
    "disasm: Disassemble bytecode.\n    disasm <chip-id>\n    disasm <chip-id> <line>\n    disasm <chip-id> <line-start> <line-end>\n    dis <chip-id>\n    dis <chip-id> <line>\n    dis <chip-id> <line-start> <line-end>\n    disassemble <chip-id>\n    disassemble <chip-id> <line>\n    disassemble <chip-id> <line-start> <line-end>\n",
    "asm: Assemble code.\n    asm <name>\n    assemble <name>\n",
    "hash: Hash a string.\n    hash \n",
    "help: Displays usage of the command given. Displays all commands if no argument is provided\n    help \n    help <command>\n",
    "quit: Exits icsim\n    quit \n    exit \n",
};

typedef enum {
    CMD_UNKNOWN,
    CMD_STEP,
    CMD_TICK,
    CMD_RUN,
    CMD_INFO,
    CMD_LOAD,
    CMD_STORE,
    CMD_SET,
    CMD_WATCH,
    CMD_BREAK,
    CMD_JUMP,
    CMD_RETURN,
    CMD_DISASM,
    CMD_ASM,
    CMD_HASH,
    CMD_HELP,
    CMD_QUIT,
} icsim_cmd;

typedef struct {
    icsim_cmd command;
    size_t argc;
    char** argv;
} icsim_console_cmd;

bool parse_command(const std::string& command, icsim_console_cmd *cmd);

void free_command(icsim_console_cmd *cmd);

void print_usage(icsim_cmd cmd);

icsim_cmd get_command(std::string command);

#ifdef __cplusplus
}
#endif
#endif //PARSER_H
