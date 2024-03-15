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

#include <ctime>
#include "SimulatedIC.h"
#include "SimulatedICInterface.h"

double epsilon = std::numeric_limits<double>::epsilon();

template <typename T> void SimulatedIC<T>::handle_branch(ic_instruction current_instruction) {
    const int line_number = this->resolve_line_number(current_instruction.args[0])-1;
    if (this->compute_compare(current_instruction)) {
        if (current_instruction.instruction_flags & FLAG_RELATIVE)
            this->instruction_counter += line_number; // Relative jump
        else
            this->instruction_counter = line_number; // Normal jump

        if (current_instruction.instruction_flags & FLAG_AL)
            *this->get_register_directly(17) = this->instruction_counter + 1; // Store in ra
    }
}

template <typename T> void SimulatedIC<T>::handle_select(ic_instruction current_instruction) {
    double *current_register = this->get_register(current_instruction.args[0]);
    if (!current_instruction.comparison) {
        current_instruction.comparison = COMPARE_NEZ;
        *current_register = this->compute_compare(current_instruction)
                            ? this->resolve_argument(current_instruction.args[1])
                            : this->resolve_argument(current_instruction.args[2]);
        current_instruction.comparison = COMPARE_NULL;
    }
    else
        *current_register = this->compute_compare(current_instruction) ? 1 : 0;
}

template <typename T> void SimulatedIC<T>::handle_math_op(ic_instruction current_instruction) {
    double *current_register = this->get_register(current_instruction.args[0]);
    const double arg1 = this->resolve_argument(current_instruction.args[7]);
    const double arg2 = this->resolve_argument(current_instruction.args[6]);
    switch (current_instruction.operation.op_math) {
        case OP_ABS:
            *current_register = std::abs(arg1);
            break;
        case OP_ACOS:
            *current_register = std::acos(arg1);
            break;
        case OP_ADD:
            *current_register = arg1 + arg2;
            break;
        case OP_ASIN:
            *current_register = std::asin(arg1);
            break;
        case OP_ATAN:
            *current_register = std::atan(arg1);
            break;
        case OP_CEIL:
            *current_register = std::ceil(arg1);
            break;
        case OP_COS:
            *current_register = std::cos(arg1);
            break;
        case OP_DIV:
            *current_register = arg1 / arg2;
            break;
        case OP_EXP:
            *current_register = std::exp(arg1);
            break;
        case OP_FLOOR:
            *current_register = std::floor(arg1);
            break;
        case OP_LOG:
            *current_register = std::log(arg1);
            break;
        case OP_MAX:
            *current_register = std::max(arg1, arg2);
            break;
        case OP_MIN:
            *current_register = std::min(arg1, arg2);
            break;
        case OP_MOD:
            *current_register = std::fmod(arg1, arg2);
            if (*current_register < 0)
                *current_register += arg2;
            break;
        case OP_MUL:
            *current_register = arg1 * arg2;
            break;
        case OP_RAND:
            *current_register = this->distribution(this->generator);
            break;
        case OP_ROUND:
            *current_register = std::round(arg1);
            break;
        case OP_SIN:
            *current_register = std::sin(arg1);
            break;
        case OP_SQRT:
            *current_register = std::sqrt(arg1);
            break;
        case OP_SUB:
            *current_register = arg1 - arg2;
            break;
        case OP_TAN:
            *current_register = std::tan(arg1);
            break;
        case OP_TRUNC:
            *current_register = std::trunc(arg1);
            break;
    }
}

template <typename T> void SimulatedIC<T>::handle_logic_op(ic_instruction current_instruction) {
    double *current_register = this->get_register(current_instruction.args[0]);
    const double arg1 = this->resolve_argument(current_instruction.args[7]);
    const double arg2 = this->resolve_argument(current_instruction.args[6]);
    switch (current_instruction.operation.op_logic) {
        case OP_AND:
            *current_register = (double) (arg1 != 0 & arg2 != 0);
            break;
        case OP_NOR:
            *current_register = (double) !(arg1 != 0 | arg2 != 0);
            break;
        case OP_OR:
            *current_register = (double) (arg1 != 0 | arg2 != 0);
            break;
        case OP_XOR:
            *current_register = (double) (arg1 != 0 ^ arg2 != 0);
            break;
    }
}

