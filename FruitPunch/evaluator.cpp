#include "evaluator.h"
#include "numeric_types.h"
#include "fstring.h"

void evaluate(closure_t closure, context_t root, Stack* stack) {
	uint8_t* pc = closure->bytecode;
	uint8_t* end = closure->bytecode + closure->len;

	context_t locals = new_context();

#define PUSH(obj) stack->push(obj)
#define READ_PC_AS(type) *reinterpret_cast<type*>(pc)
#define POP() stack->pop()
	
	while (pc < end) {
		switch (*pc++) {
		case 0x01:
		{
			PUSH(closure->subs[READ_PC_AS(uint8_t)]);
			pc++;
		} break;
		case 0x02:
		{
			PUSH(new_int32(READ_PC_AS(uint32_t)));
			pc += 4;
		} break;
		case 0x04:
		{
			PUSH(new_float32(READ_PC_AS(float)));
			pc += 4;
		} break;
		case 0x0B:
		{
			PUSH(new_string((char*) pc));
			pc += strlen((char*) pc);
		} break;
		case 0x10:
		{
			// TODO callv
		} break;
		case 0x11:
		{
			// GETV
			symbol_t sym = READ_PC_AS(symbol_t);
			PUSH(locals->getv(sym));
		} break;
		case 0x12:
		{
			// SETV
			symbol_t sym = READ_PC_AS(symbol_t);
			obj_t value = POP();
			locals->setv(sym, value);
		} break;
		case 0x13:
		{
			// BINDV
			symbol_t sym = READ_PC_AS(symbol_t);
			obj_t value = POP();
			locals->bindv(sym, value);
		} break;
		}
	}
}