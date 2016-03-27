#include "context.h"

obj_t Context::getv(symbol_t key) {
	auto it = values.find(key);
	if (it != values.end()) {
		return it->second;
	} else {
		// TODO exception
	}
}

bool Context::hasv(symbol_t key) {
	auto it = values.find(key);
	return it != values.end();
}

void Context::setv(symbol_t key, obj_t value) {
	auto it = values.find(key);
	if (it != values.end()) {
		it->second = value;
	} else {
		// TODO exception
	}
}

void Context::bindv(symbol_t key, obj_t value) {
	values[key] = value;
}