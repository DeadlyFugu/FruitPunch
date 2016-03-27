#pragma once
#include <cstdint>

typedef uint16_t symbol_t;

symbol_t symbol(char* name);
const char* symbol_name(symbol_t sym);
