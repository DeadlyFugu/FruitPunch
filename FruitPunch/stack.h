#pragma once
#include <vector>
#include "object.h"

class Stack {
private:
	std::vector<obj_t> stack;
public:
	void push(obj_t v) {
		stack.push_back(v);
	}
	obj_t pop() {
		auto v = stack.back();
		stack.pop_back();
		return v;
	}
	void print_debug();
};