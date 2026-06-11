cmake_minimum_required(VERSION 3.10)
project(c-samples C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler options
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror=implicit-function-declaration
    -Werror=format
)

# Coverage support
option(ENABLE_COVERAGE "Enable code coverage reporting" ON)

if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Source files
set(SOURCES
    src/string_builder.c
)

# Create library
add_library(csamples ${SOURCES})
target_include_directories(csamples PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Build tests
enable_testing()

# String builder tests
add_executable(test_string_builder tests/test_string_builder.c)
target_include_directories(test_string_builder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_string_builder csamples)
add_test(NAME string_builder COMMAND test_string_builder)

# Coverage reporting
if(ENABLE_COVERAGE)
    find_program(GCOV gcov)
    find_program(LCOV lcov)

    if(LCOV)
        add_custom_target(coverage
            COMMAND ${LCOV} --directory . --capture --output-file test_coverage.info --ignore-errors unused
            COMMAND ${LCOV} --remove test_coverage.info '/usr/*' --output-file test_coverage.info --ignore-errors unused || true
            COMMAND ${LCOV} --list test_coverage.info
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS test_string_builder
            COMMENT "Generating code coverage report"
        )
    else()
        message(WARNING "lcov not found - coverage report generation will be skipped")
    endif()
endif()
