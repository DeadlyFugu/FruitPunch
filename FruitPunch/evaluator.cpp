#include "evaluator.h"
#include "numeric_types.h"

void evaluate(Closure* closure, context_t root, Stack* stack) {
	uint8_t* pc = closure->bytecode;
	uint8_t* end = closure->bytecode + closure->len;

#define PUSH(obj) stack->push(obj)
	
	while (pc < end) {
		switch (*pc++) {
		case 0x02:
		{
			PUSH(new_int32(*reinterpret_cast<uint32_t*>(pc)));
			pc += 4;
		}
		}
	}
}