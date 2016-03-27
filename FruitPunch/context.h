#pragma once
#include "object.h"
#include "symbols.h"
#include <map>

class Context : public Object {
private:
	std::map<symbol_t, obj_t> values;
public:
	obj_t getv(char* key) {
		return this->getv(symbol(key));
	}
	obj_t getv(symbol_t key);

	bool hasv(char* key) {
		return this->hasv(symbol(key));
	}
	bool hasv(symbol_t key);

	void setv(char* key, obj_t value) {
		return this->setv(symbol(key), value);
	}
	void setv(symbol_t key, obj_t value);

	void bindv(char* key, obj_t value) {
		return this->bindv(symbol(key), value);
	}
	void bindv(symbol_t key, obj_t value);

	virtual const char* get_debug_string() {
		return ":{}";
	}
	virtual const char* get_debug_type() {
		return "Context";
	}
};

typedef std::shared_ptr<Context> context_t;

inline context_t new_context() {
	return std::make_shared<Context>();
}