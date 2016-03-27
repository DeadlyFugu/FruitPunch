#pragma once
#include "object.h"

class Int32 : public Object {
private:
	uint32_t value;
public:
	Int32(uint32_t value) : value(value) {}
	virtual const char* get_debug_string() {
		static char buf[16];
		sprintf_s(buf, "%i", value);
		return buf;
	}
	virtual const char* get_debug_type() {
		return "Int32";
	}
};

typedef std::shared_ptr<Int32> fint32_t;

inline fint32_t new_int32(uint32_t v) {
	return std::make_shared<Int32>(v);
}

class Float32 : public Object {
private:
	float value;
public:
	Float32(float value) : value(value) {}
	virtual const char* get_debug_string() {
		static char buf[32];
		sprintf_s(buf, "%f", value);
		return buf;
	}
	virtual const char* get_debug_type() {
		return "Float32";
	}
};

typedef std::shared_ptr<Float32> ffloat32_t;

inline ffloat32_t new_float32(float v) {
	return std::make_shared<Float32>(v);
}
