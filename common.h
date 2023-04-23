//#include <assert.h>       // [C89] assert macro (only ifndef NDEBUG, i.e. DEBUG builds)
//#include <stddef.h>       // [C89] size_t, ptrdiff_t, offsetof, etc.
//#include <stdint.h>       // [C99] fixed width integer types & more (e.g. int_fast32_t)
//#include <inttypes.h>     // [C99] stdint + portable format conversions
//#include <limits.h>       // [C89] integers limits
//#include <stdckdint.h>    // [C23] checked integer arithmetic macros
//#include <fenv.h>         // [C99] float environment (e.g. control rounding behavior)
//#include <float.h>        // [C89] float limits
//#include <complex.h>      // [C99] complex number arithmetic (__STDC_NO_COMPLEX__ is 1 if not supported)
//#include <stdbool.h>      // [C99] _Bool, true, false
//#include <stdbit.h>       // [C23] popcount, rotl, rotr, etc.
//#include <iso646.h>       // [C95] alternative ascii operator spellings (e.g. && -> and, || -> or, ^ -> xor, etc.)
//#include <ctype.h>        // [C89] isalpha, isalnum, isspace & friends
//#include <wctype.h>       // [C95] iswalpha, iswdigit, iswspace, iswprint, iswupper & friends
//#include <wchar.h>        // [C95] wide characters extended utilities (e.g. wprintf)
//#include <uchar.h>        // [C11] UTF16 and UTF32 utilities
//#include <string.h>       // [C89] memory primitives (memcpy, memset) & str ops (strchr, etc.)
//#include <math.h>         // [C89] math & trigonometric functions
//#include <tgmath.h>       // [C99] type-generic math (convenience macros wrapping math.h and complex.h)
//#include <time.h>         // [C89] time and date utilities
//#include <locale.h>       // [C89] local formats for date, currency & more
//#include <errno.h>        // [C89] errno (and macros) used by system functions to report errors
//#include <signal.h>       // [C89] system level handling of signals like ^C to interrupt
//#include <setjmp.h>       // [C89] non-local jumps meant for embedded error-handling
//#include <stdnoreturn.h>  // [C11] noreturn convenience macro, may allow better cc optimizations
//#include <stdarg.h>       // [C89] va_list & friends
//#include <stdalign.h>     // [C11] alignas and alignof macros
//#include <stdlib.h>       // [C89] malloc, atoi, rand, abs, bsearch, qsort, exit, system to run cmds in shell & more.
//#include <threads.h>      // [C11] threads & mutexes (e.g. thrd_create, thrd_join, mtx_lock, mtx_unlock) (__STDC_NO_THREADS__ is 1 if not supported)
//#include <stdatomic.h>    // [C11] atomic types & ops (e.g. atomic_int, store, load, etc.) (__STDC_NO_ATOMICS__ is 1 if not supported)
//#include <stdio.h>        // [C89] standard input/output (e.g. fopen, printf, etc.)

#ifndef SW_COMMON_INCL
#define SW_COMMON_INCL (1)

// USER OVERWRITABLE DEFINES
// - `SW_API`: precedes every function decl & impl (defaults to static).
// - `SW_DEBUG`: compile-time flag signaling debug-mode is on/off (used for debug-only assertions i.e. `sw_debug_assert`).
// - `SW_NO_BUILTIN`: compile-time flag disabling the use of gcc-style `__builtin_*` functions in the source.
// - `sw_always_assert`: by default crashes at run-time if the condition is false.
// - `sw_debug_assert`: by default, matches the behavior of `sw_always_assert` if `SW_DEBUG` or expands to nothing.
// - `sw_static_assert`: by default crashes at compile-time if the contion is false.

// `SW_API` prefix used to denote all functions in this module (defaults to `static`).
#ifndef SW_API
#define SW_API static
#endif

// `SW_DEBUG` compile-time flag to indicate a debug build.
#ifndef SW_DEBUG
#define SW_DEBUG (1)
#endif
// `SW_NO_BUILTIN` compile-time flag to indicate the use of `__builtin_*` call is not allowed (for maximum portability at the cost of some performance).
#ifndef SW_NO_BUILTIN
#define SW_NO_BUILTIN (0)
#endif

