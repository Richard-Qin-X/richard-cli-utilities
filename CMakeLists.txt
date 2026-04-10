# Project : Richard CLI Utilities
# License : GPL v3.0 or later

cmake_minimum_required(VERSION 3.20.3)
cmake_policy(SET CMP0048 NEW)

project(richard-cli-utilities
    VERSION 0.1.0
    DESCRIPTION "A collection of modular command-line utilities"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

# clang-tidy
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" ON)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}. Static analysis ENABLED.")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy requested but not found on the system!")
    endif()
else()
    message(STATUS "clang-tidy static analysis is DISABLED.")
endif()

# clang-format
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
    message(STATUS "Found clang-format: ${CLANG_FORMAT_EXE}")
    
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        "src/*.[ch]pp" "src/*.h" "src/*.cc" "src/*.cpp"
        "include/*.[ch]pp" "include/*.h"
        "tests/*.[ch]pp" "tests/*.cpp"
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_CXX_SOURCE_FILES}
        COMMENT "Formatting all source files..."
    )

    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT_EXE} --dry-run -Werror -style=file ${ALL_CXX_SOURCE_FILES}
        COMMENT "Checking code format..."
    )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach()

add_library(rcli_common_includes INTERFACE)
target_include_directories(rcli_common_includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src/core)
add_subdirectory(src/tools/clock)

add_executable(rcli src/main.cc)

target_link_libraries(
    rcli
    PRIVATE
    core_lib
    rcli_common_includes
)