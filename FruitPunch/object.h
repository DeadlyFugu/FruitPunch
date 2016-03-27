#pragma once
#include <memory>

class Object {
public:
	virtual const char* get_debug_string() = 0;
	virtual const char* get_debug_type() = 0;
};

typedef std::shared_ptr<Object> obj_t;