// utilities macros
#define SW_REPEAT2(x) (x),(x)
#define SW_REPEAT4(x) SW_REPEAT_2(x),SW_REPEAT_2(x)
#define SW_REPEAT8(x) SW_REPEAT_4(x),SW_REPEAT_4(x)
// `SW_CVA` counts the number of variadic arguments (used for variadic macros dispatching).
#define SW__CVA(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,N,...) N
#define SW_CVA(...) SW__CVA(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
// `SW_TOK` is the token-paste macro with one extra indirection to allow the preprocessor to evaluate its arguments.
#define SW__TOK(x,y) x##y
#define SW_TOK(x,y) SW__TOK(x,y)
// `SW_CAT` is a generalized token-paste macro for multiple arguments (up to 8) (recursive marco would be `#define SW_CATR(a,...) SW_TOK(a,SW_CATR(SW_CAT,SW_CVA(__VA_ARGS__))(__VA_ARGS__))`)
#define SW_CAT2(a,b) SW_TOK(a,b)
#define SW_CAT3(a,b,c) SW_TOK(a,SW_CAT2(b,c))
#define SW_CAT4(a,b,c,d) SW_TOK(a,SW_CAT3(b,c,d))
#define SW_CAT5(a,b,c,d,e) SW_TOK(a,SW_CAT4(b,c,d,e))
#define SW_CAT6(a,b,c,d,e,f) SW_TOK(a,SW_CAT5(b,c,d,e,f))
#define SW_CAT7(a,b,c,d,e,f,g) SW_TOK(a,SW_CAT6(b,c,d,e,f,g))
#define SW_CAT8(a,b,c,d,e,f,g,h) SW_TOK(a,SW_CAT7(b,c,d,e,f,g,h))
#define SW_CAT(...) SW_TOK(SW_CAT,SW_CVA(__VA_ARGS__))(__VA_ARGS__)
// `SW_STR` is the stringize macro with one extra indirection to allow the preprocessor to evaluate its arguments.
#define SW__STR(x) #x
#define SW_STR(x) SW__STR(x)

// `sw_static_assert` is an overridable compile-time assert macro.
#ifndef sw_static_assert
#define sw_static_assert(cond,...) typedef char SW_TOK(sw__StaticAssertLine_,__LINE__)[(cond)?1:-1]
#endif
// `sw_always_assert` is an overridable run-time assert macro (triggered even in non debug builds).
#ifndef sw_always_assert
#define sw_always_assert(cond,...) do{if(!(cond)){(*(volatile int*)0=0);}}while(0)
#endif
// `sw_debug_assert` is an overridable run-time assert macro, by default active only in debug-mode (`SW_DEBUG` flag) and behaving like `sw_always_assert`.
#ifndef sw_debug_assert
#if SW_DEBUG
#define sw_debug_assert(cond,...) sw_always_assert(cond,__VA_ARGS__)
#else
#define sw_debug_assert(cond,...) ((void)0)
#endif
#endif
// `sw_unreachable` in a macro, by default behaving like `__builtin_unreachable()` (or `sw_debug_assert(0)` if NO_BUILTIN).
#if SW_NO_BUILTIN
#define sw_unreachable(...) sw_debug_assert(0)
#else
#define sw_unreachable(...) __builtin_unreachable()
#endif

// primitive types
typedef void               sw_Void;
typedef float              sw_F32;
typedef double             sw_F64;
typedef unsigned char      sw_U8;
typedef unsigned short     sw_U16;
typedef unsigned int       sw_U32;
typedef unsigned long long sw_U64;
typedef unsigned long long sw_Nat;
typedef signed char        sw_I8;
typedef signed short       sw_I16;
typedef signed int         sw_I32;
typedef signed long long   sw_I64;
typedef signed long long   sw_Int;
typedef sw_I8              sw_Bool8;
typedef sw_I16             sw_Bool16;
typedef sw_I32             sw_Bool32;
typedef sw_I64             sw_Bool64;
typedef sw_Int             sw_Bool;
typedef char               sw_CharA;
typedef sw_U8              sw_Char8;
typedef sw_U16             sw_Char16;
typedef sw_U32             sw_Char32; 

