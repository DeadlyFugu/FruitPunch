#pragma once
#include "Closure.h"

closure_t parse(int len, char* src);
closure_t parseClosure(char* start, char* end, char** master_c);
