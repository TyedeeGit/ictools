cmake_minimum_required(VERSION 3.27)
project(iclib C)
project(icsim CXX)
project(icasm CXX)

find_package(Python)
find_package(FLEX)
find_package(BISON)

set(ICLIB_DIR ${PROJECT_SOURCE_DIR}/iclib)
set(ICSIM_DIR ${PROJECT_SOURCE_DIR}/icsim)
set(ICSIM_PARSER_DIR ${ICSIM_DIR}/cmd_parser)
set(ICASM_DIR ${PROJECT_SOURCE_DIR}/icasm)
set(ICASM_PARSER_DIR ${ICASM_DIR}/parser)

# Build iclib
add_library(iclib ${ICLIB_DIR}/iclib.c)

# Build icasm_parser
set(LEXER ${ICASM_PARSER_DIR}/lexer.l)
set(SYNTAX ${ICASM_PARSER_DIR}/syntax.y)
set(LEXER_OUTPUT ${ICASM_PARSER_DIR}/lex.yy.c)
set(SYNTAX_OUTPUT_C ${ICASM_PARSER_DIR}/syntax.tab.c)
set(SYNTAX_OUTPUT_H ${ICASM_PARSER_DIR}/syntax.tab.h)
set(SYNTAX_OUTPUT ${SYNTAX_OUTPUT_C} ${SYNTAX_OUTPUT_H})

add_custom_command(
        OUTPUT ${SYNTAX_OUTPUT_H}
        COMMENT "Generating icasm parser syntax files"
        DEPENDS ${SYNTAX}
        WORKING_DIRECTORY ${ICASM_PARSER_DIR}
        COMMAND bison ${SYNTAX}
        ARGS -d
)

add_custom_command(
        OUTPUT ${LEXER_OUTPUT}
        COMMENT "Generating icasm parser lexer files"
        DEPENDS ${LEXER} ${SYNTAX_OUTPUT}
        WORKING_DIRECTORY ${ICASM_PARSER_DIR}
        COMMAND flex ${LEXER}
)

add_library(icasm_parser
        ${LEXER_OUTPUT}
        ${SYNTAX_OUTPUT_C}
)

# Build icasmlib
add_library(icasmlib
        ${ICASM_DIR}/icasmlib.cpp
        ${ICASM_DIR}/icasmlib.h)
target_link_libraries(icasmlib iclib)

# Build icsim_parser
set(COMMANDS_JSON ${ICSIM_PARSER_DIR}/commands.json)
set(PARSER_GENERATOR ${ICSIM_PARSER_DIR}/generate_parser.py)
set(PARSER_GENERATOR_OUTPUT ${ICSIM_PARSER_DIR}/cmd_parser.cpp icsim/cmd_parser/cmd_parser.h)

add_custom_command(
        OUTPUT ${PARSER_GENERATOR_OUTPUT}
        COMMENT "Generating icsim command parser files"
        DEPENDS ${COMMANDS_JSON} ${PARSER_GENERATOR}
        WORKING_DIRECTORY ${ICSIM_PARSER_DIR}
        COMMAND py ${PARSER_GENERATOR} ${COMMANDS_JSON}
)

add_library(icsim_parser
        ${PARSER_GENERATOR_OUTPUT}
)

# Build icsimlib
add_library(icsimlib
        ${ICSIM_DIR}/SimulatedDevice.cpp
        ${ICSIM_DIR}/SimulatedICInterface.cpp
        ${ICSIM_DIR}/SimulatedIC.cpp
        ${ICSIM_DIR}/icsimlib.cpp
)
target_link_libraries(icsimlib iclib)
target_link_libraries(icsimlib icasmlib)
target_link_libraries(icsimlib icsim_parser)

# Build icsim
add_executable(icsim ${ICSIM_DIR}/main.cpp)
target_link_libraries(icsim icsimlib)

# Build icasm
add_executable(icasm ${ICASM_DIR}/main.cpp)
target_link_libraries(icasm icasmlib)
target_link_libraries(icasm icsimlib)
target_link_libraries(icasm icasm_parser)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