sw_static_assert(sizeof(sw_U8)  == 1 && sizeof(sw_I8)  == 1 && sizeof(sw_CharA) == 1, "invalid 8-bits primitive types");
sw_static_assert(sizeof(sw_U16) == 2 && sizeof(sw_I16) == 2, "invalid 16-bits primitive types");
sw_static_assert(sizeof(sw_U32) == 4 && sizeof(sw_I32) == 4 && sizeof(sw_F32) == 4, "invalid 32-bits primitive types");
sw_static_assert(sizeof(sw_U64) == 8 && sizeof(sw_I64) == 8 && sizeof(sw_F64) == 8, "invalid 64-bits primitive types");
sw_static_assert(sizeof(sw_Nat) == sizeof(sw_Int) && sizeof(sw_Nat) >= sizeof(sw_Void*), "invalid sizes for sw_Nat and sw_Int types");

// type constants
#define SW_NULL ((void*)0)
#define SW_TRUE (1)
#define SW_FALSE (0)

#define SW_F32_MAX 3.40282347e+38
#define SW_F64_MAX 1.7976931348623157e+308
#define SW_U8_MAX  0xFF
#define SW_U16_MAX 0xFFFF
#define SW_U32_MAX 0xFFFFFFFF
#define SW_U64_MAX 0xFFFFFFFFFFFFFFFF
#define SW_I8_MAX  127
#define SW_I16_MAX 32767
#define SW_I32_MAX 2147483647
#define SW_I64_MAX 9223372036854775807

#define SW_U32_LO(w) ((1u<<(w))-1)
#define SW_U32_HI(w) (SW_U32_LO(w)<<(32-w))
#define SW_U64_LO(w) ((1llu<<(w))-1)
#define SW_U64_HI(w) (SW_U64_LO(w)<<(64-w))
// Optional hex constants SW_U{32|64}_{LO|HI}{N} for N in [1, bitwidth].
// ```python3
// from collections import defaultdict
// from itertools import product as X
// out = defaultdict(list)
// for W in range(1,64+1):
//     lo64 = lo32 = (1 << W) - 1
//     if W <= 32:
//         hi32 = (lo32 << (32 - W))
//         out["U32_LO"].append(f"#define SW_U32_LO{W}{' ' if (W<10) else ''} 0x{lo32:0{8}X}u  // 0b{lo32:0{32}b}")
//         out["U32_HI"].append(f"#define SW_U32_HI{W}{' ' if (W<10) else ''} 0x{hi32:0{8}X}u  // 0b{hi32:0{32}b}")
//     hi64 = (lo64 << (64 - W))
//     out["U64_LO"].append(f"#define SW_U64_LO{W}{' ' if (W<10) else ''} 0x{lo64:0{16}X}llu  // 0b{lo64:0{64}b}")
//     out["U64_HI"].append(f"#define SW_U64_HI{W}{' ' if (W<10) else ''} 0x{hi64:0{16}X}llu  // 0b{hi64:0{64}b}")
// print(*['\n'.join(out[f"U{W}_{PAT}"]) for W, PAT in X((32,64),("LO","HI"))], sep='\n\n')
// ```


// math ops
#define sw_abs(x) ((x)<0?(-(x)):(x))
#define sw_min(x,y) (((x)<(y))?(x):(y))
#define sw_max(x,y) (((x)>(y))?(x):(y))
#define sw_clamp(x,l,h) (((x)<(l))?(l):((x)>(h))?(h):(x))
#define sw_sign(x) (((x)>0)-((x)<0))
// TODO: some math.h (trig fn, pow, EPS, PI, INF, NAN, (isnan, isinf, etc.)) 


// ascii ops
#define sw_isbindigit(cA) (((sw_Nat)(cA)-'0')<2)
#define sw_isoctdigit(cA) (((sw_Nat)(cA)-'0')<8)
#define sw_isdecdigit(cA) (((sw_Nat)(cA)-'0')<10)
#define sw_ishexdigit(cA) ((((sw_Nat)(cA)-'0')<10)||(((sw_Nat)(cA)-'a')<6)||(((sw_Nat)(cA)-'A')<6))
#define sw_isdigit(cA) sw_isdecdigit(cA)
#define sw_isupper(cA) (((sw_Nat)(cA)-'A')<26)
#define sw_islower(cA) (((sw_Nat)(cA)-'a')<26)
#define sw_isalpha(cA) (sw_isupper(cA)||sw_islower(cA))
#define sw_isalnum(cA) (sw_isalpha(cA)||sw_isdigit(cA))
#define sw_isspace(cA) (((sw_Nat)(cA)==' ')||((sw_Nat)((cA)-'\t')<5))  // \t\n\v\f\r
#define sw_toupper(cA) (cA^(' '*sw_islower(cA)))
#define sw_tolower(cA) (cA^(' '*sw_isupper(cA)))
#define sw_swapcase(cA) (cA^(' '*sw_isalpha(cA)))


