#pragma once
#include <vector>
#include <memory>

struct Closure {
	std::vector<std::shared_ptr<Closure>> subs;
	int len;
	char* bytecode;

	~Closure() {
		if (bytecode)
			delete[] bytecode;
	}
};