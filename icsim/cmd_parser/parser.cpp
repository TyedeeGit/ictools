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

#include "parser.h"

bool parse_command(const std::string& command, icsim_console_cmd *cmd) {
    std::istringstream iss(command);
    std::string cmd_str;
    iss >> cmd_str;

    cmd->argc = 0;
    cmd->argv = new char*[6];
    if (cmd_str == "step") {
        cmd->command = CMD_STEP;
        std::string arg;
    } else     if (cmd_str == "tick") {
        cmd->command = CMD_TICK;
        std::string arg;
        while (iss >> arg && cmd->argc <= 1) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 0;
    } else     if (cmd_str == "run") {
        cmd->command = CMD_RUN;
        std::string arg;
        while (iss >> arg && cmd->argc <= 2) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 1;
    } else     if (cmd_str == "info") {
        cmd->command = CMD_INFO;
        std::string arg;
        while (iss >> arg && cmd->argc <= 3) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 3;
    } else     if (cmd_str == "load") {
        cmd->command = CMD_LOAD;
        std::string arg;
        while (iss >> arg && cmd->argc <= 6) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 4;
    } else     if (cmd_str == "store") {
        cmd->command = CMD_STORE;
        std::string arg;
        while (iss >> arg && cmd->argc <= 6) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 4;
    } else     if (cmd_str == "set") {
        cmd->command = CMD_SET;
        std::string arg;
        while (iss >> arg && cmd->argc <= 4) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 4;
    } else     if (cmd_str == "watch") {
        cmd->command = CMD_WATCH;
        std::string arg;
        while (iss >> arg && cmd->argc <= 3) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 3;
    } else     if (cmd_str == "break") {
        cmd->command = CMD_BREAK;
        std::string arg;
        while (iss >> arg && cmd->argc <= 1) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 1;
    } else     if (cmd_str == "jump") {
        cmd->command = CMD_JUMP;
        std::string arg;
        while (iss >> arg && cmd->argc <= 1) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 1;
    } else     if (cmd_str == "return") {
        cmd->command = CMD_RETURN;
        std::string arg;
    } else     if (cmd_str == "dis" || cmd_str == "disassemble" || cmd_str == "disasm") {
        cmd->command = CMD_DISASM;
        std::string arg;
        while (iss >> arg && cmd->argc <= 1) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 1;
    } else     if (cmd_str == "assemble" || cmd_str == "asm") {
        cmd->command = CMD_ASM;
        std::string arg;
        while (iss >> arg && cmd->argc <= 2) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 1;
    } else     if (cmd_str == "save") {
        cmd->command = CMD_SAVE;
        std::string arg;
        while (iss >> arg && cmd->argc <= 4) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 2;
    } else     if (cmd_str == "hash") {
        cmd->command = CMD_HASH;
        std::string arg;
    } else     if (cmd_str == "help") {
        cmd->command = CMD_HELP;
        std::string arg;
        while (iss >> arg && cmd->argc <= 1) {
            cmd->argv[cmd->argc] = new char[arg.size() + 1];
            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);
            cmd->argc++;
        }
        return cmd->argc < 0;
    } else     if (cmd_str == "exit" || cmd_str == "quit") {
        cmd->command = CMD_QUIT;
        std::string arg;
    } else {
        cmd->command = CMD_UNKNOWN;
        return true;
    }
}

void free_command(icsim_console_cmd *cmd) {
    for (uint32_t i = 0; i < cmd->argc; ++i) {
        delete[] cmd->argv[i];
    }
    delete[] cmd->argv;
}

void print_usage(icsim_cmd cmd) {
    printf("%s", help_messages[cmd]);
}

icsim_cmd get_command(std::string cmd_str) {
    if (cmd_str == "step")
        return CMD_STEP;
    else     if (cmd_str == "tick")
        return CMD_TICK;
    else     if (cmd_str == "run")
        return CMD_RUN;
    else     if (cmd_str == "info")
        return CMD_INFO;
    else     if (cmd_str == "load")
        return CMD_LOAD;
    else     if (cmd_str == "store")
        return CMD_STORE;
    else     if (cmd_str == "set")
        return CMD_SET;
    else     if (cmd_str == "watch")
        return CMD_WATCH;
    else     if (cmd_str == "break")
        return CMD_BREAK;
    else     if (cmd_str == "jump")
        return CMD_JUMP;
    else     if (cmd_str == "return")
        return CMD_RETURN;
    else     if (cmd_str == "dis" || cmd_str == "disassemble" || cmd_str == "disasm")
        return CMD_DISASM;
    else     if (cmd_str == "assemble" || cmd_str == "asm")
        return CMD_ASM;
    else     if (cmd_str == "save")
        return CMD_SAVE;
    else     if (cmd_str == "hash")
        return CMD_HASH;
    else     if (cmd_str == "help")
        return CMD_HELP;
    else     if (cmd_str == "exit" || cmd_str == "quit")
        return CMD_QUIT;
    else 
        return CMD_UNKNOWN;
}