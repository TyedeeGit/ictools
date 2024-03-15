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
#ifndef ICLIB_H
#define ICLIB_H

#ifdef __cplusplus
extern "C" {
#endif

const int FLAG_AL = 1;
const int FLAG_RELATIVE = 2;
const int FLAG_DEVICE_ALIAS = 4;

typedef enum {
    BATCH_AVERAGE,
    BATCH_SUM,
    BATCH_MIN,
    BATCH_MAX
} ic_batch_mode;

typedef enum {
    REAGENT_CONTENTS,
    REAGENT_REQUIRED,
    REAGENT_RECIPE
} ic_reagent_mode;

typedef enum {
    BRANCH,
    SELECT,
    OP_MATH,
    OP_LOGIC,
    OP_STACK,
    OP_IO,
    OP_MISC
} ic_instruction_type;

typedef enum {
    COMPARE_NULL,
    COMPARE_EQ,
    COMPARE_EQZ,
    COMPARE_GE,
    COMPARE_GEZ,
    COMPARE_GT,
    COMPARE_GTZ,
    COMPARE_LE,
    COMPARE_LEZ,
    COMPARE_LT,
    COMPARE_LTZ,
    COMPARE_NE,
    COMPARE_NEZ,
    COMPARE_DNS,
    COMPARE_DSE,
    COMPARE_AP,
    COMPARE_APZ,
    COMPARE_NA,
    COMPARE_NAZ,
} ic_compare;

typedef enum {
    ARG_REGISTER,
    ARG_DEVICE,
    ARG_JUMP_TAG,
    ARG_FLOAT,
    ARG_INT,
    ARG_REGISTER_ALIAS,
    ARG_DEFINITION
} ic_arg_type;

typedef enum {
    OP_ABS,
    OP_ACOS,
    OP_ADD,
    OP_ASIN,
    OP_ATAN,
    OP_CEIL,
    OP_COS,
    OP_DIV,
    OP_EXP,
    OP_FLOOR,
    OP_LOG,
    OP_MAX,
    OP_MIN,
    OP_MOD,
    OP_MUL,
    OP_RAND,
    OP_ROUND,
    OP_SIN,
    OP_SQRT,
    OP_SUB,
    OP_TAN,
    OP_TRUNC,
} ic_op_math;

typedef enum {
    OP_AND,
    OP_NOR,
    OP_OR,
    OP_XOR
} ic_op_logic;

typedef enum {
    OP_POKE,
    OP_PEEK,
    OP_POP,
    OP_PUSH
} ic_op_stack;

typedef enum {
    OP_LOADD,
    OP_LOADB,
    OP_LOADBN,
    OP_LOADSD,
    OP_LOADSB,
    OP_LOADSBN,
    OP_LOADRD,
    OP_LOADRB,
    OP_LOADRBN,
    OP_STORED,
    OP_STOREB,
    OP_STOREBN
} ic_op_io;

typedef enum {
    OP_ALIAS,
    OP_DEFINE,
    OP_HCF,
    OP_SLEEP,
    OP_YIELD,
    OP_JUMP_TAG,
    OP_MOVE
} ic_op_misc;

typedef union {
    ic_op_math op_math;
    ic_op_logic op_logic;
    ic_op_stack op_stack;
    ic_op_io op_io;
    ic_op_misc op_misc;
} ic_operation;

typedef struct {
    int depth;
    int value;
} ic_reference;

typedef union {
    ic_reference reference;
    int jump_tag;
    int io_var;
    double float_value;
    int int_value;
    int alias;
} ic_arg_value;

typedef struct {
    ic_arg_type arg_type;
    ic_arg_value value;
} ic_arg;

typedef struct {
    ic_instruction_type instruction_type;
    ic_operation operation;
    ic_compare comparison;
    int instruction_flags;
    ic_arg args[8];
} ic_instruction;

unsigned int hash(const char *message);
const char *unhash_property(unsigned int hashed);

#ifdef __cplusplus
}

template<typename T> inline T *increment_pointer(void **pointer) {
    auto old_value = (T*) *pointer;
    *pointer = old_value + 1;
    return old_value;
}
#endif //__cplusplus

#endif //ICLIB_H