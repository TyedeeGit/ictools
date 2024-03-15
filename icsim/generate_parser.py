import sys
import json

cpp_license = """/*
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
"""


def modify_sig(sigs):
    return ", ".join(f"{{{", ".join(f"\"{sig_type}\"" for sig_type in sig)}}}" for sig in sigs)


def get_name_comps(cmd):
    return ' || '.join(f'cmd_str == "{name}"' for name in cmd.get('aliases', []) + [cmd.get('name', '')])


def generate_cpp_parser(commands_info):
    commands_info.append({'name': 'help',
                          'arg_signatures': [[], ["command"]],
                          'help_message': 'Displays usage of the command given. Displays all commands if no argument '
                                          'is provided'})
    commands_info.append({'name': 'quit',
                          'aliases': ['exit'], 'arg_signatures': [[]],
                          'help_message': 'Exits icsim'})
    # Determine the maximum argument count
    max_arg_count = max(
        max(len(signature) for signature in command.get('arg_signatures', [[]])) for command in commands_info)

    help_message = "List of commands:\\n"
    messages = []

    for command in commands_info:
        message = f'    {command.get('name', '')}: {command.get('help_message', '')}\\n'
        for sig in command.get('arg_signatures', [[]]):
            message += f'        {command.get('name', '')} {' '.join(f'<{sig_type}>' for sig_type in sig)}\\n'
        for alias in command.get('aliases', []):
            for sig in command.get('arg_signatures', [[]]):
                message += f'        {alias} {' '.join(f'<{sig_type}>' for sig_type in sig)}\\n'
        messages.append(message)
    help_message += '\\n'.join(messages)

    # Generate the header file content
    header_code = f'''{cpp_license}\n#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#define MAX_ARG_COUNT {max_arg_count}
#define TOTAL_COMMANDS {len(commands_info)}

#ifdef __cplusplus
extern "C" {{
#endif\n
'''
    header_code += f'static const char* main_help_message = "{help_message}";\n'
    header_code += 'static const char* command_names[TOTAL_COMMANDS] = {\n'
    for command in commands_info:
        header_code += f'   "{command.get('name', '')}",\n'
    header_code += '};\n\n'
    header_code += 'static const char* help_messages[TOTAL_COMMANDS] = {\n'
    for command in commands_info:
        message = f'{command.get('name', '')}: {command.get('help_message', '')}\\n'
        for sig in command.get('arg_signatures', [[]]):
            message += f'    {command.get('name', '')} {' '.join(f'<{sig_type}>' for sig_type in sig)}\\n'
        for alias in command.get('aliases', []):
            for sig in command.get('arg_signatures', [[]]):
                message += f'    {alias} {' '.join(f'<{sig_type}>' for sig_type in sig)}\\n'
        header_code += f'    "{message}",\n'
    header_code += '};\n\n'
    header_code += 'typedef enum {\n    CMD_UNKNOWN,\n'
    for command in commands_info:
        command_name = command['name'].upper()
        header_code += f'    CMD_{command_name},\n'

    header_code += '} icsim_cmd;\n\n'
    header_code += 'typedef struct {\n'

    header_code += f'''    icsim_cmd command;
    size_t argc;
    char** argv;
}} icsim_console_cmd;

bool parse_command(const std::string& command, icsim_console_cmd *cmd);

void free_command(icsim_console_cmd *cmd);

void print_usage(icsim_cmd cmd);

icsim_cmd get_command(std::string command);

#ifdef __cplusplus
}}
#endif
#endif //PARSER_H
'''

    # Generate the implementation file content
    implementation_code = f'''{cpp_license}\n#include "parser.h"

bool parse_command(const std::string& command, icsim_console_cmd *cmd) {{
    std::istringstream iss(command);
    std::string cmd_str;
    iss >> cmd_str;

    cmd->argc = 0;
'''

    # Allocate argv with the maximum arg count
    implementation_code += f'    cmd->argv = new char*[{max_arg_count}];\n'

    # Add code to parse each command
    for command in commands_info:
        command_name = command['name']
        command_upper = command_name.upper()
        arg_signatures = command.get('arg_signatures', [[]])
        implementation_code += f'    if ({get_name_comps(command)}) {{\n'
        implementation_code += f'        cmd->command = CMD_{command_upper};\n'
        implementation_code += '        std::string arg;\n'
        if max(len(sig) for sig in arg_signatures):
            comp = f'iss >> arg && cmd->argc <= {max(len(sig) for sig in arg_signatures)}'
            implementation_code += f'        while ({comp}) {{\n'
            implementation_code += '            cmd->argv[cmd->argc] = new char[arg.size() + 1];\n'
            implementation_code += '            std::strncpy(cmd->argv[cmd->argc], arg.c_str(), arg.size() + 1);\n'
            implementation_code += '            cmd->argc++;\n'
            implementation_code += '        }\n'
            implementation_code += f'        return cmd->argc < {min(len(sig) for sig in arg_signatures)};\n'
        implementation_code += '    } else '

    # Add default case
    implementation_code += '''{
        cmd->command = CMD_UNKNOWN;
        return true;
    }
}

void free_command(icsim_console_cmd *cmd) {
    for (size_t i = 0; i < cmd->argc; ++i) {
        delete[] cmd->argv[i];
    }
    delete[] cmd->argv;
}

void print_usage(icsim_cmd cmd) {
    printf("%s", help_messages[cmd]);
}

icsim_cmd get_command(std::string cmd_str) {
'''
    for command in commands_info:
        implementation_code += f'    if ({get_name_comps(command)})\n'
        implementation_code += f'        return CMD_{command.get('name', '').upper()};\n'
        implementation_code += '    else '
    implementation_code += '\n        return CMD_UNKNOWN;\n'
    implementation_code += '}'
    return header_code, implementation_code


def main():
    if len(sys.argv) != 2:
        print("Usage: python generate_parser.py commands.json")
        return

    json_file = sys.argv[1]

    try:
        with open(json_file) as f:
            data = json.load(f)
            commands_info = data.get('info', [])
    except FileNotFoundError:
        print(f"File {json_file} not found.")
        return
    except json.JSONDecodeError:
        print(f"Error decoding JSON file: {json_file}.")
        return

    header_content, implementation_content = generate_cpp_parser(commands_info)

    with open('parser.h', 'w') as header_file:
        header_file.write(header_content)

    with open('parser.cpp', 'w') as implementation_file:
        implementation_file.write(implementation_content)


if __name__ == '__main__':
    main()
