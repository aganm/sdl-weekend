#pragma once

/**
 * @file
 * @brief Various utility macros related to compiler warnings.
 */

#ifdef __cplusplus
extern "C" {
#define _Static_assert static_assert
#endif

/**
 * @brief Disable/enable warnings for gcc,clang,msvc.
 * @see
 * https://stackoverflow.com/questions/3378560/how-to-disable-gcc-warnings-for-a-few-lines-of-code
 * https://stackoverflow.com/a/36175016/6784916
 *
 * Example:
 *   DISABLE_WARNING(unused-variable,unused-variable,42)
 *   [.... some code with warnings in here ....]
 *   ENABLE_WARNING(unused-variable,unused-variable,42)
 *
 */

#define DIAG_STR(s) #s
#define DIAG_JOINSTR(x,y) DIAG_STR(x ## y)
#ifdef _MSC_VER
#define DIAG_DO_PRAGMA(x) __pragma (x)
#define DIAG_PRAGMA(compiler,x) DIAG_DO_PRAGMA(warning(x))
#else
#define DIAG_DO_PRAGMA(x) _Pragma (#x)
#define DIAG_PRAGMA(compiler,x) DIAG_DO_PRAGMA(compiler diagnostic x)
#endif

#if defined(__clang__)
# define DIAG_PUSH(gcc_unused,clang_option,msvc_unused) DIAG_PRAGMA(clang,push) DIAG_PRAGMA(clang,warning DIAG_JOINSTR(-W,clang_option))
# define DIAG_PUSH_IGNORE(gcc_unused,clang_option,msvc_unused) DIAG_PRAGMA(clang,push) DIAG_PRAGMA(clang,ignored DIAG_JOINSTR(-W,clang_option))
# define DIAG_POP(gcc_unused,clang_option,msvc_unused) DIAG_PRAGMA(clang,pop)
#elif defined(_MSC_VER)
# define DIAG_PUSH(gcc_unused,clang_unused,msvc_errorcode) DIAG_PRAGMA(msvc,push) DIAG_DO_PRAGMA(warning(1:##msvc_errorcode))
# define DIAG_PUSH_IGNORE(gcc_unused,clang_unused,msvc_errorcode) DIAG_PRAGMA(msvc,push) DIAG_DO_PRAGMA(warning(disable:##msvc_errorcode))
# define DIAG_POP(gcc_unused,clang_unused,msvc_errorcode) DIAG_PRAGMA(msvc,pop)
#elif defined(__GNUC__)
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
# define DIAG_PUSH(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,push) DIAG_PRAGMA(GCC,warning DIAG_JOINSTR(-W,gcc_option))
# define DIAG_PUSH_IGNORE(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,push) DIAG_PRAGMA(GCC,ignored DIAG_JOINSTR(-W,gcc_option))
# define DIAG_POP(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,pop)
#else
# define DIAG_PUSH_IGNORE(gcc_option,clang_unused,msvc_unused) DIAG_PRAGMA(GCC,ignored DIAG_JOINSTR(-W,gcc_option))
# define DIAG_POP(gcc_option,clang_option,msvc_unused) DIAG_PRAGMA(GCC,warning DIAG_JOINSTR(-W,gcc_option))
#endif
#endif

#define DISABLE_UNUSED_PARAMETER DIAG_PUSH_IGNORE(unused-parameter,unused-parameter,4100)
#define ENABLE_UNUSED_PARAMETER DIAG_POP(unused-parameter,unused-parameter,4100)

#define DISABLE_RETURN_TYPE DIAG_PUSH_IGNORE(return-type,return-type,4716)
#define ENABLE_RETURN_TYPE DIAG_POP(return-type,return-type,4716)

#define ENABLE_PADDED DIAG_PUSH(padded,padded,4324)
#define DISABLE_PADDED DIAG_POP(padded,padded,4324)

/**
 * @brief NODISCARD macro to simulate c2x [[nodiscard]] attribute.
 * When put in front of a function, the compiler will warn about the return
 * value not being used.
 */

#if defined(__clang__)
#define NODISCARD __attribute__((warn_unused_result))
#elif defined(__GNUC__)
#define NODISCARD __attribute__((warn_unused_result))
#elif defined(_MSC_VER)
#define NODISCARD _Check_return_
#endif

/**
 * @brief PAD macro is to fix the warnings thrown by the compiler when -Wpadded
 * is on. -Wpadded throws warnings whenever hidden padding is found in a struct,
 * this fixes garbage to be found in struct's padding and with this practice,
 * struct initialization and struct assignment is always fully zero initialized.
 */

_Static_assert(sizeof(char) == 1, "PAD macro relies on char type being size 1");
#define PAD_PASTE2(x, y) x##y
#define PAD_PASTE(x, y) PAD_PASTE2(x, y)
#define PAD(size) char PAD_PASTE(_padding, __LINE__)[size]

#ifdef __cplusplus
#undef _Static_assert
}
#endif
