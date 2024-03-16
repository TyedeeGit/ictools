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

# Build icasmlib
add_library(icasmlib
        ${ICASM_DIR}/icasmlib.cpp
        ${ICASM_DIR}/icasmlib.h)
target_link_libraries(icasmlib iclib)
add_dependencies(icasmlib iclib)

# Build icsim_parser
set(COMMANDS_JSON ${ICSIM_PARSER_DIR}/commands.json)
set(PARSER_GENERATOR ${ICSIM_PARSER_DIR}/generate_parser.py)
set(PARSER_GENERATOR_OUTPUT ${ICSIM_PARSER_DIR}/parser.cpp icsim/cmd_parser/parser.h)

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
add_dependencies(icsimlib iclib)
add_dependencies(icsimlib icasmlib)
add_dependencies(icsimlib icsim_parser)

# Build icsim
add_executable(icsim ${ICSIM_DIR}/main.cpp)
target_link_libraries(icsim icsimlib)
add_dependencies(icsim icsimlib)

# Build icasm
add_executable(icasm ${ICASM_DIR}/main.cpp)
target_link_libraries(icasm icasmlib)
target_link_libraries(icasm icsimlib)
add_dependencies(icasm icasmlib)
add_dependencies(icasm icsimlib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