// unicode ops
// TODO: see https://stackoverflow.com/questions/27415935/does-unicode-have-a-defined-maximum-number-of-code-points


// bit ops
#define sw_bsizeof(T) sizeof(T)
#define sw_offsetof(T,m) (sw_Nat)(&(((T*)0)->m))
#define sw_bitsizeof(T) (sizeof(T)<<3)
// TODO: more stdbit.h?


// `sw_bitsum32` counts # of 1-bits (or, equivalently, the sum of the bits).
SW_API inline sw_U32 sw_bitsum32(sw_U32 x) {
#if SW_NO_BUILTIN
    // source: https://en.wikipedia.org/wiki/Hamming_weight
    x -= (x >> 1) & 0x55555555u;
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = (x + (x >> 4)) & 0x0F0F0F0Fu;
    x += x >> 8;
    x += x >> 16;
    return x & 0x3f;
#else
    return __builtin_popcount(x)
#endif
}
// `sw_bitsum64` counts # of 1-bits (or, equivalently, the sum of the bits).
SW_API inline sw_U64 sw_bitsum64(sw_U64 x) {
#if SW_NO_BUILTIN
    // source: https://en.wikipedia.org/wiki/Hamming_weight
    x -= (x >> 1) & 0x5555555555555555llu;
    x = (x & 0x3333333333333333llu) + ((x >> 2) & 0x3333333333333333llu);
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0Fllu;
    x += x >>  8;
    x += x >> 16;
    x += x >> 32;
    return x & 0x7f;
#else
    return __builtin_popcountll(x);
#endif
}
// `sw_parity32` returns true (false) if the number of 1-bits is odd (even).
SW_API inline sw_U32 sw_bitparity32(sw_U32 x) {
#if SW_NO_BUILTIN
    return sw_bitsum32(x) & 1;
#else
    return __builtin_parity(x);
#endif
}
// `sw_parity64` returns true (false) if the number of 1-bits is odd (even).
SW_API inline sw_U64 sw_bitparity64(sw_U64 x) {
#if SW_NO_BUILTIN
    return sw_bitsum64(x) & 1;
#else
    return __builtin_parityll(x);
#endif
}
// `sw_bitclz32` counts # of leading 0-bits, preceding the most significant bit.
SW_API inline sw_U32 sw_bitclz32(sw_U32 x) {
    sw_debug_assert(x != 0, "`bitclz32` is not defined in 0!");
#if SW_NO_BUILTIN
    // clz32(x) = 32 - bitsum32(x) iff leading zeros are followed by 1-bits only
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    // hp sat: all bits after lz are now 1-bits!
    return 32 - sw_bitsum32(x);  // well defined in 0: returns 32 (bitwidth).
#elif 0
    // bisection + nibble lookup (likely less performant).
    // source: https://embeddedgurus.com/state-space/2014/09/fast-deterministic-and-portable-counting-leading-zeros/
    // + replaced comparisons of the form (x >= (1u << P)) with (x & BITMASK((bitindex >= P) ? 1 : 0))
    // + replaced static table with 0b01010101101011u (U2[15]) and adjusted lookup.
    // note that the above constant can fit in a U32 iff we do not store the mapping for zero (otherwise we'd need 33 bits)
    #define SWL_CLZ32_U2x15_TABLE 0b01010101101011u;
    #define SWL_CLZ32_U2x15_TABLE_GET(index_in_range_1_16) (28u + ((SW_CLZ32_U2x15_TABLE >> (((index_in_range_1_16) - 1) * 2)) & 0b11))
    sw_U32 n;
    if (x & 0xFFFF0000u) {
        if (x & 0xFF000000u) {
            n = (x & 0xF0000000u) ? 28 : 24;
        } else {
            n = (x & 0xFFF00000u) ? 20 : 16;
        }
    } else {
        if (x & 0xFFFFFF00u) {
            n = (x & 0xFFFFF000u) ? 12 : 8;
        } else {
            n = (x & 0xFFFFFFF0u) ? 4 : 0;
        }
    }
    x >>= n;
    return SWL_CLZ32_U2x15_TABLE_GET(x) - n;
    #undef SWL_CLZ32_U2x15_TABLE
    #undef SWL_CLZ32_U2x15_TABLE_GET
#else
    return __builtin_clz(x);
#endif
}
// `sw_bitclz64` counts # of leading 0-bits, preceding the most significant bit.
SW_API inline sw_U64 sw_bitclz64(sw_U64 x) {
    sw_debug_assert(x != 0, "`bitclz64` is not defined in 0!");
#if SW_NO_BUILTIN
    // clz64(x) = 64 - bitsum64(x) iff leading zeros are followed by 1-bits only!
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    // hp sat: all bits after lz are now 1-bits!
    return 64 - sw_bitsum64(x);  // well defined in 0: returns 64 (bitwidth).
#elif 0
    // bisection + nibble lookup (likely less performant): current implementation not defined in zero (to minimize lookup memory) but can easily be adjusted.
    return (x & SW_U64_HI(32)) ? (sw_clz32((sw_U32)(x >> 32))) : (32 + sw_clz32((sw_U32)x));
#else
    return __builtin_clzll(x);
#endif
}
// `sw_bitctz32` counts # of trailing 0-bits, following the least significant bit.
SW_API inline sw_U32 sw_bitctz32(sw_U32 x) {
    sw_debug_assert(x != 0, "`bitctz32` is not defined in 0!");
#if SW_NO_BUILTIN
    // (x & -x) isolates the LSB
    // (x & -x) - 1 converts into a 32-bit mask where bits following LSB are 1-bits.
    return sw_bitsum32((x & -x) - 1);  // well defined in 0: returns 32 (bitwidth).
#else
    return __builtin_ctz(x);
#endif
}
// `sw_bitctz64` counts # of trailing 0-bits, following the least significant bit.
SW_API inline sw_U64 sw_bitctz64(sw_U64 x) {
    sw_debug_assert(x != 0, "`bitctz64` is not defined in 0!");
#if SW_NO_BUILTIN
    // (x & -x) isolates the LSB
    // (x & -x) - 1 converts into a 64-bit mask where bits following LSB are 1-bits.
    return sw_bitsum64((x & -x) - 1);  // well defined in 0: returns 64 (bitwidth).
#else
    return __builtin_ctzll(x);
#endif
}
// `sw_bitcompact32` returns true iff all the 1-bits in the value are contiguous.
SW_API inline sw_Bool sw_bitcompact32(sw_U32 x) {
    // (x & -x) isolates the LSB
    // x + (x & -x) converts the contiguous 1-bits sequence to a single 1-bit higher up (or wraps to zero if x = 0 and no LSB)
    // x & (x + x & -x) clears only the contiguous 1-bits sequence so that if any other bit remains on, x is not compact.
    return (x & x + (x & -x)) == 0;  // wll defined in 0: returns 0.
}
// `sw_bitcompact64` returns true iff all the 1-bits in the value are contiguous.
SW_API inline sw_Bool sw_bitcompact64(sw_U64 x) {
    // (x & -x) isolates the LSB
    // x + (x & -x) converts the contiguous 1-bits sequence to a single 1-bit higher up (or wraps to zero if x = 0 and no LSB)
    // x & (x + x & -x) clears only the contiguous 1-bits sequence so that if any other bit remains on, x is not compact.
    return (x & x + (x & -x)) == 0;  // wll defined in 0: returns 0.
}
// `sw_bitflip32` flips target bits (from bitindex i to i + bitwidth w).
SW_API inline sw_U32 sw_bitflip32(sw_U32 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 32 && w <= (32 - i) && w < 32, "`bitflip32` overflow!");
    return (x ^ (SW_U32_LO(w) << i));
}
// `sw_bitflip64` flips target bits (from bitindex i to i + bitwidth w).
SW_API inline sw_U64 sw_bitflip64(sw_U64 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 64 && w <= (64 - i) && w < 64, "`bitflip64` overflow!");
    return (x ^ (SW_U64_LO(w) << i));
}
// `sw_bitfillz32` fills target bits (from bitindex i to i + bitwidth w) with zeros.
SW_API inline sw_U32 sw_bitfillz32(sw_U32 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 32 && w <= (32 - i) && w < 32, "`bitclear32` overflow!");
    return (x & ~(SW_U32_LO(w) << i));
}
// `sw_bitfillz64` fills target bits (from bitindex i to i + bitwidth w) with zeros.
SW_API inline sw_U64 sw_bitfillz64(sw_U64 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 64 && w <= (64 - i) && w < 64, "`bitclear64` overflow!");
    return (x & ~(SW_U64_LO(w) << i));
}
// `sw_bitfillo32` fills targets bits (from bitindex i to i + bitwidth w) with ones.
SW_API inline sw_U32 sw_bitfillo32(sw_U32 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 32 && w <= (32 - i) && w < 32, "`bitfill32` overflow!");
    return (x | (SW_U32_LO(w) << i));
}
// `sw_bitfillo64` fills targets bits (from bitindex i to i + bitwidth w) with ones.
SW_API inline sw_U64 sw_bitfillo64(sw_U64 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 64 && w <= (64 - i) && w < 64, "`bitfill64` overflow!");
    return (x | (SW_U64_LO(w) << i));
}
// `sw_bitread32` reads target bits (from bit index i to i + bitwidth w).
SW_API inline sw_U32 sw_bitread32(sw_U32 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 32 && w <= (32 - i) && w < 32, "`bitread32` overflow!");
    return (x >> i) & SW_U32_LO(w);
}
// `sw_bitread64` reads target bits (from bit index i to i + bitwidth w).
SW_API inline sw_U64 sw_bitread64(sw_U64 x, sw_Nat i, sw_Nat w) {
    sw_debug_assert(i < 64 && w <= (64 - i) && w < 64, "`bitread64` overflow!");
    return (x >> i) & SW_U64_LO(w);
}
// `sw_bitwrite32` writes target bits (from bit index i to i + bitwidth w) with value v.
SW_API inline sw_U32 sw_bitwrite32(sw_U32 x, sw_Nat i, sw_Nat w, sw_U32 v) {
    sw_debug_assert(i < 32 && w <= (32 - i) && w < 32 && v <= SW_U32_LO(w), "`bitwrite32` overflow!");
    return (x & ~(SW_U32_LO(w) << i)) | (v << i);
}
// `sw_bitwrite64` writes target bits (from bit index i to i + bitwidth w) with value v.
SW_API inline sw_U64 sw_bitwrite64(sw_U64 x, sw_Nat i, sw_Nat w, sw_U64 v) {
    sw_debug_assert(i < 64 && w <= (64 - i) && w < 64 && v <= SW_U64_LO(w), "`bitwrite64` overflow!");
    return (x & ~(SW_U64_LO(w) << i)) | (v << i);
}
// `sw_bitrotl32` rotates left by `i` bit-positions in a circular fashion (i.e. a left-shift where vacant bit-positions are filled-in with the ones shifted out of the sequence).
SW_API inline sw_U32 sw_bitrotl32(sw_U32 x, sw_U32 i) {
    sw_debug_assert(i > 0 && i < 32, "`bitrotl32` overflow!");
    // source: https://en.wikipedia.org/wiki/Circular_shift
    return x << i | x >> (32 - i);
}
// `sw_bitrotl64` rotates left by `i` bit-positions in a circular fashion (i.e. a left-shift where vacant bit-positions are filled-in with the ones shifted out of the sequence).
SW_API inline sw_U64 sw_bitrotl64(sw_U64 x, sw_U64 i) {
    sw_debug_assert(i > 0 && i < 64, "`bitrotl64` overflow!");
    // source: https://en.wikipedia.org/wiki/Circular_shift
    return x << i | x >> (64 - i);
}
// `sw_bitrotr32` rotates right by `i` bit-positions in a circular fashion (i.e. a right-shift where vacant bit-positions are filled-in with the ones shifted out of the sequence).
SW_API inline sw_U32 sw_bitrotr32(sw_U32 x, sw_U32 i) {
    sw_debug_assert(i > 0 && i < 32, "`bitrotr32` overflow!");
    // source: https://en.wikipedia.org/wiki/Circular_shift
    return x >> i | x << (32 - i);
}
// `sw_bitrotr64` rotates right by `i` bit-positions in a circular fashion (i.e. a right-shift where vacant bit-positions are filled-in with the ones shifted out of the sequence).
SW_API inline sw_U64 sw_bitrotr64(sw_U64 x, sw_U64 i) {
    sw_debug_assert(i > 0 && i < 64, "`bitrotr64` overflow!");
    // source: https://en.wikipedia.org/wiki/Circular_shift
    return x >> i | x << (64 - i);
}
// `sw_bitreverse8` returns the input with its bits reversed.
SW_API inline sw_U8 sw_bitreverse8(sw_U8 x) {
    x = ((x & 0x55u) << 1) | ((x & 0xAAu) >> 1);
    x = ((x & 0x33u) << 2) | ((x & 0xCCu) >> 2);
    x = ((x & 0x0Fu) << 4) | ((x & 0xF0u) >> 4);
    return x;
}
// `sw_bitreverse16` returns the input with its bits reversed.
SW_API inline sw_U16 sw_bitreverse16(sw_U16 x) {
    x = ((x & 0x5555u) << 1) | ((x & 0xAAAAu) >> 1);
    x = ((x & 0x3333u) << 2) | ((x & 0xCCCCu) >> 2);
    x = ((x & 0x0F0Fu) << 4) | ((x & 0xF0F0u) >> 4);
    x = ((x & 0x00FFu) << 8) | ((x & 0xFF00u) >> 8);
    return x;
}
// `sw_bitreverse32` returns the input with its bits reversed.
SW_API inline sw_U32 sw_bitreverse32(sw_U32 x) {
    x = ((x & 0x55555555u) <<  1) | ((x & 0xAAAAAAAAu) >>  1);
    x = ((x & 0x33333333u) <<  2) | ((x & 0xCCCCCCCCu) >>  2);
    x = ((x & 0x0F0F0F0Fu) <<  4) | ((x & 0xF0F0F0F0u) >>  4);
    x = ((x & 0x00FF00FFu) <<  8) | ((x & 0xFF00FF00u) >>  8);
    x = ((x & 0x0000FFFFu) << 16) | ((x & 0xFFFF0000u) >> 16);
    return x;
}
// `sw_bitreverse64` returns the input with its bits reversed.
SW_API inline sw_U64 sw_bitreverse64(sw_U64 x) {
    x = ((x & 0x5555555555555555llu) <<  1) | ((x & 0xAAAAAAAAAAAAAAAAllu) >>  1);
    x = ((x & 0x3333333333333333llu) <<  2) | ((x & 0xCCCCCCCCCCCCCCCCllu) >>  2);
    x = ((x & 0x0F0F0F0F0F0F0F0Fllu) <<  4) | ((x & 0xF0F0F0F0F0F0F0F0llu) >>  4);
    x = ((x & 0x00FF00FF00FF00FFllu) <<  8) | ((x & 0xFF00FF00FF00FF00llu) >>  8);
    x = ((x & 0x0000FFFF0000FFFFllu) << 16) | ((x & 0xFFFF0000FFFF0000llu) >> 16);
    x = ((x & 0x00000000FFFFFFFFllu) << 32) | ((x & 0xFFFFFFFF00000000llu) >> 32);
    return x;
}
// `sw_bswap16` returns the input with its bytes reversed (e.g. 0xAABB becomes 0xBBAA).
SW_API inline sw_U16 sw_bswap16(sw_U16 x) {
#if SW_NO_BUILTIN
    return (x << 8) | (x >> 8);
#else
    return __builtin_bswap16(x);
#endif
}
// `sw_bswap32` returns the input with its bytes reversed (e.g. 0xAABBCCDD becomes 0xDDCCBBAA).
SW_API inline sw_U32 sw_bswap32(sw_U32 x) {
#if SW_NO_BUILTIN
    return (
        (x << 24) |
        ((x & 0x0000FF00) << 8) |
        ((x & 0x00FF0000) >> 8) |
        (x >> 24)
    );
#else
    return __builtin_bswap32(x);
#endif
}
// `sw_bswap64` returns the input with its bytes reversed (e.g. 0xAABBCCDDEEFFGGHH becomes 0xHHGGFFEEDDCCBBAA).
SW_API inline sw_U64 sw_bswap64(sw_U64 x) {
#if SW_NO_BUILTIN
    return (
        (x << 56) |
        ((x & 0x000000000000FF00llu) << 40) |
        ((x & 0x0000000000FF0000llu) << 24) |
        ((x & 0x00000000FF000000llu) <<  8) |
        ((x & 0x000000FF00000000llu) >>  8) |
        ((x & 0x0000FF0000000000llu) >> 24) |
        ((x & 0x00FF000000000000llu) >> 40) |
        (x >> 56)
    );
#else
    return __builtin_bswap64(x);
#endif
}


