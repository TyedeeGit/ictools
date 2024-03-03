

cmake_minimum_required(VERSION 3.27)
project(iclib C)
project(icsim CXX)
project(icsimlib CXX)


add_library(iclib iclib/iclib.c)

add_library(icsimlib
        icsim/SimulatedDevice.cpp
        icsim/SimulatedICInterface.cpp
        icsim/SimulatedIC.cpp
)
target_link_libraries(icsimlib iclib)
add_dependencies(icsimlib iclib)

add_executable(icsim icsim/main.cpp)
target_link_libraries(icsim icsimlib)
add_dependencies(icsim icsimlib)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

