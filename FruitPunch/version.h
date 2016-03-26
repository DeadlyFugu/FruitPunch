#pragma once

// determine compiler
#if defined(__clang__)
#define COMPILER_NAME "Clang/LLVM"
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#define COMPILER_NAME "Intel ICC/ICPC"
#elif defined(__GNUC__) || defined(__GNUG__)
#define COMPILER_NAME "GNU GCC/G++"
#elif defined(__HP_cc) || defined(__HP_aCC)
#define COMPILER_NAME "HP C/aC++"
#elif defined(__IBMC__) || defined(__IBMCPP__)
#define COMPILER_NAME "IBM XL C/C++"
#elif defined(_MSC_VER)
#define COMPILER_NAME "MSVC++"
#elif defined(__PGI)
#define COMPILER_NAME "PGCC/PGCPP"
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define COMPILER_NAME "Oracle Solaris Studio"
#else
#define COMPILER_NAME "Unknown C/C++"
#endif

// version string
#define FP_VERSION "0.0"

// does this really need to be a #define?
#define APP_NAME "FruitPunch"