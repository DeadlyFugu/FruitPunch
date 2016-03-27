#pragma once
#include "Closure.h"
#include "context.h"
#include "stack.h"

void evaluate(Closure* closure, context_t root, Stack* stack);
