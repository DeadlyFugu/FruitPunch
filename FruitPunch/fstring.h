#pragma once
#include "object.h"


class String : public Object {
private:
	char* value;
public:
	String(char* value) : value(value) {}
	virtual const char* get_debug_string() {
		int len = strlen(value) + 3;
		static char* buf = new char[len];
		sprintf_s(buf, len, "\"%s\"", value);
		return buf;
	}
	virtual const char* get_debug_type() {
		return "String";
	}
};

typedef std::shared_ptr<String> fstring_t;

inline fstring_t new_string(char* v) {
	return std::make_shared<String>(v);
}