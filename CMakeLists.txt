cmake_minimum_required(VERSION 3.21)
project(advent_of_code_2019
    LANGUAGES CXX
    VERSION 0.0.1
)

# ------------------------------------------------------------------------------
# Create target for specifying the C++ standard and compiler specific options
# ------------------------------------------------------------------------------
add_library(project_options INTERFACE)
target_compile_features(project_options
    INTERFACE
        cxx_std_20
)

# Enable multi-processor compilation on MSVC
if(MSVC)
    target_compile_options(project_options
        INTERFACE
            /MP
    )
endif()

# ------------------------------------------------------------------------------
# Create target for compiler warnings
# ------------------------------------------------------------------------------
include(cmake/compiler_warnings.cmake)

add_library(project_warnings INTERFACE)

option(warnings_as_errors "Treat compiler warnings as errors" ON)
set_project_warnings(project_warnings ${warnings_as_errors})

# ------------------------------------------------------------------------------
# Manage dependencies
# ------------------------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
    GIT_TAG        "8.1.1"
)

message(STATUS "Populating dependencies...")
FetchContent_MakeAvailable(fmt)

# ------------------------------------------------------------------------------
# Create executable
# ------------------------------------------------------------------------------

add_executable(aoc_2019_app "src/main.cpp"  "src/utility/day.h" "src/utility/io.h" "src/utility/io.cpp" "src/utility/string.h" "src/utility/string.cpp"  "src/utility/math.h" "src/utility/point.h"  "src/utility/point.cpp" "src/utility/math.cpp" "src/day_1/day_1.h" "src/day_1/day_1.cpp" "src/day_2/day_2.h" "src/day_2/day_2.cpp" "src/intcode/basic_vm.h" "src/intcode/basic_vm.cpp" "src/intcode/opcode.h" "src/intcode/opcode.cpp" "src/intcode/program_io.h" "src/intcode/program_io.cpp" "src/day_3/day_3.h" "src/day_3/day_3.cpp"   "src/day_4/day_4.h" "src/day_4/day_4.cpp" "src/day_5/day_5.h" "src/day_5/day_5.cpp" "src/intcode/vm.h" "src/intcode/vm.cpp" "src/day_6/day_6.h" "src/day_6/day_6.cpp" "src/day_7/day_7.h" "src/day_7/day_7.cpp"  "src/day_8/day_8.h" "src/day_8/day_8.cpp")

target_include_directories(aoc_2019_app
    PRIVATE
        "src/"
)

target_link_libraries(aoc_2019_app
    PRIVATE
        project_options
        project_warnings
        fmt::fmt
)

# ------------------------------------------------------------------------------
# Install options
# ------------------------------------------------------------------------------
install(
    TARGETS
        aoc_2019_app
)
