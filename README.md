# ECS 034 Project 1:
**Author:** Carley Smith  
**Date:** January 2026

## Description

This project contains a group of C++ functions created to emulate the following built-in Python string operations:
`slice()`, `capitalize()`, `upper()`, `lower()`, `lstrip()`, `rstrip()`, `strip()`, `center()`, `ljust()`, `rjust()`, `replace()`, `split()`, `join()`, `expandtabs()`

It also includes a function to calculate Levenshtein distance, implemented with dynamic programming. 

All function definitions are located in the `StringUtils.cpp` file, and `StringUtilsTest.cpp` contains Google Tests to confirm that the functions operate correctly and cover all edge cases. 

## Sources

Referenced https://cplusplus.com/reference/string/string/ to see all modifiers and operations for the std::string class, used to implement the functions.  
Referenced https://en.wikipedia.org/wiki/Levenshtein_distance for iterative matrix pseudocode for Levenshtein Distance.

## Project Structure

- `StringUtils.h` = function declarations only
- `StringUtils.cpp` = function implementations
- `StringUtilsTest.cpp` = Google Tests
- `Makefile` = automated build and test

## Build and Test Instructions:

In bash:

- `make` - build functions and tests
- `make runtests` - builds and runs tests
- `make clean` - removes build directories
