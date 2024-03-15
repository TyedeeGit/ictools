cmake_minimum_required(VERSION 3.27)
project(iclib C)
project(icsim CXX)
project(icasm CXX)

find_package(Python)

add_library(iclib iclib/iclib.c)

set(COMMANDS_JSON ${PROJECT_SOURCE_DIR}/icsim/commands.json)
set(PARSER_GENERATOR ${PROJECT_SOURCE_DIR}/icsim/generate_parser.py)
set(GENERATED_PARSER ${PROJECT_SOURCE_DIR}/icsim/parser.cpp ${PROJECT_SOURCE_DIR}/icsim/parser.h)

add_custom_command(
        OUTPUT ${GENERATED_PARSER}
        COMMENT "Generating parser files"
        PRE_BUILD
        DEPENDS ${COMMANDS_JSON} ${PARSER_GENERATOR}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/icsim
        COMMAND py ${PARSER_GENERATOR} ${COMMANDS_JSON}
)

add_custom_target(icsim_parser ALL
    DEPENDS ${GENERATED_PARSER}
)

add_library(icsimlib
        icsim/SimulatedDevice.cpp
        icsim/SimulatedICInterface.cpp
        icsim/SimulatedIC.cpp
        icsim/icsimlib.cpp
        icsim/parser.cpp
)
target_link_libraries(icsimlib iclib)
add_dependencies(icsimlib iclib)
add_dependencies(icsimlib icsim_parser)

add_executable(icsim icsim/main.cpp)
target_link_libraries(icsim icsimlib)
add_dependencies(icsim icsimlib)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

