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
#define MAX_ARG_COUNT 2
#define TOTAL_COMMANDS 5

#ifdef __cplusplus
extern "C" {
#endif

static const char* main_help_message = "List of commands:\n    step: Steps the simulation.\n        step \n\n    tick: Ticks the simulation. 128 max instructions will be run by default.\n        tick \n        tick <max_instructions>\n\n    run: Runs the simulation for a given number of ticks. 128 max instructions will be run by default.\n        run <ticks>\n        run <ticks> <max_instructions>\n\n    help: Displays usage of the command given. Displays all commands if no argument is provided\n        help \n        help <command>\n\n    quit: Exits icsim\n        quit \n        exit \n";
static const char* command_names[TOTAL_COMMANDS] = {
   "step",
   "tick",
   "run",
   "help",
   "quit",
};

static const char* help_messages[TOTAL_COMMANDS] = {
    "step: Steps the simulation.\n    step \n",
    "tick: Ticks the simulation. 128 max instructions will be run by default.\n    tick \n    tick <max_instructions>\n",
    "run: Runs the simulation for a given number of ticks. 128 max instructions will be run by default.\n    run <ticks>\n    run <ticks> <max_instructions>\n",
    "help: Displays usage of the command given. Displays all commands if no argument is provided\n    help \n    help <command>\n",
    "quit: Exits icsim\n    quit \n    exit \n",
};

typedef enum {
    CMD_UNKNOWN,
    CMD_STEP,
    CMD_TICK,
    CMD_RUN,
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