template <typename T> void SimulatedIC<T>::handle_stack_op(ic_instruction current_instruction) {
    double *current_register = this->get_register(current_instruction.args[0]);
    switch (current_instruction.operation.op_stack) {
        case OP_PEEK:
            *current_register = this->ic_interface->get_stack_value();
            break;
        case OP_POP:
            *current_register = this->ic_interface->get_stack_value();
            (*this->get_register_directly(16))--;
            break;
        case OP_PUSH:
            this->ic_interface->set_stack_value(*current_register);
            (*this->get_register_directly(16))++;
            break;
        case OP_POKE:
            this->ic_interface->set_stack_value(*current_register);
            break;
    }
}

template <typename T> void SimulatedIC<T>::handle_io_op(ic_instruction current_instruction) {
    double *current_register = this->get_register(current_instruction.args[0]);
    unsigned device = this->resolve_argument(current_instruction.args[1]);
    unsigned property_hash = this->resolve_argument(current_instruction.args[2]);
    unsigned name_hash = this->resolve_argument(current_instruction.args[3]);
    int slot = this->resolve_argument(current_instruction.args[4]);
    auto batch_mode = (ic_batch_mode) this->resolve_argument(current_instruction.args[5]);
    auto reagent_mode = (ic_reagent_mode) this->resolve_argument(current_instruction.args[6]);
    double value = this->resolve_argument(current_instruction.args[7]);
    switch (current_instruction.operation.op_io) {
        case OP_LOADD:
            *current_register = this->ic_interface->loadd(property_hash, device);
            break;
        case OP_LOADB:
            *current_register = this->ic_interface->loadb(property_hash, device, batch_mode);
            break;
        case OP_LOADBN:
            *current_register = this->ic_interface->loadbn(property_hash, device, batch_mode, name_hash);
            break;
        case OP_LOADRD:
            *current_register = this->ic_interface->loadrd(property_hash, device, reagent_mode);
            break;
        case OP_LOADRB:
            *current_register = this->ic_interface->loadrb(property_hash, device, reagent_mode, batch_mode);
            break;
        case OP_LOADRBN:
            *current_register = this->ic_interface->loadrbn(property_hash, device, reagent_mode, batch_mode, name_hash);
            break;
        case OP_LOADSD:
            *current_register = this->ic_interface->loadsd(property_hash, device, slot);
            break;
        case OP_LOADSB:
            *current_register = this->ic_interface->loadsb(property_hash, device, slot, batch_mode);
            break;
        case OP_LOADSBN:
            *current_register = this->ic_interface->loadsbn(property_hash, device, slot, batch_mode, name_hash);
            break;
        case OP_STORED:
            this->ic_interface->stored(value, property_hash, device);
            break;
        case OP_STOREB:
            this->ic_interface->storeb(value, property_hash, device);
            break;
        case OP_STOREBN:
            this->ic_interface->storebn(value, property_hash, device, name_hash);
            break;
    }
}

template <typename T> void SimulatedIC<T>::handle_misc_op(ic_instruction current_instruction) {
    const int alias = current_instruction.args[0].value.alias;
    switch (current_instruction.operation.op_misc) {
        case OP_ALIAS:
            if (current_instruction.instruction_flags & FLAG_DEVICE_ALIAS)
                this->device_aliases[alias] = (int) this->resolve_argument(current_instruction.args[1]);
            else
                this->register_aliases[alias] = this->get_register(current_instruction.args[1]);
            break;
        case OP_DEFINE:
            this->definitions[alias] = current_instruction.args[1].value.float_value;
            break;
        case OP_HCF:
            this->yielding = -1;
            break;
        case OP_SLEEP:
            this->yielding = (int) current_instruction.args[0].value.int_value/2;
            break;
        case OP_YIELD:
            this->yielding++;
            break;
        case OP_JUMP_TAG:
            this->jump_tags[alias] = this->instruction_counter;
            break;
        case OP_MOVE:
            *(this->get_register(current_instruction.args[0])) = this->resolve_argument(current_instruction.args[1]);
    }
}

template <typename T> SimulatedIC<T>::SimulatedIC(T *device_interface, ic_instruction *instruction_buffer, size_t total_instructions) { // NOLINT(*-msc51-cpp)
    this->ic_interface = device_interface;
    this->instruction_buffer = instruction_buffer;
    this->total_instructions = total_instructions;

    this->generator = std::default_random_engine(std::time(nullptr)); // NOLINT(*-msc51-cpp)
    this->distribution = std::uniform_real_distribution<double>(0.0,1.0);
}

template <typename T> double *SimulatedIC<T>::resolve_register_reference(ic_reference reference) {
    double *current_register = this->ic_interface->get_register(reference.value);
    for (int i = reference.depth-1; i > 0; i--)
        current_register = this->ic_interface->get_register((int) *current_register);
    return current_register;
}