// memory ops

// TODO: some string.h (memcpy, memset, strchr, etc.) + memory_find and similar 

// `sw_memcopy8` copies first `n` bytes from `src` to `dst`(undefined if the two regions overlap).
SW_API inline sw_Void* sw_memcopy8(sw_Void* restrict dst, const sw_Void* restrict src, sw_Nat n) {
#if SW_NO_BUILTIN
    sw_U8* dst_bytes = (sw_U8*)dst;
    sw_U8* src_bytes = (sw_U8*)src;
    for (sw_Nat i = 0; i < n; ++i) {
        dst[i] = src[i];
    }
    return dst_bytes;
#else
    return __builtin_memcpy(dst, src, n);
#endif
}
/// `sw_memmove` moves first `n` bytes from `src` to `dst`(which may overlap).
SW_API inline sw_Void* sw_memmove8(sw_Void* dst, const sw_Void* src, sw_Nat n) {
#if SW_NO_BUILTIN
    sw_U8* dst_bytes = dst;
    sw_U8* src_bytes = src;
    if ((sw_Nat)src < (sw_Nat)dst) {
        for (sw_Nat i = n - 1; i >= 0; --i) {
            dst_bytes[i] = src_bytes[i];
        }
    } else if ((sw_Nat)src > (sw_Nat)dst) {
        for (sw_Nat i = 0; i < n; ++i) {
            dst_bytes[i] = src_bytes[i];
        }
    }
    return dst_bytes;
#else
    return __builtin_memmove(dst, src, n);
#endif
}
// `sw_memfill8` fills first `n` bytes of `dst` with byte value `v`.
SW_API inline sw_Void* sw_memfill8(sw_Void* dst, sw_U8 v, sw_Nat n) {
#if SW_NO_BUILTIN
    sw_U8* dst_bytes = (sw_U8*)dst;
    for (sw_Nat i = 0; i < n; ++i) {
        dst_bytes[i] = v;
    }
    return dst_bytes;
#else
    return __builtin_memset(dst, v, n);
#endif
}
// `sw_memfind8` returns a pointer to the first occurrence of byte value `v` or NULL if not found.
SW_API inline sw_Void* sw_memfind8(const sw_Void* bb, sw_U8 v, sw_Nat n) {
#ifdef SW_NO_BUILTIN
    sw_U8* bytes = (sw_U8*)bb;
    for (sw_Nat i = 0; i < n; ++i) {
        if (bytes[i] == v) {
            return (bytes + i);
        }
    }
    return SW_NULL;
#else
    return __builtin_memchr(bb, v, n);
#endif
}
// `sw_memcomp8` compares first `n` bytes of `bb1` and `bb2` returning 0 if the bytes are equal and a negative (positive) value if the first different byte in `bb1` is lower (greater) than the corresponding one in `bb2`.
SW_API inline sw_Int sw_memcomp8(const sw_Void* bb1, const sw_Void* bb2, sw_Nat n) {
#ifdef SW_NO_BUILTIN
    sw_U8* bytes1 = (sw_U8*)bb1;
    sw_U8* bytes2 = (sw_U8*)bb2;
    for (sw_Nat i = 0; i < n; ++i) {
        if (bytes1[i] != bytes2[i]) {
            return (bytes1[i] - bytes2[i]);
        }
    }
    return 0;
#else
    return __builtin_memcmp(bb1, bb2, n);
#endif
}

#endif  // SW_COMMON_INCL
