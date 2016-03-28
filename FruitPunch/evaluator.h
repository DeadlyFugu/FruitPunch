#pragma once
#include "Closure.h"
#include "context.h"
#include "stack.h"

void evaluate(closure_t closure, context_t root, Stack* stack);
