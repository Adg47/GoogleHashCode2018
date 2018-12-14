cmake_minimum_required(VERSION 3.12)
project(HashCode18)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-lstdc++fs")
add_executable(HashCode18 main.cpp Cell.cpp Cell.h Utility.cpp Utility.h Residence.cpp Residence.h Map.cpp Map.h Parser.cpp Parser.h ParserOut.h ParserOut.cpp Batiment.cpp Batiment.h)