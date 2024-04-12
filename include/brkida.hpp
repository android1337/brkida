/*
 * MIT License https://github.com/Android1337/brkida/blob/main/LICENSE
 *
 * Copyright (c) 2024 Android1337
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BRKIDA_HPP
#define BRKIDA_HPP

#if _MSC_VER && _WIN64 == 1 // only implemented for MSVC and x64 for now
#include <intrin.h> // __AddressOfReturnAddress

// very simple compile-time hash algorithm for binary randomness
unsigned constexpr long long const_hash(const char* input) {
    return *input ? static_cast<unsigned long long>(*input) + 33 * const_hash(input + 1) : 5381;
}

/*
* stub proc
* jmp useless ; E8 08
* mov [rsp + BIGINT_HERE], rcx; this will never be executed (48 89 8C 24 DE AD BE EF)
* useless:
* ret ; C3
* stub endp
*/

#define BRKIDA \
{ \
    constexpr unsigned __int8 stub[] = { \
        0xEB, 0x08, /* jmp 0x8 */ \
        0x48, 0x89, 0x8C, 0x24, /* mov [rsp + ????????], rcx */ \
        unsigned __int8((const_hash(__DATE__ __TIME__) + __COUNTER__ * __COUNTER__) % 0xFF /* mod of max uint8_t */), \
        unsigned __int8((const_hash(__DATE__ __TIME__) + __COUNTER__ * __COUNTER__) % 0xFF /* mod of max uint8_t */), \
        unsigned __int8((const_hash(__DATE__ __TIME__) + __COUNTER__ * __COUNTER__) % 0xFF /* mod of max uint8_t */), \
        unsigned __int8((const_hash(__DATE__ __TIME__) + __COUNTER__ * __COUNTER__) % 0xFF /* mod of max uint8_t */), \
        0xC3 /* ret */ \
    }; \
    \
	/* we don't want to execute the stub because we don't even change the protection to executable so it would crash */ \
    if (!_AddressOfReturnAddress()) { \
        ((void(*)())uintptr_t(stub))(); \
        ((void(*)())uintptr_t(0x0))(); /* a call to 0x0 sometimes breaks ida decompiler too */ \
	} \
}
#else
#define BRKIDA
#error("BRKIDA is currently only supported on MSVC x64")
#endif

#endif // include guard
