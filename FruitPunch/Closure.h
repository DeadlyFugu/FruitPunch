#pragma once
#include <vector>
#include <memory>
#include "object.h"

struct Closure : public Object {
	std::vector<std::shared_ptr<Closure>> subs;
	int len;
	uint8_t* bytecode;

	~Closure() {
		if (bytecode)
			delete[] bytecode;
	}

	virtual const char* get_debug_string() {
		return "{}";
	}
	virtual const char* get_debug_type() {
		return "Closure";
	}
};

typedef std::shared_ptr<Closure> closure_t;
inline closure_t new_closure() {
	return std::make_shared<Closure>();
}