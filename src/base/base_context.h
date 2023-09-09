#ifndef BASE_CONTEXT_H
#define BASE_CONTEXT_H

// NOTE(calco): Build mode
// TODO(calco): Actualyl get this info from cmake.
#define BASE_BUILD_DEBUG 1
// #ifdef CMAKE_DEBUG
// #  define BASE_BUILD_DEBUG   1
// #  define BASE_BUILD_RELEASE 0
// #elif CMAKE_RELEASE
// #  define BASE_BUILD_DEBUG   0
// #  define BASE_BUILD_RELEASE 1
// #endif

// NOTE(calco): Data
// NOTE(calco): -- Compilers --
#ifdef _MSC_VER
#  define BASE_COMPILER_MSVC 1
#elif __clang__
#  define BASE_COMPILER_CLANG 1
#elif __GNUC__
#  define BASE_COMPILER_GCC 1
#else
#  error Cannot detect compiler.
#endif

// NOTE(calco): -- Operating Systems --
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

// NOTE(calco): -- Files --
#ifdef COMPILER_CLANG
#  define FILE_NAME __FILE_NAME__
#else
#  define FILE_NAME __FILE__
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