template <typename T> double *SimulatedIC<T>::get_register(ic_arg arg) {
    if (arg.arg_type == ARG_REGISTER_ALIAS)
        return this->register_aliases[arg.value.alias];
    return this->resolve_register_reference(arg.value.reference);
}

template <typename T> double *SimulatedIC<T>::get_register_directly(int i) {
    return this->get_register({ARG_REGISTER, {1, i}});
}

template <typename T> double SimulatedIC<T>::resolve_argument(ic_arg arg) {
    switch (arg.arg_type) {
        case ARG_REGISTER:
            return *(this->get_register(arg));
        case ARG_FLOAT:
            return arg.value.float_value;
        case ARG_INT:
            return (double) arg.value.int_value;
        case ARG_DEFINITION:
            return this->definitions[arg.value.alias];
        case ARG_REGISTER_ALIAS:
            return *(this->register_aliases[arg.value.alias]);
        default:
            return 0;
    }
}

template <typename T> int SimulatedIC<T>::resolve_line_number(ic_arg line) {
    return line.arg_type == ARG_JUMP_TAG ? this->jump_tags[line.value.jump_tag] : (int) this->resolve_argument(line);
}

template <typename T> bool SimulatedIC<T>::compute_compare(ic_instruction instruction) {
    double arg1, arg2, arg3;
    arg1 = this->resolve_argument(instruction.args[7]);
    arg2 = this->resolve_argument(instruction.args[6]);
    arg3 = this->resolve_argument(instruction.args[5]);
    int device = (int) this->resolve_argument(instruction.args[7]);
    switch (instruction.comparison) {
        case COMPARE_NULL:
            return true;
        case COMPARE_EQ:
            return arg1 == arg2;
        case COMPARE_EQZ:
            return arg1 == 0;
        case COMPARE_GE:
            return arg1 >= arg2;
        case COMPARE_GEZ:
            return arg1 >= 0;
        case COMPARE_GT:
            return arg1 > arg2;
        case COMPARE_GTZ:
            return arg1 > 0;
        case COMPARE_LE:
            return arg1 <= arg2;
        case COMPARE_LEZ:
            return arg1 <= 0;
        case COMPARE_LT:
            return arg1 < arg2;
        case COMPARE_LTZ:
            return arg1 < 0;
        case COMPARE_NE:
            return arg1 != arg2;
        case COMPARE_NEZ:
            return arg1 != 0;
        case COMPARE_DNS:
            return !this->ic_interface->get_device_set(device);
        case COMPARE_DSE:
            return this->ic_interface->get_device_set(device);
        case COMPARE_AP:
            return std::abs(arg1 - arg2) <= std::max(arg3 * std::max(std::abs(arg1), std::abs(arg2)), epsilon * 8);
        case COMPARE_APZ:
            return std::abs(arg1) <= epsilon * 8;
        case COMPARE_NA:
            return std::abs(arg1 - arg2) > std::max(arg3 * std::max(std::abs(arg1), std::abs(arg2)), epsilon * 8);
        case COMPARE_NAZ:
            return std::abs(arg1) > epsilon * 8;
        default:
            return true;
    }
}

template <typename T> bool SimulatedIC<T>::step() {
    if (this->instruction_counter > this->total_instructions)
        return true;
    if (this->yielding) {
        if (this->yielding > 0)
            this->yielding--;
        return true;
    }
    ic_instruction current_instruction = *(this->instruction_buffer + this->instruction_counter);
    switch (current_instruction.instruction_type) {
        case BRANCH:
            this->handle_branch(current_instruction);
            break;
        case SELECT:
            this->handle_select(current_instruction);
            break;
        case OP_MATH:
            this->handle_math_op(current_instruction);
            break;
        case OP_LOGIC:
            this->handle_logic_op(current_instruction);
            break;
        case OP_STACK:
            this->handle_stack_op(current_instruction);
            break;
        case OP_IO:
            this->handle_io_op(current_instruction);
            break;
        case OP_MISC:
            this->handle_misc_op(current_instruction);
            break;
    }
    this->instruction_counter++;
    return false;
}

template <typename T> int SimulatedIC<T>::run_single_tick(unsigned max_instructions) {
    int instructions_run = 0;
    for (; !(step() || (instructions_run >= max_instructions)); instructions_run++);
    return instructions_run;
}

template <typename T> int SimulatedIC<T>::run(int ticks, unsigned max_instructions) {
    int instructions_run = 0;
    for (int i = 0; i < ticks; i++) {
        instructions_run += this->run_single_tick(max_instructions);
    }
    return instructions_run;
}


template class SimulatedIC<SimulatedICInterface>;