# brkida | C++ macro for x64 programs that breaks ida hex-rays decompiler tool.

## Description
This repository provides a one-header project that can easily prevent IDA decompiler tool to decompile the functions of any program by throwing a decompilation failure.\
Users can easily protect their functions using the `BRKIDA` macro provided in the header.\
The repository includes an example demonstrating the usage of `BRKIDA`.\
Currently only supports MSVC and x64.

## Key Aspects
 - The stub is generated at compile-time by using a random ptr formed by 4 random bytes, each based on an hash that's based on the date, time and a counter which increases every time a function is protected.
 - Supports C++14 and higher versions.

## What it actually does
This project exploits the fact that IDA decompiler fails when it encounters a stack access on a pointer that's too big.\
ASM:
```asm
jmp useless ; jump 8 byte after to skip the next instruction (E8 08)
mov [rsp + BIGINT_HERE], rcx ; this will never be executed or we would crash too (48 89 8C 24 DE AD BE EF)
useless:
ret ; C3
```

## How it shows
![IDA Decompilation Failure](https://i.imgur.com/ctg9Zxv.png)\

## Repository Structure
- **`include/`**: Contains the `brkida.hpp` header file.
- **`src/`**: Holds the example `main.cpp` file showcasing the usage of `BRKIDA`.
- **`LICENSE`**: Licensing information for the provided code.
- **`README.md`**: Documentation explaining how to use everything.

## Usage Example
The repository includes an example demonstrating the usage of the `BRKIDA` macro:

### `main.cpp`
```cpp
#include <stdio.h>
#include "brkida.hpp"

int main() {
    BRKIDA; // define this inside every function you want to break

    printf("Hello!\n");

    return 0;
}
```
