# C Samples

A modern C programming language template project showcasing contemporary design patterns, best practices, and professional development workflows.

## Overview

This project demonstrates modern C development practices including:

- **Opaque Data Structures**: Encapsulation of internal implementation details
- **Error Handling**: Proper status code-based error handling patterns
- **Memory Safety**: Careful memory management with proper allocation and deallocation
- **Modularity**: Clear separation of concerns with well-defined interfaces
- **API Documentation**: Comprehensive documentation in header files
- **Testing**: Comprehensive unit test coverage with custom testing framework
- **CI/CD**: Automated linting, building, testing, and coverage reporting
- **Code Coverage**: Automated code coverage measurement and reporting

## Project Structure

```
.
├── include/              # Header files (public API)
│   ├── string_builder.h # String builder module
│   └── test_framework.h # Simple testing framework
├── src/                  # Source implementation files
│   └── string_builder.c # String builder implementation
├── tests/                # Test files
│   └── test_string_builder.c # String builder unit tests
├── CMakeLists.txt        # CMake build configuration
├── .clang-format         # Code style configuration
└── .github/workflows/    # GitHub Actions CI/CD workflows
    └── ci.yml            # Continuous Integration workflow
```

## Building the Project

### Prerequisites

- CMake 3.10 or later
- GCC or Clang compiler
- Make or Ninja build system
- For coverage reports: `lcov` and `gcov`

### Build Steps

```bash
# Create build directory
mkdir build
cd build

# Configure the project
cmake ..

# Build
cmake --build .

# Run tests
ctest --output-on-failure
```

### Build with Coverage

```bash
mkdir build
cd build

# Configure with coverage enabled (enabled by default)
cmake -DENABLE_COVERAGE=ON ..

# Build
cmake --build .

# Run tests
ctest --output-on-failure

# Generate coverage report
make coverage
```

## Testing

The project includes comprehensive unit tests using a simple, self-contained testing framework.

### Run Tests

```bash
cd build
ctest --output-on-failure
```

### View Test Results

The test output will show:
- Individual test results (PASS/FAIL)
- Failure details if any tests fail
- Test summary with total count and pass/fail statistics

## Code Coverage

The project uses `gcov` and `lcov` to measure and report code coverage.

### Generate Coverage Report

```bash
cd build
make coverage
```

This will generate a `test_coverage.info` file with detailed coverage information, which can be used to create HTML reports or integrated with CI/CD systems.

### Viewing Coverage Summary

After running `make coverage`, you'll see a summary like:

```
Reading data file test_coverage.info
GCC Code Coverage Report
...
Overall coverage rate:
  lines: X% (Y of Z lines)
  functions: X% (Y of Z functions)
  branches: X% (Y of Z branches)
```

## Modern C Patterns Demonstrated

### String Builder Module

The `string_builder` module demonstrates several modern C patterns:

1. **Opaque Pointers**: The `StringBuilderHandle` type is an opaque pointer, hiding internal implementation
2. **Error Codes**: Operations return `StringBuilderStatus` codes instead of using exceptions
3. **Memory Management**: Proper dynamic memory allocation and reallocation
4. **API Documentation**: Comprehensive documentation using inline comments
5. **Defensive Programming**: NULL pointer checks and safe operations on invalid handles

### Error Handling Pattern

```c
StringBuilderStatus status = string_builder_append(builder, "text");
if (status != SB_OK) {
    // Handle error appropriately
    if (status == SB_ERR_ALLOC) {
        // Handle allocation failure
    }
}
```

### Safe Resource Management

```c
StringBuilderHandle* builder = string_builder_create(64);
if (builder != NULL) {
    string_builder_append(builder, "Hello");
    // ... use builder ...
    string_builder_destroy(builder); // Always clean up
}
```

## CI/CD Pipeline

The project includes a GitHub Actions workflow that:

1. **Linting**: Checks code formatting using `clang-format`
2. **Build**: Compiles the project with `-Wall -Wextra -Werror` flags
3. **Testing**: Runs all unit tests and reports results
4. **Coverage**: Generates and reports code coverage metrics
5. **Static Analysis**: Performs static analysis using `clang-tidy`

The workflow runs on:
- Push to `main` or `develop` branches
- Pull requests to `main` or `develop` branches

## Compiler Warnings as Errors

The project treats all compiler warnings as errors, ensuring code quality:

```bash
-Wall -Wextra -Wpedantic -Werror=implicit-function-declaration -Werror=format
```

## Code Style

Code formatting follows the LLVM style guide, configured in `.clang-format`. To format your code:

```bash
clang-format -i *.c *.h
```

## Future Enhancements

This template can be extended with:

- Additional sample modules demonstrating other patterns
- Documentation generation using Doxygen
- Benchmarking framework
- Memory leak detection using Valgrind
- More complex data structures (linked lists, trees, etc.)

## License

This project is provided as a template for learning and reference purposes.
