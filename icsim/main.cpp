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

#include "main.h"

int process_commands(const std::vector<SimulatedIC<SimulatedICInterface>*>& chips, FILE *output_log) {
    std::string command_string;
    std::stringstream error_stream;
    icsim_console_cmd command;
    bool parsing_failed;
    while (true) {
        std::cerr << error_stream.str();
        std::cerr.flush();
        std::cout << ">";
        std::getline(std::cin, command_string);
        parsing_failed = parse_command(command_string, &command);
        if (parsing_failed) {
            if (command.command == CMD_UNKNOWN)
                error_stream << "Unknown command. Type 'help' for a list of commands.\n";
            else {
                char *str = nullptr;
                sprintf(str, "Invalid usage. Type 'help %s' for a list of valid usages.\n", command_names[command.command-1]);
                error_stream << str;
            }
            continue;
        }
        switch (command.command) {
            case CMD_UNKNOWN:
                error_stream << "Unknown command. Type 'help' for a list of commands.\n";
                break;
            case CMD_HELP:
                if (!command.argc)
                    printf("%s", main_help_message);
                else
                    if (get_command(command.argv[0]) == CMD_UNKNOWN)
                        error_stream << "Unknown command. Type 'help' for a list of commands.\n";
                    else
                        print_usage((icsim_cmd)(((int) get_command(command.argv[0])) - 1));
                break;
            case CMD_QUIT:
                return 0;
            case CMD_STEP:
                break;
            case CMD_TICK:
                break;
            case CMD_RUN:
                break;
            case CMD_INFO:
                break;
            case CMD_SET:
                break;
            case CMD_WATCH:
                break;
            case CMD_BREAK:
                break;
            case CMD_JUMP:
                break;
            case CMD_RETURN:
                break;
            case CMD_DISASM:
                break;
            case CMD_LOAD:
                break;
            case CMD_STORE:
                break;
            case CMD_HASH:
                break;
            case CMD_ASM:
                break;
        }
    }
}

void print_help() {
    printf("Usage: icsim [options] <filename>\n");
    printf("Options:\n");
    printf("  [-h | --help]               Display this help message\n");
    printf("  [[-l | --log] [output]]     Log output to file\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    char *output_filename;
    FILE *output_file = nullptr;
    bool log_output = strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--log") == 0;
    if (log_output) {
        output_filename = argv[2];
        output_file = fopen(output_filename, "w");
        if (output_file == nullptr) {
            fprintf(stderr, "Error opening input_file %s\n", output_filename);
            return 1;
        }
    }

    char *input_filename;
    input_filename = argv[log_output ? 3 : 1];

    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == nullptr) {
        fprintf(stderr, "Error opening input_file %s\n", input_filename);
        return 1;
    }

    std::vector<char>buffer(1024);
    void *pointer;
    icsim_header header;
    std::vector<icsim_device> serialized_devices;
    std::vector<icsim_chip> serialized_chips;
    std::vector<icsim_chip_data> chips_data;
    std::vector<std::vector<ic_instruction>> instruction_data;
    std::vector<std::vector<icsim_io_var>> var_data;
    size_t devices_consumed = 0;
    size_t chips_consumed = 0;
    size_t instructions_consumed = 0;
    size_t vars_consumed = 0;
    size_t bytes_to_consume = 0;

    bool consuming_instuctions = false;
    bool consuming_vars = false;

    while ((pointer = fgets(buffer.data(), sizeof(char [1024]), input_file)) != nullptr) {
        if (!bytes_to_consume && pointer < &buffer[1023] + 1) {
            if (pointer == buffer.data()) {
                header = *(icsim_header *) pointer;
                serialized_devices = *new std::vector<icsim_device>(header.devices_count);
                serialized_chips = *new std::vector<icsim_chip>(header.chips_count);
                bytes_to_consume = sizeof(header);
            } else if (devices_consumed < header.devices_count) {
                if (!consuming_vars) {
                    serialized_devices[devices_consumed] = *(icsim_device *)pointer;
                    var_data[devices_consumed].reserve(serialized_devices[devices_consumed].total_var_count);
                    serialized_devices[devices_consumed].io_vars = var_data[devices_consumed].data();
                    bytes_to_consume = sizeof(icsim_device);
                    consuming_vars = true;
                } else if (vars_consumed < serialized_devices[devices_consumed].total_var_count) {
                    var_data[devices_consumed][vars_consumed] = *(icsim_io_var *)pointer;
                    bytes_to_consume = sizeof(icsim_io_var);
                    vars_consumed++;
                } else {
                    consuming_vars = false;
                    devices_consumed++;
                }

            } else if (chips_consumed < header.chips_count) {
                if (!consuming_instuctions) {
                    serialized_chips[chips_consumed] = *(icsim_chip *)pointer;
                    chips_data[chips_consumed].serialized_chip = &serialized_chips[chips_consumed];
                    instruction_data[chips_consumed].reserve(serialized_chips[chips_consumed].instruction_count);
                    chips_data[chips_consumed].instructions = instruction_data[chips_consumed].data();
                    bytes_to_consume = sizeof(icsim_chip);
                    consuming_instuctions = true;
                } else if (instructions_consumed < serialized_chips[chips_consumed].instruction_count) {
                    instruction_data[chips_consumed][instructions_consumed] = *(ic_instruction *)pointer;
                    bytes_to_consume = sizeof(ic_instruction);
                    instructions_consumed++;
                } else {
                    consuming_instuctions = false;
                    chips_consumed++;
                }
            }
        }
    }
    fclose(input_file);

    std::vector<SimulatedIC<SimulatedICInterface>*> chips(header.chips_count);
    int i = 0;
    for (auto chip_data : chips_data) {
        deserialize_interface(&chip_data.interface, &header, serialized_devices);
        deserialize_chip(&chip_data.chip, &header, chip_data.serialized_chip, &chip_data.interface, chip_data.instructions);
        chips[i] = &chip_data.chip;
        i++;
    }

    printf("Copyright (C) 2024 Tyedee\nMIT License\n");
    return process_commands(chips, output_file);
}