#ifndef BASE_CONTEXT_H
#define BASE_CONTEXT_H

// NOTE(calco): Actual Data (aka a mess)
#ifdef _MSC_VER
#  define BASE_COMPILER_MSVC 1
#elif __clang__
#  define BASE_COMPILER_CLANG 1
#elif __GNUC__
#  define BASE_COMPILER_GCC 1
#else
#  error Cannot detect compiler.
#endif

#ifdef _WIN32
#  define BASE_OS_WIN 1
#elif macintosh
#  define BASE_OS_MAC 1
#elif Macintosh
#  define BASE_OS_MAC 1
#elif __APPLE__
#  define BASE_OS_MAC 1
#elif __linux__
#  define BASE_OS_LINUX 1
#endif

// NOTE(calco): Defaults
// NOTE(calco): -- Compilers --
#ifndef BASE_COMPILER_GCC
#  define BASE_COMPILER_GCC 0
#endif
#ifndef BASE_COMPILER_MSVC
#  define BASE_COMPILER_MSVC 0
#endif
#ifndef BASE_COMPILER_CLANG
#  define BASE_COMPILER_CLANG 0
#endif

// NOTE(calco): -- Operating Systems --
#ifndef BASE_OS_WIN
#  define BASE_OS_WIN 0
#endif
#ifndef BASE_OS_LINUX
#  define BASE_OS_LINUX 0
#endif
#ifndef BASE_OS_MAC
#  define BASE_OS_MAC 0
#endif

#endif